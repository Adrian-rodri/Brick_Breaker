#include "bloquesimple.h"

BloqueSimple::BloqueSimple(int posX, int posY):
    Bloque(SIMPLE,posX,posY){
    golpesRestantes=1;
}
void BloqueSimple::recibirGolpe(const EstadisticasJugador& stats){
    golpesRestantes--;
}
int BloqueSimple::getValorMoneda() const{
    return 1;
}
QBrush BloqueSimple::getColor() const{
    return QBrush(QColor(252, 173, 56));
}
std::string BloqueSimple::getImagen() const{
    return "";
}