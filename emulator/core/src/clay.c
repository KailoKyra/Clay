
#include "clay.h"

//TODO :void Z80INT (Z80Context* ctx, byte value);

t_clay       g_clay;

void        init_clay(t_clay *clay, const char *rom_path)
{
    clay->cpu.memRead   = mmu_mem_read;
    clay->cpu.memWrite  = mmu_mem_write;
    clay->cpu.ioRead    = io_handler_read;
    clay->cpu.ioWrite   = io_handler_write;

    init_mmu(&clay->mmu, rom_path);
}

void        update_clay(t_clay *clay, double deltaTime)
{
    (void)deltaTime;
    Z80Execute(&clay->cpu);
}
