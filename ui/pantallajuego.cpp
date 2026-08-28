#include "pantallajuego.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
PantallaJuego::PantallaJuego(QWidget* parent) : QWidget(parent) {
    cargarUI();
}
void PantallaJuego::cargarUI(){
    QVBoxLayout *layoutPrincipal= new QVBoxLayout(this);
    QLabel *titulo= new QLabel("BR br patapim");
    layoutPrincipal->addWidget(titulo);
}
//destructor
PantallaJuego::~PantallaJuego(){

}
