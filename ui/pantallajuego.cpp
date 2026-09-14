#include "pantallajuego.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include "EstadisticasJugador.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBrush>
#include <QPen>
#include <QtMath>
#include <QDialog>
#include <QMessageBox>

PantallaJuego::PantallaJuego(int nivel, QWidget* parent)
    : QWidget(parent){
    motor= new MotorJuego(nivel);
    ptrBloques = nullptr;
    cargarUi();
}

PantallaJuego::PantallaJuego(Partida* partidaCargada, QWidget* parent)
    : QWidget(parent){
    motor= new MotorJuego(partidaCargada->getNivel()->getNumeroNivel());
    motor->partidaActual= partidaCargada;
    ptrBloques= nullptr;
    cargarUi();
}

PantallaJuego::~PantallaJuego(){
    timerJuego->stop();
    liberarBloques();
    if(itemsPelotas!=nullptr){
        int cant= motor->getPartida()->getCantidadPelotas();
        for(int i=0;i<cant;i++){
            delete itemsPelotas[i];
        }
        delete[] itemsPelotas;
        itemsPelotas=nullptr;
    }
    for(int i=0;i<cantidadPowerUps;i++){
        delete itemsPowerUps[i];
    }
    delete[] itemsPowerUps;

    for(int i=0;i<cantidadOrbes;i++){
        delete itemsOrbes[i];
    }
    delete[] itemsOrbes;

    delete motor;
    motor= nullptr;
}

void PantallaJuego::cargarUi(){
    this->setStyleSheet("background-color: #000000;");
    moverIzq= false;
    moverDer= false;
    esperando= true;
    itemsPelotas= nullptr;
    itemsPowerUps= nullptr;
    cantidadPowerUps= 0;
    itemsOrbes= nullptr;
    cantidadOrbes=0;
    monedasAcumuladas= 0;
    enPausa= false;

    QVBoxLayout* layoutVertical= new QVBoxLayout(this);

    cargarHUD(layoutVertical);

    QHBoxLayout* layoutCentro= new QHBoxLayout();
    escena= new QGraphicsScene(0, 0, LIMITE_PANTALLA, 480, this);
    vista= new QGraphicsView(escena, this);
    vista->setFocusPolicy(Qt::NoFocus);
    vista->setStyleSheet("border: 2px solid white; background-color: #000000;");

    layoutCentro->addStretch();
    layoutCentro->addWidget(vista);
    layoutCentro->addStretch();
    layoutVertical->addLayout(layoutCentro);
    layoutVertical->addStretch();

    dibujarBloques();
    dibujarPlataforma();
    dibujarPelotas();

    totalBloques= motor->getPartida()->getNivel()->getBloquesRestantes();
    cronometro.start();

    timerJuego= new QTimer(this);
    connect(timerJuego, &QTimer::timeout,this,&PantallaJuego::actualizarJuego);
    timerJuego->start(16);
    actualizarHUD();

    this->setFocus();
}
void PantallaJuego::actualizarHUD(){
    lblVidas->setText(QString("Vidas: %1").arg(motor->partidaActual->getVidas()));
    lblPuntos->setText(QString("Puntos: %1").arg(motor->partidaActual->getPuntaje()));
    lblBloques->setText(QString("Bloques: %1 / %2").arg(motor->partidaActual->getNivel()->getBloquesRestantes()).arg(totalBloques));
    lblTiempo->setText(QString("Tiempo: %1 secs").arg(cronometro.elapsed()/1000));
    lblMonedas->setText(QString("Monedas: %1").arg(monedasAcumuladas));

    lblAviso->setVisible(esperando);
    if(esperando){
        int x= vista->x()+(vista->width()- lblAviso->width())/2;
        int y= vista->y()+vista->height()-120;
        lblAviso->move(x, y);
        lblAviso->raise();
    }
}
void PantallaJuego::cargarHUD(QVBoxLayout* layoutVertical){
    QHBoxLayout* layoutHUD= new QHBoxLayout();
    layoutHUD->setContentsMargins(20, 10, 20, 10);

    QString estiloLabel="color: "+COLORFONT+";"
                        "font-size: 18px;"
                        "font-weight: bold;"
                        "background-color: transparent;";

    lblVidas= new QLabel();
    lblPuntos= new QLabel();
    lblTiempo=new QLabel();
    lblBloques=new QLabel();
    lblMonedas= new QLabel();

    lblVidas->setStyleSheet(estiloLabel);
    lblPuntos->setStyleSheet(estiloLabel);
    lblTiempo->setStyleSheet(estiloLabel);
    lblBloques->setStyleSheet(estiloLabel);
    lblMonedas->setStyleSheet(estiloLabel);

    layoutHUD->addWidget(lblVidas);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblBloques);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblMonedas);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblPuntos);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblTiempo);

    layoutVertical->addLayout(layoutHUD);

    lblAviso= new QLabel(this);
    lblAviso->setText("Presiona W / ↑ / ESPACIO para lanzar");
    lblAviso->setAlignment(Qt::AlignCenter);
    lblAviso->setFixedSize(320, 30);
    lblAviso->setStyleSheet("color: "+COLORFONT+";"
                            "font-size: 14px;"
                            "font-weight: bold;"
                            "background-color: rgba(0,0,0,150);"
                            "border-radius: 6px;");

}
void PantallaJuego::liberarBloques(){
    if(ptrBloques==nullptr){
        return;
    }
    for(int i=0;i<filas;i++){
        delete[] ptrBloques[i];
    }
    delete[] ptrBloques;
    ptrBloques=nullptr;
}
void PantallaJuego::dibujarBloques(){
    Nivel* nivelActual= motor->getPartida()->getNivel();
    filas= nivelActual->getFilas();
    col= nivelActual->getColumnas();

    ptrBloques= new QGraphicsRectItem**[filas];

    for(int i=0;i<filas;i++){
        ptrBloques[i]= new QGraphicsRectItem*[col];
        for(int j=0;j<col;j++){
            ptrBloques[i][j]= nullptr;

            Bloque* bloque= nivelActual->getMatriz()[i][j];
            if(bloque==nullptr){
                continue;
            }

            QGraphicsRectItem* item= escena->addRect(0, 0, BRICK_ANCHO, BRICK_ALTO,
                                                      QPen(Qt::black),bloque->getColor());
            item->setPos(10+bloque->getPosX()*BRICK_ANCHO, bloque->getPosY()*BRICK_ALTO);
            ptrBloques[i][j]= item;

        }
    }
}
void PantallaJuego::dibujarPlataforma(){
    Plataforma* plat= motor->getPartida()->getPlataforma();
    itemPlataforma= escena->addRect(0,0,plat->getAncho(),plat->getAlto(),QPen(Qt::white), QBrush(Qt::white));
    itemPlataforma->setPos(plat->getX(),plat->getY());
}
void PantallaJuego::dibujarPelotas(){
    int cant= motor->getPartida()->getCantidadPelotas();
    itemsPelotas= new QGraphicsEllipseItem*[cant];

    for(int i=0;i<cant;i++){
        Pelota* pelota= motor->partidaActual->getPelotas()[i];
        QGraphicsEllipseItem* item= escena->addEllipse(0,0,pelota->getDiametro(),pelota->getDiametro(),QPen(Qt::white), QBrush(Qt::white));
        item->setPos(pelota->getX(),pelota->getY());
        itemsPelotas[i]=item;
    }
}

void PantallaJuego::keyPressEvent(QKeyEvent* event){
    if(event->isAutoRepeat()){
        return;
    }
    if(event->key()==Qt::Key_Left || event->key()==Qt::Key_A){
        moverIzq= true;
    }else if(event->key()==Qt::Key_Right || event->key()== Qt::Key_D){
        moverDer= true;
    }else if(event->key()==Qt::Key_W || event->key()==Qt::Key_Up || event->key()==Qt::Key_Space){
        if(esperando){
            esperando= false;
            motor->lanzarPelotaInicial();
        }
    }else if(event->key()==Qt::Key_Escape){
        togglePausa();
    }
}
void PantallaJuego::keyReleaseEvent(QKeyEvent* event){
    if(event->isAutoRepeat()){
        return;
    }
    if(event->key()== Qt::Key_Left || event->key()== Qt::Key_A){
        moverIzq=false;
    }else if(event->key()==Qt::Key_Right || event->key()==Qt::Key_D){
        moverDer= false;
    }
}
void PantallaJuego::actualizarJuego(){
    EstadisticasJugador stats;
    stats.damage= 4;
    stats.tieneMejoraArmadura= true;
    motor->actualizarJuego(moverIzq,moverDer,esperando,stats);

    int fila, col;
    if(motor->huboDestruccion(fila,col)){
        escena->removeItem(ptrBloques[fila][col]);
        delete ptrBloques[fila][col];
        ptrBloques[fila][col]= nullptr;

        PowerUp* power= motor->huboPowerUpNuevo();
        if(power!=nullptr){
            agregarPowerUp(power);
            delete power;
        }
    }else if(motor->huboToque(fila,col)){
        ptrBloques[fila][col]->setBrush(motor->getPartida()->getNivel()->getMatriz()[fila][col]->getColor());
    }
    int indiceEliminadp=-1;
    if(motor->huboPowerUpEliminado(indiceEliminadp)){
        eliminarPowerUp(indiceEliminadp);
    }
    TIPO_POWERUP tipoAplicado;
    if(motor->huboPowerUpAplicado(tipoAplicado)){
        if(tipoAplicado==BOLA_EXTRA){
            sincronizarPelotasExtra();
        }else if(tipoAplicado== VIDA_EXTRA){
            actualizarHUD();
        }
    }
    int xOrbe, yOrbe, valorOrbe;
    if(motor->huboNuevoOrbe(xOrbe, yOrbe, valorOrbe)){
        agregarOrbe(xOrbe,yOrbe,valorOrbe);
    }
    int idxOrbeEliminado;
    if(motor->huboOrbeEliminado(idxOrbeEliminado)){
        eliminarOrbe(idxOrbeEliminado);
    }
    int valorRecogido;
    if(motor->huboOrbeRecogido(valorRecogido)){
        monedasAcumuladas+= valorRecogido;
    }

    actualizarPosiciones();
    actualizarHUD();
    manejarFinDePartida();
}
void PantallaJuego::actualizarPosiciones(){
    Plataforma* plat= motor->getPartida()->getPlataforma();
    itemPlataforma->setRect(0, 0, plat->getAncho(), plat->getAlto());
    itemPlataforma->setPos(plat->getX(),plat->getY());

    int cant= motor->getPartida()->getCantidadPelotas();
    Pelota** pelotas= motor->getPartida()->getPelotas();
    for(int i=0;i<cant;i++){
        itemsPelotas[i]->setPos(pelotas[i]->getX(),pelotas[i]->getY());
    }

    PowerUp** powers= motor->getPowerUps();
    for(int i=0;i<cantidadPowerUps;i++){
        itemsPowerUps[i]->setPos(powers[i]->getX(),powers[i]->getY());
    }
    Orbe** orbes= motor->getOrbes();
    for(int i=0;i<cantidadOrbes;i++){
        itemsOrbes[i]->setPos(orbes[i]->getX(), orbes[i]->getY());
    }
}



void PantallaJuego::agregarPowerUp(PowerUp* nuevoPower){
    QGraphicsRectItem** nuevosItems= new QGraphicsRectItem*[cantidadPowerUps + 1];

    for(int i=0; i<cantidadPowerUps; i++){
        nuevosItems[i]= itemsPowerUps[i];
    }
    QGraphicsRectItem* item= escena->addRect(0, 0, nuevoPower->getAncho(), nuevoPower->getAlto(), QPen(Qt::black), nuevoPower->getColor());
    item->setPos(nuevoPower->getX(), nuevoPower->getY());
    nuevosItems[cantidadPowerUps]= item;

    delete[] itemsPowerUps;
    itemsPowerUps= nuevosItems;
    cantidadPowerUps++;
}

void PantallaJuego::eliminarPowerUp(int indice){
    if(indice<0 || indice>=cantidadPowerUps) return;

    escena->removeItem(itemsPowerUps[indice]);
    delete itemsPowerUps[indice];

    QGraphicsRectItem** nuevosItems= nullptr;
    if(cantidadPowerUps-1>0){
        nuevosItems= new QGraphicsRectItem*[cantidadPowerUps-1];
        int pos=0;
        for(int i=0;i<cantidadPowerUps;i++){
            if(i!=indice){
                nuevosItems[pos]=itemsPowerUps[i];
                pos++;
            }
        }
    }
    delete[] itemsPowerUps;
    itemsPowerUps=nuevosItems;
    cantidadPowerUps--;
}
void PantallaJuego::agregarOrbe(int x, int y, int valor){
    QGraphicsEllipseItem** ptrNuevo= new QGraphicsEllipseItem*[cantidadOrbes+1];

    for(int i=0;i<cantidadOrbes;i++){
        ptrNuevo[i]= itemsOrbes[i];
    }
    QGraphicsEllipseItem* item= escena->addEllipse(0,0,14,14,QPen(Qt::black),QBrush(QColor(255,215,0)));
    item->setPos(x,y);
    ptrNuevo[cantidadOrbes]= item;

    delete[] itemsOrbes;
    itemsOrbes= ptrNuevo;
    cantidadOrbes++;
}
void PantallaJuego::eliminarOrbe(int indice){
    if(indice<0 || indice>=cantidadOrbes){
        return;
    }
    escena->removeItem(itemsOrbes[indice]);
    delete itemsOrbes[indice];

    QGraphicsEllipseItem** ptrNuevo= nullptr;
    if(cantidadOrbes-1>0){
        ptrNuevo= new QGraphicsEllipseItem*[cantidadOrbes-1];
        int pos=0;
        for(int i=0;i<cantidadOrbes;i++){
            if(i!=indice){
                ptrNuevo[pos]= itemsOrbes[i];
                pos++;
            }
        }
    }
    delete[] itemsOrbes;
    itemsOrbes= ptrNuevo;
    cantidadOrbes--;
}
void PantallaJuego::sincronizarPelotasExtra(){
    int nuevaCant= motor->getPartida()->getCantidadPelotas();
    QGraphicsEllipseItem** nuevaLista= new QGraphicsEllipseItem*[nuevaCant];

    for(int i=0;i<nuevaCant-1;i++){
        nuevaLista[i]= itemsPelotas[i];
    }
    Pelota* nueva= motor->getPartida()->getPelotas()[nuevaCant-1];
    QGraphicsEllipseItem* item= escena->addEllipse(0,0,nueva->getDiametro(),nueva->getDiametro(),QPen(Qt::white),QBrush(Qt::white));
    item->setPos(nueva->getX(), nueva->getY());
    nuevaLista[nuevaCant-1]= item;

    delete[] itemsPelotas;
    itemsPelotas= nuevaLista;
}
void PantallaJuego::togglePausa(){
    if(enPausa){
        return;
    }
    enPausa= true;
    timerJuego->stop();
    QMessageBox cuadro(this);
    cuadro.setWindowTitle("Pausa");
    cuadro.setText("Juego En Pausa");
    QPushButton* btnContinuar= cuadro.addButton("Continuar",QMessageBox::AcceptRole);
    QPushButton* btnMenu= cuadro.addButton("Volver al menu",QMessageBox::RejectRole);

    cuadro.exec();
    if(cuadro.clickedButton()==btnMenu){
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        PantallaMenuPrincipal*  pantallaMenu= new PantallaMenuPrincipal();
        ventana->cambiarPantalla(pantallaMenu);
        return;
    }
    enPausa= false;
    timerJuego->start(16);
    this->setFocus();
}
void PantallaJuego::regenerarNivel(bool fueGameOver){
    liberarBloques();
    motor->getPartida()->getNivel()->regenerar();
    dibujarBloques();
    totalBloques= motor->getPartida()->getNivel()->getBloquesRestantes();

    if(fueGameOver){
        motor->getPartida()->reiniciarVidasYPuntaje();
        motor->getPartida()->agregarPelotaExtra(LIMITE_PANTALLA/2,420);
        dibujarPelotas();
    }
    Plataforma* plat= motor->getPartida()->getPlataforma();
    plat->setPosicion((LIMITE_PANTALLA-plat->getAncho())/2, plat->getY());

    esperando= true;
    actualizarHUD();

}
void PantallaJuego::manejarFinDePartida(){
    if(!esperando){
        int cant= motor->partidaActual->getCantidadPelotas();
        Pelota** pelotas= motor->partidaActual->getPelotas();

        for(int i=0;i<cant;i++){
            if(pelotas[i]->getY()>480){
                escena->removeItem(itemsPelotas[i]);
                delete itemsPelotas[i];

                QGraphicsEllipseItem** nuevaListaItems= nullptr;
                if(cant-1>0){
                    nuevaListaItems= new QGraphicsEllipseItem*[cant-1];
                    int pos=0;
                    for(int k=0;k<cant;k++){
                        if(k!=i){
                            nuevaListaItems[pos]=itemsPelotas[k];
                            pos++;
                        }
                    }
                }
                delete[] itemsPelotas;
                itemsPelotas=nuevaListaItems;

                motor->partidaActual->eliminarPelota(i);

                if(motor->partidaActual->getCantidadPelotas()<=0){
                    motor->partidaActual->perderVida();
                    motor->limpiarPowerUpsYOrbes();

                    for(int i=0;i<cantidadPowerUps;i++){
                        escena->removeItem(itemsPowerUps[i]);
                        delete itemsPowerUps[i];
                    }
                    delete[] itemsPowerUps;
                    itemsPowerUps= nullptr;
                    cantidadPowerUps= 0;

                    for(int i=0;i<cantidadOrbes;i++){
                        escena->removeItem(itemsOrbes[i]);
                        delete itemsOrbes[i];
                    }
                    delete[] itemsOrbes;
                    itemsOrbes= nullptr;
                    cantidadOrbes= 0;

                    if(motor->partidaActual->estaTerminada()){
                        timerJuego->stop();
                        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
                        PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal();
                        ventana->cambiarPantalla(pantallaMenu);
                        return;
                    }
                    motor->partidaActual->agregarPelotaExtra(LIMITE_PANTALLA/2,420);
                    dibujarPelotas();

                    Plataforma* plat= motor->partidaActual->getPlataforma();
                    plat->setPosicion((LIMITE_PANTALLA-plat->getAncho())/2,plat->getY());
                    esperando=true;
                }
                break;
            }
        }
    }
    if(motor->partidaActual->nivelCompletado()){
       regenerarNivel(false);
       motor->limpiarPowerUpsYOrbes();
    }
}