#include "PerfilProgreso.h"

PerfilProgreso::PerfilProgreso(){
    creditos=0;
    mapaMaxDesbloqueado=1;
    nivelDañoBola=1;
    nivelMultiplicadorMonedas=1;
    nivelVelocidadPlataforma=1;
    desbloqueoBlindaje=false;
    historiaCompletada=false;
    multiplicador=1.0;
    nivelPrestigio=0;
}

PerfilProgreso::PerfilProgreso(int creditos, int mapaMaxDesbloqueado, int nivelDañoBola,
                               int nivelMultiplicadorMonedas, int nivelVelocidadPlataforma,
                               bool desbloqueoBlindaje, double multiplicador){
    this->creditos=creditos;
    this->mapaMaxDesbloqueado=mapaMaxDesbloqueado;
    this->nivelDañoBola=nivelDañoBola;
    this->nivelMultiplicadorMonedas=nivelMultiplicadorMonedas;
    this->nivelVelocidadPlataforma=nivelVelocidadPlataforma;
    this->desbloqueoBlindaje=desbloqueoBlindaje;
    this->historiaCompletada=false;
    this->multiplicador=multiplicador;
    this->nivelPrestigio=0;
}

//getters
double PerfilProgreso::getCreditos() const{
    return creditos;
}
int PerfilProgreso::getMapaMaxDesbloqueado() const{
    return mapaMaxDesbloqueado;
}
int PerfilProgreso::getNivelDañoBola() const{
    return nivelDañoBola;
}
int PerfilProgreso::getNivelMultiplicadorMonedas() const{
    return nivelMultiplicadorMonedas;
}
int PerfilProgreso::getNivelVelocidadPlataforma() const{
    return nivelVelocidadPlataforma;
}
bool PerfilProgreso::getDesbloqueoBlindaje() const{
    return desbloqueoBlindaje;
}
bool PerfilProgreso::getHistoriaCompletada() const{
    return historiaCompletada;
}
double PerfilProgreso::getMultiplicador() const{
    return multiplicador;
}
int PerfilProgreso::getNivelPrestigio() const{
    return nivelPrestigio;
}
double PerfilProgreso::getMultiplicadorTotal() const{
    return multiplicador * (1.0 + 0.5 * nivelPrestigio);
}

void PerfilProgreso::sumarCreditos(double cantidad){
    creditos+=cantidad;
}

bool PerfilProgreso::gastarCreditos(double cantidad){
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
void PerfilProgreso::subirNivelVelocidadPlataforma(){
    nivelVelocidadPlataforma++;
}

void PerfilProgreso::desbloquearBlindaje(){
    desbloqueoBlindaje=true;
}

void PerfilProgreso::completarHistoria(){
    historiaCompletada=true;
}

void PerfilProgreso::setMultiplicador(double nuevoValor){
    if(nuevoValor<1.0){
        nuevoValor=1.0;
    }
    multiplicador=nuevoValor;
}

void PerfilProgreso::hacerPrestigio(){
    creditos=0;
    nivelDañoBola=1;
    nivelMultiplicadorMonedas=1;
    nivelVelocidadPlataforma=1;
    desbloqueoBlindaje=false;
    multiplicador=1.0;
    nivelPrestigio++;
}

void PerfilProgreso::guardar(std::ofstream& archivo) const{
    const int VERSION_PROGRESO = 2;
    archivo.write((char*)&VERSION_PROGRESO, sizeof(VERSION_PROGRESO));
    archivo.write((char*)&creditos, sizeof(creditos));
    archivo.write((char*)&mapaMaxDesbloqueado, sizeof(mapaMaxDesbloqueado));
    archivo.write((char*)&nivelDañoBola, sizeof(nivelDañoBola));
    archivo.write((char*)&nivelMultiplicadorMonedas, sizeof(nivelMultiplicadorMonedas));
    archivo.write((char*)&nivelVelocidadPlataforma, sizeof(nivelVelocidadPlataforma));
    archivo.write((char*)&desbloqueoBlindaje, sizeof(desbloqueoBlindaje));
    archivo.write((char*)&multiplicador, sizeof(multiplicador));
    archivo.write((char*)&historiaCompletada, sizeof(historiaCompletada));
    archivo.write((char*)&nivelPrestigio, sizeof(nivelPrestigio));
}

void PerfilProgreso::cargar(std::ifstream& archivo){
    int version = 0;
    archivo.read((char*)&version, sizeof(version));

    archivo.read((char*)&creditos, sizeof(creditos));
    archivo.read((char*)&mapaMaxDesbloqueado, sizeof(mapaMaxDesbloqueado));
    archivo.read((char*)&nivelDañoBola, sizeof(nivelDañoBola));
    archivo.read((char*)&nivelMultiplicadorMonedas, sizeof(nivelMultiplicadorMonedas));
    archivo.read((char*)&nivelVelocidadPlataforma, sizeof(nivelVelocidadPlataforma));
    archivo.read((char*)&desbloqueoBlindaje, sizeof(desbloqueoBlindaje));
    archivo.read((char*)&multiplicador, sizeof(multiplicador));
    archivo.read((char*)&historiaCompletada, sizeof(historiaCompletada));
    archivo.read((char*)&nivelPrestigio, sizeof(nivelPrestigio));
}