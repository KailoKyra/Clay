#include <iostream> //REMOVEME

#include "AudioBuffer.h"

#include "../core/includes/clay.h"

qint64          AudioBuffer::readData(char *data, qint64 maxSize)
{
    t_audio_output *audioOut = &g_clay.audio_out;

    maxSize >>= 2;                                                            // maxSize is in bytes. Get the number of samples. A sample is 4bytes (2 values of 16 bits).
    if (maxSize > audioOut->circular_buffer.data_written)
        maxSize = audioOut->circular_buffer.data_written;
    //  if (maxSize & 3)        // If the data requested is not a multiple of 4 (It happens, but how is this possible ? It mess things up, so this fix it)
    maxSize &= ~0x3;
    return (audio_output_read(audioOut, (t_stereo_sample *)data, maxSize) << 2);       // Read a given number of SAMPLES (16*2bytes). Return the amount of byte read.
}

qint64          AudioBuffer::writeData(const char *data, qint64 maxSize)
{
    std::cerr << "WriteData::Not useful" << std::endl;
    return (0);
}
