#ifndef BST_H
#define BST_H

#include <iostream>
#include "Expediente.h"

/**
 * @class TreeNode
 * @brief Nodo para el Arbol Binario de busqueda de los expedientes
 */
class TreeNode {
public:
    Expediente value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Expediente val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @class BST
 * @brief Arbol Binario de Busqueda que organiza los expedientes por su promedio.
 */
class BST {
private:
    TreeNode* root;

    void addRec(TreeNode*& node, const Expediente& val) {
        if (node == nullptr) {
            node = new TreeNode(val);
            return;
        }
        // En caso de que tengan el mismo promedio, desempata por matricula para no perder registros
        if (val.getPromedio() < node->value.getPromedio() ||
            (val.getPromedio() == node->value.getPromedio() && val.getMatricula() < node->value.getMatricula())) {
            addRec(node->left, val);
        } else {
            addRec(node->right, val);
        }
    }

    void inOrderRangeRec(TreeNode* node, float minProm, float maxProm, int& contador) const {
        if (node == nullptr) return;

        // Solo explora el subarbol izquierdo si puede haber promedios mayores o iguales a minProm
        if (node->value.getPromedio() >= minProm) {
            inOrderRangeRec(node->left, minProm, maxProm, contador);
        }

        // Si esta dentro del rango, lo va a imprimir en orden ascendente
        if (node->value.getPromedio() >= minProm && node->value.getPromedio() <= maxProm) {
            node->value.imprimir();
            contador++;
        }

        // Solo explora el subarbol derecho si puede haber promedios menores o iguales a maxProm
        if (node->value.getPromedio() <= maxProm) {
            inOrderRangeRec(node->right, minProm, maxProm, contador);
        }
    }
    
    void clearRec(TreeNode* node){
        if(node!=nullptr) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() {clear();}

    /**
     * @brief Inserta un expediente en el arbol en O(log n)
     */
    void add(const Expediente& val) {
        addRec(root, val);
    }

    /**
     * @brief Muestra los expedientes cuyo promedio se encuentre entre minProm y maxProm
     */
    void consultarRangoPromedio(float minProm, float maxProm) const {
        int encontrados = 0;
        std::cout << "\n--- Expedientes con un promedio entre " << minProm << " y " << maxProm << " ----\n";
        inOrderRangeRec(root, minProm, maxProm, encontrados);
        if (encontrados == 0) {
            std::cout << "No se encontraron expedientes en ese rango.\n";
        }
    }

    void clear(){
        clearRec(root);
        root = nullptr;
    }
};


#endif
