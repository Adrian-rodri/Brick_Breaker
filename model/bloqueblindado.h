#ifndef BLOQUEBLINDADO_H
#define BLOQUEBLINDADO_H

#include "bloque.h"
class BloqueBlindado: public Bloque
{
public:
    BloqueBlindado(int posX, int posY);

    void recibirGolpe(const EstadisticasJugador& stats) override;
    int getValorMoneda() const override;
    QBrush getColor() const override;
    std::string getImagen()const override;
    int getFrameSprite(int fila) const override;
    int getFrameEstado() const override;
};

#endif // BLOQUEBLINDADO_H
