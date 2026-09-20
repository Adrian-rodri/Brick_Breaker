#include "constantes.h"

#include <fstream>

double VOLUMEN_GLOBAL= 1.0;

void cargarConfiguracion(){
    std::ifstream archivo("data/config.bbk", std::ios::binary);
    if(archivo.is_open()){
        archivo.read((char*)&VOLUMEN_GLOBAL, sizeof(VOLUMEN_GLOBAL));
        archivo.close();
        if(VOLUMEN_GLOBAL<0 || VOLUMEN_GLOBAL> 1.0){
            VOLUMEN_GLOBAL= 1.0;
        }
    }
}

void guardarConfiguracion(){
    std::ofstream archivo("data/config.bbk", std::ios::binary);
    if(archivo.is_open()){
        archivo.write((char*)&VOLUMEN_GLOBAL, sizeof(VOLUMEN_GLOBAL));
        archivo.close();
    }
}