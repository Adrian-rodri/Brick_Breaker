#ifndef PARTIDA_H
#define PARTIDA_H
#include "nivel.h"
#include "plataforma.h"
#include "pelota.h"

class Partida {
private:
    int vidas;
    int puntaje;
    int numNivelAct;
    Nivel* nivelActual;
    Plataforma* plataforma;
    Pelota** listaPelotas;
    int cantidadPelotas;

public:
    Partida(int nivel);
    ~Partida();
    void sumarPuntos(int puntos);
    void perderVida();
    void ganarVida();
    bool estaTerminada();
    bool nivelCompletado();
    void reiniciarVidasYPuntaje();
    int getVidas();
    int getPuntaje();
    Nivel* getNivel() const;
    Plataforma* getPlataforma() const;
    Pelota** getPelotas() const;
    int getCantidadPelotas() const;
    void agregarPelotaExtra(int posX,int posY);
    void eliminarPelota(int indice);
    void liberarPelotas();
};
#endif // PARTIDA_H