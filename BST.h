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

    TreeNode(Expediente val);
};

TreeNode::TreeNode(Expediente val) : value(val), left(nullptr), right(nullptr) {}

/**
 * @class BST
 * @brief Arbol Binario de Busqueda que organiza los expedientes por su promedio.
 */
class BST {
private:
    TreeNode* root;

    /**
     * @brief Inserta recursivamente un expediente comparando promedio y desempatando por matricula.
     */
    void addRec(TreeNode*& node, const Expediente& val);

    /**
     * @brief Recorre el arbol In-Order podando subarboles fuera del rango [minAvg, maxAvg].
     */
    void inOrderRangeRec(TreeNode* node, float minAvg, float maxAvg, int& count) const;

    /**
     * @brief Libera recursivamente la memoria de los nodos en post-orden en O(n).
     */
    void clearRec(TreeNode* node);

public:
    BST();
    ~BST();

    /**
     * @brief Inserta un expediente en el arbol en O(log n)
     */
    void add(const Expediente& val);

    /**
     * @brief Muestra los expedientes cuyo promedio se encuentre entre minAvg y maxAvg
     */
    void queryAverageRange(float minAvg, float maxAvg) const;

    void clear();
};

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear();
}

void BST::addRec(TreeNode*& node, const Expediente& val) {
    if (node == nullptr) {
        node = new TreeNode(val);
        return;
    }
    // En caso de que tengan el mismo promedio, desempata por matricula para no perder registros
    if (val.getAverage() < node->value.getAverage() ||
        (val.getAverage() == node->value.getAverage() && val.getId() < node->value.getId())) {
        addRec(node->left, val);
    } else {
        addRec(node->right, val);
    }
}

void BST::inOrderRangeRec(TreeNode* node, float minAvg, float maxAvg, int& count) const {
    if (node == nullptr) return;

    // Solo explora el subarbol izquierdo si puede haber promedios mayores o iguales a minAvg
    if (node->value.getAverage() >= minAvg) {
        inOrderRangeRec(node->left, minAvg, maxAvg, count);
    }

    // Si esta dentro del rango, lo va a imprimir en orden ascendente
    if (node->value.getAverage() >= minAvg && node->value.getAverage() <= maxAvg) {
        node->value.print();
        count++;
    }

    // Solo explora el subarbol derecho si puede haber promedios menores o iguales a maxAvg
    if (node->value.getAverage() <= maxAvg) {
        inOrderRangeRec(node->right, minAvg, maxAvg, count);
    }
}

void BST::clearRec(TreeNode* node) {
    if (node != nullptr) {
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }
}

void BST::add(const Expediente& val) {
    addRec(root, val);
}

void BST::queryAverageRange(float minAvg, float maxAvg) const {
    int found = 0;
    std::cout << "\n--- Expedientes con un promedio entre " << minAvg << " y " << maxAvg << " ----\n";
    inOrderRangeRec(root, minAvg, maxAvg, found);
    if (found == 0) {
        std::cout << "No se encontraron expedientes en ese rango.\n";
    }
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
}

#endif
