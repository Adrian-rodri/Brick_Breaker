#include "nivel.h"

Nivel::Nivel(int numNivel) {
    this->numNivel=numNivel;
    cargarMatriz();
}
void Nivel::cargarMatriz(){
    switch(numNivel){
    case 1:
        filas=10;
        columnas=13;
        matrizBloques= new Bloque**[filas];
        for(int i=0;i<filas;i++){
            matrizBloques[i]= new Bloque*[columnas];
            for(int j=0;j<columnas;j++){
                matrizBloques[i][j]= new Bloque(SIMPLE,j,i);
            }
        }
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}
//getters
Bloque*** Nivel::getMatriz() const{
    return matrizBloques;
}
int Nivel::getNumeroNivel()const{
    return numNivel;
}
int Nivel::getFilas()const{
    return filas;
}
int Nivel::getColumnas()const{
    return columnas;
}
void Nivel::liberarMatriz(){
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            delete matrizBloques[i][j];
            matrizBloques[i][j]=nullptr;
        }
        delete[] matrizBloques[i];
        matrizBloques[i]=nullptr;
    }
    delete[] matrizBloques;
    matrizBloques=nullptr;
}