#include "nivel.h"
#include "cstdlib"
#include "bloquesimple.h"
#include "bloquereforzado.h"
#include "bloqueblindado.h"

Nivel::Nivel(int numNivel) {
    this->numNivel=numNivel;
    cargarMatrizAleatoria();
}
void Nivel::cargarMatrizAleatoria(){
    int probVacio, probSimple, probReforzado, probBlindado;
    switch(numNivel){
    case 1:{
        filas=5;
        columnas=13;
        probVacio=20;
        probSimple=80;
        probReforzado=0;
        probBlindado= 0;
        break;
    }case 2:{
        filas=7;
        columnas=13;
        probVacio= 20;
        probSimple= 30;
        probReforzado= 50;
        probBlindado= 0;
        break;
    }case 3:{
        filas=9;
        columnas= 13;
        probVacio= 10;
        probSimple= 0;
        probReforzado= 30;
        probBlindado= 60;
        break;
    }default:{
        filas=5;
        columnas=13;
        probVacio=20;
        probSimple=80;
        probReforzado=0;
        probBlindado= 0;
        break;
    }
    }
    matrizBloques= new Bloque**[filas];
    for(int i=0;i<filas;i++){
        matrizBloques[i]= new Bloque*[columnas];
    }
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            int chance= rand()%100;
            if(chance<probVacio){
                matrizBloques[i][j]= nullptr;
            }else if(chance<probVacio+probSimple){
                matrizBloques[i][j]= new BloqueSimple(j,i);
            }else if(chance<probVacio+probSimple+probReforzado){
                matrizBloques[i][j]= new BloqueReforzado(j,i);
            }else{
                matrizBloques[i][j]=  new BloqueBlindado(j,i);
            }
        }
    }
    bloquesRestantes= 0;
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(matrizBloques[i][j] != nullptr){
                bloquesRestantes++;
            }
        }
    }
}
void Nivel::regenerar(){
    liberarMatriz();
    cargarMatrizAleatoria();
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
Nivel::~Nivel(){
    if(matrizBloques !=nullptr){
        liberarMatriz();
    }
}

void Nivel::destruirBloque(int fila, int col){
    if(matrizBloques[fila][col]!= nullptr){
        delete matrizBloques[fila][col];
        matrizBloques[fila][col]= nullptr;
        bloquesRestantes--;
    }
}

int Nivel::getBloquesRestantes() const{
    return bloquesRestantes;
}