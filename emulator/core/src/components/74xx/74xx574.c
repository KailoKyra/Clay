#include "components/74xx/74xx574.h"

void            update_74xx574(t_74xx574 *self)
{
    if (self->CP && !self->OE)
        self->O = self->D;
}
