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
    return 15;
}
QBrush BloqueBlindado::getColor()const{
    return QBrush(QColor(117,125,111));
}
std::string BloqueBlindado::getImagen()const{
    return "";
}

