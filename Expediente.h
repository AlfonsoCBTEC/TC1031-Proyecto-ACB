#ifndef EXPEDIENTE_H
#define EXPEDIENTE_H

#include <string>
#include <iostream>

/**
 * @class Expediente
 * @brief Almacena la información académica y administrativa de un estudiante.
 */
class Expediente {
private:
    std::string matricula;
    std::string nombre;
    std::string carrera;
    float promedio;
    int creditos;

public:
    // Constructores
    Expediente() : matricula(""), nombre(""), carrera(""), promedio(0.0), creditos(0) {}
    Expediente(std::string _mat, std::string _nom, std::string _car, float _prom, int _cred) 
        : matricula(_mat), nombre(_nom), carrera(_car), promedio(_prom), creditos(_cred) {}

    // Getters
    std::string getNombre() const { return nombre; }
    float getPromedio() const { return promedio; }

    /**
     * @brief Muestra los datos del estudiante en consola.
     */
    void imprimir() const {
        std::cout << "[" << matricula << "] " << nombre 
                  << " | " << carrera 
                  << " | Promedio: " << promedio 
                  << " | Creditos: " << creditos << "\n";
    }
};

#endif
