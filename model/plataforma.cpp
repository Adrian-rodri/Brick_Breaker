#include "plataforma.h"
#include "constantes.h"
#include <QBrush>
#include <QPen>
//cambiar herencia a normal, redibujando los items
Plataforma::Plataforma(qreal posX, qreal posY):QGraphicsRectItem(0,0,PLATAFORMA_ANCHO,PLATAFORMA_ALTO),
    velocidadMovimiento(20){
    setPos(posX,posY);
    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::black));
}
void Plataforma::moverIzquierda(){
    qreal nuevaX= x()-velocidadMovimiento;
    if(nuevaX>=LIMITE_PANTALLA){
        setPos(LIMITE_PANTALLA,y());
    }else{
        setPos(nuevaX,y());
    }
}
