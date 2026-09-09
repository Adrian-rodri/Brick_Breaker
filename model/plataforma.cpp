#include "plataforma.h"
#include "constantes.h"

Plataforma::Plataforma(int posX, int posY, int _ancho, int _alto){
    this->posX= posX;
    this->posY= posY;
    ancho=_ancho;
    alto=_alto;
    velocidad= 7;
}

void Plataforma::moverIzquierda(){
    posX-= velocidad;
    if(posX<0){
        posX=0;
    }
}

void Plataforma::moverDerecha(){
    posX+= velocidad;
    if((posX+ancho)>LIMITE_PANTALLA){
        posX= LIMITE_PANTALLA -ancho;
    }
}

void Plataforma::setAncho(int nuevoAncho){
    ancho= nuevoAncho;
}

void Plataforma::setPosicion(int nuevaX, int nuevaY) {
    posX= nuevaX;
    posY= nuevaY;
}

int Plataforma::getX() const {
    return posX;
}

int Plataforma::getY() const {
    return posY;
}

int Plataforma::getAncho() const {
    return ancho;
}

int Plataforma::getAlto() const {
    return alto;
}