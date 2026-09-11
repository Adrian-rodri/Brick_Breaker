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
        return 4;
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
        color= QBrush(QColor(252, 173, 56));
        break;
    }case REFORZADO:{
        switch(golpesRestantes){
        case 1:{
            color= QBrush(QColor(252, 173, 56));
            break;
        }case 2:{
            color= QBrush(QColor(235, 127, 49));
            break;
        }case 3:{
            color= QBrush(QColor(228, 87, 66));
            break;
        }case 4:{
            color= QBrush(QColor(151, 40, 40));
            break;
        }
        }
        break;
    }case INDESTRUCTIBLE:{
        color= QBrush(QColor(117, 125, 111));
        break;
    }
    }
    return color;
}
