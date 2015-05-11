#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QIODevice>

class AudioBuffer : public QIODevice
{
    Q_OBJECT
public:
    AudioBuffer(){}
    virtual ~AudioBuffer(){}

protected:
    virtual qint64	readData(char *data, qint64 maxSize);
    virtual qint64	writeData(const char *data, qint64 maxSize);
};

#endif // AUDIOBUFFER_H
