#ifndef NIVEL_H
#define NIVEL_H

#include "bloque.h"
class Nivel
{
private:
    Bloque*** matrizBloques;
    int numNivel;
    int bloquesRestantes;
    int filas;
    int columnas;
public:
    Nivel(int numNivel);
    void cargarMatriz();
    Bloque*** getMatriz() const;
    int getNumeroNivel() const;
    int getFilas()const;
    int getColumnas()const;

    void liberarMatriz();
};

#endif // NIVEL_H
