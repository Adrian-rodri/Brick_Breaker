#include "pantallarecords.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include "constantes.h"
#include "PerfilProgreso.h"

#include <QVBoxLayout>
#include <string>

using namespace std;

struct EntradaRanking{
    string username;
    double creditos;
};

void ordenarRankingBurbuja(EntradaRanking* ranking, int n);

PantallaRecords::PantallaRecords(QWidget* parent): QWidget(parent){
    cargarUI();
}

void PantallaRecords::cargarUI(){
    this->setMinimumSize(600, 600);
    this->setStyleSheet("background-color: black;");

    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();

    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);

    QLabel* lblTitulo= new QLabel("🏆 Records");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("color: #FFD700; "
                             "font-size: 34px; "
                             "font-weight: bold; "
                             "background-color: transparent;");
    layoutPrincipal->addWidget(lblTitulo);

    QLabel* lblSub= new QLabel("Ranking de jugadores por monedas");
    lblSub->setAlignment(Qt::AlignCenter);
    lblSub->setStyleSheet("color: " + COLORFONT + ";"
                          "font-size: 16px; "
                          "background-color: transparent;");
    layoutPrincipal->addWidget(lblSub);
    layoutPrincipal->addSpacing(15);

    int cantidad= 0;
    if(ventana!= nullptr && ventana->gestorUsers !=nullptr){
        int cant= ventana->gestorUsers->getCantidadUsuarios();
        for(int i=0; i<cant; i++){
            string user= ventana->gestorUsers->getUsername(i);
            if(!user.empty()){
                cantidad++;
            }
        }
    }

    EntradaRanking* ranking= new EntradaRanking[cantidad];
    int indice= 0;
    if(ventana!= nullptr && ventana->gestorUsers!=nullptr){
        int cant= ventana->gestorUsers->getCantidadUsuarios();
        for(int i=0; i<cant; i++){
            string user= ventana->gestorUsers->getUsername(i);
            if(user.empty()){
                continue;
            }
            PerfilProgreso* perfil= ventana->gestorUsers->cargarProgreso(user);
            double creditos= 0;
            if(perfil!=nullptr){
                creditos= perfil->getCreditos();
                delete perfil;
            }
            ranking[indice].username= user;
            ranking[indice].creditos= creditos;
            indice++;
        }
    }

    ordenarRankingBurbuja(ranking, cantidad);

    string usuarioActual= "";
    if(ventana != nullptr && ventana->gestorUsers->usuarioActual != nullptr){
        usuarioActual = ventana->gestorUsers->usuarioActual->getUsername();
    }

    int posicionActual= -1;
    for(int i=0; i<cantidad; i++){
        bool esActual= (ranking[i].username == usuarioActual);
        if(esActual){
            posicionActual= i+1;
        }

        QString texto= QString("#%1   %2   -   %3 🪙")
                            .arg(i + 1)
                            .arg(QString::fromStdString(ranking[i].username))
                            .arg(qRound(ranking[i].creditos));
        QLabel* lblFila= new QLabel(texto);
        lblFila->setAlignment(Qt::AlignCenter);
        lblFila->setStyleSheet(esActual
                                   ? "color: #FFD700; font-size: 20px; font-weight: bold; background-color: transparent;"
                                   : "color: " + COLORFONT + "; font-size: 18px; background-color: transparent;");
        layoutPrincipal->addWidget(lblFila);
    }

    if(cantidad == 0){
        QLabel* lblVacio = new QLabel("Todavía no hay jugadores registrados.");
        lblVacio->setAlignment(Qt::AlignCenter);
        lblVacio->setStyleSheet("color: " + COLORFONT + "; font-size: 16px; background-color: transparent;");
        layoutPrincipal->addWidget(lblVacio);
    }

    delete[] ranking;

    QLabel* lblPosicion = new QLabel("");
    if(posicionActual > 0){
        lblPosicion->setText(QString("Tu posición: #%1").arg(posicionActual));
    }
    lblPosicion->setAlignment(Qt::AlignCenter);
    lblPosicion->setStyleSheet("color: #FFD700; font-size: 18px; font-weight: bold; background-color: transparent;");
    layoutPrincipal->addWidget(lblPosicion);

    layoutPrincipal->addStretch();

    QPushButton* btnVolver = new QPushButton("← Volver al menú");
    btnVolver->setStyleSheet("QPushButton{"
                             "background-color: transparent;"
                             "color: " + COLORFONT + ";"
                                           "font-size: 18px;"
                                           "font-weight: bold;"
                                           "border-radius: 10px;"
                                           "border: 2px solid white;"
                                           "padding: 12px;"
                                           "}"
                                           "QPushButton:hover{"
                                           "background-color: " + COLORBOTONHOVER + ";"
                                                 "}"
                                                 "QPushButton:pressed{"
                                                 "background-color: " + COLORBOTONPRESSED + ";"
                                                   "}");
    btnVolver->setFixedSize(220, 50);
    connect(btnVolver, &QPushButton::clicked, this, &PantallaRecords::volverAlMenu);
    layoutPrincipal->addWidget(btnVolver, 0, Qt::AlignHCenter);
    layoutPrincipal->addSpacing(20);
}
void ordenarRankingBurbuja(EntradaRanking* ranking, int n){
    if(n < 2){
        return;
    }
    for(int i=0; i<n-1; i++){
        bool huboIntercambio= false;
        for(int j=0; j<n-1-i; j++){
            if(ranking[j].creditos <ranking[j+1].creditos){
                EntradaRanking temp= ranking[j];
                ranking[j]= ranking[j+1];
                ranking[j+1]= temp;
                huboIntercambio= true;
            }
        }
        if(!huboIntercambio){
            break;
        }
    }
}

void PantallaRecords::volverAlMenu(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal(ventana);
    ventana->cambiarPantalla(pantallaMenu);
}