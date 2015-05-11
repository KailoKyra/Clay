#ifndef INTEL_8255_H
#define INTEL_8255_H

// todo:  put infos about the 8255 here
#include "defines.h"

typedef struct      s_intel_8255
{
  byte          reg[4];         /* Registers    */
  byte          portOut[3];     /* Output ports */
  byte          portIn[3];      /* Input ports  */
}                   t_intel_8255;


void            intel_8255_init(t_intel_8255   *self);
void            intel_8255_write(t_intel_8255  *self, byte cs, byte data);          // cs : channel select (register)
byte            intel_8255_read(t_intel_8255   *self, byte cs);
void            intel_8255_update(t_intel_8255 *self, unsigned int system_clock_tstastes);



//Channel (registers)
# define        PIO_PORT_A      0x00
# define        PIO_PORT_B      0x01
# define        PIO_PORT_C      0x02
# define        PIO_CONFIG      0x03

// PIO Configuration - Mode definition control word

# define        PIO_LOWER_PORT_C_IS_INPUT       0x01
# define        PIO_LOWER_PORT_C_IS_OUTPUT      0x00
# define        PIO_PORTB_IS_INPUT              0x02
# define        PIO_PORTB_IS_OUTPUT             0x00
# define        PIO_GROUP_B_MODE_0              0x00
# define        PIO_GROUP_B_MODE_1              0x04
# define        PIO_UPPER_PORT_C_IS_INPUT       0x08
# define        PIO_UPPER_PORT_C_IS_OUTPUT      0x00
# define        PIO_PORTA_IS_INPUT              0x10
# define        PIO_PORTA_IS_OUTPUT             0x00
# define        PIO_GROUP_A_MODE_0              0x00
# define        PIO_GROUP_A_MODE_1              0x20
# define        PIO_GROUP_A_MODE_2              0x40
# define        PIO_MODE_SET_FLAG               0x80

// PIO Configuration - Bit set/reset control word (if PIO_MODE_SET_FLAG is not set)
# define        PIO_BIT_SET_RESET               0x01        // 1 set / 0 reset

#endif
