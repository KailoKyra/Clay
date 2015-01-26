/*
 * As the Z80 can only address 64KB of memory (2^16 addresses),
 * we virtualy extend its address space to 256KB to be able to handle both the 32K rom and the 128K RAM
 * via 16KB memory pages.
 * Clay uses a 74670 (4x4bits register) as a MMU (memory management unit).
 *      Ex :
 *
 *                                                  Virtual address space :
 *                                                  (18 bits)
 *                                                         ______________  0x00000
 *                                                         |             |
 *                                                         |             |
 *  Z80 address space :        MMU :                       |  ROM (32K)  |
 *  (16 bits)                                              |             |
 *  ___________  0x0000         ____________               |_____________| 0x07FFF
 * |           |               |   0x0      |              |             |
 * |-----------|               |------------|              |             |
 * |           |               |   0x3      |              |             |
 * |-----------|      <=>      |------------|     <=>      |  RAM (128K) |
 * |           |               |   0x1      |              |             |
 * |-----------|               |------------|              |             |
 * |           |               |   0x9      |              |             |
 * |-----------|               |------------|              |_____________| 0x27FFF
 *               0xFFFF                                    |             |
 *                              (Page 0/3/1/2)             |  FREE/EXT   |
 *                                                         |    (96K)    |
 *                                                         |             |
 *                                                         |-------------| 0x3FFFF
 *
 * Virtual to physical memory address :
 *      A0 to A13 = first 13 bits of the address
 *      A14 to A15 = MMU register selection (register 0 to 3)
 *     MMU register content = last 4 bits of the address.
 *
 * So, using the above exemple, the physical address 0b1100 0000 0000 1111 (0xC00F) will
 * point to the virtual address : 0b10 0100 0000 0000 1111 (0x2400F), somewhere in the beggining of
 * the last 16K of the 128K RAM chip.
*/


#ifndef     MMU_H_
# define    MMU_H_

#include "defines.h"

typedef struct      s_mmu
{
    byte            ram[RAM_SIZE];
    byte            rom[ROM_SIZE];
    byte            address_extender[4];        // four 4bits register
}                   t_mmu;

void        init_mmu(t_mmu *mmu, const char *rom_path);
byte        mmu_mem_read(int param, uint16 address);                      // Z80 Memory read callback
void        mmu_mem_write(int param, uint16 address, byte data);          // Z80 Memory write callback

#endif
