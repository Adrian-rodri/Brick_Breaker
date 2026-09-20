#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QIcon>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "pantallalogin.h"
#include "gestorusuario.h"
#include "pantallamenuprincipal.h"

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
public:
    VentanaPrincipal(QWidget *parent=nullptr);
    ~VentanaPrincipal() override;

    GestorUsuario *gestorUsers;

    PantallaLogin *pantallaLogin;
    PantallaMenuPrincipal* menuPrincipal;
    void cambiarPantalla(QWidget *pantalla);
    void actualizarVolumenMusica();


private:
    void iniciarMusica();
    QStackedWidget *stackWidget;
    QMediaPlayer *reproductorMusica;
    QAudioOutput *salidaMusica;

};

#endif // VENTANAPRINCIPAL_H
