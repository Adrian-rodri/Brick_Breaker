#ifndef POWERUP_H
#define POWERUP_H
#include <QBrush>

enum TIPO_POWERUP{
    BOLA_EXTRA,
    VIDA_EXTRA,
    PLATAFORMA_GRANDE
    //todavia falta la tnt
};

class PowerUp
{
private:
    TIPO_POWERUP tipo;
    int posX, posY;
    int ancho, alto;
    int velocidadCaida;
public:
    PowerUp(TIPO_POWERUP tipo, int posX, int posY);

    void caer();
    void setPosicion(int nuevaX, int nuevaY);

    int getX() const;
    int getY() const;
    int getAncho() const;
    int getAlto() const;
    TIPO_POWERUP getTipo() const;
    QBrush getColor() const;
};
#endif // POWERUP_H