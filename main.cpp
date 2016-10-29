#include "mainwidget.h"
#include <QApplication>
#pragma comment(lib,"ws2_32")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
