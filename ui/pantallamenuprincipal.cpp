#include "pantallamenuprincipal.h"
#include "constantes.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

PantallaMenuPrincipal::PantallaMenuPrincipal(QWidget *parent):QWidget(parent){
    cargarUI();
}

void PantallaMenuPrincipal::cargarUI(){
    this->setMinimumSize(800,600);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout *layoutPrincipal=new QVBoxLayout(this);

    QWidget *contenedorMenu=new QWidget();
    contenedorMenu->setStyleSheet("border-radius: 10px;"
                                  "background-color: #1e1e1e;");
    contenedorMenu->setFixedSize(300,450);

    QVBoxLayout *layoutMenu=new QVBoxLayout(contenedorMenu);

    lblTitulo=new QLabel("BRICK\nBREAKER", this);
    btnJugar=new QPushButton("Jugar",this);
    btnInstrucciones=new QPushButton("Opciones",this);
    btnNiveles=new QPushButton("Niveles",this);
    btnRecords=new QPushButton("Records",this);
    btnSalir=new QPushButton("Salir ",this);

    lblTitulo->setAlignment(Qt::AlignCenter);

    lblTitulo->setStyleSheet("font-size: 50px;"
                             "color : "+COLORFONT+";"
                                           "font-family: 'Gill Sans MT Condensed';"
                                           "background-color: transparent;");

    QString estiloBotones=
        "QPushButton {"
        "background-color: transparent;"
        "color: "+COLORFONT+";"
        "font-size: 20px;"
        "font-weight: bold;"
        "border-radius: 10px;"
        "border: 2px solid white;"
        "padding: 15px;"
        "}"
        "QPushButton:hover {"
        "background-color: "+COLORBOTONHOVER+";"
        "}"
        "QPushButton:pressed {"
        "background-color: "+COLORBOTONPRESSED+";"
        "}";

    btnJugar->setStyleSheet(estiloBotones);
    btnInstrucciones->setStyleSheet(estiloBotones);
    btnNiveles->setStyleSheet(estiloBotones);
    btnRecords->setStyleSheet(estiloBotones);
    btnSalir->setStyleSheet(estiloBotones);

    layoutMenu->addWidget(lblTitulo);
    layoutMenu->addWidget(btnJugar);
    layoutMenu->addWidget(btnInstrucciones);
    layoutMenu->addWidget(btnNiveles);
    layoutMenu->addWidget(btnRecords);
    layoutMenu->addWidget(btnSalir);
    layoutMenu->addStretch();

    layoutPrincipal->addStretch();

    QHBoxLayout *layoutCentrado=new QHBoxLayout();
    layoutCentrado->addStretch();
    layoutCentrado->addWidget(contenedorMenu);
    layoutCentrado->addStretch();

    layoutPrincipal->addLayout(layoutCentrado);
    layoutPrincipal->addStretch();
}

PantallaMenuPrincipal::~PantallaMenuPrincipal(){

}