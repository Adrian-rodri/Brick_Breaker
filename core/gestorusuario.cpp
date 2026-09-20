#include "gestorusuario.h"
#include "usuario.h"
#include "constantes.h"

#include <fstream>
#include <filesystem>

using namespace std;
//Se van a usar archivos .bbk para guardar los datos de los users
//en archivos binarios, estos archivos van en /data que esta dentro del build
//con usuarios.bbk para los todos los usernames
//el formato seria [int cantidadUsers]
//                 [int length][string usuario]
//y por cada usuario se creara una carpeta con sus datos y estadisticas
GestorUsuario::GestorUsuario() {
    filesystem::create_directories("data");
    cargarUsuarios();
    usuarioActual=nullptr;
}

void GestorUsuario::cargarUsuarios(){
    ifstream archivo("data/usuarios.bbk",ios::binary);

    if(!archivo.is_open()){
        cantidadUsuarios=0;
        ptrUsuarios=nullptr;
        return;
    }
    archivo.read((char*)&cantidadUsuarios,sizeof(cantidadUsuarios));

    if(cantidadUsuarios>=0){
        ptrUsuarios= new string[cantidadUsuarios];

        for(int i=0;i<cantidadUsuarios;i++){
            ptrUsuarios[i]=leerString(archivo);
        }
    }else{
        ptrUsuarios=nullptr;
    }
    archivo.close();
}
bool GestorUsuario::validarLogin(const string &username,const string &passwordIntento){
    Usuario* perfil= cargarPerfil(username);
    if(perfil==nullptr){
        return false;
    }
    bool coincide= (passwordIntento==perfil->getPassword());
    delete perfil;
    return coincide;
}

void GestorUsuario::iniciarSesion(const string& username){
    if(usuarioActual!=nullptr){
        delete usuarioActual;
    }
    usuarioActual=cargarPerfil(username);
}
void GestorUsuario::cerrarSesion(){
    if(usuarioActual!=nullptr){
        guardarProgreso(usuarioActual->getUsername(), usuarioActual->getPerfil());
        delete usuarioActual;
        usuarioActual= nullptr;
    }
}
bool GestorUsuario::agregarUsuarioDisco(Usuario &nuevoUsuario){
    if(existeUsuario(nuevoUsuario.getUsername())){
        return false;
    }
    agregarUsuarioRAM(nuevoUsuario.getUsername());

    ofstream archivo("data/usuarios.bbk",ios::binary);
    archivo.write((char*)&cantidadUsuarios,sizeof(cantidadUsuarios));

    for(int i=0;i<cantidadUsuarios;i++){
        escribirString(archivo,ptrUsuarios[i]);
    }
    archivo.close();
    crearArchivosUsuario(nuevoUsuario);
    return true;
}
Usuario* GestorUsuario::cargarPerfil(const string &username){
    string rutaArchivo="data/users/"+username+"/perfil.bbk";

    ifstream archivo(rutaArchivo,ios::binary);

    if(!archivo.is_open()){
        return nullptr;
    }

    string nombre= leerString(archivo);
    string user= leerString(archivo);
    string pass= leerString(archivo);

    int puntos(0);
    archivo.read((char*)&puntos,sizeof(puntos));

    int mejorPuntuacion(0);
    archivo.read((char*)&mejorPuntuacion,sizeof(mejorPuntuacion));

    Usuario *perfilCargado= new Usuario(nombre,user,pass,puntos,mejorPuntuacion);

    PerfilProgreso* progreso= cargarProgreso(username);
    if(progreso!=nullptr){
        perfilCargado->setPerfil(*progreso);
        delete progreso;
    }

    return perfilCargado;
}
void GestorUsuario::crearArchivosUsuario(Usuario &usuario){//crear los archivos necesarios
    string rutaCarpeta= "data/users/"+usuario.getUsername();
    filesystem::create_directories(rutaCarpeta);

    string rutaArchivo= rutaCarpeta+"/perfil.bbk";
    ofstream archivo(rutaArchivo,ios::binary);

    if(archivo.is_open()){
        string nombre= usuario.getNombre();
        string username= usuario.getUsername();
        string password= usuario.getPassword();
        int puntos= usuario.getPuntos();
        int mejorTiempo= usuario.getMejorTiempo();

        escribirString(archivo,nombre);
        escribirString(archivo,username);
        escribirString(archivo,password);

        archivo.write((char*)&puntos,sizeof(puntos));
        archivo.write((char*)&mejorTiempo,sizeof(mejorTiempo));

        archivo.close();
    }
    ofstream archivoLogros(rutaCarpeta+"/logros.bbk",ios::app);
    archivoLogros.close();
    ofstream archivoProgreso(rutaCarpeta+"/progreso.bbk", ios::binary);
    PerfilProgreso perfilInicial;
    perfilInicial.guardar(archivoProgreso);
    archivoProgreso.close();
}
void GestorUsuario::agregarUsuarioRAM(string nuevoUsername){//agregar el user al puntero en RAM
    string* nuevoPtr= new string[cantidadUsuarios+1];

    for(int i=0;i<cantidadUsuarios;i++){//copiar de nuevo el puntero
        nuevoPtr[i]=ptrUsuarios[i];
    }
    nuevoPtr[cantidadUsuarios]=nuevoUsername;//agregar el nuevo user al final

    delete[] ptrUsuarios;
    ptrUsuarios=nuevoPtr;

    cantidadUsuarios++;
}

bool GestorUsuario::existeUsuario(string username){
    for(int i=0;i<cantidadUsuarios;i++){
        if(ptrUsuarios[i]==username){
            return true;
        }
    }
    return false;
}
void GestorUsuario::liberarMemoria(){
    if(ptrUsuarios!=nullptr){
        delete[] ptrUsuarios;
        ptrUsuarios=nullptr;
    }
    cerrarSesion();
}

void GestorUsuario::escribirString(ofstream& archivo,const string& palabra){
    size_t length= palabra.size();

    archivo.write((char*)&length,sizeof(length));
    archivo.write(palabra.c_str(),length);
}
string GestorUsuario::leerString(ifstream& archivo){
    size_t length;
    archivo.read((char*)&length,sizeof(length));
    //guarda la longitud del string

    string result;
    result.resize(length);//cambia el size del string
    archivo.read(&result[0],length);//guarda el texto como tal
    return result;
}
void GestorUsuario::guardarProgreso(const string& username, PerfilProgreso& perfil){
    string rutaArchivo= "data/users/"+username+"/progreso.bbk";
    ofstream archivo(rutaArchivo, ios::binary);

    if(archivo.is_open()){
        perfil.guardar(archivo);
        archivo.close();
    }
}

PerfilProgreso* GestorUsuario::cargarProgreso(const string& username){
    string rutaArchivo= "data/users/"+username+"/progreso.bbk";
    ifstream archivo(rutaArchivo, ios::binary);

    if(!archivo.is_open()){
        return nullptr;
    }

    PerfilProgreso* perfilCargado= new PerfilProgreso();
    perfilCargado->cargar(archivo);
    archivo.close();

    return perfilCargado;
}

int GestorUsuario::getCantidadUsuarios() const{
    return cantidadUsuarios;
}

string GestorUsuario::getUsername(int indice) const{
    if(indice<0 || indice>=cantidadUsuarios){
        return "";
    }
    return ptrUsuarios[indice];
}

//destructor
GestorUsuario::~GestorUsuario(){
    liberarMemoria();
}