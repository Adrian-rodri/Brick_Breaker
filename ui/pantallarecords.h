#ifndef PANTALLARECORDS_H
#define PANTALLARECORDS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class PantallaRecords: public QWidget
{
    Q_OBJECT
public:
    PantallaRecords(QWidget* parent=nullptr);
private:
    void cargarUI();
    void volverAlMenu();
};

#endif // PANTALLARECORDS_H