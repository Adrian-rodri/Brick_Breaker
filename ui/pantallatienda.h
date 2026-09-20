#ifndef PANTALLATIENDA_H
#define PANTALLATIENDA_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "PerfilProgreso.h"

class PantallaTienda: public QWidget
{
    Q_OBJECT
public:
    PantallaTienda(QWidget* parent=nullptr);
private:
    void cargarUI();
    void actualizarUI();
    void comprarDamage();
    void comprarMultiplicador();
    void comprarVelocidadPlataforma();
    void comprarBlindaje();
    void hacerPrestigio();
    void volverAlMenu();

    PerfilProgreso* perfil;
    QLabel* lblCreditos;
    QLabel* lblDano;
    QLabel* lblMultiplicador;
    QLabel* lblVelocidad;
    QLabel* lblBlindaje;
    QPushButton* btnDano;
    QPushButton* btnMultiplicador;
    QPushButton* btnVelocidad;
    QPushButton* btnBlindaje;
    QLabel* lblPrestigio;
    QPushButton* btnPrestigio;
};

#endif // PANTALLATIENDA_H