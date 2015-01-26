#include        "components/74xx/74xx145.h"

void            update_74xx145(t_74xx145 *self)
{
    self->O = ~(1 << self->ABCD);
}
