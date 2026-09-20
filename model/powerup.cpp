#include "powerup.h"
#include <QPixmap>

PowerUp::PowerUp(TIPO_POWERUP tipo, int posX, int posY){
    this->tipo=tipo;
    this->posX=posX;
    this->posY=posY;
    ancho=20;
    alto=20;
    velocidadCaida=3;
}
void PowerUp::caer(){
    posY+=velocidadCaida;
}
void PowerUp::setPosicion(int nuevaX,int nuevaY){
    posX=nuevaX;
    posY=nuevaY;
}
int PowerUp::getX() const{
    return posX;
}
int PowerUp::getY() const{
    return posY;
}
int PowerUp::getAncho() const{
    return ancho;
}
int PowerUp::getAlto() const{
    return alto;
}
TIPO_POWERUP PowerUp::getTipo() const{
    return tipo;
}

QBrush PowerUp::getColor() const{
    QPixmap skin;
    switch(tipo){
    case BOLA_EXTRA:
        skin.load(":/assets/bolaExtra.png");
        break;
    case VIDA_EXTRA:
        skin.load(":/assets/corazon.png");
        break;
    case PLATAFORMA_GRANDE:
        skin.load(":/assets/aumento.png");
        break;
    }
    if(!skin.isNull()){
        return QBrush(skin.scaled(ancho, alto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    return QBrush(Qt::white);
}