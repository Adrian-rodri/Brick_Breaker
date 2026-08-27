#ifndef PANTALLASIGNUP_H
#define PANTALLASIGNUP_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class PantallaSignUp: public QWidget
{
    Q_OBJECT
public:
    explicit PantallaSignUp(QWidget *parent=nullptr);
    ~PantallaSignUp() override;
private:

    QLabel* titulo;
    QLabel* lblStatus;
    QLineEdit* lineNombre;
    QLineEdit* lineUser;
    QLineEdit* linePass;
    QLineEdit* lineConfirm;
    QPushButton* btnBack;
    QPushButton* btnVer;
    QPushButton* btnCrear;

    void cargarUi();
    bool passwordCoinciden();
    bool existeUsuario();
    void verPassword();
    void regresar();
};

#endif // PANTALLASIGNUP_H