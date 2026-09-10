#include "partida.h"
#include "constantes.h"

Partida::Partida(int nivel) {
    vidas= 300;
    puntaje= 0;
    numNivelAct= nivel;
    nivelActual= new Nivel(numNivelAct);
    plataforma= new Plataforma((LIMITE_PANTALLA - PLATAFORMA_ANCHO)/2,440,
        PLATAFORMA_ANCHO,PLATAFORMA_ALTO);
    pelota= new Pelota(LIMITE_PANTALLA/2, 420, 15);
}

Partida::~Partida() {
    delete nivelActual;
    nivelActual= nullptr;
    delete plataforma;
    plataforma= nullptr;
    delete pelota;
    pelota= nullptr;
}

void Partida::sumarPuntos(int puntos){
    puntaje+= puntos;
}
void Partida::perderVida(){
    vidas--;
}
bool Partida::estaTerminada(){
    return vidas<=0;
}
bool Partida::nivelCompletado(){
    return nivelActual->getBloquesRestantes()<=0;
}

int Partida::getVidas(){
    return vidas;
}
int Partida::getPuntaje(){
    return puntaje;
}
Nivel* Partida::getNivel() const{
    return nivelActual;
}
Plataforma* Partida::getPlataforma()const{
    return plataforma;
}
Pelota* Partida::getPelota() const {
    return pelota;
}