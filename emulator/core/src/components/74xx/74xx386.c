#include "components/74xx/74xx386.h"

void            update_74xx386_xor(t_74xx386_xor *self)
{
    self->O = self->A ^ self->B;
}


void            update_74xx386(t_74xx386 *self)
{
    update_74xx386_xor(self->gate + 0);
    update_74xx386_xor(self->gate + 1);
    update_74xx386_xor(self->gate + 2);
    update_74xx386_xor(self->gate + 3);
}
