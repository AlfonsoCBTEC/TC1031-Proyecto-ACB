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
 * @brief Reconstruye el BST a partir de los elementos actuales en la DList.
 *        Se utiliza cuando se elimina un registro para asegurarnos que ambas estructuras estan sincronizadas.
 * @param lista Referencia constante a la DList.
 * @param arbol Referencia al BST a reconstruir.
 */
void sincronizarArbol(const DList<Expediente>& lista, BST& arbol) {
    arbol.clear();
    DLink<Expediente>* curr = lista.getHead();
    while (curr != nullptr) {
        arbol.add(curr->value);
        curr = curr->next;
    }
}

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

/**
 * @brief Recorre e imprime en consola todos los elementos de la DList.
 * @param lista Referencia a la DList.
 */
void mostrarExpedientes(const DList<Expediente>& lista) {
    if (lista.empty()) {
        cout << "\nEsta vacia la lista.\n";
        return;
    }
    cout << "\n-----Expedientes actuales (" << lista.length() << " registros) ---\n";
    DLink<Expediente>* curr = lista.getHead();
    while (curr != nullptr) {
        curr->value.imprimir();
        curr = curr->next;
    }
}

/**
 * @brief Captura un nuevo expediente desde consola y lo inserta en la DList y en el BST.
 * @param lista Referencia a la DList.
 * @param arbol Referencia al BST.
 */
void registrarNuevoExpediente(DList<Expediente>& lista, BST& arbol) {

    string matricula, nombre, carrera;
    float promedio;
    int creditos;

    cout << "\n----- Registrar Nuevo Expediente ---\n";
    cout << "Matricula: ";
    cin >> matricula;

    if (lista.findByMatricula(matricula) != nullptr) {
        cout << "\nYa existe estudiante con la siguiente matricula " << matricula << ".\n";
        return;
    }

    cin.ignore();
    cout << "Nombre completo (Apellidos y Nombre): ";
    getline(cin, nombre);

    cout << "Carrera: ";
    getline(cin, carrera);

    cout << "Promedio (0 a 100): ";
    cin >> promedio;

    cout << "Creditos aprobados: ";
    cin >> creditos;

    Expediente nuevo(matricula, nombre, carrera, promedio, creditos);
    lista.addLast(nuevo);
    arbol.add(nuevo);

    cout << "\nEl expediente se agrego a la DList y al BST.\n";
}

/**
 * @brief Busca un expediente por su matricula directamente en la DList.
 * @param lista Referencia a la DList.
 */
void buscarPorMatricula(const DList<Expediente>& lista) {
    string matricula;
    cout << "\nIngresa la matricula a buscar: ";
    cin >> matricula;

    DLink<Expediente>* nodo = lista.findByMatricula(matricula);
    if (nodo != nullptr) {
        cout << "\n-----Expediente Encontrado------\n";
        nodo->value.imprimir();
    } else {
        cout << "\nNo se encontro ningun expediente con la matricula " << matricula << ".\n";
    }
}


/**
 * @brief Elimina un expediente por su matricula de la DList y actualiza el BST.
 * @param lista Referencia a la DList.
 * @param arbol Referencia al BST.
 */
void eliminarExpediente(DList<Expediente>& lista, BST& arbol) {
    string matricula;
    cout << "\nIngresa la matricula del expediente a eliminar: ";
    cin >> matricula;

    if (lista.removeByMatricula(matricula)) {
        sincronizarArbol(lista, arbol);
        cout << "\nel Expediente  " << matricula << " fue eliminado correctamente.\n";
    } else {
        cout << "\nNo se ecnontro la matricula " << matricula << " para eliminar.\n";
    }
}

/**
 * @brief Consulta el BST para mostrar expedientes dentro de un rango de promedios.
 * @param arbol Referencia al BST.
 */
void filtrarPorRangoPromedio(const BST& arbol) {
    float minProm, maxProm;
    cout << "\n----Consulta por Rango de Promedio (BST In-Order) ---\n";
    cout << "Ingresa el promedio minimo (ej. 90.0): ";
    cin >> minProm;
    cout << "Ingresa el promedio maximo (ej. 100.0): ";
    cin >> maxProm;

    if (minProm > maxProm) {
        cout << "\nel minimo no puede ser mayor al maximo.\n";
        return;
    }

    arbol.consultarRangoPromedio(minProm, maxProm);
}
