#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>

#include "partida.h"

class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaJuego(Partida* partidaActual,QWidget* parent = nullptr);
    ~PantallaJuego() override;
private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    Partida* partidaActual;

};

#endif // PANTALLAJUEGO_H