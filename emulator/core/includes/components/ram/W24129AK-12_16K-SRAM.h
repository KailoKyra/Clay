#ifndef     _W24129AK12_16K_SRAM_H_
# define    _W24129AK12_16K_SRAM_H_

#include "defines.h"

typedef struct          s_W24129AK12_16K_SRAM
{
    byte                data[16 * 1024];            // 128K RAM
    byte                D;                          // I/O port (8 bits)
    uint32              A;                          // Address (14 bits)
    byte                CS;                         // !Chip select
    byte                WE;                         // !Write Enable
    byte                OE;                         // !Output Enable
}                       s_W24129AK12_16K_SRAM;

void                update_W24129AK12_16K_SRAM(s_W24129AK12_16K_SRAM *ram);

#endif
