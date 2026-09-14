#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H
#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTimer>
#include <QElapsedTimer>
#include <QLabel>

#include "partida.h"
#include "powerup.h"
#include "motorjuego.h"
class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    PantallaJuego(int nivel, QWidget* parent = nullptr);
    PantallaJuego(Partida* partidaCargada, QWidget* parent = nullptr);
    ~PantallaJuego() override;

private:
    MotorJuego* motor;
    QGraphicsRectItem*** ptrBloques;
    QGraphicsRectItem* itemPlataforma;
    QGraphicsEllipseItem** itemsPelotas;
    QGraphicsRectItem** itemsPowerUps;
    QTimer* timerJuego;
    QElapsedTimer cronometro;
    int cantidadPowerUps;

    void actualizarJuego();
    void manejarFinDePartida();
    //movimiento
    bool moverIzq;
    bool moverDer;
    bool esperando;
    void actualizarPosiciones();

    void agregarPowerUp(PowerUp* nuevoPower);
    void eliminarPowerUp(int indice);
    void sincronizarPelotasExtra();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    //hud
    QLabel* lblVidas;
    QLabel* lblPuntos;
    QLabel* lblTiempo;
    QLabel* lblBloques;
    QLabel* lblAviso;
    int totalBloques;
    void cargarHUD(QVBoxLayout* layoutVertical);
    void actualizarHUD();
    //elemntos ui
    int filas;
    int col;
    QGraphicsScene* escena;
    QGraphicsView* vista;
    void cargarUi();
    void liberarBloques();
    void dibujarBloques();
    void dibujarPlataforma();
    void dibujarPelotas();
};
#endif // PANTALLAJUEGO_H