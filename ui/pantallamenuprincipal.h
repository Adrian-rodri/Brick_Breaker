#ifndef PANTALLAMENUPRINCIPAL_H
#define PANTALLAMENUPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>

class PantallaMenuPrincipal : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaMenuPrincipal(QWidget *parent=nullptr);
    ~PantallaMenuPrincipal();

private:
    QLabel *lblTitulo;
    QPushButton *btnJugar;
    QPushButton *btnInstrucciones;
    QPushButton *btnNiveles;
    QPushButton *btnRecords;
    QPushButton *btnSalir;

    QVBoxLayout *layoutPrincipal;
    void cargarUI();
    void irAlJuego();
    void irAOpciones();
};

#endif // PANTALLAMENUPRINCIPAL_H
