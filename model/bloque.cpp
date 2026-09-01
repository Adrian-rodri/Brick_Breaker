#include "bloque.h"
#include <QBrush>
#include <QPen>
Bloque::Bloque(TIPO_BLOQUE tipoBloque,qreal posX, qreal posY)
    : QGraphicsRectItem(0,0,50,20){
    //Bloque hereda de QGracpichsRectItem para sincronizar mas facil la UI
    this->tipoBloque=tipoBloque;
    golpesRestantes= getGolpes();
    setPos(posX,posY);
    setBrush(getColor());
    setPen(QPen(Qt::white));
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
        color= QBrush(Qt::green);
        break;
    }case REFORZADO:{
        if(golpesRestantes==2){
            color= QBrush(QColor(255,140,0));
        }else{
            color= QBrush(Qt::red);
        }
        break;
    }case INDESTRUCTIBLE:{
        color= QBrush(Qt::gray);
        break;
    }
    }
    return color;
}
