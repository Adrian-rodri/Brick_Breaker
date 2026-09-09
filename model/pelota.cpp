#include "pelota.h"
#include <QBrush>
#include <QPen>

Pelota::Pelota(int posX, int posY, int diametro){
    this->posX=posX;
    this->posY=posY;
    this->diametro= diametro;
    velocidadX=3;
    velocidadY=-3;
}
void Pelota::mover(){
    posX+=velocidadX;
    posY+=velocidadY;
}
void Pelota::setVelocidad(int velX, int velY){
    velocidadX= velX;
    velocidadY= velY;
}
void Pelota::invertirVelocidadX(){
    velocidadX= -velocidadX;
}
void Pelota::invertirVelocidadY(){
    velocidadY= -velocidadY;
}
void Pelota::setPosicion(int nuevaX, int nuevaY) {
    posX=nuevaX;
    posY= nuevaY;
}
//getters
int Pelota::getX()const {
    return posX;
}
int Pelota::getY()const{
    return posY;
}
int Pelota::getDiametro() const{
    return diametro;
}
int Pelota::getVelocidadX() const{
    return velocidadX;
}
int Pelota::getVelocidadY() const{
    return velocidadY;
}

