#include "MainWindow.h"
#include <QApplication>
#include <iostream>

#include "../core/includes/clay.h"

int main(int argc, char *argv[])
{
 /*   QApplication a(argc, argv);
    MainWindow w;
    w.show();
*/
    if (argc > 1)
    {
        init_clay(&g_clay, argv[1]);
        run_clay(&g_clay);
      //  return a.exec();
    }
    else
        std::cerr << "Usage: ./claymulator path_to_rom" << std::endl;
    return (EXIT_FAILURE);
}
