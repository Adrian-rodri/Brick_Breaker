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

class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaJuego(QWidget* parent = nullptr);
    ~PantallaJuego() override;
private:
    QGraphicsScene* escena;
    QGraphicsView* vista;

};

#endif // PANTALLAJUEGO_H