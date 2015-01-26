#ifndef     _74XX574_H_
# define    _74XX574_H_

#include "defines.h"

/*
 * ***********************  74xx574 ************************
 *  Octal 3 state buffer
 * *********************************************************
 */

typedef struct      s_74xx574
{
    byte            D;                      // Data I/O port (8bits)
    byte            O;                      // Buffer output (8bits)
    byte            OE;                     // !Output Enable
    byte            CP;                     // Output common clock
}                   t_74xx574;

void            update_74xx574(t_74xx574 *self);

#endif
