#include "pantallamenuprincipal.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include "pantallajuego.h"
#include "partida.h"
#include "nivel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

PantallaMenuPrincipal::PantallaMenuPrincipal(QWidget *parent):QWidget(parent){
    cargarUI();
}

void PantallaMenuPrincipal::cargarUI(){
    this->setMinimumSize(600,600);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout *layoutPrincipal=new QVBoxLayout(this);
    QWidget *contenedorMenu=new QWidget();
    contenedorMenu->setStyleSheet("border-radius: 10px;"
                                  "background-color: transparent;");
    contenedorMenu->setFixedSize(500,600);

    QVBoxLayout *layoutMenu=new QVBoxLayout(contenedorMenu);

    titulo= new QLabel("");
    QPixmap logo(":/assets/titulo.png");
    titulo->setPixmap(logo.scaled(360,180,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("background-color: transparent; "
                          "margin-bottom: 5px;");
    btnJugar=new QPushButton("Jugar",this);
    btnNiveles=new QPushButton("Niveles",this);
    btnRecords=new QPushButton("Records",this);
    btnSalir=new QPushButton("Salir ",this);
    btnAyuda=new QPushButton("Ayuda ",this);
    btnLogros=new QPushButton("Logros ",this);
    btnOpciones=new QPushButton("Opciones",this);

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
    btnNiveles->setStyleSheet(estiloBotones);
    btnRecords->setStyleSheet(estiloBotones);
    btnSalir->setStyleSheet(estiloBotones);
    btnAyuda->setStyleSheet(estiloBotones);
    btnLogros->setStyleSheet(estiloBotones);
    btnOpciones->setStyleSheet(estiloBotones);

    btnJugar->setFixedSize(200, 60);
    btnNiveles->setFixedSize(200, 60);
    btnRecords->setFixedSize(200, 60);
    btnSalir->setFixedSize(200, 60);
    btnAyuda->setFixedSize(50,50);
    btnLogros->setFixedSize(50,50);
    btnOpciones->setFixedSize(50, 50);

    layoutMenu->addWidget(titulo);
    layoutMenu->addWidget(btnJugar, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnNiveles, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnRecords, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnSalir, 0, Qt::AlignHCenter);

    layoutMiniBtns=new QHBoxLayout();
    layoutMiniBtns->setAlignment(Qt::AlignHCenter);
    layoutMiniBtns->setSpacing(15);

    layoutMiniBtns->addWidget(btnAyuda);
    layoutMiniBtns->addWidget(btnLogros);
    layoutMiniBtns->addWidget(btnOpciones);

    layoutMenu->addLayout(layoutMiniBtns);

    layoutPrincipal->addStretch();
    QHBoxLayout *layoutCentrado=new QHBoxLayout();
    layoutCentrado->addStretch();
    layoutCentrado->addWidget(contenedorMenu);

    layoutCentrado->addStretch();

    layoutPrincipal->addLayout(layoutCentrado);
    layoutPrincipal->addStretch();

    connect(btnJugar,&QPushButton::clicked,this,&PantallaMenuPrincipal::irAlJuego);
}

void PantallaMenuPrincipal::irAlJuego(){
    VentanaPrincipal* ventana=(VentanaPrincipal*)this->window();
    partida= new Partida(new Nivel(2));
    PantallaJuego *pantallaJuego= new PantallaJuego(partida);
    ventana->cambiarPantalla(pantallaJuego);
}

PantallaMenuPrincipal::~PantallaMenuPrincipal(){

}