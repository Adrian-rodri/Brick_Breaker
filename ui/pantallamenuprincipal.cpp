#include "pantallamenuprincipal.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include "pantallajuego.h"
#include "pantallaselectorniveles.h"
#include "pantallatienda.h"
#include "pantallarecords.h"
#include "pantallaopciones.h"
#include "pantallaayuda.h"
#include "PerfilProgreso.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>

PantallaMenuPrincipal::PantallaMenuPrincipal(QWidget *parent) : QWidget(parent) {
    cargarUI();
}

void PantallaMenuPrincipal::cargarUI() {
    this->setMinimumSize(600, 600);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout *layoutPrincipal= new QVBoxLayout(this);
    QWidget *contenedorMenu= new QWidget();
    contenedorMenu->setStyleSheet("border-radius: 10px;"
                                  "background-color: transparent;");
    contenedorMenu->setFixedSize(500, 600);

    QVBoxLayout *layoutMenu= new QVBoxLayout(contenedorMenu);

    titulo= new QLabel("");
    QPixmap logo(":/assets/titulo.png");
    titulo->setPixmap(logo.scaled(360, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("background-color: transparent; "
                          "margin-bottom: 5px;");

    lblCreditos = new QLabel("");
    lblCreditos->setAlignment(Qt::AlignCenter);
    lblCreditos->setStyleSheet("color: #FFD700;"
                               "font-size: 18px;"
                               "font-weight: bold;"
                               "background-color: transparent;");
    VentanaPrincipal* ventana= qobject_cast<VentanaPrincipal*>(this->window());
    if(ventana != nullptr && ventana->gestorUsers->usuarioActual != nullptr){
        lblCreditos->setText(QString("%1 🪙").arg(qRound(ventana->gestorUsers->usuarioActual->getPerfil().getCreditos())));
    }else{
        lblCreditos->setText("0 🪙");
    }

    btnJugar= new QPushButton("Jugar", this);
    btnNiveles= new QPushButton("Niveles", this);
    btnRecords= new QPushButton("Records", this);
    btnSalir= new QPushButton("Salir", this);

    btnAyuda= new QPushButton("❓", this);
    btnTienda= new QPushButton("🛒", this);
    btnOpciones= new QPushButton("⚙️", this);

    QString estiloBotones= "QPushButton {"
                        "background-color: transparent;"
                        "color: " + COLORFONT + ";"
                        "font-size: 20px;"
                        "font-weight: bold;"
                        "border-radius: 10px;"
                        "border: 2px solid white;"
                        "padding: 15px;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: " + COLORBOTONHOVER + ";"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: " + COLORBOTONPRESSED + ";"
                        "}";
    QString estiloMiniBotones= "QPushButton {"
                            "background-color: transparent;"
                            "font-size: 22px;"
                            "border-radius: 10px;"
                            "border: 2px solid white;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: " + COLORBOTONHOVER + ";"
                            "}"
                            "QPushButton:pressed {"
                            "background-color: " + COLORBOTONPRESSED + ";"
                              "}";

    btnJugar->setStyleSheet(estiloBotones);
    btnNiveles->setStyleSheet(estiloBotones);
    btnRecords->setStyleSheet(estiloBotones);
    btnSalir->setStyleSheet(estiloBotones);

    btnAyuda->setStyleSheet(estiloMiniBotones);
    btnTienda->setStyleSheet(estiloMiniBotones);
    btnOpciones->setStyleSheet(estiloMiniBotones);

    btnJugar->setFixedSize(200, 60);
    btnNiveles->setFixedSize(200, 60);
    btnRecords->setFixedSize(200, 60);
    btnSalir->setFixedSize(200, 60);

    btnAyuda->setFixedSize(50, 50);
    btnTienda->setFixedSize(50, 50);
    btnOpciones->setFixedSize(50, 50);

    layoutMenu->addWidget(titulo);
    layoutMenu->addWidget(lblCreditos);
    layoutMenu->addWidget(btnJugar, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnNiveles, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnRecords, 0, Qt::AlignHCenter);
    layoutMenu->addWidget(btnSalir, 0, Qt::AlignHCenter);

    layoutMiniBtns = new QHBoxLayout();
    layoutMiniBtns->setAlignment(Qt::AlignHCenter);
    layoutMiniBtns->setSpacing(15);

    layoutMiniBtns->addWidget(btnAyuda);
    layoutMiniBtns->addWidget(btnTienda);
    layoutMiniBtns->addWidget(btnOpciones);

    layoutMenu->addLayout(layoutMiniBtns);

    layoutPrincipal->addStretch();
    QHBoxLayout *layoutCentrado = new QHBoxLayout();
    layoutCentrado->addStretch();
    layoutCentrado->addWidget(contenedorMenu);
    layoutCentrado->addStretch();

    layoutPrincipal->addLayout(layoutCentrado);
    layoutPrincipal->addStretch();

    connect(btnJugar, &QPushButton::clicked, this, &PantallaMenuPrincipal::irAlJuego);
    connect(btnNiveles, &QPushButton::clicked, this, &PantallaMenuPrincipal::irANiveles);
    connect(btnTienda, &QPushButton::clicked, this, &PantallaMenuPrincipal::irATienda);
    connect(btnRecords, &QPushButton::clicked, this, &PantallaMenuPrincipal::irARecords);
    connect(btnOpciones, &QPushButton::clicked, this, &PantallaMenuPrincipal::irAOpciones);
    connect(btnAyuda, &QPushButton::clicked, this, &PantallaMenuPrincipal::irAAyuda);
    connect(btnSalir, &QPushButton::clicked, this, &PantallaMenuPrincipal::salir);
}

void PantallaMenuPrincipal::irAlJuego() {
    VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
    int nivel= 1;
    if(ventana->gestorUsers->usuarioActual != nullptr){
        nivel= ventana->gestorUsers->usuarioActual->getPerfil().getMapaMaxDesbloqueado();
        if(nivel < 1){
            nivel= 1;
        }
        if(nivel> 3){
            nivel= 3;
        }
    }
    PantallaJuego* pantallaJuego= new PantallaJuego(nivel, true, ventana);
    ventana->cambiarPantalla(pantallaJuego);
}

void PantallaMenuPrincipal::irANiveles() {
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaSelectorNiveles* pantallaNiveles= new PantallaSelectorNiveles(ventana);
    ventana->cambiarPantalla(pantallaNiveles);
}

void PantallaMenuPrincipal::irATienda() {
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaTienda* pantallaTienda= new PantallaTienda(ventana);
    ventana->cambiarPantalla(pantallaTienda);
}

void PantallaMenuPrincipal::irARecords() {
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaRecords* pantallaRecords= new PantallaRecords(ventana);
    ventana->cambiarPantalla(pantallaRecords);
}

void PantallaMenuPrincipal::irAOpciones() {
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaOpciones* pantallaOpciones= new PantallaOpciones(ventana);
    ventana->cambiarPantalla(pantallaOpciones);
}

void PantallaMenuPrincipal::irAAyuda() {
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaAyuda* pantallaAyuda= new PantallaAyuda(ventana);
    ventana->cambiarPantalla(pantallaAyuda);
}

void PantallaMenuPrincipal::salir() {
    QApplication::quit();
}

PantallaMenuPrincipal::~PantallaMenuPrincipal() {

}