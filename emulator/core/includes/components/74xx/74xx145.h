#ifndef     _74XX145_H_
# define    _74XX145_H_

#include "defines.h"

/*
 * ***********************  74xx145 ************************
 *  BCD to Decimal decoder
 * *********************************************************
 */

typedef struct      s_74xx145
{
    byte            ABCD;                       // Chosen output (4 bits)
    uint16          O;                          // Output (10 bits)
}                   t_74xx145;

void            update_74xx145(t_74xx145 *self);

#endif
