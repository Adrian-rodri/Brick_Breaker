#include "pantallajuego.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBrush>
#include <QPen>
#include <QtMath>
#include <iostream>
#include <QRandomGenerator>
PantallaJuego::PantallaJuego(int nivel, QWidget* parent)
    : QWidget(parent){
    std::cout<<"Pr";
    partidaActual= new Partida(nivel);
    ptrBloques = nullptr;
    velocidad= 6.0+(nivel-1)*1.5;
    partidaActual->getPlataforma()->setVelocidad(7+(nivel-1)* 2);
    cargarUi();
}

PantallaJuego::PantallaJuego(Partida* partidaCargada, QWidget* parent)
    : QWidget(parent){
    partidaActual= partidaCargada;
    ptrBloques= nullptr;
    velocidad= 6.0;
    cargarUi();
}

PantallaJuego::~PantallaJuego(){
    timerJuego->stop();
    liberarBloques();
    if(itemsPelotas!=nullptr){
        int cant= partidaActual->getCantidadPelotas();
        for(int i=0;i<cant;i++){
            delete itemsPelotas[i];
        }
        delete[] itemsPelotas;
        itemsPelotas=nullptr;
    }
    for(int i=0;i<cantidadPowerUps;i++){
        delete itemsPowerUps[i];
        delete ptrPowerUps[i];
    }
    delete[] itemsPowerUps;
    delete[] ptrPowerUps;

    delete partidaActual;
    partidaActual= nullptr;
}

void PantallaJuego::cargarUi(){
    this->setStyleSheet("background-color: #000000;");
    moverIzq= false;
    moverDer= false;
    esperando= true;
    itemsPelotas= nullptr;
    ptrPowerUps= nullptr;
    itemsPowerUps= nullptr;
    cantidadPowerUps= 0;
    contadorPlataformaGrande= 0;
    anchoOriginalPlataforma= PLATAFORMA_ANCHO;

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

    totalBloques= partidaActual->getNivel()->getBloquesRestantes();
    cronometro.start();

    timerJuego= new QTimer(this);
    connect(timerJuego, &QTimer::timeout,this,&PantallaJuego::actualizarJuego);
    timerJuego->start(16);
    actualizarHUD();

    this->setFocus();
}
void PantallaJuego::actualizarHUD(){
    lblVidas->setText(QString("Vidas: %1").arg(partidaActual->getVidas()));
    lblPuntos->setText(QString("Puntos: %1").arg(partidaActual->getPuntaje()));
    lblBloques->setText(QString("Bloques: %1 / %2").arg(partidaActual->getNivel()->getBloquesRestantes()).arg(totalBloques));
    lblTiempo->setText(QString("Tiempo: %1 secsw").arg(cronometro.elapsed()/1000));

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

    lblVidas->setStyleSheet(estiloLabel);
    lblPuntos->setStyleSheet(estiloLabel);
    lblTiempo->setStyleSheet(estiloLabel);
    lblBloques->setStyleSheet(estiloLabel);

    layoutHUD->addWidget(lblVidas);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblBloques);
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
    Nivel* nivelActual= partidaActual->getNivel();
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
    Plataforma* plat= partidaActual->getPlataforma();
    itemPlataforma= escena->addRect(0,0,plat->getAncho(),plat->getAlto(),QPen(Qt::white), QBrush(Qt::white));
    itemPlataforma->setPos(plat->getX(),plat->getY());
}
void PantallaJuego::dibujarPelotas(){
    int cant= partidaActual->getCantidadPelotas();
    itemsPelotas= new QGraphicsEllipseItem*[cant];

    for(int i=0;i<cant;i++){
        Pelota* pelota= partidaActual->getPelotas()[i];
        QGraphicsEllipseItem* item= escena->addEllipse(0,0,pelota->getDiametro(),pelota->getDiametro(),QPen(Qt::white), QBrush(Qt::white));
        item->setPos(pelota->getX(),pelota->getY());
        itemsPelotas[i]=item;
    }
}
void PantallaJuego::lanzarPelota(){
    double anguloInicial=25.0;
    double anguloEnRads= qDegreesToRadians(anguloInicial);

    int velX= (int)(velocidad*qSin(anguloEnRads));
    int velY= (int)(-velocidad*qCos(anguloEnRads));
    partidaActual->getPelotas()[0]->setVelocidad(velX,velY);
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
            partidaActual->getPlataforma()->setAncho(PLATAFORMA_ANCHO);
            lanzarPelota();
        }
    }else if(event->key()==Qt::Key_Escape){
        esperando=true;
    }
    if(event->key()==Qt::Key_P){
        partidaActual->getPlataforma()->setAncho(partidaActual->getPlataforma()->getAncho()+6);
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
    Plataforma* plat= partidaActual->getPlataforma();
    if(moverIzq){
        plat->moverIzquierda();
    }
    if(moverDer){
        plat->moverDerecha();
    }

    if(contadorPlataformaGrande>0){
        contadorPlataformaGrande--;
        if(contadorPlataformaGrande==0){
            plat->setAncho(anchoOriginalPlataforma);
        }
    }

    int cant= partidaActual->getCantidadPelotas();
    Pelota** pelotas= partidaActual->getPelotas();

    if(esperando){
        int posX=plat->getX() + plat->getAncho()/2 -pelotas[0]->getDiametro()/2;
        int posY=plat->getY()- pelotas[0]->getDiametro();
        pelotas[0]->setPosicion(posX,posY);
    }else{
        for(int i=0;i<cant;i++){
            pelotas[i]->mover();
        }
        manejarColisiones();
        actualizarPowerUps();
    }
    actualizarPosiciones();
    actualizarHUD();
    manejarFinDePartida();
}
void PantallaJuego::actualizarPosiciones(){
    Plataforma* plat= partidaActual->getPlataforma();
    itemPlataforma->setRect(0, 0, plat->getAncho(), plat->getAlto());
    itemPlataforma->setPos(plat->getX(),plat->getY());
    int cant= partidaActual->getCantidadPelotas();
    Pelota** pelotas= partidaActual->getPelotas();
    for(int i=0;i<cant;i++){
        itemsPelotas[i]->setPos(pelotas[i]->getX(),pelotas[i]->getY());
}
}
void PantallaJuego::manejarColisiones(){
    int cant= partidaActual->getCantidadPelotas();
    Pelota** pelotas= partidaActual->getPelotas();
    for(int i=0;i<cant;i++){
        manejarColisionesPelota(pelotas[i]);
    }
}

void PantallaJuego::manejarColisionesPelota(Pelota* pelota){
    Plataforma* plat= partidaActual->getPlataforma();
    int diametro= pelota->getDiametro();

    if(pelota->getX()<=0){
        pelota->setPosicion(0,pelota->getY());
        pelota->invertirVelocidadX();
    }
    if(pelota->getX()+diametro>= LIMITE_PANTALLA){
        pelota->setPosicion(LIMITE_PANTALLA-diametro,pelota->getY());
        pelota->invertirVelocidadX();
    }
    if(pelota->getY()<=0){
        pelota->setPosicion(pelota->getX(),0);
        pelota->invertirVelocidadY();
    }
    QRectF rectPelota(pelota->getX(),pelota->getY(),diametro,diametro);
    QRectF rectPlat(plat->getX(),plat->getY(),plat->getAncho(),plat->getAlto());

    if(rectPelota.intersects(rectPlat)&& pelota->getVelocidadY()>0){
        rebotarEnPlataforma(pelota);
        return;
    }
    Nivel* nivel= partidaActual->getNivel();
    for(int i=0;i<filas;i++){
        for(int j=0;j<col;j++){
            Bloque* bloque= nivel->getMatriz()[i][j];
            if(bloque==nullptr){
                continue;
            }
            QRectF rectBloque(10+bloque->getPosX()*BRICK_ANCHO, bloque->getPosY()*BRICK_ALTO,BRICK_ANCHO,BRICK_ALTO);

            if(rectPelota.intersects(rectBloque)){
                bloque->recibirGolpe();
                if(bloque->estaRoto()){
                    partidaActual->sumarPuntos(bloque->getPuntos());
                    intentarSoltarPowerUp(10+bloque->getPosX()*BRICK_ANCHO, bloque->getPosY()*BRICK_ALTO);

                    escena->removeItem(ptrBloques[i][j]);
                    delete ptrBloques[i][j];
                    ptrBloques[i][j]= nullptr;

                    nivel->destruirBloque(i,j);
                }else{
                    ptrBloques[i][j]->setBrush(bloque->getColor());
                }
                double collisionX= qMin(rectPelota.right(), rectBloque.right())- qMax(rectPelota.left(),rectBloque.left());
                double collisionY= qMin(rectPelota.bottom(),rectBloque.bottom())- qMax(rectPelota.top(),rectBloque.top());

                if(collisionX<collisionY){
                    pelota->invertirVelocidadX();
                    if(rectPelota.center().x()<rectBloque.center().x()){
                        pelota->setPosicion(rectBloque.left()-diametro, pelota->getY());
                    }else{
                        pelota->setPosicion(rectBloque.right(), pelota->getY());
                    }
                }else{
                    pelota->invertirVelocidadY();
                    if (rectPelota.center().y() < rectBloque.center().y()) {
                        pelota->setPosicion(pelota->getX(), rectBloque.top() - diametro);
                    } else {
                        pelota->setPosicion(pelota->getX(), rectBloque.bottom());
                    }
                }
                return;
            }
        }
    }
}
void PantallaJuego::rebotarEnPlataforma(Pelota* pelota){
    Plataforma* plat= partidaActual->getPlataforma();

    double centroPelota= pelota->getX()+pelota->getDiametro()/2.0;
    double centroPlat= plat->getX()+plat->getAncho()/2.0;

    double proporcion= (centroPelota- centroPlat)/(plat->getAncho()/2.0);

    if(proporcion< -1){
        proporcion=-1;
    }
    if(proporcion>1){
        proporcion=1;
    }
    double anguloMax=60.0;
    double anguloRad= qDegreesToRadians(proporcion*anguloMax);

    double nuevaVelX= velocidad*qSin(anguloRad);
    double nuevaVelY= -velocidad*qCos(anguloRad);

    if(nuevaVelY==0){
        nuevaVelY=-2.0;
    }
    pelota->setVelocidad(nuevaVelX,nuevaVelY);
    pelota->setPosicion(pelota->getX(),plat->getY()-pelota->getDiametro());
}

void PantallaJuego::intentarSoltarPowerUp(int x, int y){
    int chance= QRandomGenerator::global()->bounded(100); //0-99
    if(chance<20){ //20% de probabilidad de soltar un power-up

        // entre los tipos que hay disponibles
        TIPO_POWERUP tipoElegido;
        int tipoRand= QRandomGenerator::global()->bounded(3);
        if(tipoRand==0){
            tipoElegido= BOLA_EXTRA;
        }else if(tipoRand==1){
            tipoElegido= VIDA_EXTRA;
        }else{
            tipoElegido= PLATAFORMA_GRANDE;
        }

        PowerUp* nuevo= new PowerUp(tipoElegido,x,y);

        PowerUp** nuevaLista= new PowerUp*[cantidadPowerUps+1];
        QGraphicsRectItem** nuevosItems= new QGraphicsRectItem*[cantidadPowerUps+1];

        for(int i=0;i<cantidadPowerUps;i++){
            nuevaLista[i]=ptrPowerUps[i];
            nuevosItems[i]=itemsPowerUps[i];
        }
        nuevaLista[cantidadPowerUps]=nuevo;

        QGraphicsRectItem* item= escena->addRect(0,0,nuevo->getAncho(),nuevo->getAlto(),QPen(Qt::black),nuevo->getColor());
        item->setPos(nuevo->getX(),nuevo->getY());
        nuevosItems[cantidadPowerUps]=item;

        delete[] ptrPowerUps;
        delete[] itemsPowerUps;
        ptrPowerUps=nuevaLista;
        itemsPowerUps=nuevosItems;
        cantidadPowerUps++;
    }
}


void PantallaJuego::actualizarPowerUps(){
    Plataforma* plat= partidaActual->getPlataforma();
    QRectF rectPlat(plat->getX(),plat->getY(),plat->getAncho(),plat->getAlto());

    for(int i=0;i<cantidadPowerUps;i++){
        ptrPowerUps[i]->caer();
        itemsPowerUps[i]->setPos(ptrPowerUps[i]->getX(),ptrPowerUps[i]->getY());

        QRectF rectPower(ptrPowerUps[i]->getX(),ptrPowerUps[i]->getY(),
                         ptrPowerUps[i]->getAncho(),ptrPowerUps[i]->getAlto());

        if(rectPower.intersects(rectPlat)){
            aplicarPowerUp(ptrPowerUps[i]);
            eliminarPowerUp(i);
            i--;
            continue;
        }
        if(ptrPowerUps[i]->getY()>480){
            eliminarPowerUp(i);
            i--;
        }
    }
}

void PantallaJuego::aplicarPowerUp(PowerUp* power){
    switch(power->getTipo()){
    case BOLA_EXTRA:{
        Plataforma* plat= partidaActual->getPlataforma();
        int x= plat->getX()+plat->getAncho()/2;
        int y= plat->getY()-20;

        partidaActual->agregarPelotaExtra(x,y);

        int nuevaCant= partidaActual->getCantidadPelotas();
        QGraphicsEllipseItem** nuevaListaItems= new QGraphicsEllipseItem*[nuevaCant];
        for(int i=0;i<nuevaCant-1;i++){
            nuevaListaItems[i]=itemsPelotas[i];
        }
        Pelota* nueva= partidaActual->getPelotas()[nuevaCant-1];
        QGraphicsEllipseItem* item= escena->addEllipse(0,0,nueva->getDiametro(),nueva->getDiametro(),
                                                        QPen(Qt::white),QBrush(Qt::white));
        item->setPos(nueva->getX(),nueva->getY());
        nuevaListaItems[nuevaCant-1]=item;

        delete[] itemsPelotas;
        itemsPelotas=nuevaListaItems;
        break;
    }
    case VIDA_EXTRA:{
        partidaActual->ganarVida();
        actualizarHUD();
        break;
    }
    case PLATAFORMA_GRANDE:{
        Plataforma* plat= partidaActual->getPlataforma();

        if(contadorPlataformaGrande<=0){
            anchoOriginalPlataforma= plat->getAncho();
            plat->setAncho(anchoOriginalPlataforma + 40); //se agranda 40px
        }
        //si ya estaba activo, solo se reinicia la duracion
        contadorPlataformaGrande= 300; //300 ticks
        break;
    }
    }
}

void PantallaJuego::eliminarPowerUp(int indice){
    if(indice<0 || indice>=cantidadPowerUps) return;

    escena->removeItem(itemsPowerUps[indice]);
    delete itemsPowerUps[indice];
    delete ptrPowerUps[indice];

    PowerUp** nuevaLista= nullptr;
    QGraphicsRectItem** nuevosItems= nullptr;

    if(cantidadPowerUps-1>0){
        nuevaLista= new PowerUp*[cantidadPowerUps-1];
        nuevosItems= new QGraphicsRectItem*[cantidadPowerUps-1];
        int pos=0;
        for(int i=0;i<cantidadPowerUps;i++){
            if(i!=indice){
                nuevaLista[pos]=ptrPowerUps[i];
                nuevosItems[pos]=itemsPowerUps[i];
                pos++;
            }
        }
    }
    delete[] ptrPowerUps;
    delete[] itemsPowerUps;
    ptrPowerUps=nuevaLista;
    itemsPowerUps=nuevosItems;
    cantidadPowerUps--;
}

void PantallaJuego::manejarFinDePartida(){
    if(!esperando){
        int cant= partidaActual->getCantidadPelotas();
        Pelota** pelotas= partidaActual->getPelotas();

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

                partidaActual->eliminarPelota(i);

                if(partidaActual->getCantidadPelotas()<=0){
                    partidaActual->perderVida();
                    actualizarHUD();

                    if(partidaActual->estaTerminada()){
                        timerJuego->stop();
                        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
                        PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal();
                        ventana->cambiarPantalla(pantallaMenu);
                        return;
                    }
                    partidaActual->agregarPelotaExtra(LIMITE_PANTALLA/2,420);
                    dibujarPelotas();

                    Plataforma* plat= partidaActual->getPlataforma();
                    plat->setPosicion((LIMITE_PANTALLA-plat->getAncho())/2,plat->getY());
                    esperando=true;
                }
                break;
            }
        }
    }
    if(partidaActual->nivelCompletado()){
        timerJuego->stop();
        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
        PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal();
        ventana->cambiarPantalla(pantallaMenu);
    }
}