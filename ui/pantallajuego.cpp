#include "pantallajuego.h"
#include "constantes.h"
#include "ventanaprincipal.h"
#include "pantallamenuprincipal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBrush>
#include <QPen>
#include <QtMath>

PantallaJuego::PantallaJuego(int nivel, QWidget* parent)
    : QWidget(parent){
    partidaActual= new Partida(nivel);
    ptrBloques = nullptr;
    velocidad= 6.0+(nivel-1)*1.5;
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
    delete partidaActual;
    partidaActual= nullptr;
}

void PantallaJuego::cargarUi(){
    this->setStyleSheet("background-color: #000000;");
    moverIzq= false;
    moverDer= false;
    esperando= true;

    QVBoxLayout* layoutVertical= new QVBoxLayout(this);

    cargarHUD(layoutVertical);

    QHBoxLayout* layoutCentro= new QHBoxLayout();
    escena= new QGraphicsScene(0, 0, LIMITE_PANTALLA, 480, this);
    vista= new QGraphicsView(escena, this);
    vista->setFocusPolicy(Qt::NoFocus);

    layoutCentro->addStretch();
    layoutCentro->addWidget(vista);
    layoutCentro->addStretch();
    layoutVertical->addLayout(layoutCentro);
    layoutVertical->addStretch();

    dibujarBloques();
    dibujarPlataforma();
    dibujarPelota();

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
void PantallaJuego::dibujarPelota(){
    Pelota* pelota= partidaActual->getPelota();
    itemPelota= escena->addEllipse(0,0,pelota->getDiametro(),pelota->getDiametro(),QPen(Qt::white), QBrush(Qt::white));
    itemPelota->setPos(pelota->getX(),pelota->getY());
}
void PantallaJuego::lanzarPelota(){
    double anguloInicial=25.0;
    double anguloEnRads= qDegreesToRadians(anguloInicial);

    int velX= (int)(velocidad*qSin(anguloEnRads));
    int velY= (int)(-velocidad*qCos(anguloEnRads));

    partidaActual->getPelota()->setVelocidad(velX,velY);
}
void PantallaJuego::keyPressEvent(QKeyEvent* event){
    if(event->key()==Qt::Key_Left || event->key()==Qt::Key_A){
        moverIzq= true;
    }else if(event->key()==Qt::Key_Right || event->key()== Qt::Key_D){
        moverDer= true;
    }else if(event->key()==Qt::Key_W || event->key()==Qt::Key_Up || event->key()==Qt::Key_Space){
        if(esperando){
            esperando= false;
            lanzarPelota();
        }
    }
}
void PantallaJuego::keyReleaseEvent(QKeyEvent* event){
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
    Pelota* pelota= partidaActual->getPelota();

    if(esperando){
        int posX=plat->getX() + plat->getAncho()/2 -pelota->getDiametro()/2;
        int posY=plat->getY()- pelota->getDiametro();
        pelota->setPosicion(posX,posY);
    }else{
        pelota->mover();
        manejarColisiones();
    }
    actualizarPosiciones();
    actualizarHUD();
    manejarFinDePartida();
}
void PantallaJuego::actualizarPosiciones(){
    Plataforma* plat= partidaActual->getPlataforma();
    itemPlataforma->setPos(plat->getX(),plat->getY());

    Pelota* pelota= partidaActual->getPelota();
    itemPelota->setPos(pelota->getX(),pelota->getY());
}
void PantallaJuego::manejarColisiones(){
    Pelota* pelota= partidaActual->getPelota();
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
        rebotarEnPlataforma();
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
                }else{
                    pelota->invertirVelocidadY();
                }
                return;
            }
        }
    }
}
void PantallaJuego::rebotarEnPlataforma(){
    Pelota* pelota= partidaActual->getPelota();
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
void PantallaJuego::manejarFinDePartida(){
    Pelota* pelota= partidaActual->getPelota();

    if(!esperando && pelota->getY()>480){
        partidaActual->perderVida();
        actualizarHUD();
        if(partidaActual->estaTerminada()){
            timerJuego->stop();
            VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
            PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal();
            ventana->cambiarPantalla(pantallaMenu);
            return;
        }
        Plataforma* plat= partidaActual->getPlataforma();
        plat->setPosicion((LIMITE_PANTALLA-plat->getAncho())/2,plat->getY());
        esperando=true;
    }
    if(partidaActual->nivelCompletado()){
        timerJuego->stop();
        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
        PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal();
        ventana->cambiarPantalla(pantallaMenu);
    }
}