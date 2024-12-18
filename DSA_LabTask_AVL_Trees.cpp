#include <iostream>
using namespace std;


struct Node {
    int key;
    int height;
    int x, y;
    Node* left;
    Node* right;

    Node(int val) : key(val), height(1), left(nullptr), right(nullptr), x(0), y(0) {}
};


int height(Node* n) {
    return n ? n->height : 0;
}


int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}


void updateHeight(Node* n) {
    if (n) n->height = 1 + max(height(n->left), height(n->right));
}


Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}


Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}
Node* rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}


Node* rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}


Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rotateRight(node);
    if (balance < -1 && key > node->right->key) return rotateLeft(node);
    if (balance > 1 && key > node->left->key) return rotateLeftRight(node);
    if (balance < -1 && key < node->right->key) return rotateRightLeft(node);

    return node;
}




int main() {
    Node* root = nullptr;

    root = insert(root, 50);
    cout << "Height of root after inserting 50: " << root->height << endl;

    root = insert(root, 30);
    cout << "Height of root after inserting 30: " << root->height << endl;

    root = insert(root, 70);
    cout << "Height of root after inserting 70: " << root->height << endl;

    root = insert(root, 20);
    cout << "Height of root after inserting 20: " << root->height << endl;

    root = insert(root, 40);
    cout << "Height of root after inserting 40: " << root->height << endl;

    root = insert(root, 60);
    cout << "Height of root after inserting 60: " << root->height << endl;

    root = insert(root, 80);
    cout << "Height of root after inserting 80: " << root->height << endl;



    return 0;
}
