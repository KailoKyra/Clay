#include "components/ctc/z80ctc.h"

void            update_74xx138(t_74xx138 *self)
{
    if (self->E1 && !self->E2 && !self->E3)
        self->Y = ~(1 << self->ABC);
}
