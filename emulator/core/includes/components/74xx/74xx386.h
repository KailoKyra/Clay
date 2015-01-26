#ifndef     _74XX386_H_
# define    _74XX386_H_

#include "defines.h"

/*
 * ***********************  74xx386 ************************
 *  4 XOR
 * *********************************************************
 */

typedef struct      s_74xx386_xor
{
    byte            A;                      // input 1
    byte            B;                      // input 1
    byte            O;                      // Output (A ^ B)
}                   t_74xx386_xor;

typedef struct      s_74xx386
{
    t_74xx386_xor   gate[4];
}                   t_74xx386;

void            update_74xx386_xor(t_74xx386_xor *self);
void            update_74xx386(t_74xx386 *self);

#endif
