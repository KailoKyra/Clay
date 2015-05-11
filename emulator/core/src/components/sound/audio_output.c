#include "components/sound/audio_output.h"

#include <pthread.h> // Try to do something to avoid the usage of a mutex.

// quick and dirty to test:

pthread_mutex_t     _circular_buffer_mutex = PTHREAD_MUTEX_INITIALIZER;		// TODO : MOVE THIS 

int         audio_output_init(t_audio_output *self, unsigned int audio_buffer_size,
                              void *sound_chip, audio_output_sample_callback sample_callback)
{
    if (circular_buffer_init(&self->circular_buffer, audio_buffer_size, sizeof(t_stereo_sample)) < 0)
        return (-1);
    self->cycle_counter = 0;
    self->_sound_chip = sound_chip;
    self->_sample_callback = sample_callback;
    return (0);
}


void            audio_output_update(t_audio_output *self, unsigned int elapsed_cycles)
{
    t_stereo_sample         sample;

    if (self->circular_buffer.buffer)
    {
        self->cycle_counter += elapsed_cycles;
        if (self->cycle_counter >= CYCLES_PER_SAMPLE)
        {
            self->cycle_counter -= CYCLES_PER_SAMPLE;
            self->_sample_callback(self->_sound_chip, &sample.l, &sample.r);
            pthread_mutex_lock(&_circular_buffer_mutex);
            circular_buffer_write(&self->circular_buffer, &sample, 1);
            pthread_mutex_unlock(&_circular_buffer_mutex);
        }
    }
}


int             audio_output_read(t_audio_output *self, t_stereo_sample *buf, unsigned int nbSamples)
{
    int ret = 0;
    if (nbSamples)
    {
        pthread_mutex_lock(&_circular_buffer_mutex);
        ret = circular_buffer_read(&self->circular_buffer, buf, nbSamples);
        pthread_mutex_unlock(&_circular_buffer_mutex);
    }
    return (ret);
}
