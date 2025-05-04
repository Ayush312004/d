#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct node {
    char name[20];
    node* next;   
    node* down;   
    int flag;     
};

class Gll {
    char ch[20];
    int n, i;
    node *head = NULL, *temp = NULL, *t1 = NULL, *t2 = NULL;

public:
    node* create();      
    void insertb();      
    void insertc();      
    void inserts();      
    void insertss();     
    void displayb();     
};

node* Gll::create() {
    node* p = new node;
    p->next = NULL;
    p->down = NULL;
    p->flag = 0;

    cout << "\nEnter the name: ";
    cin >> p->name;

    return p;
}

void Gll::insertb() {
    if (head == NULL) {
        t1 = create();
        head = t1;
    } else {
        cout << "\nBook already exists.";
    }
}

void Gll::insertc() {
    if (head == NULL) {
        cout << "\nNo book available.";
    } else {
        cout << "\nHow many chapters do you want to insert? ";
        cin >> n;

        for (i = 0; i < n; i++) {
            t1 = create();
            if (head->flag == 0) {
                head->down = t1;
                head->flag = 1;
            } else {
                temp = head->down;
                while (temp->next != NULL) temp = temp->next;
                temp->next = t1;
            }
        }
    }
}

void Gll::inserts() {
    if (head == NULL) {
        cout << "\nNo book available.";
        return;
    }

    cout << "\nEnter the name of chapter to insert section: ";
    cin >> ch;

    if (head->flag == 0) {
        cout << "\nNo chapters in book.";
        return;
    }

    temp = head->down;
    while (temp != NULL) {
        if (!strcmp(ch, temp->name)) {
            cout << "\nHow many sections do you want to insert? ";
            cin >> n;

            for (i = 0; i < n; i++) {
                t1 = create();
                if (temp->flag == 0) {
                    temp->down = t1;
                    temp->flag = 1;
                    t2 = temp->down;
                } else {
                    while (t2->next != NULL) t2 = t2->next;
                    t2->next = t1;
                }
            }
            return;
        }
        temp = temp->next;
    }

    cout << "\nChapter not found.";
}

void Gll::insertss() {
    if (head == NULL) {
        cout << "\nNo book available.";
        return;
    }

    cout << "\nEnter the name of chapter to insert subsection: ";
    cin >> ch;

    if (head->flag == 0) {
        cout << "\nNo chapters in book.";
        return;
    }

    temp = head->down;
    while (temp != NULL) {
        if (!strcmp(ch, temp->name)) {
            cout << "\nEnter name of section to insert subsection: ";
            cin >> ch;

            if (temp->flag == 0) {
                cout << "\nNo sections in chapter.";
                return;
            }

            temp = temp->down;
            while (temp != NULL) {
                if (!strcmp(ch, temp->name)) {
                    cout << "\nHow many subsections do you want to insert? ";
                    cin >> n;

                    for (i = 0; i < n; i++) {
                        t1 = create();
                        if (temp->flag == 0) {
                            temp->down = t1;
                            temp->flag = 1;
                            t2 = temp->down;
                        } else {
                            while (t2->next != NULL) t2 = t2->next;
                            t2->next = t1;
                        }
                    }
                    return;
                }
                temp = temp->next;
            }

            cout << "\nSection not found.";
            return;
        }
        temp = temp->next;
    }

    cout << "\nChapter not found.";
}

void Gll::displayb() {
    if (head == NULL) {
        cout << "\nBook not found.";
        return;
    }

    temp = head;
    cout << "\nNAME OF BOOK: " << temp->name;

    if (temp->flag == 1) {
        temp = temp->down;

        while (temp != NULL) {
            cout << "\n\tCHAPTER: " << temp->name;
            t1 = temp;

            if (t1->flag == 1) {
                t1 = t1->down;
                while (t1 != NULL) {
                    cout << "\n\t\tSECTION: " << t1->name;
                    t2 = t1;

                    if (t2->flag == 1) {
                        t2 = t2->down;
                        while (t2 != NULL) {
                            cout << "\n\t\t\tSUBSECTION: " << t2->name;
                            t2 = t2->next;
                        }
                    }

                    t1 = t1->next;
                }
            }

            temp = temp->next;
        }
    }
}

int main() {
    Gll g;
    int x;

    while (1) {
        cout << "\n\nMenu:";
        cout << "\n1. Insert Book";
        cout << "\n2. Insert Chapter";
        cout << "\n3. Insert Section";
        cout << "\n4. Insert Subsection";
        cout << "\n5. Display Book";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> x;

        switch (x) {
            case 1: g.insertb(); break;
            case 2: g.insertc(); break;
            case 3: g.inserts(); break;
            case 4: g.insertss(); break;
            case 5: g.displayb(); break;
            case 6: exit(0);
            default: cout << "\nInvalid choice!";
        }
    }

    return 0;
}