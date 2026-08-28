#include "usuario.h"
#include <string>
using namespace std;

Usuario::Usuario(string& nombre, string& username, string& passwordHash) {
    this->nombre=nombre;
    this->username=username;
    this->passwordHash=passwordHash;
    this->puntos=0;
    this->mejorTiempo=0;
}
//constructor para reconstruir el user (login)
Usuario::Usuario(string& nombre, string& username, string& passwordPlano,int puntos,int mejorTiempo){
    this->nombre=nombre;
    this->username=username;
    this->passwordHash=to_string(hash<string>{}(passwordPlano + username));
    this->puntos=puntos;
    this->mejorTiempo=mejorTiempo;
}

void Usuario::sumarPuntos(int puntos){
    this->puntos+=puntos;
}

/*
 * Getters
 */
const string& Usuario::getNombre() const{
    return nombre;
}
const string& Usuario::getUsername() const{
    return username;
}
const string& Usuario::getPasswordHash() const{
    return passwordHash;
}
int Usuario::getPuntos() const{
    return puntos;
}
int Usuario::getMejorTiempo() const{
    return mejorTiempo;
}

/*
 * Setters
 */
void Usuario::setNombre(string &nombre){
    this->nombre=nombre;
}
void Usuario::setUsername(string& username){
    this->username=username;
}
void Usuario::setPasswordHash(string& passwordHash){
    this->passwordHash=passwordHash;
}
void Usuario::setPuntos(int puntos){
    this->puntos=puntos;
}
void Usuario::setMejorTiempo(int mejorTiempo){
    this->mejorTiempo=mejorTiempo;
}