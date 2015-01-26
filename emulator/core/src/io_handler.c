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
      return 0; //CTC stuff
      break;
    case PIO:
      //return (Read8255(&pio, address & 0x03)); //PIO A0/A1
      break;
    case VDP:
      return 0; //VDP stuff
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
  case MMU:
      g_clay.mmu.address_extender[(data & 0x30) >> 4] = data & ~0xF0;
      break;
  case SIO:
      //sio_write(&sio, address, data);
      break;
  case PIO:
      //Write8255(&pio, address & 0x03, data);
      break;
  case DEBUG:
        write(STDOUT_FILENO, &data, 1);
      break;
  }
}
