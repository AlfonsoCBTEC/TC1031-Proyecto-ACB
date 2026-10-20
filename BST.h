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

    void clear(){
        clearRec(root);
        root = nullptr;
    }
};


#endif
