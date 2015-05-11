#ifndef AY_3_8912_H
#define AY_3_8912_H
/*
 * From the PHP version of the Amstrad CPC's AY-3-8912 emulator, written by grim :
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE" (Revision 42):
* <grim@cpcscene.com> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return.
* ----------------------------------------------------------------------------
*
*/

#include "defines.h"

/* todo : Sound generating blocks :
    - Tone generators
    - Noise generator
    - Amplitude control
    - Envelope generator
    - D/A converter + Mixers
*/

typedef struct      s_ay_3_8912
{
    byte            reg[18];
    byte            selected_reg;

    uint16          analog_out[3];

    byte            noise_level;
    byte            envel_level;
    byte            tone_level[3];

    uint16          noise_period;
    uint16          envel_period;
    uint16          tone_period[3];

    byte            clock_div_8;
    byte            envel_pos;
    uint32          noise_seed;

    float           elapsed_t_states;                       // As the CPU is running at 3.6864, I need a float here (1 AY T-state each 3.6864 CPU t_state)
}                   t_ay_3_8912;



    void            ay_3_8912_init(t_ay_3_8912   *self);
    void            ay_3_8912_write(t_ay_3_8912  *self, byte data);
    void            ay_3_8912_latch_address(t_ay_3_8912  *self, byte data);
    byte            ay_3_8912_read(t_ay_3_8912   *self);
    void            ay_3_8912_update(t_ay_3_8912 *self, unsigned int system_clock_tstastes);

    void            ay_3_8912_sample_stereo(t_ay_3_8912 *self, uint16 *left, uint16 *right);                                        // Sample the AY mixer output at a given time


    // chip-related defines
# define        AY_FACTORY_MASK                         0x00
# define        AY_CLK_SPEED                            (2.0f*MHZ)
# define        AY_CLK_SYSTEM_CLK_RATIO                 (CPU_SPEED/AY_CLK_SPEED)           // 3.6863/1Mhz

    // Registers
# define        AY_CHAN_A_TONE_PERIOD_FINE_TUNE         0
# define        AY_CHAN_A_TONE_PERIOD_COARSE_TUNE       1
# define        AY_CHAN_B_TONE_PERIOD_FINE_TUNE         2
# define        AY_CHAN_B_TONE_PERIOD_COARSE_TUNE       3
# define        AY_CHAN_C_TONE_PERIOD_FINE_TUNE         4
# define        AY_CHAN_C_TONE_PERIOD_COARSE_TUNE       5
# define        AY_NOISE_PERIOD                         6
# define        AY_ENABLE_REG                           7    // There is a gap between reg 7 and 10 in the doc but it seems wrong ?
# define        AY_CHAN_A_AMPLITUDE                     8
# define        AY_CHAN_B_AMPLITUDE                     9
# define        AY_CHAN_C_AMPLITUDE                     10
# define        AY_ENVELOPE_PERIOD_FINE_TUNE            11
# define        AY_ENVELOPE_PERIOD_COARSE_TUNE          12
# define        AY_ENVELOPE_SHAPE_CYCLE                 13
# define        AY_PORT_A_DATA                          14
# define        AY_PORT_B_DATA                          15

#endif
