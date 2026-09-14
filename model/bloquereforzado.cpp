#include "bloquereforzado.h"

BloqueReforzado::BloqueReforzado(int posX, int posY):
    Bloque(REFORZADO,posX,posY){
    golpesRestantes=4;
}
void BloqueReforzado::recibirGolpe(const EstadisticasJugador& stats){
    golpesRestantes-=stats.damage;
}
int BloqueReforzado::getValorMoneda() const{
    return 6;
}
QBrush BloqueReforzado::getColor()const{
    QBrush color;
    switch(golpesRestantes){
        case 1:{
            color=QBrush(QColor(252, 173, 56));
            break;
        }case 2:{
            color=QBrush(QColor(235, 127, 49));
            break;
        }case 3:{
            color=QBrush(QColor(228, 87, 66));
            break;
        }case 4:{
            color=QBrush(QColor(151, 40, 40));
            break;
        }default:
            color= QBrush(QColor(252, 173, 56));
            break;
    }
    return color;
}
std::string BloqueReforzado::getImagen()const{
    return "";
}
