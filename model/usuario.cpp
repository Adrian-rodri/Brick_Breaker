#include "usuario.h"
#include <string>
using namespace std;

Usuario::Usuario(string& nombre, string& username, string& password) {
    this->nombre=nombre;
    this->username=username;
    this->password=password;
    this->puntos=0;
    this->mejorTiempo=0;
}
//constructor para reconstruir el user (login)
Usuario::Usuario(string& nombre, string& username, string& password,int puntos,int mejorTiempo){
    this->nombre=nombre;
    this->username=username;
    this->password=password;
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
const string& Usuario::getPassword() const{
    return password;
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
void Usuario::setPassword(string& password){
    this->password=password;
}
void Usuario::setPuntos(int puntos){
    this->puntos=puntos;
}
void Usuario::setMejorTiempo(int mejorTiempo){
    this->mejorTiempo=mejorTiempo;
}