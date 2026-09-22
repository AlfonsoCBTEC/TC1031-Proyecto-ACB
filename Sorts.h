#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include "Expediente.h"

/**
 * @class Sorts
 * @brief Algoritmos de ordenamiento para la coleccion de expedientes.
 */
class Sorts {
private:
    /**
     * @brief Fusiona dos subvectores ordenados alfabeticamente por nombre.
     */
    static void merge(std::vector<Expediente>& arr, int inicio, int medio, int fin) {
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        // Subarreglos temporales
        std::vector<Expediente> L(n1);
        std::vector<Expediente> R(n2);

        for (int i = 0; i < n1; i++) {
            L[i] = arr[inicio + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = arr[medio + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = inicio;

        // Fusion en orden alfabetico
        while (i < n1 && j < n2) {
            if (L[i].getNombre() <= R[j].getNombre()) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copiar elementos restantes de L[] si quedaron
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copiar elementos restantes de R[] si quedaron
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    /**
     * @brief Funcion auxiliar recursiva para Merge Sort.
     */
    static void mergeSortRecursivo(std::vector<Expediente>& arr, int inicio, int fin) {
        if (inicio < fin) {
            int medio = inicio + (fin - inicio) / 2;

            // Divide
            mergeSortRecursivo(arr, inicio, medio);
            mergeSortRecursivo(arr, medio + 1, fin);

            // Fusiona
            merge(arr, inicio, medio, fin);
        }
    }

public:
    /**
     * @brief Ordena un vector de Expedientes alfabeticamente por nombre usando Merge Sort.
     * @param arr Vector de expedientes pasado por referencia.
     */
    static void mergeSortPorNombre(std::vector<Expediente>& arr) {
        if (!arr.empty()) {
            mergeSortRecursivo(arr, 0, arr.size() - 1);
        }
    }

    /**
     * @brief Ordena un vector de Expedientes por su promedio usando Insertion Sort (Descendente).
     * @param arr Vector de expedientes pasado por referencia.
     */
    static void insertionSortPorPromedio(std::vector<Expediente>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            Expediente key = arr[i];
            int j = i - 1;

            // Orden descendente (promedios mas altos primero)
            while (j >= 0 && arr[j].getPromedio() < key.getPromedio()) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
};

#endif
