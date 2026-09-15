#include "partida.h"
#include "constantes.h"

Partida::Partida(int nivel) {
    vidas= 3;
    puntaje= 0;
    numNivelAct= nivel;
    nivelActual= new Nivel(numNivelAct);
    plataforma= new Plataforma((LIMITE_PANTALLA - PLATAFORMA_ANCHO)/2,440,
        PLATAFORMA_ANCHO,PLATAFORMA_ALTO);
    cantidadPelotas=1;
    listaPelotas= new Pelota*[cantidadPelotas];
    listaPelotas[0]= new Pelota(LIMITE_PANTALLA/2, 420, 20);
}

Partida::~Partida() {
    delete nivelActual;
    nivelActual= nullptr;
    delete plataforma;
    plataforma= nullptr;
    liberarPelotas();
}

void Partida::liberarPelotas(){
    if(listaPelotas!=nullptr){
        for(int i=0;i<cantidadPelotas;i++){
            delete listaPelotas[i];
        }
        delete[] listaPelotas;
        listaPelotas=nullptr;
    }
    cantidadPelotas=0;
}
void Partida::reiniciarVidasYPuntaje(){
    vidas= 3;
    puntaje= 0;
}
void Partida::agregarPelotaExtra(int posX, int posY){
    Pelota** nuevaLista= new Pelota*[cantidadPelotas+1];
    for(int i=0;i<cantidadPelotas;i++){
        nuevaLista[i]=listaPelotas[i];
    }
    Pelota* nueva= new Pelota(posX,posY,20);
    nueva->setVelocidad(-4,-4); //para que no salga quieta
    nuevaLista[cantidadPelotas]=nueva;

    delete[] listaPelotas;
    listaPelotas=nuevaLista;
    cantidadPelotas++;
}

void Partida::eliminarPelota(int indice){
    if(indice<0 || indice>=cantidadPelotas){
        return;
    }
    delete listaPelotas[indice];

    Pelota** nuevaLista= nullptr;
    if(cantidadPelotas-1>0){
        nuevaLista= new Pelota*[cantidadPelotas-1];
        int pos=0;
        for(int i=0;i<cantidadPelotas;i++){
            if(i!=indice){
                nuevaLista[pos]=listaPelotas[i];
                pos++;
            }
        }
    }
    delete[] listaPelotas;
    listaPelotas=nuevaLista;
    cantidadPelotas--;
}

void Partida::sumarPuntos(int puntos){
    puntaje+= puntos;
}
void Partida::perderVida(){
    vidas--;
}
void Partida::ganarVida(){
    vidas++;
}
bool Partida::estaTerminada(){
    return vidas<=0;
}
bool Partida::nivelCompletado(){
    return nivelActual->getBloquesRestantes()<=0;
}

int Partida::getVidas(){
    return vidas;
}
int Partida::getPuntaje(){
    return puntaje;
}
Nivel* Partida::getNivel() const{
    return nivelActual;
}
Plataforma* Partida::getPlataforma()const{
    return plataforma;
}
Pelota** Partida::getPelotas() const{
    return listaPelotas;
}
int Partida::getCantidadPelotas() const{
    return cantidadPelotas;
}