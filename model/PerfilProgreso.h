#ifndef PERFILPROGRESO_H
#define PERFILPROGRESO_H

class PerfilProgreso{
private:
    int creditos;
    int mapaMaxDesbloqueado;

    int nivelDañoBola;
    int nivelMultiplicadorMonedas;
    int nivelVelocidadBola;

    bool desbloqueoBlindaje;
    double multiplicador;

public:
    PerfilProgreso();
    PerfilProgreso(int creditos, int mapaMaxDesbloqueado, int nivelDañoBola,
                   int nivelMultiplicadorMonedas, int nivelVelocidadBola,
                   bool desbloqueoBlindaje, double multiplicador);

    //getters
    int getCreditos() const;
    int getMapaMaxDesbloqueado() const;
    int getNivelDañoBola() const;
    int getNivelMultiplicadorMonedas() const;
    int getNivelVelocidadBola() const;
    bool getDesbloqueoBlindaje() const;
    double getMultiplicador() const;

    void sumarCreditos(int cantidad);
    bool gastarCreditos(int cantidad);
    void desbloquearMapa(int numMapa);

    void subirNivelDañoBola();
    void subirNivelMultiplicadorMonedas();
    void subirNivelVelocidadBola();

    void desbloquearBlindaje();
    void setMultiplicador(double nuevoValor);
};

#endif // PERFILPROGRESO_H