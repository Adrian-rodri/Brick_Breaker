#include "pantallajuego.h"
#include <QVBoxLayout>
#include <QBrush>
#include <QRandomGenerator>

PantallaJuego::PantallaJuego(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layoutVertical= new QVBoxLayout(this);
    QHBoxLayout* layoutCentro= new QHBoxLayout();

    escena= new QGraphicsScene(0,0,500,380,this);
    vista= new QGraphicsView(escena,this);

    QGraphicsRectItem* miRectangulo = escena->addRect(0, 0, 50, 11, QPen(Qt::white), QBrush(Qt::white));
    miRectangulo->setPos(10, 50);
    escena->addEllipse(10-5,50,11,11,QPen(Qt::white),QBrush(Qt::white));
    escena->addEllipse(50+10-5,50,11,11,QPen(Qt::white),QBrush(Qt::white));

    layoutCentro->addStretch();
    layoutCentro->addWidget(vista);
    layoutCentro->addStretch();

    layoutVertical->addStretch();
    layoutVertical->addLayout(layoutCentro);
    layoutVertical->addStretch();
}

PantallaJuego::~PantallaJuego(){
}