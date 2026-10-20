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

    void clear(){
        clearRec(root);
        root = nullptr;
    }
};


#endif
