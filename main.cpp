/**
 * @file main.cpp
 * @brief Menu interactivo para el Sistema de Gestion de Expedientes.
 *        Integra DList, Sorts sobre nodos y BST para busquedas por rango.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Expediente.h"
#include "DList.h"
#include "Sorts.h"
#include "BST.h"

using namespace std;

/**
 * @brief Lee el archivo CSV y añade registros tanto a la DList como en el BST inicial.
 * @param nombreArchivo Ruta del archivo CSV.
 * @param lista Referencia a la DList principal.
 * @param arbol Referencia al BST.
 */
void cargarExpedientes(const string& nombreArchivo, DList<Expediente>& lista, BST& arbol) {

    lista.clear();
    arbol.clear();

    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    getline(archivo, linea); // Omitimos los encabezados del CSV

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string matricula, nombre, carrera, prom_str, cred_str;

        getline(ss, matricula, ',');
        getline(ss, nombre, ',');
        getline(ss, carrera, ',');
        getline(ss, prom_str, ',');
        getline(ss, cred_str, ',');

        if (!matricula.empty()) {
            Expediente nuevo(matricula, nombre, carrera, stof(prom_str), stoi(cred_str));
            lista.addLast(nuevo);
            arbol.add(nuevo);
        }
    }
    archivo.close();
}


/**
 * @brief Sobreescribe el archivo CSV con elorden actual de la DList.
 * @param lista Referencia a la DList.
 * @param nombreArchivo Ruta del archivo CSV.
 */
void guardarExpedientes(const DList<Expediente>& lista, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    archivo << "matricula,nombre,carrera,promedio,creditos\n";

    DLink<Expediente>* curr = lista.getHead();
    while (curr != nullptr) {
        archivo << curr->value.getMatricula() << ","
                << curr->value.getNombre() << ","
                << curr->value.getCarrera() << ","
                << curr->value.getPromedio() << ","
                << curr->value.getCreditos() << "\n";
        curr = curr->next;
    }

    archivo.close();
    cout << "\nLos cambios se guardaron en: " << nombreArchivo << "\n";
}
