#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
        this->lthread = false;
        this->rthread = false;
    }
};

void getInorder(Node* root, vector<Node*>& inorder) {
    if (root == NULL)
        return;

    getInorder(root->left, inorder);
    inorder.push_back(root);
    getInorder(root->right, inorder);
}

class BST {
    Node* root;
    bool isThreaded;

public:
    BST() {
        root = NULL;
        isThreaded = false;
    }

    void insert(int d) {
        root = insertUtil(root, d);
    }

    bool search(int d) {
        return searchUtil(root, d);
    }

    bool searchUtil(Node* node, int d) {
        if (node == NULL)
            return false;

        if (node->data == d)
            return true;

        if (d < node->data) {
            return searchUtil(node->left, d);
        } else {
            return searchUtil(node->right, d);
        }
    }

    Node* insertUtil(Node* node, int d) {
        if (node == NULL) {
            node = new Node(d);
            return node;
        }

        if (d > node->data) {
            node->right = insertUtil(node->right, d);
        } else {
            node->left = insertUtil(node->left, d);
        }

        return node;
    }

    void makeThreaded() {
        vector<Node*> inorder;
        getInorder(root, inorder);

        for (int i = 0; i < inorder.size(); i++) {
            Node* curr = inorder[i];

            if (!curr->left && i - 1 >= 0) {
                curr->left = inorder[i - 1];
                curr->lthread = true;
            }

            if (!curr->right && i + 1 < inorder.size()) {
                curr->right = inorder[i + 1];
                curr->rthread = true;
            }
        }

        isThreaded = true;
    }

    void threadedInTraversal() {
        cout << "Inorder Traversal: ";

        if (root == NULL) {
            cout << "Empty BST" << endl;
        }

        if (!isThreaded) {
            makeThreaded();
        }

        Node* current = root;
        while (current->left != NULL) {
            current = current->left;
        }

        while (current != NULL) {
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter the number of nodes to insert in BST: ";
    cin >> n;

    BST tree;

    int val;
    cout << "Enter the numbers to insert: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        tree.insert(val);
    }

    tree.makeThreaded();
    tree.threadedInTraversal();

    return 0;
}
