#include "io_handler.h"
#include "clay.h"

#include "unistd.h"
//#include "debug.h"

byte                io_handler_read(int param, ushort address)
{
    unsigned int    periph = address & 0x00F0;

    (void)param;
    switch(periph)
    {
    case MMU:
        return (0x00);		// With the current design, the MMU cannot be read.
        break;
    case SIO:
        //return (sio_read(&sio, address));
        break;
    case CTC:
        return (z80ctc_read(&g_clay.ctc, (address & 0x03)));
        break;
    case AY:
        if (address & 0x01)                           // The AY can be read only if A0 is high.
            return (ay_3_8912_read(&g_clay.ay));      // The I/O port is not used, so no need to handle portA
        break;
    case VDP:
        return (tms9918a_read(&g_clay.vdp, (address & 0x01)));    // address & 0x01 == read from status reg or ram
        break;

    case DEBUG:
        write(STDOUT_FILENO, "?\n", 2);
        return (fgetc(stdin));
        break;
    }
    return (0x00);
}

void                io_handler_write(int param, ushort address, byte data)
{
    unsigned int    periph = address & 0x00F0;
    (void)param;

    switch(periph)
    {
    case MMU:                                                 // 0x00 - 0x0F
        g_clay.mmu.address_extender[(data & 0x30) >> 4] = data & ~0xF0;
        break;
    case SIO:                                                 // 0x10 - 0x1F
        //sio_write(&sio, address, data);
        break;
    case CTC:                                                 // 0x20 - 0X2F
        z80ctc_write(&g_clay.ctc, (address & 0x03), data);                        // address & 0x3 because we use only A0|A1 for the channel/reg select
        break;
    case AY:                                                 // 0x30 - 0x3F
        if (address & 0x01)                           // latch address mode
            ay_3_8912_latch_address(&g_clay.ay, data);
        else                                          // Normal write mode
            ay_3_8912_write(&g_clay.ay, data);
        break;
    case VDP:
        tms9918a_write(&g_clay.vdp, data, (address & 0x01));  // address & 0x01 -> write to register or ram
        break;
    case DEBUG:
        write(STDOUT_FILENO, &data, 1);
        break;
    }
}
