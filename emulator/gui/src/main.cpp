#include "MainWindow.h"
#include <QApplication>
#include <iostream>
#include <thread>

#include <unistd.h>

#include "../core/includes/clay.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
        init_clay(&g_clay, argv[1]);
    else
    {
        std::cerr << "Usage: ./claymulator path_to_rom" << std::endl;
        return (EXIT_FAILURE);
    }
    std::thread     coreThread([]() { run_clay(&g_clay); });        // could test without thread and processevent ect. May be better ?

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int ret = a.exec();
    g_clay.is_running = false;      //stop the core properly and wait for the thread to terminate
    coreThread.join();
    return (ret);
}
