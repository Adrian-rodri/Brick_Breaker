#include "bloqueblindado.h"

BloqueBlindado::BloqueBlindado(int posX, int posY):
    Bloque(BLINDADO,posX,posY){
    golpesRestantes=6;
}
void BloqueBlindado::recibirGolpe(const EstadisticasJugador& stats){
    if(!stats.tieneMejoraArmadura){
        return;
    }
    golpesRestantes-= stats.damage;
}
int BloqueBlindado::getValorMoneda() const{
    return 5;
}
QBrush BloqueBlindado::getColor()const{
    return QBrush(QColor(117,125,111));
}
std::string BloqueBlindado::getImagen()const{
    return "";
}

int BloqueBlindado::getFrameSprite(int fila) const{
    return fila % 5;
}
int BloqueBlindado::getFrameEstado() const{
    switch(golpesRestantes){
    case 1:{
        return 5;
    }case 2:{
        return 4;
    }case 3:{
        return 3;
    }case 4:{
        return 2;
    }case 5:{
        return 1;
    }case 6:{
        return 0;
    }
    default:{
        return 0;
    }
    }
}