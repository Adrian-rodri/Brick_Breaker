#include "nivel.h"

Nivel::Nivel(int numNivel) {
    this->numNivel=numNivel;
    cargarMatriz();
}
void Nivel::cargarMatriz(){
    switch(numNivel){
    case 1:
        filas=5;
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
        filas=7;
        columnas=13;
        matrizBloques= new Bloque**[filas];
        for(int i=0;i<filas;i++){//Llenar de bloques simples
            matrizBloques[i]= new Bloque*[columnas];
            for(int j=0;j<columnas;j++){
                matrizBloques[i][j]= new Bloque(SIMPLE,j,i);
            }
        }
        //Poner bloques reforzados
        for(int i=0;i<columnas;i++){
            if(!(i%2==0)){
                matrizBloques[5][i]= new Bloque(REFORZADO,i,5);
            }else{
                matrizBloques[6][i]= new Bloque(REFORZADO,i,6);
            }
        }
        for(int i=0;i<filas;i++){
            if(i%2==0){
                matrizBloques[i][6]= new Bloque(REFORZADO,6,i);
            }
        }
        matrizBloques[1][5]= new Bloque(REFORZADO,5,1);
        matrizBloques[1][7]= new Bloque(REFORZADO,7,1);
        matrizBloques[2][4]= new Bloque(REFORZADO,4,2);
        matrizBloques[2][8]= new Bloque(REFORZADO,8,2);
        matrizBloques[3][3]= new Bloque(REFORZADO,3,3);
        matrizBloques[3][9]= new Bloque(REFORZADO,9,3);
        matrizBloques[4][2]= new Bloque(REFORZADO,2,4);
        matrizBloques[4][10]= new Bloque(REFORZADO,10,4);
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