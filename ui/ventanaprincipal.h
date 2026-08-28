#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QIcon>

#include "pantallalogin.h"

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
public:
    explicit VentanaPrincipal(QWidget *parent=nullptr);
    ~VentanaPrincipal() override;

    PantallaLogin *pantallaLogin;
    void cambiarPantalla(QWidget *pantalla);

private:
    QStackedWidget *stackWidget;

};

#endif // VENTANAPRINCIPAL_H
