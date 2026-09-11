#include "powerup.h"

PowerUp::PowerUp(TIPO_POWERUP tipo, int posX, int posY){
    this->tipo=tipo;
    this->posX=posX;
    this->posY=posY;
    ancho=20;
    alto=20;
    velocidadCaida=3;
}
void PowerUp::caer(){
    posY+=velocidadCaida;
}
void PowerUp::setPosicion(int nuevaX,int nuevaY){
    posX=nuevaX;
    posY=nuevaY;
}
int PowerUp::getX() const{ return posX; }
int PowerUp::getY() const{ return posY; }
int PowerUp::getAncho() const{ return ancho; }
int PowerUp::getAlto() const{ return alto; }
TIPO_POWERUP PowerUp::getTipo() const{ return tipo; }

QBrush PowerUp::getColor() const{
    switch(tipo){
    case BOLA_EXTRA:
        return QBrush(QColor(255,255,255)); //blanco
        case VIDA_EXTRA:
        return QBrush(QColor(220,20,60)); //rojo
        case PLATAFORMA_GRANDE:
            return QBrush(QColor(70,130,180)); //azul
    }
    return QBrush(Qt::white);
}