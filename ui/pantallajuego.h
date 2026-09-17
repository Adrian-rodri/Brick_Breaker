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
#include <QSoundEffect>

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
    QGraphicsPixmapItem** itemsPelotas;
    QGraphicsRectItem** itemsPowerUps;
    QGraphicsEllipseItem** itemsOrbes;
    QTimer* timerJuego;
    QElapsedTimer cronometro;
    int cantidadPowerUps;
    int cantidadOrbes;
    int monedasAcumuladas;//moverlo a perfilprogrseo despues
    EstadisticasJugador stats;
    bool enPausa;
    void togglePausa();

    void actualizarJuego();
    void manejarFinDePartida();
    void regenerarNivel(bool fueGameOver);
    //effects
    QSoundEffect* sonidosToque[3];
    int indiceToque= 0;
    QSoundEffect* sonidoDestruir[3];
    int indiceDestruir=0;
    QSoundEffect* sonidoBloqueado[3];
    int indiceBloquead=0;
    QSoundEffect* sonidoMoneda[3];
    int indiceMoneda=0;
    void cargarSonidos();
    //movimiento
    bool moverIzq;
    bool moverDer;
    bool esperando;
    void actualizarPosiciones();

    void agregarPowerUp(PowerUp* nuevoPower);
    void eliminarPowerUp(int indice);
    void sincronizarPelotasExtra();

    void agregarOrbe(int x,int y, int valor);
    void eliminarOrbe(int indice);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    //hud
    QLabel* lblVidas;
    QLabel* lblTiempo;
    QLabel* lblBloques;
    QLabel* lblMonedas;
    QLabel* lblAviso;
    int totalBloques;
    void cargarHUD(QVBoxLayout* layoutVertical);
    void actualizarHUD();

    //caida
    bool animandoEntrada;
    int offsetAnimacion;
    void actualizarPosicionesBloques();
    void limpiarItemsPowerUpsYOrbes();
    double escalaJugador;
    bool animandoPelota;
    double plataformaXInicio;
    double plataformaXDestino;
    //elemntos ui
    int filas;
    int col;
    QGraphicsScene* escena;
    QGraphicsView* vista;

    QPixmap spriteSimple;
    QPixmap spriteReforzado;
    QPixmap spriteBlindado;
    QPixmap spritePelota;

    QPixmap obtenerSprite(Bloque* bloque, int fila);
    void cargarUi();
    void liberarBloques();
    void dibujarBloques();
    void dibujarPlataforma();
    void dibujarPelotas();
    void guardarProgresoActual();
};
#endif // PANTALLAJUEGO_H