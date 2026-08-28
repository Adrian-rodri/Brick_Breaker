#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <functional>

using namespace std;
class Usuario
{
public:
    Usuario(string& nombre, string& username, string& passwordPlano);
    Usuario(string& nombre, string& username, string& passwordHash,int puntos,int mejorTiempo);
    //getters
    const string& getNombre() const;
    const string& getUsername() const;
    const string& getPasswordHash() const;
    int getPuntos() const;
    int getMejorTiempo() const;

    //setters
    void setNombre(string& nombre) ;
    void setUsername(string& username);
    void setPasswordHash(string& passwordHash);
    void setPuntos(int puntos);
    void setMejorTiempo(int mejorTiempo);

    void sumarPuntos(int puntos);
private:
    //Datos generales
    string nombre;
    string username;
    string passwordHash;

    //Estadisticas
    int puntos;
    int mejorTiempo;

};

#endif // USUARIO_H
