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
#include <QDebug>

PantallaJuego::PantallaJuego(int nivel, bool modoHistoria, QWidget* parent)
    : QWidget(parent){
    this->modoHistoria= modoHistoria;
    motor= new MotorJuego(nivel);
    ptrBloques = nullptr;
    cargarUi();
}

PantallaJuego::PantallaJuego(Partida* partidaCargada, QWidget* parent)
    : QWidget(parent){
    modoHistoria= true;
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
    enPausa= false;
    animandoEntrada= false;
    animandoPelota= false;
    offsetAnimacion= 0;
    cargarSonidos();

    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    PerfilProgreso* perfil= nullptr;
    if(ventana != nullptr && ventana->gestorUsers->usuarioActual != nullptr){
        perfil= &ventana->gestorUsers->usuarioActual->getPerfil();
    }

    if(perfil!= nullptr){
        monedasAcumuladas= perfil->getCreditos();
    }else{
        monedasAcumuladas= 0;
    }
    creditosIniciales= monedasAcumuladas;

    if(perfil!= nullptr){
        stats.damage= perfil->getNivelDañoBola();
        stats.tieneMejoraArmadura= perfil->getDesbloqueoBlindaje();
        motor->aplicarMejoraVelocidadPlataforma(perfil->getNivelVelocidadPlataforma());

        int numeroNivel= motor->getPartida()->getNivel()->getNumeroNivel();
        nivelDesbloqueado= (perfil->getMapaMaxDesbloqueado() >= numeroNivel);
    }else{
        stats.damage= 1;
        stats.tieneMejoraArmadura= false;
        nivelDesbloqueado= false;
    }
    motor->setGenerarOrbes(nivelDesbloqueado);

    spriteSimple= QPixmap(":/assets/bloqueSimple.png");
    spriteReforzado= QPixmap(":/assets/bloqueReforzado.png");
    spriteBlindado= QPixmap(":/assets/bloqueBlindado.png");
    spritePelota= QPixmap(":/assets/pelota.png");
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
    QString vida;
    for(int i=0;i<motor->getPartida()->getVidas();i++){
        vida+="💗 ";
    }
    lblVidas->setText(vida);
    lblBloques->setText(QString("%1 / %2 🧱").arg(motor->partidaActual->getNivel()->getBloquesRestantes()).arg(totalBloques));
    lblTiempo->setText(QString("🕛 %1 secs").arg(cronometro.elapsed()/1000));
    lblMonedas->setText(QString("%1 🪙").arg(qRound(monedasAcumuladas)));

    lblAviso->setVisible(esperando);
    if(esperando&&!animandoEntrada && !animandoPelota){
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
                        "font-size: 20px;"
                        "font-weight: bold;"
                        "background-color: transparent;";

    lblVidas= new QLabel();
    lblTiempo=new QLabel();
    lblBloques=new QLabel();
    lblMonedas= new QLabel();

    lblVidas->setStyleSheet(estiloLabel);
    lblVidas->setFixedWidth(200);
    lblVidas->setAlignment(Qt::AlignLeft);
    lblTiempo->setStyleSheet(estiloLabel);
    lblTiempo->setFixedWidth(200);
    lblTiempo->setAlignment(Qt::AlignRight);
    lblBloques->setStyleSheet(estiloLabel);
    lblMonedas->setStyleSheet(estiloLabel);

    layoutHUD->addWidget(lblVidas);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblBloques);
    layoutHUD->addStretch();
    layoutHUD->addWidget(lblMonedas);
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
void PantallaJuego::cargarSonidos() {
    for(int i=0;i<3;i++){
        crearEfectoSonido(sonidosToque[i], QUrl("qrc:/assets/toque.wav"), 0.8f);
        crearEfectoSonido(sonidoDestruir[i], QUrl("qrc:/assets/pop.wav"), 0.9f);
        crearEfectoSonido(sonidoBloqueado[i], QUrl("qrc:/assets/block.wav"), 0.8f);
        crearEfectoSonido(sonidoMoneda[i], QUrl("qrc:/assets/coin.wav"), 0.4f);
    }
}

void PantallaJuego::crearEfectoSonido(EfectoAudio& efecto, const QUrl& fuente, float volumen){
    efecto.player= new QMediaPlayer(this);
    efecto.output= new QAudioOutput(this);
    efecto.output->setVolume(volumen * VOLUMEN_GLOBAL);
    efecto.player->setAudioOutput(efecto.output);
    efecto.player->setSource(fuente);
}

void PantallaJuego::reconstruirSonido(EfectoAudio& efecto, const QUrl& fuente, float volumen){
    EfectoAudio viejo= efecto;

    efecto.player= new QMediaPlayer(this);
    efecto.output= new QAudioOutput(this);
    efecto.output->setVolume(volumen * VOLUMEN_GLOBAL);
    efecto.player->setAudioOutput(efecto.output);
    efecto.player->setSource(fuente);

    viejo.player->deleteLater();
    viejo.output->deleteLater();
}

void PantallaJuego::reconstruirTodosLosSonidos(){
    for(int i=0;i<3;i++){
        reconstruirSonido(sonidosToque[i], QUrl("qrc:/assets/toque.wav"), 0.8f);
        reconstruirSonido(sonidoDestruir[i], QUrl("qrc:/assets/pop.wav"), 0.9f);
        reconstruirSonido(sonidoBloqueado[i], QUrl("qrc:/assets/block.wav"), 0.8f);
        reconstruirSonido(sonidoMoneda[i], QUrl("qrc:/assets/coin.wav"), 0.4f);
    }
}

void PantallaJuego::reproducirSonido(EfectoAudio& efecto, int& indice, const QUrl& fuente, float volumen){
    efecto.player->setPosition(0);
    efecto.player->play();
    indice= (indice + 1)%3;
}
void PantallaJuego::verificarSonidos(){
    contadorVerificacionSonidos++;
    if(contadorVerificacionSonidos<60){
        return;
    }
    contadorVerificacionSonidos= 0;

    for(int i=0;i<3;i++){
        if(sonidosToque[i].player->error()!= QMediaPlayer::NoError){
            reconstruirSonido(sonidosToque[i], QUrl("qrc:/assets/toque.wav"), 0.8f);
        }
        if(sonidoDestruir[i].player->error()!= QMediaPlayer::NoError){
            reconstruirSonido(sonidoDestruir[i], QUrl("qrc:/assets/pop.wav"), 0.9f);
        }
        if(sonidoBloqueado[i].player->error()!= QMediaPlayer::NoError){
            reconstruirSonido(sonidoBloqueado[i], QUrl("qrc:/assets/block.wav"), 0.8f);
        }
        if(sonidoMoneda[i].player->error()!= QMediaPlayer::NoError){
            reconstruirSonido(sonidoMoneda[i], QUrl("qrc:/assets/coin.wav"), 0.4f);
        }
    }
}
QPixmap PantallaJuego::obtenerSprite(Bloque* bloque, int fila){
    QPixmap hoja;
    int columna, filaSprite;
    switch(bloque->getTipoBloque()){

    case SIMPLE:{
        columna= bloque->getFrameSprite(fila);
        filaSprite=0;
        hoja= spriteSimple;
        break;
    }case REFORZADO:{
        hoja= spriteReforzado;
        columna= bloque->getFrameEstado();
        filaSprite= bloque->getFrameSprite(fila);
        break;
    }case BLINDADO:{
        hoja= spriteBlindado;
        columna= bloque->getFrameEstado();
        filaSprite= bloque->getFrameSprite(fila);
        break;
    }}


    return hoja.copy(columna*BRICK_ANCHO, filaSprite*BRICK_ALTO, BRICK_ANCHO, BRICK_ALTO);
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
            QPixmap sprite = obtenerSprite(bloque, i);
            item->setBrush(QBrush(sprite));


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
    itemsPelotas= new QGraphicsPixmapItem*[cant];

    for(int i=0;i<cant;i++){
        Pelota* pelota= motor->partidaActual->getPelotas()[i];

        QPixmap spriteEscalado= spritePelota.scaled(pelota->getDiametro(), pelota->getDiametro(),
                                                     Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QGraphicsPixmapItem* item= escena->addPixmap(spriteEscalado);
        item->setPos(pelota->getX(), pelota->getY());
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
        if(esperando&&!animandoEntrada && !animandoPelota){
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
    verificarSonidos();
    if(animandoEntrada){
        offsetAnimacion += 10;

        double progreso= 1.0-(double)(-offsetAnimacion)/480.0;
        if(progreso<0.0){
            progreso= 0.0;
        }
        if(progreso>1.0){
            progreso= 1.0;
        }
        double xActual= plataformaXInicio+(plataformaXDestino-plataformaXInicio)*progreso;

        Plataforma* plat= motor->getPartida()->getPlataforma();
        plat->setPosicion(xActual, plat->getY());
        itemPlataforma->setPos(xActual, plat->getY());

        if(offsetAnimacion>=0){
            offsetAnimacion = 0;
            animandoEntrada = false;
            animandoPelota = true;

            plat->setPosicion(plataformaXDestino, plat->getY());
            itemPlataforma->setPos(plataformaXDestino, plat->getY());
        }
        actualizarPosicionesBloques();
        actualizarHUD();
        return;
    }
    if(animandoPelota){
        escalaJugador += 0.01;
        if(escalaJugador>= 1.0){
            escalaJugador= 1.0;
            animandoPelota= false;
        }
        int cant= motor->getPartida()->getCantidadPelotas();
        for(int i=0;i<cant;i++){
            itemsPelotas[i]->setScale(escalaJugador);
        }
        actualizarHUD();
        return;
    }
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
        reproducirSonido(sonidoDestruir[indiceDestruir], indiceDestruir,
                         QUrl("qrc:/assets/pop.wav"), 0.9f);

    }else if(motor->huboToque(fila,col)){
        Bloque* bloqueActualizado= motor->getPartida()->getNivel()->getMatriz()[fila][col];
        QPixmap sprite= obtenerSprite(bloqueActualizado, fila);
        ptrBloques[fila][col]->setBrush(QBrush(sprite));
        if(bloqueActualizado->getTipoBloque()==BLINDADO && !stats.tieneMejoraArmadura){
            reproducirSonido(sonidoBloqueado[indiceBloquead], indiceBloquead,
                             QUrl("qrc:/assets/block.wav"), 0.8f);
        }else{
            reproducirSonido(sonidosToque[indiceToque], indiceToque,
                             QUrl("qrc:/assets/toque.wav"), 0.8f);
        }
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
        if(nivelDesbloqueado){
            VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
            double valorFinal= valorRecogido;
            if(ventana->gestorUsers->usuarioActual!=nullptr){
                valorFinal= valorRecogido *ventana->gestorUsers->usuarioActual->getPerfil().getMultiplicadorTotal();
                ventana->gestorUsers->usuarioActual->getPerfil().sumarCreditos(valorFinal);
            }
            monedasAcumuladas+= valorFinal;
        }
        reproducirSonido(sonidoMoneda[indiceMoneda], indiceMoneda,QUrl("qrc:/assets/coin.wav"), 0.4f);
    }

    actualizarPosiciones();
    actualizarHUD();
    manejarFinDePartida();
}
void PantallaJuego::actualizarPosicionesBloques(){
    Nivel* nivelActual = motor->getPartida()->getNivel();
    for(int i=0;i<filas;i++){
        for(int j=0;j<col;j++){
            if(ptrBloques[i][j]!=nullptr){
                Bloque* bloque = nivelActual->getMatriz()[i][j];
                ptrBloques[i][j]->setPos(10+bloque->getPosX()*BRICK_ANCHO,
                                         bloque->getPosY()*BRICK_ALTO + offsetAnimacion);
            }
        }
    }
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
void PantallaJuego::limpiarItemsPowerUpsYOrbes(){
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
}

void PantallaJuego::guardarProgresoActual(){
    VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
    if(ventana->gestorUsers->usuarioActual!=nullptr){
        ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(),
                                              ventana->gestorUsers->usuarioActual->getPerfil());
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
    if(indice<0 || indice>=cantidadPowerUps) {
        return;
    }

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
    QPixmap skinMoneda(":/assets/moneda.png");
    QGraphicsEllipseItem* item= escena->addEllipse(0,0,15,15,QPen(Qt::black),QBrush(skinMoneda));
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
    QGraphicsPixmapItem** nuevaLista= new QGraphicsPixmapItem*[nuevaCant];

    for(int i=0; i<nuevaCant-1; i++){
        nuevaLista[i]= itemsPelotas[i];
    }
    Pelota* nueva= motor->getPartida()->getPelotas()[nuevaCant - 1];

    QPixmap spriteEscalado= spritePelota.scaled(nueva->getDiametro(), nueva->getDiametro(),
                                                 Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem* item= escena->addPixmap(spriteEscalado);
    item->setPos(nueva->getX(),nueva->getY());

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
    moverIzq= false;
    moverDer= false;

    QDialog dialogo(this);
    dialogo.setWindowTitle("Pausa");
    dialogo.setModal(true);
    dialogo.setFixedSize(340, 300);
    dialogo.setStyleSheet("background-color: " + COLORSUBFONDO + ";");

    QVBoxLayout* layoutDialogo = new QVBoxLayout(&dialogo);
    layoutDialogo->setContentsMargins(25, 25, 25, 25);
    layoutDialogo->setSpacing(15);

    QLabel* lblPausa = new QLabel("⏸️ PAUSA");
    lblPausa->setAlignment(Qt::AlignCenter);
    lblPausa->setStyleSheet("color: " + COLORFONT + "; "
                            "font-size: 30px; "
                            "font-weight: bold; "
                            "background-color: transparent;");
    layoutDialogo->addWidget(lblPausa);

    QLabel* lblInfo= new QLabel("El juego está detenido");
    lblInfo->setAlignment(Qt::AlignCenter);
    lblInfo->setStyleSheet("color: #AAAAAA; "
                           "font-size: 15px; "
                           "background-color: transparent;");
    layoutDialogo->addWidget(lblInfo);
    layoutDialogo->addStretch();

    QString estiloBtnPausa ="QPushButton{"
                            "background-color: transparent;"
                            "color: " + COLORFONT + ";"
                            "font-size: 18px;"
                            "font-weight: bold;"
                            "border-radius: 10px;"
                            "border: 2px solid white;"
                            "padding: 12px;"
                            "}"
                            "QPushButton:hover{"
                            "background-color: " + COLORBOTONHOVER + ";"
                            "}"
                            "QPushButton:pressed{"
                            "background-color: " + COLORBOTONPRESSED + ";"
                            "}";
    QPushButton* btnContinuar= new QPushButton("▶ Continuar");
    btnContinuar->setStyleSheet(estiloBtnPausa);
    btnContinuar->setFixedSize(220, 50);
    connect(btnContinuar, &QPushButton::clicked, &dialogo, &QDialog::accept);
    layoutDialogo->addWidget(btnContinuar, 0, Qt::AlignHCenter);

    QPushButton* btnMenu= new QPushButton("🏠 Volver al menú");
    btnMenu->setStyleSheet(estiloBtnPausa);
    btnMenu->setFixedSize(220, 50);
    connect(btnMenu, &QPushButton::clicked, &dialogo, &QDialog::reject);
    layoutDialogo->addWidget(btnMenu, 0, Qt::AlignHCenter);

    int resultado= dialogo.exec();
    if(resultado== QDialog::Rejected){
        guardarProgresoActual();
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        PantallaMenuPrincipal*  pantallaMenu= new PantallaMenuPrincipal(ventana);
        ventana->cambiarPantalla(pantallaMenu);
        return;
    }
    moverIzq= false;
    moverDer= false;

    enPausa= false;
    timerJuego->start(16);
    this->setFocus();
}
void PantallaJuego::regenerarNivel(bool fueGameOver){
    liberarBloques();
    motor->getPartida()->getNivel()->regenerar();
    dibujarBloques();
    reconstruirTodosLosSonidos();
    animandoEntrada= true;
    offsetAnimacion= -480;
    escalaJugador= 0.0;
    animandoPelota= false;
    totalBloques= motor->getPartida()->getNivel()->getBloquesRestantes();

    Plataforma* plat= motor->getPartida()->getPlataforma();
    plataformaXInicio= plat->getX();
    plataformaXDestino= (LIMITE_PANTALLA-plat->getAncho())/2;


    double centroPlataforma= plataformaXDestino+plat->getAncho()/2.0;

    if(fueGameOver){
        motor->getPartida()->reiniciarVidas();
        motor->getPartida()->agregarPelotaExtra(centroPlataforma-20,420);
        dibujarPelotas();
    }else{
        int cant= motor->getPartida()->getCantidadPelotas();
        Pelota** pelotas= motor->getPartida()->getPelotas();
        for(int i=0;i<cant;i++){
            pelotas[i]->setPosicion(centroPlataforma-pelotas[i]->getDiametro()/2.0, 420);
        }
    }
    int cant= motor->getPartida()->getCantidadPelotas();
    Pelota** pelotas= motor->getPartida()->getPelotas();
    for(int i=0;i<cant;i++){
        itemsPelotas[i]->setPos(pelotas[i]->getX(), pelotas[i]->getY());
        itemsPelotas[i]->setScale(0.0);
    }

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

                QGraphicsPixmapItem** nuevaListaItems= nullptr;
                if(cant-1>0){
                    nuevaListaItems= new QGraphicsPixmapItem*[cant-1];
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
                    limpiarItemsPowerUpsYOrbes();

                    if(motor->partidaActual->estaTerminada()){
                        guardarProgresoActual();
                        timerJuego->stop();
                        VentanaPrincipal* ventana = (VentanaPrincipal*)this->window();
                        PantallaMenuPrincipal* pantallaMenu = new PantallaMenuPrincipal(ventana);
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
        timerJuego->stop();
        VentanaPrincipal* ventana= (VentanaPrincipal*)this->window();
        int nivelActual= motor->getPartida()->getNivel()->getNumeroNivel();

        bool primeraVez= true;
        if(ventana->gestorUsers->usuarioActual != nullptr){
            PerfilProgreso& perfil= ventana->gestorUsers->usuarioActual->getPerfil();
            if(nivelActual < 3){
                primeraVez= (perfil.getMapaMaxDesbloqueado() <= nivelActual);
            }else{
                primeraVez= !perfil.getHistoriaCompletada();
            }
        }
        if(!modoHistoria || !primeraVez){
            guardarProgresoActual();
            regenerarNivel(false);
            motor->limpiarPowerUpsYOrbes();
            limpiarItemsPowerUpsYOrbes();
            timerJuego->start(16);
            return;
        }
        if(ventana->gestorUsers->usuarioActual != nullptr){
            PerfilProgreso& perfil = ventana->gestorUsers->usuarioActual->getPerfil();
            if(nivelActual < 3){
                perfil.desbloquearMapa(nivelActual + 1);
            }else{
                perfil.completarHistoria();
            }
            ventana->gestorUsers->guardarProgreso(ventana->gestorUsers->usuarioActual->getUsername(), perfil);
        }

        double monedasGanadas= monedasAcumuladas- creditosIniciales;
        if(monedasGanadas<0){
            monedasGanadas= 0;
        }

        QMessageBox cuadro(this);
        cuadro.setWindowTitle("Nivel Completado");

        QPushButton* btnSiguiente= nullptr;
        if(nivelActual< 3){
            cuadro.setText(QString("¡Nivel %1 completado! 🎉\n\nHas desbloqueado el Nivel %2\n\nTiempo: %3 s\nMonedas ganadas: %4 🪙")
                               .arg(nivelActual)
                               .arg(nivelActual + 1)
                               .arg(cronometro.elapsed()/1000)
                               .arg(qRound(monedasGanadas)));
            btnSiguiente = cuadro.addButton("Siguiente Nivel ▶", QMessageBox::AcceptRole);
        }else{
            cuadro.setText(QString("¡Felicidades! 🏆\n\nCompletaste todos los niveles del modo historia.\n\nTiempo: %1 s\nMonedas ganadas: %2 🪙")
                               .arg(cronometro.elapsed()/1000)
                               .arg(qRound(monedasGanadas)));
        }
        cuadro.addButton("Menú Principal", QMessageBox::RejectRole);
        cuadro.exec();

        if(btnSiguiente !=nullptr && cuadro.clickedButton()==btnSiguiente){
            PantallaJuego* siguiente= new PantallaJuego(nivelActual+1, true, ventana);
            ventana->cambiarPantalla(siguiente);
        }else{
            PantallaMenuPrincipal* pantallaMenu= new PantallaMenuPrincipal(ventana);
            ventana->cambiarPantalla(pantallaMenu);
        }
        return;
    }
}