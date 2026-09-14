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
    ~Nivel();
    void cargarMatrizAleatoria();
    Bloque*** getMatriz() const;
    int getNumeroNivel() const;
    int getFilas()const;
    int getColumnas()const;

    void liberarMatriz();
    void destruirBloque(int fila, int col);
    void regenerar();
    int getBloquesRestantes() const;
};

#endif // NIVEL_H
