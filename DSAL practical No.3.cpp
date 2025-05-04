#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

struct node {
    char label[10];
    int ch_count;
    struct node *child[10];
} *root;

class GT {
public:
    void create_tree();
    void display(node *r1);
    GT() {
        root = NULL;
    }
};

void GT::create_tree() {
    int tchapters, i, j, k;
    root = new node;
    cout << "Enter name of book: ";
    cin >> root->label;
    cout << "Enter number of chapters in book: ";
    cin >> tchapters;
    root->ch_count = tchapters;

    for (i = 0; i < tchapters; i++) {
        root->child[i] = new node;
        cout << "Enter Chapter name: ";
        cin >> root->child[i]->label;
        cout << "Enter number of sections in Chapter " << root->child[i]->label << ": ";
        cin >> root->child[i]->ch_count;

        for (j = 0; j < root->child[i]->ch_count; j++) {
            root->child[i]->child[j] = new node;
            cout << "Enter Section " << j + 1 << " name: ";
            cin >> root->child[i]->child[j]->label;
            cout << "Enter number of Subsections in Section " << root->child[i]->child[j]->label << ": ";
            cin >> root->child[i]->child[j]->ch_count;

            for (k = 0; k < root->child[i]->child[j]->ch_count; k++) {
                root->child[i]->child[j]->child[k] = new node;
                cout << "Enter Subsection " << k + 1 << " name: ";
                cin >> root->child[i]->child[j]->child[k]->label;
            }
        }
    }
}

void GT::display(node *r1) {
    int i, j, k, tchapters;
    if (r1 != NULL) {
        cout << "\n-----Book Hierarchy---";
        cout << "\nBook title: " << r1->label;
        tchapters = r1->ch_count;

        for (i = 0; i < tchapters; i++) {
            cout << "\n  Chapter " << i + 1 << ": " << r1->child[i]->label;
            cout << "\n  Sections:";
            for (j = 0; j < r1->child[i]->ch_count; j++) {
                cout << "\n    Section " << j + 1 << ": " << r1->child[i]->child[j]->label;
                cout << "\n    Subsections:";
                for (k = 0; k < r1->child[i]->child[j]->ch_count; k++) {
                    cout << "\n      Subsection " << k + 1 << ": " << r1->child[i]->child[j]->child[k]->label;
                }
            }
        }
    }
}

int main() {
    int choice;
    GT gt;
    while (1) {
        cout << "\n\nBook Tree Creation\n1.Create\n2.Display\n3.Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: gt.create_tree(); break;
            case 2: gt.display(root); break;
            case 3: exit(0);
            default: cout << "Wrong choice" << endl;
            }
        
    }
}
