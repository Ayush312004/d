#include <iostream>
#include <cstdlib>
using namespace std;

class node {
public:
    int info;
    node *left;
    node *right;
} *root;

class BST {
public:
    node *root;

    BST() { root = NULL; }

    void insert(node *, node *);
    void display(node *, int);
    int min(node *);
    int height(node *);
    void mirror(node *);
    void preorder(node *);
    void inorder(node *);
    void postorder(node *);
    void search(node *, int);
};

int main() {
    int choice, num;
    BST bst;
    node *temp;

    while (1) {
        cout << "-----------------" << endl;
        cout << "Operations on BST" << endl;
        cout << "-----------------" << endl;
        cout << "1.Insert Element\n2.Display\n3.Min value find\n4.Height\n5.Mirror of node"
                "\n6.Preorder\n7.Inorder\n8.Postorder\n9.No. of nodes in longest path"
                "\n10.Search an element\n11.Quit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                temp = new node();
                cout << "Enter the number to be inserted : ";
                cin >> temp->info;
                bst.insert(bst.root, temp);
                break;
            case 2:
                cout << "Display BST:" << endl;
                bst.display(bst.root, 1);
                cout << endl;
                break;
            case 3:
                cout << "Min value of tree: " << bst.min(bst.root) << endl;
                break;
            case 4:
                cout << "Height of tree = " << bst.height(bst.root) << endl;
                break;
            case 5:
                cout << "Mirror\n";
                bst.mirror(bst.root);
                bst.display(bst.root, 1);
                break;
            case 6:
                cout << "\nDisplay preorder Binary tree = ";
                bst.preorder(bst.root);
                cout << endl;
                break;
            case 7:
                cout << "\nDisplay inorder Binary tree = ";
                bst.inorder(bst.root);
                cout << endl;
                break;
            case 8:
                cout << "\nDisplay postorder Binary tree = ";
                bst.postorder(bst.root);
                cout << endl;
                break;
            case 9:
                cout << "No. of nodes in longest path from root is " << bst.height(bst.root) << endl;
                break;
            case 10:
                int searchdata;
                cout << "Enter the element to be searched: ";
                cin >> searchdata;
                bst.search(bst.root, searchdata);
                cout << endl;
                break;
            case 11:
                exit(0);
            default:
                cout << "Wrong choice" << endl;
        }
    }
}

void BST::insert(node *tree, node *newnode) {
    if (root == NULL) {
        root = new node;
        root->info = newnode->info;
        root->left = NULL;
        root->right = NULL;
        cout << "Root Node is Added" << endl;
        return;
    }

    if (tree->info == newnode->info) {
        cout << "Element already in the tree" << endl;
        return;
    }

    if (tree->info > newnode->info) {
        if (tree->left != NULL) {
            insert(tree->left, newnode);
        } else {
            tree->left = newnode;
            tree->left->left = NULL;
            tree->left->right = NULL;
            cout << "Node Added To Left" << endl;
        }
    } else {
        if (tree->right != NULL) {
            insert(tree->right, newnode);
        } else {
            tree->right = newnode;
            tree->right->left = NULL;
            tree->right->right = NULL;
            cout << "Node Added To Right" << endl;
        }
    }
}

void BST::display(node *ptr, int level) {
    int i;
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout << "Root->:  ";
        else {
            for (i = 0; i < level; i++)
                cout << "       ";
        }
        cout << ptr->info;
        display(ptr->left, level + 1);
    }
}

int BST::min(node *root) {
    node *temp;
    if (root == NULL) {
        cout << "Tree is empty";
        return -1;
    } else {
        temp = root;
        while (temp->left != NULL)
            temp = temp->left;
        return temp->info;
    }
}

int BST::height(node *root) {
    int htleft, htright;
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;

    htleft = height(root->left);
    htright = height(root->right);

    return (htright >= htleft ? htright : htleft) + 1;
}

void BST::mirror(node *root) {
    node *temp;
    if (root != NULL) {
        temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirror(root->left);
        mirror(root->right);
    }
}

void BST::preorder(node *ptr) {
    if (ptr != NULL) {
        cout << ptr->info << "\t";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void BST::inorder(node *ptr) {
    if (ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->info << "\t";
        inorder(ptr->right);
    }
}

void BST::postorder(node *ptr) {
    if (ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->info << "\t";
    }
}

void BST::search(node *ptr, int searchdata) {
    if (ptr == NULL) {
        cout << "Element not found..." << endl;
        return;
    }

    if (ptr->info == searchdata) {
        cout << "Element Found..." << endl;
    } else if (ptr->info < searchdata) {
        search(ptr->right, searchdata);
    } else {
        search(ptr->left, searchdata);
    }
}
