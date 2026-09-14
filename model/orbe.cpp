#include "orbe.h"

Orbe::Orbe(int posX, int posY, int valor){
    this->posX= posX;
    this->posY= posY;
    this->valor= valor;
    ancho= 14;
    alto= 14;
    velocidadCaida= 3;
}
void Orbe::caer(){
    posY+= velocidadCaida;
}
int Orbe::getX() const{
    return posX;
}
int Orbe::getY() const{
    return posY;
}
int Orbe::getAncho() const{
    return ancho;
}
int Orbe::getAlto() const{
    return alto;
}
int Orbe::getValor() const{
    return valor;
}
QBrush Orbe::getColor() const{
    return QBrush(QColor(255, 215, 0)); //dorado
}