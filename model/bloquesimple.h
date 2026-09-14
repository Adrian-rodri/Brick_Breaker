#ifndef BLOQUESIMPLE_H
#define BLOQUESIMPLE_H

#include "bloque.h"
class BloqueSimple : public Bloque
{
public:
    BloqueSimple(int posX, int posY);

    void recibirGolpe(const EstadisticasJugador& stats) override;
    int getValorMoneda() const override;
    QBrush getColor() const override;
    std::string getImagen()const override;
};

#endif // BLOQUESIMPLE_H
