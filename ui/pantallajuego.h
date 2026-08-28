#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>

class PantallaJuego : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaJuego(QWidget* parent=nullptr);
    ~PantallaJuego() override;
private:
    void cargarUI();
    void actualizar();
};

#endif // PANTALLAJUEGO_H
