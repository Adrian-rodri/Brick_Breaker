#ifndef PANTALLASELECTORNIVELES_H
#define PANTALLASELECTORNIVELES_H
#include <QWidget>
#include <QLabel>

class PantallaSelectorNiveles: public QWidget
{
    Q_OBJECT
public:
    PantallaSelectorNiveles(QWidget *parent=nullptr);
private:
    void cargarUi();
    void irAlNivel(int numNivel);
    void volverAlMenu();

    QLabel* lblCreditos;
};

#endif // PANTALLASELECTORNIVELES_H