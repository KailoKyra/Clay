
#include "clay.h"

//TODO :void Z80INT (Z80Context* ctx, byte value);

t_clay       g_clay;

void        init_clay(t_clay *clay, const char *rom_path)
{
    clay->cpu.memRead   = mmu_mem_read;
    clay->cpu.memWrite  = mmu_mem_write;
    clay->cpu.ioRead    = io_handler_read;
    clay->cpu.ioWrite   = io_handler_write;

    mmu_init(&clay->mmu, rom_path);
    z80ctc_init(&clay->ctc);
    ay_3_8912_init(&clay->ay);
   if (audio_output_init(&clay->audio_out, 44100*2, &clay->ay, (audio_output_sample_callback)ay_3_8912_sample_stereo))  // 2 sec sound buffer
       fprintf(stderr, "An error occured while initializing the sound sampler.\n");
}

void        update_clay(t_clay *clay)
{
    unsigned int        tstate_delta = clay->cpu.tstates;

    Z80Execute(&clay->cpu);         // Execute next instruction
    tstate_delta = clay->cpu.tstates - tstate_delta;

    // Update components
    z80ctc_update(&clay->ctc, tstate_delta);
    ay_3_8912_update(&clay->ay, tstate_delta);
    audio_output_update(&clay->audio_out, tstate_delta);
    // update SIO    

    // Process interrupts if any (and if possible)
    if (clay->cpu.IFF1)
    {
        if (clay->ctc.interrupt_request)
        {
            Z80INT(&clay->cpu, clay->ctc.interrupt_channel_vector);
            z80ctc_ack_interrupt_req(&clay->ctc);
        }
        // ellse if (...)
        // ;
    }
}
