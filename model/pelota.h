#ifndef PELOTA_H
#define PELOTA_H

class Pelota
{
private:
    int posX, posY;
    int diametro;
    int velocidadX;
    int velocidadY;
public:
    Pelota(int posX, int posY, int diametro);
    void mover();
    void setVelocidad(int velX,int velY);

    int getX() const;
    int getY() const;
    int getDiametro() const;
    int getVelocidadX()const;
    int getVelocidadY()const;

    void setPosicion(int nuevaX, int nuevaY);
    void invertirVelocidadX();
    void invertirVelocidadY();
};

#endif // PELOTA_H
