#include "pantallaopciones.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include "pantallalogin.h"
#include "constantes.h"

#include <QVBoxLayout>

PantallaOpciones::PantallaOpciones(QWidget* parent) : QWidget(parent){
    cargarUI();
}

void PantallaOpciones::cargarUI(){
    this->setMinimumSize(600, 600);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);

    QLabel* lblTitulo= new QLabel("⚙️ Opciones");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("color: " + COLORFONT + ";"
                            " font-size: 34px; "
                            "font-weight: bold; "
                            "background-color: transparent;");
    layoutPrincipal->addWidget(lblTitulo);
    layoutPrincipal->addSpacing(30);

    QLabel* lblVolumen= new QLabel("🔊 Volumen");
    lblVolumen->setAlignment(Qt::AlignCenter);
    lblVolumen->setStyleSheet("color: " + COLORFONT + "; "
                            "font-size: 22px; font-weight: bold; "
                            "background-color: transparent;");
    layoutPrincipal->addWidget(lblVolumen);
    sliderVolumen= new QSlider(Qt::Horizontal);
    sliderVolumen->setRange(0, 100);
    sliderVolumen->setValue((int)(VOLUMEN_GLOBAL * 100));
    sliderVolumen->setFixedWidth(300);
    sliderVolumen->setStyleSheet("QSlider::groove:horizontal{"
                                 "height: 8px;"
                                 "background: #444444;"
                                 "border-radius: 4px;"
                                 "}"
                                 "QSlider::handle:horizontal{"
                                 "width: 18px;"
                                 "height: 18px;"
                                 "margin: -5px 0;"
                                 "border-radius: 9px;"
                                 "background: " + COLORBOTON + ";"
                                 "}");
    layoutPrincipal->addWidget(sliderVolumen, 0, Qt::AlignHCenter);

    lblValorVolumen= new QLabel(QString("%1 %").arg(sliderVolumen->value()));
    lblValorVolumen->setAlignment(Qt::AlignCenter);
    lblValorVolumen->setStyleSheet("color: #FFD700; font-size: 18px; font-weight: bold; background-color: transparent;");
    layoutPrincipal->addWidget(lblValorVolumen);

    connect(sliderVolumen, &QSlider::valueChanged, this, &PantallaOpciones::cambiarVolumen);
    layoutPrincipal->addSpacing(40);

    QPushButton* btnCerrarSesion= new QPushButton("🚪 Cerrar sesión");
    btnCerrarSesion->setStyleSheet("QPushButton{"
                                   "background-color: transparent;"
                                   "color: " + COLORFONT + ";"
                                   "font-size: 20px;"
                                   "font-weight: bold;"
                                   "border-radius: 10px;"
                                   "border: 2px solid white;"
                                   "padding: 14px;"
                                   "}"
                                   "QPushButton:hover{"
                                   "background-color: " + COLORBOTONHOVER + ";"
                                   "}"
                                   "QPushButton:pressed{"
                                   "background-color: " + COLORBOTONPRESSED + ";"
                                   "}");
    btnCerrarSesion->setFixedSize(240, 55);
    connect(btnCerrarSesion, &QPushButton::clicked, this, &PantallaOpciones::cerrarSesion);
    layoutPrincipal->addWidget(btnCerrarSesion, 0, Qt::AlignHCenter);

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
    connect(btnVolver, &QPushButton::clicked, this, &PantallaOpciones::volverAlMenu);
    layoutPrincipal->addWidget(btnVolver, 0, Qt::AlignHCenter);
    layoutPrincipal->addSpacing(20);
}

void PantallaOpciones::cambiarVolumen(int valor){
    VOLUMEN_GLOBAL= valor/100.0;
    lblValorVolumen->setText(QString("%1 %").arg(valor));
    guardarConfiguracion();

    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    if(ventana != nullptr){
        ventana->actualizarVolumenMusica();
    }
}

void PantallaOpciones::cerrarSesion(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    if(ventana != nullptr && ventana->gestorUsers!= nullptr){
        ventana->gestorUsers->cerrarSesion();
    }
    PantallaLogin* login= new PantallaLogin(ventana);
    ventana->cambiarPantalla(login);
}

void PantallaOpciones::volverAlMenu(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaMenuPrincipal* pantallaMenu= new PantallaMenuPrincipal(ventana);
    ventana->cambiarPantalla(pantallaMenu);
}