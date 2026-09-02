#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
enum TIPO_BLOQUE{
    SIMPLE,REFORZADO,INDESTRUCTIBLE
};

class Bloque : public QGraphicsRectItem
{
private:
TIPO_BLOQUE tipoBloque;
int golpesRestantes;

public:
    Bloque(TIPO_BLOQUE tipoBloque,qreal posX, qreal posY);
    void recibirGolpe();
    bool estaRoto();
    TIPO_BLOQUE getTipoBloque() const;
    int getPuntos() const;
    int getGolpes() const;
    QBrush getColor() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
};

#endif // BLOQUE_H
