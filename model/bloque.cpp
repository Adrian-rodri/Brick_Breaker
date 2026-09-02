#include "bloque.h"
#include <QBrush>
#include <QPen>
#include "constantes.h"
Bloque::Bloque(TIPO_BLOQUE tipoBloque,qreal posX, qreal posY)
    : QGraphicsRectItem(0,0,BRICK_ANCHO,BRICK_ALTO){
    //Bloque hereda de QGracpichsRectItem para sincronizar mas facil la UI
    this->tipoBloque=tipoBloque;
    golpesRestantes= getGolpes();
    setPos(10+(posX*BRICK_ANCHO),6+(posY*BRICK_ALTO));
    setBrush(getColor());
    setPen(QPen(QColor(35, 61, 77)));
}
void Bloque::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRoundedRect(rect(), 7, 7);
}
void Bloque::recibirGolpe(){
    if(tipoBloque==INDESTRUCTIBLE){
        return;
    }
    golpesRestantes--;
    setBrush(getColor());
}
bool Bloque::estaRoto(){
    if(tipoBloque==INDESTRUCTIBLE){
        return false;
    }
    return golpesRestantes<=0;
}
//getters
TIPO_BLOQUE Bloque::getTipoBloque() const{
    return tipoBloque;
}
int Bloque::getGolpes() const{
    switch(tipoBloque){
    case SIMPLE:{
        return 1;
    }case REFORZADO:{
        return 2;
    }case INDESTRUCTIBLE:{
        return -1;
    }
    }
    return 0;
}
int Bloque::getPuntos() const{
    switch(tipoBloque){
    case SIMPLE:{
        return 10;
    }case REFORZADO:{
        return 20;
    }case INDESTRUCTIBLE:{
        return 0;
    }
    }
    return 0;
}
QBrush Bloque::getColor() const{
    QBrush color;
    switch(tipoBloque){
    case SIMPLE:{
        color= QBrush(QColor(146, 238, 255));
        break;
    }case REFORZADO:{
        if(golpesRestantes==2){
            color= QBrush(QColor(255,140,0));
        }else{
            color= QBrush(QColor(204,58,99));
        }
        break;
    }case INDESTRUCTIBLE:{
        color= QBrush(Qt::gray);
        break;
    }
    }
    return color;
}
