#include "pantallatienda.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include "constantes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

const int MAX_NIVEL_MEJORA= 5;
const int MAX_NIVEL_DANO= 6;
const int COSTO_BLINDAJE= 500;

PantallaTienda::PantallaTienda(QWidget* parent): QWidget(parent){
    VentanaPrincipal* ventana= qobject_cast<VentanaPrincipal*>(this->window());
    if(ventana!= nullptr && ventana->gestorUsers->usuarioActual != nullptr){
        perfil= &ventana->gestorUsers->usuarioActual->getPerfil();
    }else{
        perfil= nullptr;
    }
    cargarUI();
}

void PantallaTienda::cargarUI(){
    this->setMinimumSize(700, 550);
    this->setStyleSheet("background-color: black;");

    QVBoxLayout* layoutPrincipal= new QVBoxLayout(this);
    layoutPrincipal->addStretch();

    QWidget* contenedor= new QWidget();
    contenedor->setFixedWidth(700);
    QVBoxLayout* layoutContenedor= new QVBoxLayout(contenedor);

    QLabel* lblTitulo= new QLabel("🛒 Tienda de Mejoras");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setStyleSheet("color: "+COLORFONT+";"
                            "font-size: 28px;"
                            "font-weight: bold;"
                            "background-color: transparent;");
    lblCreditos= new QLabel();
    lblCreditos->setAlignment(Qt::AlignCenter);
    lblCreditos->setStyleSheet("color: #FFD700;"
                               "font-size: 20px;"
                               "font-weight: bold;"
                               "background-color: transparent;");

    QString estiloGrupo="QGroupBox {"
                        "   background-color: "+COLORSUBFONDO+";"
                        "   color: white;"
                        "   border: 2px solid white;"
                        "   border-radius: 8px;"
                        "   margin-top: 1ex;"
                        "   font-size: 16px;"
                        "   font-weight: bold;"
                        "}"
                        "QGroupBox::title {"
                        "   color: "+COLORFONT+";"
                        "   subcontrol-origin: margin;"
                        "   left: 10px;"
                        "}";
    QString estiloInfo= "color: "+COLORFONT+";"
                        "font-size: 14px;"
                        "background-color: transparent;";
    QString estiloBtn= "QPushButton {"
                        "   background-color: #2E86AB;"
                        "   color: white;"
                        "   font-size: 14px;"
                        "   font-weight: bold;"
                        "   border-radius: 8px;"
                        "   padding: 8px 14px;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color: #3AA0CC;"
                        "}"
                        "QPushButton:pressed {"
                        "   background-color: #1B5E7A;"
                        "}"
                        "QPushButton:disabled {"
                        "   background-color: #3A3A3A;"
                        "   color: #888888;"
                        "}";
    QGroupBox* grupoDano= new QGroupBox("💥 Daño de bola");
    grupoDano->setStyleSheet(estiloGrupo);
    QHBoxLayout* layoutDano= new QHBoxLayout(grupoDano);
    lblDano= new QLabel();
    lblDano->setStyleSheet(estiloInfo);
    btnDano= new QPushButton("");
    btnDano->setStyleSheet(estiloBtn);
    btnDano->setFixedWidth(120);
    connect(btnDano, &QPushButton::clicked, this, &PantallaTienda::comprarDamage);
    layoutDano->addWidget(lblDano);
    layoutDano->addStretch();
    layoutDano->addWidget(btnDano);

    QGroupBox* grupoMult= new QGroupBox("🪙 Multiplicador de monedas");
    grupoMult->setStyleSheet(estiloGrupo);
    QHBoxLayout* layoutMult= new QHBoxLayout(grupoMult);
    lblMultiplicador= new QLabel();
    lblMultiplicador->setStyleSheet(estiloInfo);
    btnMultiplicador= new QPushButton("");
    btnMultiplicador->setStyleSheet(estiloBtn);
    btnMultiplicador->setFixedWidth(120);
    connect(btnMultiplicador, &QPushButton::clicked, this, &PantallaTienda::comprarMultiplicador);
    layoutMult->addWidget(lblMultiplicador);
    layoutMult->addStretch();
    layoutMult->addWidget(btnMultiplicador);

    QGroupBox* grupoVel= new QGroupBox("⚡ Velocidad de plataforma");
    grupoVel->setStyleSheet(estiloGrupo);
    QHBoxLayout* layoutVel= new QHBoxLayout(grupoVel);
    lblVelocidad= new QLabel();
    lblVelocidad->setStyleSheet(estiloInfo);
    btnVelocidad= new QPushButton("");
    btnVelocidad->setStyleSheet(estiloBtn);
    btnVelocidad->setFixedWidth(120);
    connect(btnVelocidad, &QPushButton::clicked, this, &PantallaTienda::comprarVelocidadPlataforma);
    layoutVel->addWidget(lblVelocidad);
    layoutVel->addStretch();
    layoutVel->addWidget(btnVelocidad);

    QGroupBox* grupoBlindaje= new QGroupBox("🛡 Blindaje (rompe bloques blindados)");
    grupoBlindaje->setStyleSheet(estiloGrupo);
    QHBoxLayout* layoutBlindaje= new QHBoxLayout(grupoBlindaje);
    lblBlindaje= new QLabel();
    lblBlindaje->setStyleSheet(estiloInfo);
    btnBlindaje= new QPushButton("");
    btnBlindaje->setStyleSheet(estiloBtn);
    btnBlindaje->setFixedWidth(120);
    connect(btnBlindaje, &QPushButton::clicked, this, &PantallaTienda::comprarBlindaje);
    layoutBlindaje->addWidget(lblBlindaje);
    layoutBlindaje->addStretch();
    layoutBlindaje->addWidget(btnBlindaje);

    QGroupBox* grupoPrestigio= new QGroupBox("⭐ Prestigiar");
    grupoPrestigio->setStyleSheet(estiloGrupo);
    QHBoxLayout* layoutPrestigio= new QHBoxLayout(grupoPrestigio);
    lblPrestigio= new QLabel();
    lblPrestigio->setStyleSheet(estiloInfo);
    btnPrestigio= new QPushButton("");
    btnPrestigio->setStyleSheet(estiloBtn);
    btnPrestigio->setFixedWidth(120);
    connect(btnPrestigio, &QPushButton::clicked, this, &PantallaTienda::hacerPrestigio);
    layoutPrestigio->addWidget(lblPrestigio);
    layoutPrestigio->addStretch();
    layoutPrestigio->addWidget(btnPrestigio);

    QPushButton* btnVolver= new QPushButton("← Volver al menú");
    btnVolver->setStyleSheet("QPushButton {"
                            "   background-color: transparent;"
                            "   color: "+COLORFONT+";"
                            "   font-size: 16px;"
                            "   font-weight: bold;"
                            "   border: 2px solid white;"
                            "   border-radius: 8px;"
                            "   padding: 8px 16px;"
                            "}"
                            "QPushButton:hover {"
                            "   background-color: "+COLORBOTONHOVER+";"
                            "}"
                            "QPushButton:pressed {"
                            "   background-color: "+COLORBOTONPRESSED+";"
                            "}");
    connect(btnVolver, &QPushButton::clicked, this, &PantallaTienda::volverAlMenu);

    layoutContenedor->addWidget(lblTitulo);
    layoutContenedor->addWidget(lblCreditos);
    layoutContenedor->addSpacing(20);
    layoutContenedor->addWidget(grupoDano);
    layoutContenedor->addWidget(grupoMult);
    layoutContenedor->addWidget(grupoVel);
    layoutContenedor->addWidget(grupoBlindaje);
    layoutContenedor->addSpacing(10);
    layoutContenedor->addWidget(grupoPrestigio);
    layoutContenedor->addSpacing(20);
    layoutContenedor->addWidget(btnVolver, 0, Qt::AlignHCenter);
    layoutContenedor->addStretch();

    layoutPrincipal->addWidget(contenedor, 0, Qt::AlignHCenter);
    layoutPrincipal->addStretch();

    actualizarUI();
}

void PantallaTienda::actualizarUI(){
    if(perfil==nullptr){
        lblCreditos->setText("0 🪙");
        return;
    }

    lblCreditos->setText(QString("%1 🪙").arg(qRound(perfil->getCreditos())));

    int nivelDamage= perfil->getNivelDañoBola();
    int damageActual= nivelDamage;
    int mejorasDano= nivelDamage - 1;
    if(nivelDamage>=MAX_NIVEL_DANO){
        lblDano->setText(QString("Daño: %1 (MÁX) - Mejora %2 / 5").arg(damageActual).arg(mejorasDano));
        btnDano->setText("MÁX");
        btnDano->setEnabled(false);
    }else{
        int costo= 100 * nivelDamage;
        lblDano->setText(QString("Daño: %1 → %2 - Mejora %3 / 5").arg(damageActual).arg(damageActual + 1).arg(mejorasDano));
        btnDano->setText(QString("%1 🪙").arg(costo));
        btnDano->setEnabled(perfil->getCreditos() >= costo);
    }

    int nivelMult= perfil->getNivelMultiplicadorMonedas();
    if(nivelMult >= MAX_NIVEL_MEJORA){
        lblMultiplicador->setText(QString("Nivel %1 / %2 (MÁX)").arg(nivelMult).arg(MAX_NIVEL_MEJORA));
        btnMultiplicador->setText("MÁX");
        btnMultiplicador->setEnabled(false);
    }else{
        int costo= 150*nivelMult;
        double multActual= 1+ 0.5*(nivelMult-1);
        double multSiguiente= 1.0+0.5*nivelMult;
        lblMultiplicador->setText(QString("Nivel %1 / %2 - x%3 → x%4")
                                      .arg(nivelMult).arg(MAX_NIVEL_MEJORA)
                                      .arg(multActual, 0, 'f', 1)
                                      .arg(multSiguiente, 0, 'f', 1));
        btnMultiplicador->setText(QString("%1 🪙").arg(costo));
        btnMultiplicador->setEnabled(perfil->getCreditos() >= costo);
    }

    int nivelVel= perfil->getNivelVelocidadPlataforma();
    if(nivelVel>=MAX_NIVEL_MEJORA){
        lblVelocidad->setText(QString("Nivel %1 / %2 (MÁX) - +%3 de velocidad")
                                  .arg(nivelVel).arg(MAX_NIVEL_MEJORA).arg(nivelVel - 1));
        btnVelocidad->setText("MÁX");
        btnVelocidad->setEnabled(false);
    }else{
        int costo= 100*nivelVel;
        lblVelocidad->setText(QString("Nivel %1 / %2 - +%3 de velocidad")
                                  .arg(nivelVel).arg(MAX_NIVEL_MEJORA).arg(nivelVel - 1));
        btnVelocidad->setText(QString("%1 🪙").arg(costo));
        btnVelocidad->setEnabled(perfil->getCreditos()>=costo);
    }

    if(perfil->getDesbloqueoBlindaje()){
        lblBlindaje->setText("Desbloqueado ✔");
        btnBlindaje->setText("COMPRADO");
        btnBlindaje->setEnabled(false);
    }else{
        lblBlindaje->setText(QString("Costo: %1 🪙").arg(COSTO_BLINDAJE));
        btnBlindaje->setText(QString("%1 🪙").arg(COSTO_BLINDAJE));
        btnBlindaje->setEnabled(perfil->getCreditos() >= COSTO_BLINDAJE);
    }
    bool todasMax= perfil->getNivelDañoBola()>=MAX_NIVEL_DANO
                    && perfil->getNivelMultiplicadorMonedas()>=MAX_NIVEL_MEJORA
                    && perfil->getNivelVelocidadPlataforma()>=MAX_NIVEL_MEJORA
                    && perfil->getDesbloqueoBlindaje();
    int nivelPres= perfil->getNivelPrestigio();
    double bonusActual= 1+0.5*nivelPres;
    double bonusSiguiente= 1+0.5*(nivelPres+ 1);
    if(!todasMax){
        lblPrestigio->setText("Completa todas las mejoras para desbloquear el Prestigio");
        btnPrestigio->setText("🔒");
        btnPrestigio->setEnabled(false);
    }else{
        lblPrestigio->setText(QString("Nivel de prestigio: %1 - Bonus permanente: x%2 → x%3")
                                  .arg(nivelPres)
                                  .arg(bonusActual, 0, 'f', 1)
                                  .arg(bonusSiguiente, 0, 'f', 1));
        btnPrestigio->setText("⭐ Prestigio");
        btnPrestigio->setEnabled(true);
    }
}

void PantallaTienda::comprarDamage(){
    if(perfil==nullptr){
        return;
    }
    int nivel= perfil->getNivelDañoBola();
    if(nivel>=MAX_NIVEL_DANO){
        return;
    }
    int costo= 100*nivel;
    if(perfil->gastarCreditos(costo)){
        perfil->subirNivelDañoBola();
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), *perfil);
        actualizarUI();
    }else{
        QMessageBox::information(this, "Tienda", "No tienes suficientes créditos.");
    }
}

void PantallaTienda::comprarMultiplicador(){
    if(perfil==nullptr){
        return;
    }
    int nivel= perfil->getNivelMultiplicadorMonedas();
    if(nivel>=MAX_NIVEL_MEJORA){
        return;
    }
    int costo= 150*nivel;
    if(perfil->gastarCreditos(costo)){
        perfil->subirNivelMultiplicadorMonedas();
        perfil->setMultiplicador(1+0.5* (perfil->getNivelMultiplicadorMonedas()-1));
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), *perfil);
        actualizarUI();
    }else{
        QMessageBox::information(this, "Tienda", "No tienes suficientes créditos.");
    }
}

void PantallaTienda::comprarVelocidadPlataforma(){
    if(perfil==nullptr){
        return;
    }
    int nivel= perfil->getNivelVelocidadPlataforma();
    if(nivel>=MAX_NIVEL_MEJORA){
        return;
    }
    int costo= 100*nivel;
    if(perfil->gastarCreditos(costo)){
        perfil->subirNivelVelocidadPlataforma();
        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
        ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), *perfil);
        actualizarUI();
    }else{
        QMessageBox::information(this, "Tienda", "No tienes suficientes créditos.");
    }
}

void PantallaTienda::comprarBlindaje(){
    if(perfil==nullptr){
        return;
    }
    if(perfil->getDesbloqueoBlindaje()){
        return;
    }
    if(perfil->gastarCreditos(COSTO_BLINDAJE)){
        perfil->desbloquearBlindaje();
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), *perfil);
        actualizarUI();
    }else{
        QMessageBox::information(this, "Tienda", "No tienes suficientes créditos.");
    }
}

void PantallaTienda::hacerPrestigio(){
    if(perfil== nullptr){
        return;
    }
    int nivelPres= perfil->getNivelPrestigio();
    double bonusSiguiente= 1+0.5*(nivelPres+1);

    QMessageBox cuadro(this);
    cuadro.setWindowTitle("⭐ Prestigio");
    cuadro.setText(QString("¿Hacer Prestigio?\n\n"
                           "Reiniciarás tus mejoras y monedas (0 🪙) a cambio de:\n"
                           "• Bonus permanente de monedas: x%1\n"
                           "• Nivel de prestigio: %2\n\n"
                           "Tus niveles desbloqueados e historia se conservan.")
                       .arg(bonusSiguiente, 0, 'f', 1)
                       .arg(nivelPres + 1));
    QPushButton* btnSi= cuadro.addButton("⭐ ¡Sí, prestigio!", QMessageBox::AcceptRole);
    cuadro.addButton("Cancelar", QMessageBox::RejectRole);
    cuadro.exec();

    if(cuadro.clickedButton()!= btnSi){
        return;
    }

    perfil->hacerPrestigio();
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), *perfil);
    actualizarUI();
}

void PantallaTienda::volverAlMenu(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PantallaMenuPrincipal* pantallaMenu= new PantallaMenuPrincipal(ventana);
    ventana->cambiarPantalla(pantallaMenu);
}