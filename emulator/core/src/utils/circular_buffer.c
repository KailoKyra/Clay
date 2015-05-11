#include <string.h>
#include <stdlib.h>
#include "utils/circular_buffer.h"

int        circular_buffer_init(t_circular_buffer *self, unsigned int n, unsigned int size)
{
    memset(self, 0, sizeof(t_circular_buffer));
    if (!size || (n < 2))
        return (0);
    self->data_size = size;
    self->buffer_size = n;
    if ((self->buffer = malloc(self->buffer_size * self->data_size)) == NULL)
        return (0);
    return (1);
}


int         circular_buffer_read(t_circular_buffer *self, void *buffer, unsigned int n)
{
    if (n > self->data_written)
        return (-1);
    if ((self->read_cursor + n) < self->buffer_size)
        memcpy(buffer, ((char *)self->buffer) + self->read_cursor, (n * self->data_size));
    else
    {
        const unsigned int sub_buffer_size = (self->buffer_size - self->read_cursor) * self->data_size;
        memcpy(buffer, ((char *)self->buffer) + (self->read_cursor * self->data_size), sub_buffer_size);
        memcpy((char *)buffer + sub_buffer_size, self->buffer, (n * self->data_size) - sub_buffer_size);
    }
    self->read_cursor = (self->read_cursor + n) % self->buffer_size;            // TODO : don't use modulo.
    self->data_written -= n;
    return (n);
}

int         circular_buffer_write(t_circular_buffer *self, const void *buffer, unsigned int n)
{
    if (n > (self->buffer_size - self->data_written))     // If there is not enough free space in the buffer
        return (-1);
    if ((self->write_cursor + n) < self->buffer_size)
        memcpy((char *)self->buffer + (self->write_cursor * self->data_size), buffer, n * self->data_size);
    else
    {
        const unsigned int sub_buffer_size = (self->buffer_size - self->write_cursor) * self->data_size;
        memcpy(((char *)self->buffer) + (self->write_cursor * self->data_size), buffer, sub_buffer_size);
        memcpy(self->buffer, (char *)buffer + sub_buffer_size, (n * self->data_size) - sub_buffer_size);
    }
    self->write_cursor = (self->write_cursor + n) % self->buffer_size;            // TODO : don't use modulo.
    self->data_written += n;
    return (n);
}

int         circular_buffer_write_overwrite(t_circular_buffer *self, const void *buffer, unsigned int n)
{
    if ((self->data_written + n) > self->buffer_size)
        self->read_cursor = (self->read_cursor + n - (self->buffer_size - self->data_written)) % self->buffer_size;
    while (n)
    {
        unsigned int tocopy = (n > self->buffer_size) ? self->buffer_size : n;
        if ((self->write_cursor + tocopy) < self->buffer_size)
            memcpy((char *)self->buffer + (self->write_cursor * self->data_size), buffer, tocopy * self->data_size);
        else
        {
            const unsigned int sub_buffer_size = (self->buffer_size - self->write_cursor) * self->data_size;
            memcpy(((char *)self->buffer) + (self->write_cursor * self->data_size), buffer, sub_buffer_size);
            memcpy(self->buffer, (char *)buffer + sub_buffer_size, (tocopy * self->data_size) - sub_buffer_size);
        }
        self->write_cursor = (self->write_cursor + tocopy) % self->buffer_size;            // TODO : don't use modulo.
        self->data_written += tocopy;
    }
    if (self->data_written > self->buffer_size)
        self->data_written = self->buffer_size;
    return (n);
}

void        circular_buffer_delete(t_circular_buffer *self)
{
    free(self->buffer);
    self->buffer = NULL;
}
