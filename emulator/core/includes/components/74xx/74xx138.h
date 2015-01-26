#ifndef     _74XX138_H_
# define    _74XX138_H_

#include "defines.h"

/*
 * ***********************  74xx138 ************************
 *  A 3-to-8 demux
 * *********************************************************
 */

typedef struct      s_74xx138
{
    byte            ABC;                        // Chosen output (3 bits)
    byte            E1, E2, E3;                 // Output enable (E1 . !E2 . !E3)
    byte            Y;                          // Output (8 bits)
}                   t_74xx138;

void            update_74xx138(t_74xx138 *self);

#endif
