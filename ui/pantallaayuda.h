#ifndef PANTALLAYUDA_H
#define PANTALLAYUDA_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class PantallaAyuda: public QWidget
{
    Q_OBJECT
public:
    PantallaAyuda(QWidget* parent=nullptr);
private:
    void cargarUI();
    void volverAlMenu();
};

#endif // PANTALLAYUDA_H