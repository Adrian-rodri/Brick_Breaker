#ifndef PARTIDA_H
#define PARTIDA_H

#include "nivel.h"
class Partida
{
private:
    Nivel* nivelActual;
public:
    Partida(Nivel* nivelActual);
    Nivel* getNivel();
};

#endif // PARTIDA_H
