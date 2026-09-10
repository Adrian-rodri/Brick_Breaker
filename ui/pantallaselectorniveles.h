#ifndef PANTALLASELECTORNIVELES_H
#define PANTALLASELECTORNIVELES_H
#include <QWidget>

class PantallaSelectorNiveles : public QWidget
{
    Q_OBJECT
public:
    PantallaSelectorNiveles(QWidget *parent=nullptr);
private:
    void cargarUi();
    void irAlNivel(int numNivel);
};

#endif // PANTALLASELECTORNIVELES_H
