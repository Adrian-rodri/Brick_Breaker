#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <string>

#include "pantallalogin.h"
#include "ventanaprincipal.h"
#include "constantes.h"
#include "pantallasignup.h"
#include "pantallamenuprincipal.h"

using namespace std;
void verPassword();
PantallaLogin::PantallaLogin(QWidget *parent) : QWidget(parent) {
    cargarUI();
}

void PantallaLogin::cargarUI(){
    this->setMinimumSize(800,600);
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    QGroupBox *boxLogin = new QGroupBox("Log In");
    boxLogin->setFixedSize(400,350);
    boxLogin->setStyleSheet("QGroupBox{"
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

    QVBoxLayout *layoutBox= new QVBoxLayout(boxLogin);

    titulo= new QLabel("Brick\nBreaker");
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 80px;"
                          "color : "+COLORFONT+";"
                          "font-family: 'Gill Sans MT Condensed';"
                          "background-color: transparent;");
    QFormLayout *layoutForm = new QFormLayout();

    QString estiloLblForm= "font-family: 'Consolas';"
                            "background-color: transparent;"
                            "font-weight:bold;";
    QLabel *lblUser = new QLabel("Usuario");
    lblUser->setStyleSheet(estiloLblForm);
    QLabel *lblPass = new QLabel("Contraseña");
    lblPass->setStyleSheet(estiloLblForm);

    QString estiloLineEdit= "background-color: #EEEEEE;"
                             "color: #0B0909;"
                             "font-family: '8514oem';";
    lineUser= new QLineEdit();
    lineUser->setStyleSheet(estiloLineEdit);

    linePass= new QLineEdit();
    linePass->setEchoMode(QLineEdit::Password);
    linePass->setStyleSheet(estiloLineEdit);

    btnVerPass= new QPushButton("👁");
    btnVerPass->setFixedWidth(20);
    btnVerPass->setStyleSheet("QPushButton{"
                              "background-color: transparent;"
                              "border:0px;"
                              "font-size:15px;"
                              "font-weight:bold;"
                              "}QPushButton::hover{"
                              "font-size:17px;"
                              "font-weight:bold;"
                              "}QPushButton::pressed{"
                              "font-size:19px;"
                              "}");

    QHBoxLayout *layoutPassH = new QHBoxLayout();
    layoutPassH->addWidget(linePass);
    layoutPassH->addWidget(btnVerPass);

    lblStatus= new QLabel("");
    lblStatus->setStyleSheet("color: red;"
                             "font-size: 10px;"
                             "font-family: 'Console';"
                             "background-color: transparent;"
                             "padding:0px;");

    layoutForm->addRow(lblUser,lineUser);
    layoutForm->addRow(lblPass,layoutPassH);
    layoutForm->addRow(lblStatus);

    btnLogin = new QPushButton("Log In");
    btnLogin->setStyleSheet("QPushButton{"
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

    btnCrear = new QPushButton("Aun no tienes una cuenta?");
    btnCrear->setStyleSheet("QPushButton{"
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
                            "   font-size:19px;"
                            "}"
                            "QPushButton:pressed {"
                            "   color: "+COLORFONT+";"
                            "}");
    layoutBox->addWidget(titulo);
    layoutBox->addLayout(layoutForm);
    layoutBox->addWidget(btnLogin);
    layoutBox->addWidget(btnCrear);

    layoutPrincipal->addStretch();

    QHBoxLayout *layoutCentrado= new QHBoxLayout();
    layoutCentrado->addStretch();
    layoutCentrado->addWidget(boxLogin);
    layoutCentrado->addStretch();

    layoutPrincipal->addLayout(layoutCentrado);
    layoutPrincipal->addStretch();

    //connects
    connect(btnVerPass,&QPushButton::clicked,this,&PantallaLogin::verPassword);
    connect(btnCrear,&QPushButton::clicked,this,&PantallaLogin::irACrearCuenta);
    connect(btnLogin,&QPushButton::clicked,this,&PantallaLogin::solicitarLogin);
}
void PantallaLogin::verPassword(){
    if(linePass->echoMode()==QLineEdit::Password){
        linePass->setEchoMode(QLineEdit::Normal);
        btnVerPass->setText("🙈");
    }else{
        linePass->setEchoMode(QLineEdit::Password);
        btnVerPass->setText("👁");
    }
}
void PantallaLogin::solicitarLogin(){
    string txtUser= lineUser->text().toStdString();
    string txtPass= linePass->text().toStdString();

    if(txtUser.empty() || txtPass.empty()){
        lblStatus->setText("Llene todos los campos.");

    }else if(txtUser=="admin" && txtPass=="1234"){
        VentanaPrincipal* ventana=(VentanaPrincipal*)this->window();
        PantallaMenuPrincipal* menuPrincipal= new PantallaMenuPrincipal();
        ventana->cambiarPantalla(menuPrincipal);
    }else{
        lblStatus->setText("Credenciales Incorrectas.");
    }
}
void PantallaLogin::irACrearCuenta(){
    VentanaPrincipal* principal=(VentanaPrincipal*)this->window();

    PantallaSignUp *pantallaCrear= new PantallaSignUp();
    principal->cambiarPantalla(pantallaCrear);

}
//destructor
PantallaLogin::~PantallaLogin(){
}