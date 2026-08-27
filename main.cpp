#include "pantallamenuprincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PantallaMenuPrincipal w;
    w.show();
    return QApplication::exec();
}
