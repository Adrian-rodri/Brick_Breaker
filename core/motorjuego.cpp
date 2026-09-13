#include "motorjuego.h"
#include "constantes.h"
#include <qmath.h>

MotorJuego::MotorJuego(int nivel){
    partidaActual= new Partida(nivel);
    velocidad= 6.0+(nivel-1)*1.5;
}
MotorJuego::~MotorJuego(){
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
                }else{
                    //cambiar el estado del bloque
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
void MotorJuego::actualizarJuego(bool moverIzq, bool moverDer){
    Plataforma* plataforma= partidaActual->getPlataforma();
    if(moverIzq){
        plataforma->moverIzquierda();
    }
    if(moverDer){
        plataforma->moverDerecha();
    }

}