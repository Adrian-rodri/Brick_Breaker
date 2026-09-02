#include <QLabel>
#include <QGroupBox>

#include "ventanaprincipal.h"
#include "pantallalogin.h"
#include "constantes.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) : QMainWindow(parent) {
    this->setWindowIcon(QIcon(":/assets/icono.png"));
    stackWidget= new QStackedWidget(this);
    setCentralWidget(stackWidget);

    setStyleSheet("background-color: "+COLORFONDO+";");

    /*
     * Inicializar variables necesarias
     * */
    pantallaLogin = new PantallaLogin(this);
    gestorUsers= new GestorUsuario();

    cambiarPantalla(pantallaLogin);
    this->showMaximized();
}
void VentanaPrincipal::cambiarPantalla(QWidget *pantalla){
    stackWidget->addWidget(pantalla);
    stackWidget->setCurrentWidget(pantalla);
}
//destructor
VentanaPrincipal::~VentanaPrincipal(){}