#include <QLabel>
#include <QGroupBox>

#include "ventanaprincipal.h"
#include "pantallalogin.h"
#include "constantes.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) : QMainWindow(parent) {
    stackWidget= new QStackedWidget(this);
    setCentralWidget(stackWidget);

    setStyleSheet("background-color: "+COLORFONDO+";");

    cargarLogin();
}
void VentanaPrincipal::cargarLogin(){
    pantallaLogin= new PantallaLogin(this);
    stackWidget->addWidget(pantallaLogin);
}
//destructor
VentanaPrincipal::~VentanaPrincipal(){}