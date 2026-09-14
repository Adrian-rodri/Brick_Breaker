#include "bloque.h"
Bloque::Bloque(TIPO_BLOQUE tipoBloque, int posX, int posY){
    this->tipoBloque= tipoBloque;
    this->posX= posX;
    this->posY= posY;
    golpesRestantes= 0;
}
Bloque::~Bloque(){
}
int Bloque::getPosX() const{
    return posX;
}
int Bloque::getPosY() const{
    return posY;
}
TIPO_BLOQUE Bloque::getTipoBloque() const{
    return tipoBloque;
}
bool Bloque::estaRoto() const{
    return golpesRestantes<=0;
}