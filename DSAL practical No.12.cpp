#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class EMP_CLASS {
    typedef struct { char name[10]; int emp_id, salary; } Rec;
    typedef struct { int emp_id, position; } Ind_Rec;
    Rec Records;
    Ind_Rec Ind_Records;
public:
    EMP_CLASS() { strcpy(Records.name, ""); }
    void Create(), Display(), Update(), Delete(), Append(), Search();
};

void EMP_CLASS::Create() {
    fstream seqfile("EMP.DAT", ios::binary | ios::out);
    fstream indexfile("IND.DAT", ios::binary | ios::out);
    char ch = 'y'; int i = 0;
    while (ch == 'y') {
        cout << "\nEnter Name: "; cin >> Records.name;
        cout << "Enter Emp_ID: "; cin >> Records.emp_id;
        cout << "Enter Salary: "; cin >> Records.salary;
        seqfile.write((char*)&Records, sizeof(Records));
        Ind_Records = { Records.emp_id, i++ };
        indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
        cout << "Add more records? (y/n): "; cin >> ch;
    }
    seqfile.close(); indexfile.close();
}

void EMP_CLASS::Display() {
    fstream seqfile("EMP.DAT", ios::binary | ios::in);
    fstream indexfile("IND.DAT", ios::binary | ios::in);
    cout << "\nContents of file:\n";
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        seqfile.seekg(Ind_Records.position * sizeof(Records));
        seqfile.read((char*)&Records, sizeof(Records));
        if (Records.emp_id != -1)
            cout << "Name: " << Records.name << "\nEmp_ID: " << Records.emp_id << "\nSalary: " << Records.salary << "\n";
    }
    seqfile.close(); indexfile.close();
}

void EMP_CLASS::Update() {
    int id, pos = -1; char name[10]; int salary;
    cout << "\nEnter Emp_ID to update: "; cin >> id;
    fstream seqfile("EMP.DAT", ios::binary | ios::in | ios::out);
    fstream indexfile("IND.DAT", ios::binary | ios::in);
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
        if (Ind_Records.emp_id == id) { pos = Ind_Records.position; break; }
    if (pos == -1) { cout << "Record not found."; return; }
    cout << "Enter New Name: "; cin >> name;
    cout << "Enter New Salary: "; cin >> salary;
    seqfile.seekp(pos * sizeof(Records));
    strcpy(Records.name, name);
    Records.emp_id = id;
    Records.salary = salary;
    seqfile.write((char*)&Records, sizeof(Records));
    cout << "Record updated.";
    seqfile.close(); indexfile.close();
}

void EMP_CLASS::Delete() {
    int id, pos = -1;
    cout << "\nEnter Emp_ID to delete: "; cin >> id;
    fstream seqfile("EMP.DAT", ios::binary | ios::in | ios::out);
    fstream indexfile("IND.DAT", ios::binary | ios::in | ios::out);
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
        if (Ind_Records.emp_id == id) { pos = Ind_Records.position; break; }
    if (pos == -1) { cout << "Record not found."; return; }
    seqfile.seekp(pos * sizeof(Records));
    strcpy(Records.name, "");
    Records.emp_id = Records.salary = -1;
    seqfile.write((char*)&Records, sizeof(Records));
    indexfile.seekp(pos * sizeof(Ind_Records));
    Ind_Records.emp_id = -1;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
    cout << "Record deleted.";
    seqfile.close(); indexfile.close();
}

void EMP_CLASS::Append() {
    fstream indexfile("IND.DAT", ios::binary | ios::in);
    indexfile.seekg(0, ios::end);
    int pos = indexfile.tellg() / sizeof(Ind_Records);
    indexfile.close();
    indexfile.open("IND.DAT", ios::binary | ios::app);
    fstream seqfile("EMP.DAT", ios::binary | ios::app);
    cout << "\nEnter Name: "; cin >> Records.name;
    cout << "Enter Emp_ID: "; cin >> Records.emp_id;
    cout << "Enter Salary: "; cin >> Records.salary;
    seqfile.write((char*)&Records, sizeof(Records));
    Ind_Records = { Records.emp_id, pos };
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
    cout << "Record appended.";
    seqfile.close(); indexfile.close();
}

void EMP_CLASS::Search() {
    int id, pos = -1;
    cout << "\nEnter Emp_ID to search: "; cin >> id;
    fstream indexfile("IND.DAT", ios::binary | ios::in);
    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records)))
        if (Ind_Records.emp_id == id) { pos = Ind_Records.position; break; }
    if (pos == -1) { cout << "Record not found."; return; }
    fstream seqfile("EMP.DAT", ios::binary | ios::in);
    seqfile.seekg(pos * sizeof(Records));
    seqfile.read((char*)&Records, sizeof(Records));
    if (Records.emp_id == -1) { cout << "Record not found."; return; }
    cout << "Name: " << Records.name << "\nEmp_ID: " << Records.emp_id << "\nSalary: " << Records.salary;
    seqfile.close(); indexfile.close();
}

int main() {
    EMP_CLASS List;
    char ans = 'y';
    int choice;
    do {
        cout << "\n--- Main Menu ---\n1.Create\n2.Display\n3.Update\n4.Delete\n5.Append\n6.Search\n7.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: List.Create(); break;
            case 2: List.Display(); break;
            case 3: List.Update(); break;
            case 4: List.Delete(); break;
            case 5: List.Append(); break;
            case 6: List.Search(); break;
            case 7: exit(0);
        }
        cout << "\nBack to menu? (y/n): "; cin >> ans;
    } while (ans == 'y');
}
