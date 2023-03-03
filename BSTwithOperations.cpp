#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int findMin(Node* root) {
    if (root == NULL) {
        return -1;
    }

    while (root->left != NULL) {
        root = root->left;
    }

    return root->data;
}

int findMax(Node* root) {
    if (root == NULL) {
        return -1;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root->data;
}

void executeOperation(Node* root, string operation) {
    if (operation.substr(0, 7) == "INSERT_") {
        int value = stoi(operation.substr(7));
        root = insert(root, value);
    }
    else if (operation.substr(0, 7) == "DELETE_") {
        int value = stoi(operation.substr(7));
        root = deleteNode(root, value);
    }
    else if (operation == "MIN") {
        int minValue = findMin(root);
        if (minValue == -1) {
            cout << "Tree is empty" << endl;
        }
        else {
            cout << "Minimum value is: " << minValue << endl;
        }
    }
    else if (operation == "MAX") {
        int maxValue = findMax(root);
        if (maxValue == -1) {
            cout << "Tree is empty" << endl;
        }
        else {
            cout << "Maximum value is: " << maxValue << endl;
        }
    }
    else {
        cout << "Invalid operation" << endl;}

int main() {
    Node* root = NULL;
    string input;

    while (true) {
        cout << "Enter operation: ";
        cin >> input;

        if (input == "QUIT") {
            break;
        }

        executeOperation(root, input);
    }

    return 0;
}
