#include "PerfilProgreso.h"

PerfilProgreso::PerfilProgreso(){
    creditos=0;
    mapaMaxDesbloqueado=1;
    nivelDañoBola=0;
    nivelMultiplicadorMonedas=0;
    nivelVelocidadBola=0;
    desbloqueoBlindaje=false;
    multiplicador=1.0;
}

PerfilProgreso::PerfilProgreso(int creditos, int mapaMaxDesbloqueado, int nivelDañoBola,
                               int nivelMultiplicadorMonedas, int nivelVelocidadBola,
                               bool desbloqueoBlindaje, double multiplicador){
    this->creditos=creditos;
    this->mapaMaxDesbloqueado=mapaMaxDesbloqueado;
    this->nivelDañoBola=nivelDañoBola;
    this->nivelMultiplicadorMonedas=nivelMultiplicadorMonedas;
    this->nivelVelocidadBola=nivelVelocidadBola;
    this->desbloqueoBlindaje=desbloqueoBlindaje;
    this->multiplicador=multiplicador;
}

//getters
int PerfilProgreso::getCreditos() const{ return creditos; }
int PerfilProgreso::getMapaMaxDesbloqueado() const{ return mapaMaxDesbloqueado; }
int PerfilProgreso::getNivelDañoBola() const{ return nivelDañoBola; }
int PerfilProgreso::getNivelMultiplicadorMonedas() const{ return nivelMultiplicadorMonedas; }
int PerfilProgreso::getNivelVelocidadBola() const{ return nivelVelocidadBola; }
bool PerfilProgreso::getDesbloqueoBlindaje() const{ return desbloqueoBlindaje; }
double PerfilProgreso::getMultiplicador() const{ return multiplicador; }

void PerfilProgreso::sumarCreditos(int cantidad){
    creditos+=cantidad;
}

bool PerfilProgreso::gastarCreditos(int cantidad){
    if(cantidad>creditos){
        return false;
    }
    creditos-=cantidad;
    return true;
}

void PerfilProgreso::desbloquearMapa(int numMapa){
    if(numMapa>mapaMaxDesbloqueado){
        mapaMaxDesbloqueado=numMapa;
    }
}

void PerfilProgreso::subirNivelDañoBola(){
    nivelDañoBola++;
}
void PerfilProgreso::subirNivelMultiplicadorMonedas(){
    nivelMultiplicadorMonedas++;
}
void PerfilProgreso::subirNivelVelocidadBola(){
    nivelVelocidadBola++;
}

void PerfilProgreso::desbloquearBlindaje(){
    desbloqueoBlindaje=true;
}

void PerfilProgreso::setMultiplicador(double nuevoValor){
    if(nuevoValor<1.0){
        nuevoValor=1.0;
    }
    multiplicador=nuevoValor;
}