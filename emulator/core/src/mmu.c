#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

#include "mmu.h"
#include "clay.h"

static void     init_rom(byte *rom, const char *rom_filename);

void        init_mmu(t_mmu *mmu, const char *rom_path)
{
    init_rom(mmu->rom, rom_path);
    mmu->address_extender[0] = 0;     // The registers are not set to 0 in the schematics. TODO : Check/fix that.
}

byte       mmu_mem_read(int param, uint16 address)
{
    unsigned int    virtual_address = (g_clay.mmu.address_extender[(address & 0xC000) >> 14] << 14) | (address & ~0xC000);  // See mmu.h for the details
    (void)param;

    if (virtual_address < 0x8000) // in the 32K ROM
        return (g_clay.mmu.rom[virtual_address]);
    else if (virtual_address < 0x28000) // in the 128K RAM
        return (g_clay.mmu.ram[virtual_address - 0x8000]);
    /*else
            return (0x00); // Modify this to handle something in the free address space*/
    return (0x00);
}

void      mmu_mem_write(int param, uint16 address, byte data)
{
    unsigned int    virtual_address = (g_clay.mmu.address_extender[(address & 0xC000) >> 14] << 14) | (address & ~0xC000);  // See mmu.h for the details
    (void)param;

    if (virtual_address < 0x28000) // in the 128K RAM
        g_clay.mmu.ram[virtual_address - 0x8000] = data;
    /*else
            ; // Modify this to handle something in the free address space*/
}



//------------------------------ ROM ------------------------------------

static void     init_rom(byte *rom, const char *rom_filename)
{
    int         fd;
    int         pos;
    ssize_t     ret;

    pos = 0;
    if ((fd = open(rom_filename, O_RDONLY)) < 0)
    {
        perror("Unable to open rom image : ");
        exit(EXIT_FAILURE);                         // Todo un jour, faire un truc plus propre que ça
    }
    if (lseek(fd, 0, SEEK_END) > ROM_SIZE)
    {
        fprintf(stderr, "Wrong size for rom image... should be <= %d\n", ROM_SIZE);
        exit(EXIT_FAILURE);
    }
    close(fd);
    fd = open(rom_filename, O_RDONLY);
    while ((ret = read(fd, rom + pos, ROM_SIZE - pos)) > 0)
        pos += ret;
    if (ret == -1)
    {
        perror("Unable to read rom image : ");
        exit(EXIT_FAILURE);
    }
    close(fd);
    printf("Rom \"%s\" loaded.\n", rom_filename);
}
