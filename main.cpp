#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Expediente.h"
#include "Sorts.h"

using namespace std;

/**
 * @brief Lee elarchivo CSV y carga los registros en memoria.
 * @param nombreArchivo Ruta y nombre del archivo CSV.
 * @return Vector con los objetos Expediente inicializados.
 */
vector<Expediente> cargarExpedientes(const string& nombreArchivo) {
    vector<Expediente> baseDatos;
    ifstream archivo(nombreArchivo);
    string linea, celda;

    if (!archivo.is_open()) {
        cerr << "Error, no se pudo abrir el archivo " << nombreArchivo << endl;
        return baseDatos;
    }

    // Omitimos los encabezados del CSV
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string matricula, nombre, carrera, prom_str, cred_str;

        getline(ss, matricula, ',');
        getline(ss, nombre, ',');
        getline(ss, carrera, ',');
        getline(ss, prom_str, ',');
        getline(ss, cred_str, ',');

        float promedio = stof(prom_str);
        int creditos = stoi(cred_str);

        baseDatos.push_back(Expediente(matricula, nombre, carrera, promedio, creditos));
    }
    
    archivo.close();
    return baseDatos;
}

int main() {
    cout << "== Sistema de expedientes de alfonso ===" << endl;
    vector<Expediente> registros = cargarExpedientes("expedientes.csv");

    cout << "\n-- Registros sin ordenar  ---" << endl;
    for (const auto& exp : registros) {
        exp.imprimir();
    }

    cout << "\n--- Registros Ordenados por Promedio --" << endl;
    Sorts::insertionSortPorPromedio(registros);
    for (const auto& exp : registros) {
        exp.imprimir();
    }

    cout << "\n--- Ordenados Alfabeticamente por Nombre---\n";
    Sorts::mergeSortPorNombre(registros);
    for (const auto& exp : registros) {
        exp.imprimir();
    }


    return 0;
}
