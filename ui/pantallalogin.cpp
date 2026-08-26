#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>

#include "pantallalogin.h"
#include "constantes.h"

PantallaLogin::PantallaLogin(QWidget *parent) : QWidget(parent) {
    cargarUI();
}

void PantallaLogin::cargarUI(){

    this->setMinimumSize(800,600);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    QGroupBox *boxLogin = new QGroupBox("Log In");
    boxLogin->setFixedSize(300,250);

    QVBoxLayout *layoutBox= new QVBoxLayout(boxLogin);

    titulo= new QLabel("Brick\nBreaker");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 20px;"
                          "color : "+COLORFONT+";");

    btnLogin = new QPushButton("Log In");

    layoutBox->addWidget(titulo);
    layoutBox->addWidget(btnLogin);


    layoutPrincipal->addStretch();
    QHBoxLayout *layoutCentrado= new QHBoxLayout();
    layoutCentrado->addStretch();
    layoutCentrado->addWidget(boxLogin);
    layoutCentrado->addStretch();

    layoutPrincipal->addLayout(layoutCentrado);
    layoutPrincipal->addStretch();
}
//destructor
PantallaLogin::~PantallaLogin(){}