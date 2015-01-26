#include        "components/74xx/74xx138.h"

void            update_74xx138(t_74xx138 *self)
{
    if (self->E1 && !self->E2 && !self->E3)
        self->Y = ~(1 << self->ABC);
}
