#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <QString>

const QString COLORFONT= "#FFDEDE";
const QString COLORFONDO = "#000000";
const QString COLORSUBFONDO = "#1e1e1e";
const QString COLORBOTON= "#FF0B55";
const QString COLORBOTONHOVER= "#CF0F47";
const QString COLORBOTONPRESSED= "#2E4540";

const int BRICK_ANCHO=60;
const int BRICK_ALTO=30;
const int PLATAFORMA_ANCHO=70;
const int PLATAFORMA_ALTO=10;

const int LIMITE_PANTALLA=800;

extern double VOLUMEN_GLOBAL;
void cargarConfiguracion();
void guardarConfiguracion();
#endif // CONSTANTES_H
