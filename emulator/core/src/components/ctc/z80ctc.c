#include "components/ctc/z80ctc.h"

static void            z80ctc_init_channel(t_z80ctc_channel *chan)
{
    chan->control_reg.data = 0;
    chan->timer_reg = 0;
    chan->is_init = 1;
    chan->prescaler_cycle_counter = 0;
    chan->raise_interrupt = 0;
}

void            z80ctc_init(t_z80ctc *self)
{
    z80ctc_init_channel(&(self->channel[0]));
    z80ctc_init_channel(&(self->channel[1]));
    z80ctc_init_channel(&(self->channel[2]));
    z80ctc_init_channel(&(self->channel[3]));
    self->interrupt_request = 0;
}

static void     z80ctc_update_channel(t_z80ctc_channel *chan, unsigned int system_clock_tstates)
{
    if ((chan->control_reg.soft_reset == 0) && chan->is_init)                 // Stop operating on reset
    {
        if (chan->control_reg.channel_mode == 0)                // Timer mode : The reference clock period is multiplied by the prescaler, then the counter decreases. When it reaches 0, interrupt and refill.
        {
            chan->prescaler_cycle_counter += system_clock_tstates;
            if (chan->prescaler_cycle_counter >= ((chan->control_reg.prescaler_value) ? 256 : 16))         // > or >= ? not sure here
            {
                chan->prescaler_cycle_counter -= ((chan->control_reg.prescaler_value) ? 256 : 16);
                if (--chan->counter == 0)
                {
                    chan->counter = chan->timer_reg;            // Reload counter
                    if (chan->control_reg.interrupt_enable)
                        chan->raise_interrupt = 1;
                }
            }
        }
        else
        {
            // Not implemented (yet)
        }
    }
    else if (chan->is_init)
    {
        chan->prescaler_cycle_counter = 0;
        chan->control_reg.soft_reset = 0;                   // Not sure the soft reset flag is actually set back to 0 when the chan is init...
        chan->is_init = 0;
    }
}

void            z80ctc_update(t_z80ctc *self, unsigned int system_clock_tstates)
{
    int         i;

    for (i = 0; i < 4; ++i)
    {
        z80ctc_update_channel(&(self->channel[i]), system_clock_tstates);
        if (self->channel[i].raise_interrupt && !self->interrupt_request)       // If it's possible to raise an int
        {
            self->interrupt_request = 1;
            self->interrupt_channel_vector = self->channel[0].vector_reg | (i << 1);
            self->channel[i].raise_interrupt = 0;
        }
    }
}


static byte     z80ctc_channel_read(t_z80ctc_channel *self)
{
    return (self->counter);
}

byte            z80ctc_read(t_z80ctc *self, byte cs)
{
    return (z80ctc_channel_read(&(self->channel[cs])));
}

static void     z80ctc_channel_write(t_z80ctc_channel *self, byte data)
{
    if (self->control_reg.time_constant_follows)
    {
        self->timer_reg = data;
        self->counter = data;
        self->control_reg.time_constant_follows = 0;
        self->is_init = 1;
    }
    else if (data & Z80CTC_DATA_IS_CONTROL_WORD)
        self->control_reg.data = data;
    else
        self->vector_reg = data & 0xF8;                             // The user provided part of the interrupt vector is only the first 5 MSB
}

void            z80ctc_write(t_z80ctc *self, byte cs, byte data)
{
    z80ctc_channel_write(&(self->channel[cs]), data);
}


void            z80ctc_ack_interrupt_req(t_z80ctc *self)
{
    self->interrupt_request = 0;
}
