#include "pantallaayuda.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include "constantes.h"

#include <QVBoxLayout>

PantallaAyuda::PantallaAyuda(QWidget* parent) : QWidget(parent){
    cargarUI();
}

void PantallaAyuda::cargarUI(){
    this->setMinimumSize(600, 600);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);

    QLabel* lblTitulo= new QLabel("❓ Instrucciones");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("color: " + COLORFONT + "; font-size: 34px; font-weight: bold; background-color: transparent;");
    layoutPrincipal->addWidget(lblTitulo);
    layoutPrincipal->addSpacing(20);

    QString textoInstrucciones =
        "🎮 CONTROLES\n\n"
        "← →  o  A D ............ mover la paleta\n"
        "W / ↑ / Espacio ....... lanzar la pelota\n"
        "Esc ................... pausar el juego\n\n"
        "💡 CONSEJOS\n\n"
        "• Rompe todos los bloques para completar el nivel.\n"
        "• Atrapa los power-ups que caen: alargan la paleta,\n"
        "  dan pelotas extra y más.\n"
        "• Recoge las monedas que sueltan los bloques y\n"
        "  gástalas en la tienda para mejorar tu equipo.\n"
        "• Los bloques reforzados necesitan varios golpes y\n"
        "  los metálicos no se destruyen.\n"
        "• Completa los 3 niveles en Modo Historia para\n"
        "  desbloquearlos y ganar más monedas.";

    QLabel* lblTexto= new QLabel(textoInstrucciones);
    lblTexto->setAlignment(Qt::AlignLeft);
    lblTexto->setStyleSheet("color: " + COLORFONT + "; font-size: 17px; background-color: transparent;");

    QHBoxLayout* layoutCentr= new QHBoxLayout();
    layoutCentr->addStretch();
    layoutCentr->addWidget(lblTexto);
    layoutCentr->addStretch();

    layoutPrincipal->addStretch();
    layoutPrincipal->addLayout(layoutCentr);
    layoutPrincipal->addStretch();

    QPushButton* btnVolver= new QPushButton("← Volver al menú");
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
    connect(btnVolver, &QPushButton::clicked, this, &PantallaAyuda::volverAlMenu);
    layoutPrincipal->addWidget(btnVolver, 0, Qt::AlignHCenter);
    layoutPrincipal->addSpacing(20);
}

void PantallaAyuda::volverAlMenu(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal(ventana);
    ventana->cambiarPantalla(pantallaMenu);
}