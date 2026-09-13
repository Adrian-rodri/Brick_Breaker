#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include "partida.h"
#include "powerup.h"
class MotorJuego
{
private:
    Partida* partidaActual;
    double velocidad;

    PowerUp** ptrPowerUps;
    int cantidadPowerUps;
    int contadorPlataformaGrande;
    int anchoOriginalPlataforma();

public:
    MotorJuego(int nivel);
    ~MotorJuego();

    void actualizarJuego(bool movIzq, bool movDer);
    void manejarColisiones();
    void manejarColisionesPelota(Pelota* pelota);
    void rebotarEnPlataforma(Pelota *pelota);
    void actualizarPowerUps();
    void intentarSoltarPowerUp(int x, int y);
    void aplicarPowerUp(PowerUp* powerUp);
    bool huboDestruccion(int& fila, int* col);
    Partida* getPartida() const;
};

#endif // MOTORJUEGO_H
