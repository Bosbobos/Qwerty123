#include "./loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow lw;
    lw.show();
    return a.exec();
}
