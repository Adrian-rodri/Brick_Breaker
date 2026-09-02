#include "pantallajuego.h"
#include <QVBoxLayout>
#include <QBrush>
#include <QRandomGenerator>

PantallaJuego::PantallaJuego(Partida* partidaActual,QWidget* parent)
    : QWidget(parent){
    this->partidaActual=partidaActual;
    this->setStyleSheet("background-color: #000000;");
    QVBoxLayout* layoutVertical= new QVBoxLayout(this);
    QHBoxLayout* layoutCentro= new QHBoxLayout();

    escena= new QGraphicsScene(0,0,800,480,this);
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
    Nivel* nivel= partidaActual->getNivel();
    for(int i=0;i<nivel->getFilas();i++){
        for(int j=0;j<nivel->getColumnas();j++){
            escena->addItem(nivel->getMatriz()[i][j]);
        }
    }
}

PantallaJuego::~PantallaJuego(){
}