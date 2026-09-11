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

class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    PantallaJuego(int nivel, QWidget* parent = nullptr);
    PantallaJuego(Partida* partidaCargada, QWidget* parent = nullptr);
    ~PantallaJuego() override;

private:
    Partida* partidaActual;
    QGraphicsRectItem*** ptrBloques;
    QGraphicsRectItem* itemPlataforma;
    QGraphicsEllipseItem** itemsPelotas;
    PowerUp** ptrPowerUps;
    QGraphicsRectItem** itemsPowerUps;
    double velocidad;
    QTimer* timerJuego;
    QElapsedTimer cronometro;
    int cantidadPowerUps;
    int contadorPlataformaGrande;
    int anchoOriginalPlataforma;

    void actualizarJuego();
    void manejarFinDePartida();
    //movimiento
    bool moverIzq;
    bool moverDer;
    bool esperando;
    void lanzarPelota();
    void manejarColisiones();
    void manejarColisionesPelota(Pelota* pelota);
    void actualizarPosiciones();
    void rebotarEnPlataforma(Pelota* pelota);

    void intentarSoltarPowerUp(int x, int y);
    void actualizarPowerUps();
    void aplicarPowerUp(PowerUp* power);
    void eliminarPowerUp(int indice);


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