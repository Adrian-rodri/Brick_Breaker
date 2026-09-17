#include "PerfilProgreso.h"

PerfilProgreso::PerfilProgreso(){
    creditos=0;
    mapaMaxDesbloqueado=1;
    nivelDañoBola=1;
    nivelMultiplicadorMonedas=1;
    nivelVelocidadBola=1;
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

void PerfilProgreso::guardar(std::ofstream& archivo) const{
    archivo.write((char*)&creditos, sizeof(creditos));
    archivo.write((char*)&mapaMaxDesbloqueado, sizeof(mapaMaxDesbloqueado));
    archivo.write((char*)&nivelDañoBola, sizeof(nivelDañoBola));
    archivo.write((char*)&nivelMultiplicadorMonedas, sizeof(nivelMultiplicadorMonedas));
    archivo.write((char*)&nivelVelocidadBola, sizeof(nivelVelocidadBola));
    archivo.write((char*)&desbloqueoBlindaje, sizeof(desbloqueoBlindaje));
    archivo.write((char*)&multiplicador, sizeof(multiplicador));
}

void PerfilProgreso::cargar(std::ifstream& archivo){
    archivo.read((char*)&creditos, sizeof(creditos));
    archivo.read((char*)&mapaMaxDesbloqueado, sizeof(mapaMaxDesbloqueado));
    archivo.read((char*)&nivelDañoBola, sizeof(nivelDañoBola));
    archivo.read((char*)&nivelMultiplicadorMonedas, sizeof(nivelMultiplicadorMonedas));
    archivo.read((char*)&nivelVelocidadBola, sizeof(nivelVelocidadBola));
    archivo.read((char*)&desbloqueoBlindaje, sizeof(desbloqueoBlindaje));
    archivo.read((char*)&multiplicador, sizeof(multiplicador));
}