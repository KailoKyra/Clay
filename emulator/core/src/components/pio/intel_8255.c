#include "components/pio/intel_8255.h"


// All ports in input mode when reset.
void            intel_8255_init(t_intel_8255 *self)
{
    memset(self, 0, sizeof(t_intel_8255));
    self->reg[PIO_CONFIG] = PIO_MODE_SET_FLAG | PIO_GROUP_A_MODE_0 | PIO_PORTA_IS_INPUT
            | PIO_UPPER_PORT_C_IS_INPUT | PIO_GROUP_B_MODE_0
            | PIO_PORTB_IS_INPUT | PIO_LOWER_PORT_C_IS_INPUT;
}

void        intel_8255_write(t_intel_8255 *self, byte cs, byte data)
{
    if ((cs != PIO_CONFIG) || (data & PIO_MODE_SET_FLAG))               // write to a port, or to the control reg. in "set mode" mode.
    {
        self->reg[cs] = data;
        if (!(self->reg[PIO_CONFIG] & PIO_PORTA_IS_INPUT))
            self->portOut[PIO_PORT_A] = self->reg[PIO_PORT_A];
        if (!(self->reg[PIO_CONFIG] & PIO_PORTB_IS_INPUT))
            self->portOut[PIO_PORT_B] = self->reg[PIO_PORT_B];
    }
    else                                                                // write to the control register in bit set/reset mode
    {
        if (data & PIO_BIT_SET_RESET)
            self->reg[PIO_PORT_C] |= 1 << ((data & 0x0E) >> 1);
        else
            self->reg[PIO_PORT_C] &= ~(1 << ((data & 0x0E) >> 1));
    }
    self->portOut[PIO_PORT_C] = (((self->reg[PIO_CONFIG] & PIO_UPPER_PORT_C_IS_INPUT) ? 0x00 : (self->reg[PIO_PORT_C] & 0xF0))
                                 | ((self->reg[PIO_CONFIG] & PIO_LOWER_PORT_C_IS_INPUT) ? 0x00 : (self->reg[PIO_PORT_C] & 0x0F)));
}

byte            intel_8255_read(t_intel_8255 *self, byte cs)
{
    if (cs == PIO_PORT_A)
        return (self->reg[PIO_CONFIG] & PIO_PORTA_IS_INPUT ? self->portIn[PIO_PORT_A] : self->reg[PIO_PORT_A]);
    else if (cs == PIO_PORT_B)
        return (self->reg[PIO_CONFIG] & PIO_PORTB_IS_INPUT ? self->portIn[PIO_PORT_B] : self->reg[PIO_PORT_B]);
    else if (cs == PIO_PORT_C)
        return ((((self->reg[PIO_CONFIG] & PIO_UPPER_PORT_C_IS_INPUT) ? self->portIn[PIO_PORT_C] : (self->reg[PIO_PORT_C]) & 0xF0))
                | (((self->reg[PIO_CONFIG] & PIO_LOWER_PORT_C_IS_INPUT) ? self->portIn[PIO_PORT_C] : (self->reg[PIO_PORT_C]) & 0x0F)));
    return (0);      /* Invalid address, should not happen */
}
