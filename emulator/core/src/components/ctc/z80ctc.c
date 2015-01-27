#include "components/ctc/z80ctc.h"

static void            z80ctc_init_channel(t_z80ctc_channel *chan)
{
    chan->control_reg.data = 0;
    chan->timer_reg = 0;
}

void            z80ctc_init(t_z80ctc *self)
{
    z80ctc_init_channel(&(self->channel[0]));
    z80ctc_init_channel(&(self->channel[1]));
    z80ctc_init_channel(&(self->channel[2]));
    z80ctc_init_channel(&(self->channel[3]));
}

static void     z80ctc_update_channel(t_z80ctc_channel *chan)
{

}

void            z80ctc_update(t_z80ctc *self)       //TODO : continue here
{
    int         i;

    // Simulate a clock ? Catch up with the number of t-states elapsed ? something like this ?
    // The reference clock output is "slowed down" by the prescaler, then the counter decreases. When 0, int and refill.

    for (i = 0; i < 4; ++i)
    {
        z80ctc_update_channel(&(self->channel[i]));
        //if (counter == 0)
        // int, then reload.   ?
    }
    // todo:Handle soft reset is the bit is set in the control
    // Handle when a channel pops an interrupt (and channel 0 have priority)
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
        self->control_reg.time_constant_follows = 0;
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
