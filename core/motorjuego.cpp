#include "motorjuego.h"
#include "constantes.h"
#include <qmath.h>
#include <cstdlib>

MotorJuego::MotorJuego(int nivel){
    partidaActual= new Partida(nivel);
    velocidad= 6.0+(nivel-1)*1.5;
    partidaActual->getPlataforma()->setVelocidad(velocidad);
    resetearEventos();
    ptrPowerUps= nullptr;
    cantidadPowerUps=0;
    contadorPlataformaGrande=0;
    anchoOriginalPlataforma= PLATAFORMA_ANCHO;
}
MotorJuego::~MotorJuego(){
    for(int i=0; i<cantidadPowerUps; i++){
        delete ptrPowerUps[i];
    }
    delete[] ptrPowerUps;
    ptrPowerUps= nullptr;

    delete partidaActual;
    partidaActual= nullptr;
}
void MotorJuego::manejarColisiones(){
    int cant= partidaActual->getCantidadPelotas();
    Pelota** pelotas= partidaActual->getPelotas();
    for(int i=0;i<cant;i++){
        manejarColisionesPelota(pelotas[i]);
    }
}
void MotorJuego::manejarColisionesPelota(Pelota* pelota){
    //colisiones con limites de la escena
    int diametro= pelota->getDiametro();
    if(pelota->getX()<=0){
        pelota->setPosicion(0,pelota->getY());
        pelota->invertirVelocidadX();
    }
    if(pelota->getX()+diametro>=LIMITE_PANTALLA){
        pelota->setPosicion(LIMITE_PANTALLA-diametro,pelota->getY());
        pelota->invertirVelocidadX();
    }
    if(pelota->getY()<=0){
        pelota->setPosicion(pelota->getX(),0);
        pelota->invertirVelocidadY();
    }
    //colision con plataforma
    Plataforma* plataforma= partidaActual->getPlataforma();
    QRectF rectPelota(pelota->getX(),pelota->getY(),diametro,diametro);
    QRectF rectPlat(plataforma->getX(),plataforma->getY(),plataforma->getAncho(),plataforma->getAlto());

    if(rectPelota.intersects(rectPlat)&& pelota->getVelocidadY()>0){
        rebotarEnPlataforma(pelota);
        return;
    }
    //collisiones por bloques
    Nivel* nivel= partidaActual->getNivel();
    int filas= nivel->getFilas();
    int cols= nivel->getColumnas();
    for(int i=0;i< filas;i++){
        for(int j=0;j<cols;j++){
            Bloque *bloque= nivel->getMatriz()[i][j];
            if(bloque==nullptr){
                continue;
            }
            QRectF rectBloque(10+bloque->getPosX()*BRICK_ANCHO,bloque->getPosY()*BRICK_ALTO,BRICK_ANCHO,BRICK_ALTO);

            if(rectPelota.intersects(rectBloque)){
                bloque->recibirGolpe();
                if(bloque->estaRoto()){
                    partidaActual->sumarPuntos(bloque->getPuntos());
                    intentarSoltarPowerUp(10+bloque->getPosX()*BRICK_ANCHO, bloque->getPosY()*BRICK_ALTO);
                    nivel->destruirBloque(i,j);

                    seDestruyoBloque= true;
                    filaDestruida=i;
                    colDestruida=j;
                }else{
                    seTocoBloque= true;
                    filaTocada= i;
                    colTocada= j;
                }
                double collisionX= qMin(rectPelota.right(),rectBloque.right())-qMax(rectPelota.left(),rectBloque.left());
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
                    if(rectPelota.center().y()<rectBloque.center().y()){
                        pelota->setPosicion(pelota->getX(), rectBloque.top()-diametro);
                    }
                    else{
                        pelota->setPosicion(pelota->getX(),rectBloque.bottom());
                    }
                }
                return;
            }
        }
    }
}
void MotorJuego::rebotarEnPlataforma(Pelota* pelota){
    Plataforma* plataforma= partidaActual->getPlataforma();

    double centroPelota= pelota->getX()+pelota->getDiametro()/2.0;
    double centroPlataforma= plataforma->getX()+plataforma->getAncho()/2.0;
    double proporcion= (centroPelota- centroPlataforma)/(plataforma->getAncho()/2.0);

    if(proporcion<-1){
        proporcion=-1;
    }
    if(proporcion>1){
        proporcion=1;
    }
    double angulaMax=60;
    double anguloRad= qDegreesToRadians(proporcion*angulaMax);

    double nuevaVelX= velocidad*qSin(anguloRad);
    double nuevaVelY= -velocidad*qCos(anguloRad);

    if(nuevaVelY==0){
        nuevaVelY=-2.0;
    }
    pelota->setVelocidad(nuevaVelX,nuevaVelY);
    pelota->setPosicion(pelota->getX(),plataforma->getY()-pelota->getDiametro());
}
void MotorJuego::actualizarJuego(bool moverIzq, bool moverDer,bool esperando){
    resetearEventos();
    Plataforma* plataforma= partidaActual->getPlataforma();
    Pelota** pelotas= partidaActual->getPelotas();
    if(moverIzq){
        plataforma->moverIzquierda();
    }
    if(moverDer){
        plataforma->moverDerecha();
    }
    if(contadorPlataformaGrande>0){
        contadorPlataformaGrande--;
        if(contadorPlataformaGrande==0){
            plataforma->setAncho(anchoOriginalPlataforma);
        }
    }
    if(esperando){
        int posX=plataforma->getX() + plataforma->getAncho()/2 -pelotas[0]->getDiametro()/2;
        int posY=plataforma->getY()- pelotas[0]->getDiametro();
        pelotas[0]->setPosicion(posX,posY);
    }else{

        int cant= partidaActual->getCantidadPelotas();

        for(int i=0;i<cant;i++){
            pelotas[i]->mover();
        }
        manejarColisiones();
        actualizarPowerUps();
    }

}
void MotorJuego::lanzarPelotaInicial(){
    int cant= partidaActual->getCantidadPelotas();
    if(cant>0){
        double anguloInicial= 25.0;
        double anguloEnRads= qDegreesToRadians(anguloInicial);

        int velX= (int)(velocidad*qSin(anguloEnRads));
        int velY= (int)(-velocidad*qCos(anguloEnRads));
        partidaActual->getPelotas()[0]->setVelocidad(velX, velY);
    }
}
void MotorJuego::intentarSoltarPowerUp(int x, int y){
    int chance= rand()%100;
    if(chance<=20){ //20% de probabilidad de soltar un power-up

        //entre los tipos que hay disponibles
        TIPO_POWERUP tipoElegido;
        int tipoRand= rand()%3;
        if(tipoRand==0){
            tipoElegido= BOLA_EXTRA;
        }else if(tipoRand==1){
            tipoElegido= VIDA_EXTRA;
        }else{
            tipoElegido= PLATAFORMA_GRANDE;
        }
        PowerUp* nuevo = new PowerUp(tipoElegido, x, y);
        PowerUp** nuevaLista = new PowerUp*[cantidadPowerUps + 1];
        for(int i = 0; i < cantidadPowerUps; i++){
            nuevaLista[i] = ptrPowerUps[i];
        }
        nuevaLista[cantidadPowerUps] = nuevo;

        delete[] ptrPowerUps;
        ptrPowerUps = nuevaLista;
        cantidadPowerUps++;
        huboNuevoPowerUp=true;
        posXNuevoPower=x;
        posYNuevoPower=y;
        tipoNuevoPower= tipoElegido;
    }
}
void MotorJuego::actualizarPowerUps(){
    Plataforma* plat= partidaActual->getPlataforma();
    QRectF rectPlat(plat->getX(),plat->getY(),plat->getAncho(),plat->getAlto());

    for(int i=0;i<cantidadPowerUps;i++){
        ptrPowerUps[i]->caer();

        QRectF rectPower(ptrPowerUps[i]->getX(),ptrPowerUps[i]->getY(),
                         ptrPowerUps[i]->getAncho(),ptrPowerUps[i]->getAlto());

        if(rectPower.intersects(rectPlat)){
            aplicarPowerUp(ptrPowerUps[i]);
            seEliminoPowerUp= true;
            idxPowerUpEliminado= i;
            eliminarPowerUp(i);
            return;
        }
        if(ptrPowerUps[i]->getY()>480){
            seEliminoPowerUp= true;
            idxPowerUpEliminado = i;
            eliminarPowerUp(i);
            return;
        }
    }
}
void MotorJuego::eliminarPowerUp(int indice){
    if(indice<0 || indice>=cantidadPowerUps) return;

    delete ptrPowerUps[indice];

    PowerUp** nuevaLista= nullptr;

    if(cantidadPowerUps-1>0){
        nuevaLista= new PowerUp*[cantidadPowerUps-1];
        int pos=0;
        for(int i=0;i<cantidadPowerUps;i++){
            if(i!=indice){
                nuevaLista[pos]=ptrPowerUps[i];
                pos++;
            }
        }
    }
    delete[] ptrPowerUps;
    ptrPowerUps=nuevaLista;
    cantidadPowerUps--;
}

void MotorJuego::aplicarPowerUp(PowerUp* power){
    seAplicoPowerUp= true;
    tipoPowerUpAplicado= power->getTipo();

    switch(power->getTipo()){
    case BOLA_EXTRA:{
        Plataforma* plat= partidaActual->getPlataforma();
        int x= plat->getX()+plat->getAncho()/2;
        int y= plat->getY()-20;

        partidaActual->agregarPelotaExtra(x,y);

        break;
    }
    case VIDA_EXTRA:{
        partidaActual->ganarVida();

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
void MotorJuego::resetearEventos(){
    seDestruyoBloque= false;
    filaDestruida=-1;
    colDestruida=-1;
    seTocoBloque=false;
    filaTocada=-1;
    colTocada=-1;

    huboNuevoPowerUp= false;
    posXNuevoPower=-1;
    posYNuevoPower=-1;

    seEliminoPowerUp= false;
    idxPowerUpEliminado= -1;
    seAplicoPowerUp= false;
}
bool MotorJuego::huboDestruccion(int& fila, int& col){
    if(seDestruyoBloque){
        fila= filaDestruida;
        col= colDestruida;
        return true;
    }
    return false;
}
bool MotorJuego::huboToque(int& fila, int& col){
    if(seTocoBloque){
        fila= filaTocada;
        col= colTocada;
        return true;
    }
    return false;
}
PowerUp* MotorJuego::huboPowerUpNuevo(){
    if(huboNuevoPowerUp){
        return new PowerUp(tipoNuevoPower,posXNuevoPower,posYNuevoPower);
    }
    return nullptr;
}
bool MotorJuego::huboPowerUpEliminado(int& indice){
    if(seEliminoPowerUp){
        indice= idxPowerUpEliminado;
        return true;
    }
    return false;
}
bool MotorJuego::huboPowerUpAplicado(TIPO_POWERUP& tipo){
    if(seAplicoPowerUp){
        tipo = tipoPowerUpAplicado;
        return true;
    }
    return false;
}

PowerUp** MotorJuego::getPowerUps() const{
    return ptrPowerUps;
}
Partida* MotorJuego::getPartida() const{
    return partidaActual;
}
int MotorJuego::getCantidadPowerUps()const{
    return cantidadPowerUps;
}