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

    pantallaLogin = new PantallaLogin(this);
    gestorUsers= new GestorUsuario();
    cargarConfiguracion();

    iniciarMusica();

    cambiarPantalla(pantallaLogin);
    this->showMaximized();
}
void VentanaPrincipal::iniciarMusica(){
    reproductorMusica= new QMediaPlayer(this);
    salidaMusica= new QAudioOutput(this);
    salidaMusica->setVolume(0.3*VOLUMEN_GLOBAL);
    reproductorMusica->setAudioOutput(salidaMusica);
    reproductorMusica->setSource(QUrl("qrc:/assets/musica.mp3"));
    reproductorMusica->setLoops(QMediaPlayer::Infinite);
    reproductorMusica->play();
}

void VentanaPrincipal::actualizarVolumenMusica(){
    if(salidaMusica != nullptr){
        salidaMusica->setVolume(0.3*VOLUMEN_GLOBAL);
    }
}
void VentanaPrincipal::cambiarPantalla(QWidget *pantalla){
    QWidget* anterior= stackWidget->currentWidget();

    stackWidget->addWidget(pantalla);
    stackWidget->setCurrentWidget(pantalla);

    if(anterior != nullptr){
        stackWidget->removeWidget(anterior);
        anterior->deleteLater();
    }
}
//destructor
VentanaPrincipal::~VentanaPrincipal(){
    if(reproductorMusica != nullptr){
        reproductorMusica->stop();
    }
}