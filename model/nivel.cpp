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

        //todo vacío
        for(int i=0;i<filas;i++){
            matrizBloques[i]= new Bloque*[columnas];
            for(int j=0;j<columnas;j++){
                matrizBloques[i][j]= nullptr;
            }
        }

        //reforzados
        for(int i=0;i<filas;i++){
            matrizBloques[i][0]= new Bloque(REFORZADO,0,i);
            matrizBloques[i][1]= new Bloque(REFORZADO,1,i);
            matrizBloques[i][11]= new Bloque(REFORZADO,11,i);
            matrizBloques[i][12]= new Bloque(REFORZADO,12,i);
        }
        for(int j=2;j<=10;j++){
            matrizBloques[0][j]= new Bloque(SIMPLE,j,0);
        }
        for(int j=2;j<=10;j++){
            if(j<5 || j>7){
                matrizBloques[1][j]= new Bloque(SIMPLE,j,1);
            }
        }
        for(int i=2;i<=4;i++){
            for(int j=2;j<=10;j++){
                if((i+j)%2==0){
                    matrizBloques[i][j]= new Bloque(SIMPLE,j,i);
                }
            }
        }

        matrizBloques[2][4]= new Bloque(REFORZADO,4,2);
        matrizBloques[2][8]= new Bloque(REFORZADO,8,2);
        matrizBloques[3][4]= new Bloque(REFORZADO,4,3);
        matrizBloques[3][8]= new Bloque(REFORZADO,8,3);

        for(int j=2;j<=10;j++){
            matrizBloques[5][j]= new Bloque(REFORZADO,j,5);
        }
        break;
    case 3:
        filas=9;
        columnas=13;
        matrizBloques= new Bloque**[filas];
        for(int i=0;i<filas;i++){
            matrizBloques[i]= new Bloque*[columnas];
            for(int j=0;j<columnas;j++){
                matrizBloques[i][j]= nullptr;
            }
        }
        //indestructibles
        for(int j=0;j<columnas;j++){
            matrizBloques[0][j]= new Bloque(INDESTRUCTIBLE,j,0);
        }
        for(int i=1;i<=6;i++){
            matrizBloques[i][4]= new Bloque(INDESTRUCTIBLE,4,i);
            matrizBloques[i][8]= new Bloque(INDESTRUCTIBLE,8,i);
        }
        //reforzados
        for(int i=1;i<=6;i++){
            for(int j=0;j<=3;j++){
                matrizBloques[i][j]= new Bloque(REFORZADO,j,i);
            }
        }
        for(int i=1;i<=6;i++){
            for(int j=9;j<=12;j++){
                matrizBloques[i][j]= new Bloque(REFORZADO,j,i);
            }
        }
        //indestructible
        matrizBloques[2][5]= new Bloque(INDESTRUCTIBLE,5,2);
        matrizBloques[2][7]= new Bloque(INDESTRUCTIBLE,7,2);
        //siple
        for(int i=1;i<=6;i++){
            if(matrizBloques[i][5]==nullptr) matrizBloques[i][5]= new Bloque(SIMPLE,5,i);
            matrizBloques[i][6]= new Bloque(SIMPLE,6,i);
            if(matrizBloques[i][7]==nullptr) matrizBloques[i][7]= new Bloque(SIMPLE,7,i);
        }
        for(int j=0;j<columnas;j++){
            if(j!=2 && j!=6 && j!=10){
                matrizBloques[7][j]= new Bloque(INDESTRUCTIBLE,j,7);
            }
        }
        for(int j=0;j<columnas;j++){
            matrizBloques[8][j]= new Bloque(REFORZADO,j,8);
        }
        break;
    default:
        break;
    }
    bloquesRestantes = 0;
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(matrizBloques[i][j] != nullptr && matrizBloques[i][j]->getTipoBloque()!=INDESTRUCTIBLE){
                bloquesRestantes++;
            }
        }
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