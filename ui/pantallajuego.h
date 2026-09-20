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
#include <QMediaPlayer>
#include <QAudioOutput>

#include "partida.h"
#include "powerup.h"
#include "motorjuego.h"
class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    PantallaJuego(int nivel, bool modoHistoria, QWidget* parent = nullptr);
    PantallaJuego(Partida* partidaCargada, QWidget* parent = nullptr);
    ~PantallaJuego() override;

private:
    MotorJuego* motor;
    bool modoHistoria;
    bool nivelDesbloqueado;
    QGraphicsRectItem*** ptrBloques;
    QGraphicsRectItem* itemPlataforma;
    QGraphicsPixmapItem** itemsPelotas;
    QGraphicsRectItem** itemsPowerUps;
    QGraphicsEllipseItem** itemsOrbes;
    QTimer* timerJuego;
    QElapsedTimer cronometro;
    int cantidadPowerUps;
    int cantidadOrbes;
    double monedasAcumuladas;
    double creditosIniciales;
    EstadisticasJugador stats;
    bool enPausa;
    void togglePausa();

    void actualizarJuego();
    void manejarFinDePartida();
    void regenerarNivel(bool fueGameOver);

    //audio
    struct EfectoAudio{
        QMediaPlayer* player= nullptr;
        QAudioOutput* output= nullptr;
    };
    EfectoAudio sonidosToque[3];
    int indiceToque= 0;
    EfectoAudio sonidoDestruir[3];
    int indiceDestruir=0;
    EfectoAudio sonidoBloqueado[3];
    int indiceBloquead=0;
    EfectoAudio sonidoMoneda[3];
    int indiceMoneda=0;
    void cargarSonidos();
    void crearEfectoSonido(EfectoAudio& efecto, const QUrl& fuente, float volumen);
    void reconstruirSonido(EfectoAudio& efecto, const QUrl& fuente, float volumen);
    void reconstruirTodosLosSonidos();
    void reproducirSonido(EfectoAudio& efecto, int& indice, const QUrl& fuente, float volumen);
    void verificarSonidos();
    int contadorVerificacionSonidos= 0;
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