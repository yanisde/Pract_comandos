#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) throw std::runtime_error("Element not found");
        if (e == n->elem) return n;
        if (e < n->elem) return search(n->left, e);
        return search(n->right, e);
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) return new BSNode<T>(e);
        if (e == n->elem) throw std::runtime_error("Element already exists");
        if (e < n->elem) n->left = insert(n->left, e);
        else n->right = insert(n->right, e);
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n == nullptr) return;
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) throw std::runtime_error("Empty tree");
        if (n->right == nullptr) return n->elem;
        return max(n->right);
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n == nullptr) return nullptr;
        if (n->right == nullptr) {
            BSNode<T>* l = n->left;
            delete n;
            return l;
        }
        n->right = remove_max(n->right);
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) throw std::runtime_error("Element not found");
        if (e < n->elem) {
            n->left = remove(n->left, e);
            return n;
        }
        if (e > n->elem) {
            n->right = remove(n->right, e);
            return n;
        }

        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            return nullptr;
        }
        if (n->left == nullptr) {
            BSNode<T>* r = n->right;
            delete n;
            return r;
        }
        if (n->right == nullptr) {
            BSNode<T>* l = n->left;
            delete n;
            return l;
        }

        T repl = max(n->left);
        n->elem = repl;
        n->left = remove_max(n->left);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n == nullptr) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    int size() const {
        return nelem;
    }

    T search(T e) const {
        return search(root, e)->elem;
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    void remove(T e) {
        root = remove(root, e);
        nelem--;
    }

    ~BSTree() {
        delete_cascade(root);
        root = nullptr;
        nelem = 0;
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

