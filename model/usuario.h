#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;
class Usuario
{
public:
    Usuario(string& nombre, string& username, string& password);
    Usuario(string& nombre, string& username, string& password,int puntos,int mejorTiempo);
    //getters
    const string& getNombre() const;
    const string& getUsername() const;
    const string& getPassword() const;
    int getPuntos() const;
    int getMejorTiempo() const;

    //setters
    void setNombre(string& nombre) ;
    void setUsername(string& username);
    void setPassword(string& password);
    void setPuntos(int puntos);
    void setMejorTiempo(int mejorTiempo);

    void sumarPuntos(int puntos);
private:
    //datos generales
    string nombre;
    string username;
    string password;

    //estadisticas
    int puntos;
    int mejorTiempo;

};

#endif // USUARIO_H
