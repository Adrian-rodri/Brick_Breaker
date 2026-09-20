#ifndef GESTORUSUARIO_H
#define GESTORUSUARIO_H

#include "usuario.h"
#include "PerfilProgreso.h"
#include <fstream>

class GestorUsuario
{
private:
    string* ptrUsuarios;
    int cantidadUsuarios;

    void escribirString(ofstream& archivo,const string& palabra);
    string leerString(ifstream& archivo);

public:
    GestorUsuario();
    ~GestorUsuario();

    Usuario* usuarioActual;

    bool validarLogin(const string& username,const string &passwordIntento);
    void iniciarSesion(const string& username);
    void cerrarSesion();

    bool existeUsuario(string username);
    void cargarUsuarios();
    Usuario* cargarPerfil(const string &username);
    void agregarUsuarioRAM(string nuevoUsername);
    bool agregarUsuarioDisco(Usuario &nuevoUsuario);
    void crearArchivosUsuario(Usuario &usuario);
    void liberarMemoria();

    void guardarProgreso(const string& username, PerfilProgreso& perfil);
    PerfilProgreso* cargarProgreso(const string& username);

    int getCantidadUsuarios() const;
    string getUsername(int indice) const;
};

#endif // GESTORUSUARIO_H