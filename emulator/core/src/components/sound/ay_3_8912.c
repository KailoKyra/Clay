#include "components/sound/ay_3_8912.h"
#include <string.h>

void            ay_3_8912_init(t_ay_3_8912 *self)
{
    memset(self, 0, sizeof(t_ay_3_8912));
    self->elapsed_t_states = 0.f;
    self->clock_div_8 = 0x07;
    self->envel_period = 0x000001;
    self->noise_seed = 0x024000;
}


void            ay_3_8912_write(t_ay_3_8912 *self, byte data)
{
    static const byte       regMask[] = { 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0x1F, 0xFF, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0x0F, 0xFF, 0xFF, 0x00};

    self->reg[self->selected_reg] = data & regMask[self->selected_reg];
    if (self->reg[AY_ENVELOPE_SHAPE_CYCLE])                                     // Reset the enveloppe position when the env. shape register is written
        self->envel_pos = 0;
}


byte            ay_3_8912_read(t_ay_3_8912 *self)
{
    return (self->reg[self->selected_reg]);
}


void            ay_3_8912_update(t_ay_3_8912 *self, unsigned int system_clock_tstastes)
{
    /* End of Shape codes used:      0x8x : Cycling shape       0x4x : Hold on the value */
    static const byte env_shapes[16][32] = {
        // 00xx
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x40},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x40},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x40},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x40},
        // 01xx
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0x40},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0x40},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0x40},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0x40},
        // 1nnn
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x80},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x40},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14, 0x8F},
        {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0, 0x4F},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14, 0x8F},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14, 0x4F},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, 0x80},
        {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0x40}
    };

    self->elapsed_t_states += system_clock_tstastes;
    while (self->elapsed_t_states >= AY_CLK_SYSTEM_CLK_RATIO)
    {
        self->elapsed_t_states -= AY_CLK_SYSTEM_CLK_RATIO;

        // The enveloppe generator is updated every 16 clock cycles
        if (--self->envel_period == 0)
        {
            self->envel_level = env_shapes[self->reg[AY_ENVELOPE_SHAPE_CYCLE]][self->envel_pos] & 0x0F;
            if ((env_shapes[self->reg[AY_ENVELOPE_SHAPE_CYCLE]][self->envel_pos] & 0xC0) > 0)
            {
                if ((env_shapes[self->reg[AY_ENVELOPE_SHAPE_CYCLE]][self->envel_pos] & 0x80) > 0)
                    self->envel_pos = 0;
            }
            else
                ++self->envel_pos;
            self->envel_period = (1 + self->reg[AY_ENVELOPE_PERIOD_FINE_TUNE] + (256 * self->reg[AY_ENVELOPE_PERIOD_COARSE_TUNE])) * 16;
        }

        // The noise & tone generators are updated every 8 clock cycles.
        // Also their minimum period is 1 (a period of 0 will produce the same output as a period of 1).
        self->clock_div_8 = (self->clock_div_8 + 1) & 0x07;
        if (self->clock_div_8 == 0)
        {
            ++self->noise_period;
            if (self->noise_period >= self->reg[AY_NOISE_PERIOD])
            {
                // LFSR as described in the AY3-8930 (in 8910 compatibility mode) datasheet (and verified on the real thing)
                self->noise_seed       = ((((self->noise_seed & 4) ? 1 : 0) ^ ((self->noise_seed & 1) ? 1 : 0)) ? 0x10000 : 0) + (self->noise_seed >> 1);
                self->noise_level     ^= (self->noise_seed & 2) ? 0x00 : 0xFF;
                self->noise_period     = 0;
            }
            // TONE A
            ++self->tone_period[0];
            if (self->tone_period[0] >= (self->reg[AY_CHAN_A_TONE_PERIOD_FINE_TUNE] + (256 * self->reg[AY_CHAN_A_TONE_PERIOD_COARSE_TUNE])))
            {
                self->tone_level[0] ^= 0xFF;
                self->tone_period[0] = 0;
            }
            // TONE B
            ++self->tone_period[1];
            if (self->tone_period[1] >= (self->reg[AY_CHAN_B_TONE_PERIOD_FINE_TUNE] + (256 * self->reg[AY_CHAN_B_TONE_PERIOD_COARSE_TUNE])))
            {
                self->tone_level[1] ^= 0xFF;
                self->tone_period[1] = 0;
            }
            // TONE C
            ++self->tone_period[2];
            if (self->tone_period[2] >= (self->reg[AY_CHAN_C_TONE_PERIOD_FINE_TUNE] + (256 * self->reg[AY_CHAN_C_TONE_PERIOD_COARSE_TUNE])))
            {
                self->tone_level[2] ^= 0xFF;
                self->tone_period[2] = 0;
            }
        }
    }
}


void            ay_3_8912_latch_address(t_ay_3_8912 *self, byte data)
{
    if ((data & AY_FACTORY_MASK) == AY_FACTORY_MASK)
        if (data <= 15)
            self->selected_reg = data;
}


void        ay_3_8912_sample_stereo(t_ay_3_8912 *self, uint16 *left, uint16 *right)
{
    /*  Audio DAC lookup tables
        The measured levels of the 4-bits DAC output as UINT16 are:
        MEASURE = [0,231,695,1158,2084,2779,4168,6716,8105,13200,18294,24315,32189,40757,52799,65535]

        The following lookup tables are based on the measured values and calculated like this:
        SOUND_INT16 = (MEASURE/2) * 0.333;
        JACKS_INT16 = (MEASURE/2) * 0.687 * 0.97;
        JACKC_INT16 = (MEASURE/2) * 0.313 * 0.97;

        On the stereo mixer outputs, the two channels slightly (~3%) leak on each other.
        So we keep only 97% of the levels in the LUTs to be able to add the leak.
    */
    //static const uint16 SOUND_INT16[] = {0,38,115,192,346,462,693,1118,1349,2197,3045,4048,5359,6786,8791,10911};
    static const uint16 JACKS_INT16[] = {0,76,229,381,687,916,1374,2214,2672,4352,6032,8018,10614,13440,17410,21610};
    static const uint16 JACKC_INT16[] = {0,34,104,173,313,417,626,1009,1217,1983,2748,3653,4836,6123,7932,9845};

    /*** CHANNEL A ******************************************************/

    // Select amplitude (fixed-4bit or enveloppe)
    self->analog_out[0] = (self->reg[AY_CHAN_A_AMPLITUDE] & 0x10) ? self->envel_level : self->reg[AY_CHAN_A_AMPLITUDE];
    if (!(self->reg[AY_ENABLE_REG] & 0x08))                          // If enabled, apply noise modulation
        self->analog_out[0] &= self->noise_level;
    if (!(self->reg[AY_ENABLE_REG] & 0x01))                          // If enabled, apply tone modulation
        self->analog_out[0] &= self->tone_level[0];

    // ** CHANNEL B ******************************************************
    self->analog_out[1] = (self->reg[AY_CHAN_B_AMPLITUDE] & 0x10) ? self->envel_level : self->reg[AY_CHAN_B_AMPLITUDE];
    if (!(self->reg[AY_ENABLE_REG] & 0x10))
        self->analog_out[1] &= self->noise_level;
    if (!(self->reg[AY_ENABLE_REG] & 0x02))
        self->analog_out[1] &= self->tone_level[1];

    //** CHANNEL C ******************************************************
    self->analog_out[2] = (self->reg[AY_CHAN_C_AMPLITUDE] & 0x10) ? self->envel_level : self->reg[AY_CHAN_C_AMPLITUDE];
    if (!(self->reg[AY_ENABLE_REG] & 0x20))
        self->analog_out[2] &= self->noise_level;
    if (!(self->reg[AY_ENABLE_REG] & 0x04))
        self->analog_out[2] &= self->tone_level[2];


    /*** Digital to Analog Convertion ************************************
    Instead of calculating the analog outputs of the 3 AY3 DACs and then
    the sound mixer outputs (jack/stereo & speaker/mono), we compute
    directly the output of the mixers.
    */

    *left           =  JACKS_INT16[self->analog_out[0]] + JACKC_INT16[self->analog_out[1]];

    *right          =  JACKS_INT16[self->analog_out[2]] + JACKC_INT16[self->analog_out[1]];

    // 3% leaks
    uint16 leak_right     = *left * 0.03;
    *left   += *right * 0.03;
    *right  += leak_right;

    /* uint16 mono =   SOUND_INT16[self->analog_out[0]]       // ??
            +       SOUND_INT16[self->analog_out[1]]
            +       SOUND_INT16[self->analog_out[2]];*/
}
