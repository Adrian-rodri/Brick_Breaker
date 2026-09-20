#include "pantallaselectorniveles.h"
#include "ventanaprincipal.h"
#include "pantallajuego.h"
#include "pantallamenuprincipal.h"
#include "constantes.h"
#include "PerfilProgreso.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

PantallaSelectorNiveles::PantallaSelectorNiveles(QWidget* parent):QWidget(parent){
    cargarUi();
}

void PantallaSelectorNiveles::cargarUi(){
    this->setMinimumSize(600,400);
    this->setStyleSheet("background-color: black;");

    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    int mapaMax= 1;
    double creditos= 0;
    if(ventana!= nullptr && ventana->gestorUsers->usuarioActual!= nullptr){
        PerfilProgreso& perfil= ventana->gestorUsers->usuarioActual->getPerfil();
        mapaMax= perfil.getMapaMaxDesbloqueado();
        creditos= perfil.getCreditos();
    }
    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);

    QLabel* lblTitulo= new QLabel("Elige un nivel");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("color: "+COLORFONT+";"
                            "font-size: 28px;"
                            "font-weight: bold;"
                            "background-color: transparent;");

    lblCreditos= new QLabel(QString("%1 🪙").arg(qRound(creditos)));
    lblCreditos->setAlignment(Qt::AlignCenter);
    lblCreditos->setStyleSheet("color: #FFD700;"
                               "font-size: 20px;"
                               "font-weight: bold;"
                               "background-color: transparent;");

    QLabel* lblAviso= new QLabel("Todos los niveles están disponibles.\nSolo los niveles desbloqueados otorgan créditos.");
    lblAviso->setAlignment(Qt::AlignCenter);
    lblAviso->setStyleSheet("color: #AAAAAA;"
                            "font-size: 14px;"
                            "background-color: transparent;");

    QWidget* centro= new QWidget();
    QHBoxLayout* layout= new QHBoxLayout(centro);
    layout->setSpacing(25);

    for(int i=1;i<=3;i++){
        bool completado= i < mapaMax;
        bool actual= i == mapaMax;
        QPushButton* btnNivel= new QPushButton();
        QString texto= "Nivel #"+QString::number(i);
        if(completado){
            texto+= "  ✔";
        }
        btnNivel->setText(texto);

        if(completado){
            btnNivel->setStyleSheet("QPushButton {"
                                    "   background-color: #1E7A46;"
                                    "   color: white;"
                                    "   font-size: 18px;"
                                    "   font-weight: bold;"
                                    "   border-radius: 10px;"
                                    "   padding: 10px 20px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "   background-color: #249A57;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "   background-color: #145632;"
                                    "}");
        }else if(actual){
            btnNivel->setStyleSheet("QPushButton {"
                                    "   background-color: #2E86AB;"
                                    "   color: white;"
                                    "   font-size: 18px;"
                                    "   font-weight: bold;"
                                    "   border: 3px solid #FFD700;"
                                    "   border-radius: 10px;"
                                    "   padding: 10px 20px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "   background-color: #3AA0CC;"
                                    "}"
                                    "QPushButton:pressed {"
                                    "   background-color: #1B5E7A;"
                                    "}");
        }else{
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
        }

        connect(btnNivel,&QPushButton::clicked,this,[this,i](){
            irAlNivel(i);
        });
        btnNivel->setFixedSize(180, 70);
        layout->addWidget(btnNivel);
    }

    QPushButton* btnVolver= new QPushButton("← Volver al menú");
    btnVolver->setStyleSheet("QPushButton {"
                             "   background-color: transparent;"
                             "   color: "+COLORFONT+";"
                             "   font-size: 16px;"
                             "   font-weight: bold;"
                             "   border: 2px solid white;"
                             "   border-radius: 8px;"
                             "   padding: 8px 16px;"
                             "}"
                             "QPushButton:hover {"
                             "   background-color: "+COLORBOTONHOVER+";"
                             "}"
                             "QPushButton:pressed {"
                             "   background-color: "+COLORBOTONPRESSED+";"
                             "}");
    connect(btnVolver,&QPushButton::clicked,this,&PantallaSelectorNiveles::volverAlMenu);

    layoutPrincipal->addStretch();
    layoutPrincipal->addWidget(lblTitulo);
    layoutPrincipal->addWidget(lblCreditos);
    layoutPrincipal->addWidget(lblAviso);
    layoutPrincipal->addSpacing(30);

    QHBoxLayout* layoutHor= new QHBoxLayout();
    layoutHor->addStretch();
    layoutHor->addWidget(centro);
    layoutHor->addStretch();
    layoutPrincipal->addLayout(layoutHor);

    layoutPrincipal->addSpacing(30);
    layoutPrincipal->addWidget(btnVolver, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();
}

void PantallaSelectorNiveles::irAlNivel(int numLvl){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaJuego* pantallaJuego= new PantallaJuego(numLvl, false, ventana);
    ventana->cambiarPantalla(pantallaJuego);
}

void PantallaSelectorNiveles::volverAlMenu(){
    VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
    PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal(ventana);
    ventana->cambiarPantalla(pantallaMenu);
}