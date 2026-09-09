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
    Pelota* pelota;
public:
    Partida(int nivel);
    ~Partida();
    void sumarPuntos(int puntos);
    void perderVida();
    bool estaTerminada();
    bool nivelCompletado();
    int getVidas();
    int getPuntaje();
    Nivel* getNivel() const;
    Plataforma* getPlataforma() const;
    Pelota* getPelota() const;
};
#endif // PARTIDA_H