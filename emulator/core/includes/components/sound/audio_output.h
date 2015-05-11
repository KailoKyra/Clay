#ifndef     AUDIO_OUTPUT_H_
# define    AUDIO_OUTPUT_H_

#include "utils/circular_buffer.h"
#include "defines.h"

typedef struct          s_audio_output
{
    t_circular_buffer   circular_buffer;
    float               cycle_counter;

    void                *_sound_chip;
    void                (*_sample_callback)(void *, uint16 *, uint16 *);
}                       t_audio_output;

typedef void (*audio_output_sample_callback)(void *, uint16 *, uint16 *);           // audio_output_sample_callback is a void (*)(void *, uint16 *, uint16 *) fct ptr.

typedef struct          s_stereo_sample
{
    uint16              l;
    uint16              r;
}                       t_stereo_sample;

#ifdef __cplusplus
extern "C" {
#endif

int                 audio_output_init(t_audio_output *self, unsigned int audio_buffer_size,
                                      void *sound_chip, audio_output_sample_callback sample_callback);
void                audio_output_update(t_audio_output *self, unsigned int elapsed_cycles);


int                 audio_output_read(t_audio_output *self, t_stereo_sample *buf, unsigned int nbSamples);

#ifdef __cplusplus
}
#endif

# define            AUDIO_OUTPUT_SAMPLING_RATE      (44100.0f)
# define            CYCLES_PER_SAMPLE               (CPU_SPEED / AUDIO_OUTPUT_SAMPLING_RATE) // ~83,59 cycles/sample  // 44.1Khz sampling = 22Khz sound quality (Nyquist theorem)


#endif
