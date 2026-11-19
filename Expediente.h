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
    std::string id;
    std::string name;
    std::string major;
    float average;
    int credits;

public:
    Expediente();
    Expediente(std::string _id, std::string _name, std::string _major, float _avg, int _cred);

    std::string getId() const;
    std::string getName() const;
    std::string getMajor() const;
    float getAverage() const;
    int getCredits() const;

    /**
     * @brief Muestra los datos del estudiante en consola.
     */
    void print() const;
};

Expediente::Expediente() : id(""), name(""), major(""), average(0.0), credits(0) {}

Expediente::Expediente(std::string _id, std::string _name, std::string _major, float _avg, int _cred) 
    : id(_id), name(_name), major(_major), average(_avg), credits(_cred) {}

std::string Expediente::getId() const { return id; }
std::string Expediente::getName() const { return name; }
std::string Expediente::getMajor() const { return major; }
float Expediente::getAverage() const { return average; }
int Expediente::getCredits() const { return credits; }

void Expediente::print() const {
    std::cout << "[" << id << "] " << name 
              << " | " << major 
              << " | Promedio: " << average 
              << " | Creditos: " << credits << "\n";
}

#endif
