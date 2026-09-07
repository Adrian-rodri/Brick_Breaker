#ifndef PANTALLAMENUPRINCIPAL_H
#define PANTALLAMENUPRINCIPAL_H

#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>

#include "partida.h"

class PantallaMenuPrincipal : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaMenuPrincipal(QWidget *parent=nullptr);
    ~PantallaMenuPrincipal();

private:
    QLabel *titulo;
    QPushButton *btnJugar;
    QPushButton *btnNiveles;
    QPushButton *btnRecords;
    QPushButton *btnSalir;
    QPushButton *btnAyuda;
    QPushButton *btnLogros;
    QPushButton *btnOpciones;

    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutMiniBtns;

    Partida *partida;
    void cargarUI();
    void irAlJuego();
    void irAOpciones();
};

#endif // PANTALLAMENUPRINCIPAL_H
