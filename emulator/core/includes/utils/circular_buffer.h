#ifndef     CIRCULAR_BUFFER_H_
# define    CIRCULAR_BUFFER_H_

typedef struct      s_circular_buffer
{
    void            *buffer;
    unsigned int    write_cursor;
    unsigned int    read_cursor;
    unsigned int    data_written;

    unsigned int    data_size;
    unsigned int    buffer_size;
}                   t_circular_buffer;

int                 circular_buffer_init(t_circular_buffer *self, unsigned int n, unsigned int size);       // buffer size = n * size bytes
int                 circular_buffer_read(t_circular_buffer *self, void *buffer, unsigned int n);
int                 circular_buffer_write(t_circular_buffer *self, const void *buffer, unsigned int n);
int                 circular_buffer_write_overwrite(t_circular_buffer *self, const void *buffer, unsigned int n);
void                circular_buffer_delete(t_circular_buffer *self);

#endif
