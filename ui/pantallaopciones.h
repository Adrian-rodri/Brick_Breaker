#ifndef PANTALLAOPCIONES_H
#define PANTALLAOPCIONES_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

class PantallaOpciones :public QWidget
{
    Q_OBJECT
public:
    PantallaOpciones(QWidget* parent=nullptr);
private:
    void cargarUI();
    void cambiarVolumen(int valor);
    void cerrarSesion();
    void volverAlMenu();

    QSlider* sliderVolumen;
    QLabel* lblValorVolumen;
};

#endif // PANTALLAOPCIONES_H