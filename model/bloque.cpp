#include "bloque.h"
#include <QBrush>
#include <QPen>
Bloque::Bloque(TIPO_BLOQUE tipoBloque,int posX, int posY){
    this->tipoBloque=tipoBloque;
    golpesRestantes= getGolpes();
    this->posX=posX;
    this->posY=posY;
}
void Bloque::recibirGolpe(){
    if(tipoBloque==INDESTRUCTIBLE){
        return;
    }
    golpesRestantes--;
}
bool Bloque::estaRoto()const{
    if(tipoBloque==INDESTRUCTIBLE){
        return false;
    }
    return golpesRestantes<=0;
}
//getters
int Bloque::getPosX() const{
    return posX;
}
int Bloque::getPosY() const{
    return posY;
}
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
int Bloque::getPuntos(){
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
            color= QBrush(QColor(255, 128, 199));
        }else{
            color= QBrush(QColor(146, 238, 255));
        }
        break;
    }case INDESTRUCTIBLE:{
        color= QBrush(Qt::gray);
        break;
    }
    }
    return color;
}
