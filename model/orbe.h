#ifndef ORBE_H
#define ORBE_H
#include <QBrush>

class Orbe
{
private:
    int posX, posY;
    int ancho,alto;
    int valor;
    int velocidadCaida;
public:
    Orbe(int posX, int posY, int valor);
    void caer();
    int getX() const;
    int getY() const;
    int getAncho() const;
    int getAlto() const;
    int getValor() const;
    QBrush getColor() const;
};

#endif // ORBE_H
