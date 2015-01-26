#ifndef     IO_HANDLER_H_
# define    IO_HANDLER_H_

#include "defines.h"

/*
 * The peripheral selection is done via a 74138 (3 to 8 demultiplexer)
 * The selection of a peripheral is made by placing a 3 bit value on  A4 to A6 (A7 is reserved
 * for possible external peripheral)
 * The value placed on A0 to A3 (4bits, 16 possibilities) can then be used to select a register on
 * a chip, toggle something or whatever the peripheral does with it.
 *
 * Note : A8 to A15 is not used since the IN and OUT instructions uses only the lower part of the
 * address line.
 *
 * 0 = MMU
 * 1 = SERIAL
 * 2 = CTC
 * 3 = PIO
 * 4 = VDP
 * ...
*/


# define    MMU             (0x00)
# define    SIO             (0x10)
# define    CTC             (0x20)
# define    PIO             (0x30)
# define    VDP             (0x40)

# define    DEBUG           (0x80)      // Here for testing purposes (output data on stdout, input a char with stdin)

byte        io_handler_read(int param, uint16 address);
void        io_handler_write(int param, uint16 address, byte data);

#endif
