#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void        on_actionExit_triggered();
    void        on_actionReset_triggered();

    void        handleStateChanged(QAudio::State newState);

private:
    Ui::MainWindow  *ui;
    QAudioOutput    *_audio; // class member.
};

#endif // MAINWINDOW_H
