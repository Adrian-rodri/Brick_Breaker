#include "pelota.h"
#include <QBrush>
#include <QPen>

Pelota::Pelota(qreal posX, qreal posY, qreal diametro): QGraphicsEllipseItem(0,0,diametro,diametro),
    velocidadX(3),velocidadY(-3) {
    setPos(posX,posY);
    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::black));
}
void Pelota::mover(){
    setPos(x()+velocidadX,y()+velocidadX);
}
void Pelota::setVelocidad(qreal velX, qreal velY){
    velocidadX= velX;
    velocidadY= velY;
}
qreal Pelota::getVelocidadX() const{
    return velocidadX;
}
qreal Pelota::getVelocidadY() const{
    return velocidadY;
}
void Pelota::invertirVelocidadX(){
    velocidadX= -velocidadX;
}
void Pelota::invertirVelocidadY(){
    velocidadY= -velocidadY;
}
