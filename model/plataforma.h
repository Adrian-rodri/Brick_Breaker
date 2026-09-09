#ifndef PLATAFORMA_H
#define PLATAFORMA_H

class Plataforma {
private:
    int posX,posY;
    int ancho;
    int alto;
    int velocidad;

public:
    Plataforma(int posX, int posY, int anchoInicial, int altoInicial);

    void moverIzquierda();
    void moverDerecha();

    void setAncho(int nuevoAncho);
    void setPosicion(int nuevaX, int nuevaY);

    int getX()const;
    int getY() const;
    int getAncho() const;
    int getAlto()const;
};

#endif // PLATAFORMA_H