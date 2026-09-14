#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include "partida.h"
#include "powerup.h"
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
public:
    MotorJuego(int nivel);
    ~MotorJuego();
    Partida* partidaActual;

    void actualizarJuego(bool movIzq, bool movDer, bool esperando);
    void manejarColisiones();
    void manejarColisionesPelota(Pelota* pelota);
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

    PowerUp** getPowerUps() const;
    int getCantidadPowerUps() const;
};

#endif // MOTORJUEGO_H
