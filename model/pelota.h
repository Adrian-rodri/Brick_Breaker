#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsEllipseItem>
class Pelota : QGraphicsEllipseItem
{
private:
    qreal velocidadX;
    qreal velocidadY;
public:
    Pelota(qreal posX, qreal posY, qreal diametro);
    void mover();
    void setVelocidad(qreal velX,qreal velY);

    qreal getVelocidadX()const;
    qreal getVelocidadY()const;
    void invertirVelocidadX();
    void invertirVelocidadY();
};

#endif // PELOTA_H
