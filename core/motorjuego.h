#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include "partida.h"
#include "powerup.h"
#include "orbe.h"
#include "EstadisticasJugador.h"
class MotorJuego
{
private:

    double velocidad;

    bool seDestruyoBloque;
    int filaDestruida;
    int colDestruida;

    bool seTocoBloque;
    int filaTocada;
    int colTocada;

    bool huboNuevoPowerUp;
    int posXNuevoPower;
    int posYNuevoPower;
    TIPO_POWERUP tipoNuevoPower;

    bool seEliminoPowerUp;
    int idxPowerUpEliminado;

    bool seAplicoPowerUp;
    TIPO_POWERUP tipoPowerUpAplicado;

    PowerUp** ptrPowerUps;
    int cantidadPowerUps;
    int contadorPlataformaGrande;
    int anchoOriginalPlataforma;

    void eliminarPowerUp(int indice);

    Orbe** ptrOrbes;
    int cantidadOrbes;

    bool huboOrbeNuevo;
    int posXNuevoOrbe;
    int posYNuevoOrbe;
    int valorNuevoOrbe;

    bool seEliminoOrbe;
    int idxOrbeEliminado;

    bool seRecogioOrbe;
    int valorOrbeRecogido;

    void eliminarOrbe(int indice);
public:
    MotorJuego(int nivel);
    ~MotorJuego();
    Partida* partidaActual;

    void actualizarJuego(bool movIzq, bool movDer, bool esperando,const EstadisticasJugador& stats);
    void manejarColisiones(const EstadisticasJugador& stats);
    void manejarColisionesPelota(Pelota* pelota, const EstadisticasJugador& stats);
    void rebotarEnPlataforma(Pelota *pelota);
    void lanzarPelotaInicial();

    void actualizarPowerUps();
    void intentarSoltarPowerUp(int x, int y);
    void aplicarPowerUp(PowerUp* powerUp);
    void resetearEventos();

    bool huboDestruccion(int& fila, int& col);
    bool huboToque(int& fila, int& col);
    Partida* getPartida() const;

    PowerUp* huboPowerUpNuevo();
    bool huboPowerUpEliminado(int& indice);

    bool huboPowerUpAplicado(TIPO_POWERUP& tipo);

    void actualizarOrbes();
    void soltarOrbe(int x, int y, int valor);
    void aplicarOrbe(Orbe* orbe);

    bool huboNuevoOrbe(int& x, int& y, int& valor);
    bool huboOrbeEliminado(int& indice);
    bool huboOrbeRecogido(int& valor);

    void limpiarPowerUpsYOrbes();

    Orbe** getOrbes() const;
    PowerUp** getPowerUps() const;
    int getCantidadPowerUps() const;
};

#endif // MOTORJUEGO_H
