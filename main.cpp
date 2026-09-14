#include "ventanaprincipal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(static_cast<unsigned int>(time(nullptr)));
    VentanaPrincipal w;
    w.show();
    return QApplication::exec();
}
