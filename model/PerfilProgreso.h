#ifndef PERFILPROGRESO_H
#define PERFILPROGRESO_H

#include <fstream>

class PerfilProgreso{
private:
    double creditos;
    int mapaMaxDesbloqueado;

    int nivelDañoBola;
    int nivelMultiplicadorMonedas;
    int nivelVelocidadPlataforma;

    bool desbloqueoBlindaje;
    bool historiaCompletada;
    double multiplicador;
    int nivelPrestigio;

public:
    PerfilProgreso();
    PerfilProgreso(int creditos, int mapaMaxDesbloqueado, int nivelDañoBola,
                   int nivelMultiplicadorMonedas, int nivelVelocidadPlataforma,
                   bool desbloqueoBlindaje, double multiplicador);

    //getters
    double getCreditos() const;
    int getMapaMaxDesbloqueado() const;
    int getNivelDañoBola() const;
    int getNivelMultiplicadorMonedas() const;
    int getNivelVelocidadPlataforma() const;
    bool getDesbloqueoBlindaje() const;
    bool getHistoriaCompletada() const;
    double getMultiplicador() const;
    int getNivelPrestigio() const;
    double getMultiplicadorTotal() const;

    void sumarCreditos(double cantidad);
    bool gastarCreditos(double cantidad);
    void desbloquearMapa(int numMapa);

    void subirNivelDañoBola();
    void subirNivelMultiplicadorMonedas();
    void subirNivelVelocidadPlataforma();

    void desbloquearBlindaje();
    void completarHistoria();
    void setMultiplicador(double nuevoValor);
    void hacerPrestigio();

    void guardar(std::ofstream& archivo) const;
    void cargar(std::ifstream& archivo);
};

#endif // PERFILPROGRESO_H