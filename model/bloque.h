#ifndef BLOQUE_H
#define BLOQUE_H
#include <QBrush>
enum TIPO_BLOQUE{
    SIMPLE,REFORZADO,INDESTRUCTIBLE
};
class Bloque
{
private:
    TIPO_BLOQUE tipoBloque;
    int golpesRestantes;
    int posX, posY;
public:
    Bloque(TIPO_BLOQUE tipoBloque,int posX, int posY);

    int getPosX() const;
    int getPosY() const;

    void recibirGolpe();
    bool estaRoto() const;
    TIPO_BLOQUE getTipoBloque() const;
    int getPuntos();
    int getGolpes() const;
    QBrush getColor() const;
};
#endif // BLOQUE_H