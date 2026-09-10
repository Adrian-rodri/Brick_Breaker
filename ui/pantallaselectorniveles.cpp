#include "pantallaselectorniveles.h"
#include "ventanaprincipal.h"
#include "pantallajuego.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <string>
using namespace std;
PantallaSelectorNiveles::PantallaSelectorNiveles(QWidget* parent):QWidget(parent){
    cargarUi();
}
void PantallaSelectorNiveles::cargarUi(){
    this->setMinimumSize(600,400);
    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);
    QWidget* centro= new QWidget();
    QHBoxLayout* layout= new QHBoxLayout(centro);
    for(int i=1;i<=3;i++){
        QPushButton* btnNivel= new QPushButton("Nivel #"+QString::number(i));
        btnNivel->setStyleSheet("QPushButton {"
                                "   background-color: #2E86AB;"
                                "   color: white;"
                                "   font-size: 18px;"
                                "   font-weight: bold;"
                                "   border-radius: 10px;"
                                "   padding: 10px 20px;"
                                "}"
                                "QPushButton:hover {"
                                "   background-color: #3AA0CC;"
                                "}"
                                "QPushButton:pressed {"
                                "   background-color: #1B5E7A;"
                                "}");

        connect(btnNivel,&QPushButton::clicked,this,[this,i](){
            irAlNivel(i);
        });
        layout->addWidget(btnNivel);
    }
    QHBoxLayout* layoutHor= new QHBoxLayout();
    layoutHor->addStretch();
    layoutHor->addWidget(centro);
    layoutHor->addStretch();
    layoutPrincipal->addStretch();
    layoutPrincipal->addLayout(layoutHor);
    layoutPrincipal->addStretch();


}
void PantallaSelectorNiveles::irAlNivel(int numLvl){
    VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
    PantallaJuego* pantallaJuego = new PantallaJuego(numLvl);
    ventana->cambiarPantalla(pantallaJuego);
}
