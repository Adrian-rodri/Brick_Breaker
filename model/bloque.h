#ifndef BLOQUE_H
#define BLOQUE_H
#include <QBrush>
#include <string>
#include "EstadisticasJugador.h"
enum TIPO_BLOQUE{
    SIMPLE,REFORZADO,BLINDADO
};
class Bloque
{
protected:
    TIPO_BLOQUE tipoBloque;
    int golpesRestantes;
    int posX, posY;
public:
    Bloque(TIPO_BLOQUE tipoBloque,int posX, int posY);
    virtual ~Bloque();
    int getPosX() const;
    int getPosY() const;

    bool estaRoto() const;
    TIPO_BLOQUE getTipoBloque() const;
    virtual void recibirGolpe(const EstadisticasJugador& stats)=0;
    virtual int getValorMoneda() const=0;
    virtual QBrush getColor() const=0;
    virtual std::string getImagen()const=0;
    virtual int getFrameSprite(int fila) const=0;
    virtual int getFrameEstado() const=0;
};
#endif // BLOQUE_H