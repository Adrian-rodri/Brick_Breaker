#ifndef PANTALLALOGIN_H
#define PANTALLALOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class PantallaLogin : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaLogin(QWidget *parent=nullptr);
    ~PantallaLogin() override;

private:
    QLabel *titulo;
    QPushButton *btnLogin;
    void cargarUI();
};
#endif // PANTALLALOGIN_H
