#ifndef PANTALLALOGIN_H
#define PANTALLALOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class PantallaLogin : public QWidget
{
    Q_OBJECT
public:
    explicit PantallaLogin(QWidget *parent=nullptr);
    ~PantallaLogin() override;

private:
    QLabel *titulo;
    QLineEdit *lineUser;
    QLineEdit *linePass;
    QPushButton *btnVerPass;
    QPushButton *btnLogin;
    QPushButton *btnCrear;
    void cargarUI();
    void verPassword();
    void login();
    void irACrearCuenta();
};
#endif // PANTALLALOGIN_H
