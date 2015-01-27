#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "clay.h"

#define     FPS     (1/60.)

double              get_current_time()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_usec / 1000000. + tv.tv_sec);
}

void                run_clay(t_clay *clay)
{
    double            tp, ta, delta;

    clay->is_running = 1;
    delta = 0;
    ta = get_current_time();
    while (clay->is_running)
    {
        tp = ta;
        clay->cpu.tstates = 0;
        while (clay->cpu.tstates < (CPU_SPEED * FPS))         // We simulate CPU_SPEED*FPS cycles (around 1/60s).
        {
            update_clay(&g_clay);
        }
        delta = (ta = get_current_time()) - tp;
        if (delta < (FPS - 0.005))                            // If we took less than FPS seconds to simulate CPU_SPEED*FPS cycles
            usleep((FPS - delta) * 1000. * 1000.);
    }
}
