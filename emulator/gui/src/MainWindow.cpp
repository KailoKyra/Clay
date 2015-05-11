#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <unistd.h>

#include <QAudioFormat>
#include <QDebug>
#include "AudioBuffer.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format))
    {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    QIODevice           *audiobuffer = new AudioBuffer();
    audiobuffer->open(QIODevice::ReadOnly);
    _audio = new QAudioOutput(format, this);
    connect(_audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    _audio->start(audiobuffer);
}

void            MainWindow::handleStateChanged(QAudio::State newState)
{
    switch (newState)
    {
    case QAudio::IdleState:
        std::cout << "processed Usec : " << _audio->processedUSecs() << "   Elapsed usec : " << _audio->elapsedUSecs() << std::endl;
        std::cout << "It's idle man" << std::endl;
        _audio->suspend();
        usleep(1000000);        // ugly hack to prevent sound buffer underflow. todo : Fixme with a more elegant solution.
        _audio->resume();
        break;
    case QAudio::StoppedState:
        std::cout << "It's stopped man" << std::endl;
        // Stopped for other reasons
        if (_audio->error() != QAudio::NoError)
        {
            std::cout << "It's broken man" << std::endl;

            // Error handling
        }
        break;

    default:
        // ... other cases as appropriate
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void            MainWindow::on_actionExit_triggered()
{
    this->close();
}

void            MainWindow::on_actionReset_triggered()
{

}
