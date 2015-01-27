#include "defines.h"
#include "z80.h"
#include "mmu.h"
#include "io_handler.h"

#include "components/components.h"

#ifndef     CLAY_H_
# define    CLAY_H_

typedef struct      s_clay
{
    Z80Context          cpu;
    t_mmu               mmu;

    t_z80ctc            ctc;

    // video_controller
    // CTC
    // SIO
    // PIO
    // SOUND
    // KB
    byte             is_running;
}                   t_clay;

extern t_clay       g_clay;         // Declared in clay.c

void        update_clay(t_clay *clay);

#ifdef  __cplusplus
extern "C" {
#endif

void        init_clay(t_clay *clay, const char *rom_path);
void        run_clay(t_clay *clay);                                  // Run this in a thread

#ifdef  __cplusplus
}
#endif
#endif
