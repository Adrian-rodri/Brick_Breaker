#ifndef BLOQUEREFORZADO_H
#define BLOQUEREFORZADO_H

#include "bloque.h"
class BloqueReforzado : public Bloque
{
public:
    BloqueReforzado(int posX, int posY);

    void recibirGolpe(const EstadisticasJugador& stats) override;
    int getValorMoneda() const override;
    QBrush getColor() const override;
    std::string getImagen()const override;
    int getFrameSprite(int fila) const override;
    int getFrameEstado() const override;
};

#endif // BLOQUEREFORZADO_H
