#include "partida.h"

Partida::Partida(Nivel* nivelActual) {
    this->nivelActual=nivelActual;
}
Nivel* Partida::getNivel(){
    return nivelActual;
}