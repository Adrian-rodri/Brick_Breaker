#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsRectItem>
class Plataforma : QGraphicsRectItem
{
private:
    qreal velocidadMovimiento;
public:
    Plataforma(qreal posX, qreal posY);

    void moverIzquierda();
    void moverDerecha();

    void ajustarAncho(qreal nuevoAncho);
};

#endif // PLATAFORMA_H
