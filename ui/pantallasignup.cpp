#include "pantallasignup.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>

PantallaSignUp::PantallaSignUp(QWidget* parent) : QWidget(parent){
    cargarUi();
}

void PantallaSignUp::cargarUi(){
    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);

    QGroupBox* boxCrear= new QGroupBox("Sign Up");
    boxCrear->setFixedSize(400,350);
    boxCrear->setStyleSheet("QGroupBox{"
                            "   background-color:"+COLORSUBFONDO+";"
                            "   color: white;"
                            "   border: 2px solid white;"
                            "   border-radius: 8px;"
                            "   margin-top: 1ex;"
                            "}QGroupBox::title{"
                            "   color :"+COLORFONT+";"
                            "   subcontrol-origin: margin;"
                            "   left:10px;"
                            "}");
    QVBoxLayout* layoutBox= new QVBoxLayout();
    boxCrear->setLayout(layoutBox);

    titulo= new QLabel("Brick\nBreaker");
    titulo->setStyleSheet("font-size: 60px;"
                          "color : "+COLORFONT+";"
                          "font-family: 'Gill Sans MT Condensed';"
                          "background-color: transparent;");
    titulo->setAlignment(Qt::AlignCenter);

    QFormLayout* layoutForm= new QFormLayout();

    QString estiloLblForm= "font-weight:bold;"
                            "font-family: 'Consolas';"
                            "background-color: transparent;";
    QString estiloLineEdit= "background-color: #EEEEEE;"
                             "color: #0B0909;"
                             "font-family: '8514oem';";

    QLabel* lblNombre= new QLabel("Nombre");
    lblNombre->setStyleSheet(estiloLblForm);

    lineNombre= new QLineEdit();
    lineNombre->setStyleSheet(estiloLineEdit);

    QLabel* lblUser= new QLabel("Usuario");
    lblUser->setStyleSheet(estiloLblForm);

    lineUser= new QLineEdit();
    lineUser->setStyleSheet(estiloLineEdit);

    QHBoxLayout* layoutPass= new QHBoxLayout();
    btnVer= new QPushButton("👁");
    btnVer->setFixedWidth(20);
    btnVer->setStyleSheet("border:0px;"
                          "background-color: transparent;");
    QLabel* lblPass= new QLabel("Contraseña");
    lblPass->setStyleSheet(estiloLblForm);
    linePass= new QLineEdit();
    linePass->setEchoMode(QLineEdit::Password);
    linePass->setStyleSheet(estiloLineEdit);

    layoutPass->addWidget(linePass);
    layoutPass->addWidget(btnVer);
    QLabel* lblConfirm= new QLabel("Confirmar Contra");
    lblConfirm->setStyleSheet(estiloLblForm);

    lineConfirm= new QLineEdit();
    lineConfirm->setStyleSheet(estiloLineEdit);
    lineConfirm->setEchoMode(QLineEdit::Password);

    layoutForm->addRow(lblNombre,lineNombre);
    layoutForm->addRow(lblUser,lineUser);
    layoutForm->addRow(lblPass,layoutPass);
    layoutForm->addRow(lblConfirm,lineConfirm);

    btnCrear= new QPushButton("Crear Cuenta");
    btnCrear->setStyleSheet("QPushButton{"
                            "   background-color: black;"
                            "   color: white;"
                            "   font-family: 'Gill Sans MT Condensed';"
                            "   font-size: 18px;"
                            "   font-weight: bold;"
                            "   border: 1px solid white;"
                            "   border-radius: 5px;"
                            "   padding: 6px;"
                            "}"
                            "QPushButton:hover{"
                            "   background-color:"+COLORBOTONHOVER+";"
                            "}"
                            "QPushButton:pressed {"
                            "   background-color:"+COLORBOTONPRESSED+";"
                            "}");

    btnBack= new QPushButton("Regresar");
    btnBack->setStyleSheet("QPushButton{"
                           "   background-color: transparent;"
                           "   color: "+COLORFONT+";"
                           "   font-family: 'Gill Sans MT Condensed';"
                           "   font-size: 18px;"
                           "   font-weight: bold;"
                           "   border: 0px solid white;"
                           "   border-radius: 5px;"
                           "   padding: 1px;"
                           "}"
                           "QPushButton:hover{"
                           "   color: white;"
                           "}"
                           "QPushButton:pressed {"
                           "   color: "+COLORFONT+";"
                           "}");

    layoutBox->addWidget(titulo);
    layoutBox->addLayout(layoutForm);
    layoutBox->addWidget(btnCrear);
    layoutBox->addWidget(btnBack);

    QHBoxLayout* layoutCentro= new QHBoxLayout();
    layoutCentro->addStretch();
    layoutCentro->addWidget(boxCrear);
    layoutCentro->addStretch();

    layoutPrincipal->addStretch();
    layoutPrincipal->addLayout(layoutCentro);
    layoutPrincipal->addStretch();

    //connects
    connect(btnVer,&QPushButton::clicked,this,&PantallaSignUp::verPassword);
    connect(btnBack,&QPushButton::clicked,this,&PantallaSignUp::regresar);
}
void PantallaSignUp::regresar(){
    VentanaPrincipal* ventana=(VentanaPrincipal*)this->window();
    ventana->cambiarPantalla(ventana->pantallaLogin);
}

void PantallaSignUp::verPassword(){
    if(linePass->echoMode()==QLineEdit::Password){
        linePass->setEchoMode(QLineEdit::Normal);
        lineConfirm->setEchoMode(QLineEdit::Normal);
        btnVer->setText("◡");
    }else{
        linePass->setEchoMode(QLineEdit::Password);
        lineConfirm->setEchoMode(QLineEdit::Password);
        btnVer->setText("👁");
    }
}
//destructor
PantallaSignUp::~PantallaSignUp(){
    //No se usa delete para los elementos de qt, porque se limpian
    //automaticamente
}

