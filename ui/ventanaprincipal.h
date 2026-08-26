#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
public:
    explicit VentanaPrincipal(QWidget *parent=nullptr);
    ~VentanaPrincipal() override;

private:
    QStackedWidget *stackWidget;

    void cargarLogin();
};

#endif // VENTANAPRINCIPAL_H
