#include<bits/stdc++.h>
using namespace std;

// 11

struct Student {
    int roll_number;
    string name;
    string division;
    string address;
};

void add_student(Student student) {
    fstream file;
    file.open("students.txt", ios::out | ios::app);

    file << student.roll_number << " " << student.name << " " << student.division << " " << student.address << endl;

    file.close();
}

void delete_student(int roll_number) {
    fstream file;
    file.open("students.txt", ios::in);
    
    fstream new_file;
    new_file.open("new_students.txt", ios::out);

    Student student;
    while (file >> student.roll_number >> student.name >> student.division >> student.address) {
        if (student.roll_number != roll_number) {
            new_file << student.roll_number << " " << student.name << " " << student.division << " " << student.address << endl;
        }
    }

    new_file.close();

    file.close();

    remove("students.txt");
    rename("new_students.txt", "students.txt");
}

void display_student(int roll_number) {
    fstream file;
    file.open("students.txt", ios::in);

    Student student;

    while (file >> student.roll_number >> student.name >> student.division >> student.address) {
        if (student.roll_number == roll_number) {
            cout << "Roll number: " << student.roll_number << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            file.close();
            return;
        }
    }

    cout << "No student found." << endl;
    file.close();
}

int main() {
    
    int choice;

    while (true) {
        cout << "************* MENU *************\n";
        cout << "1. Add student" << endl;
        cout << "2. Delete student" << endl;
        cout << "3. Display student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter student details: " << endl;

                int roll_number;
                string name, division, address;

                cout << "Enter Roll number: ";
                cin >> roll_number;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Division: ";
                cin >> division;
                cout << "Enter Address: ";
                cin >> address;

                Student student = {roll_number, name, division, address};

                add_student(student);
                break;
            }
            case 2: {
                cout << "Enter student roll number to delete: " << endl;

                int roll_number;
                cout << "Enter Roll number to delete: ";
                cin >> roll_number;

                delete_student(roll_number);
                break;
            }
            case 3: {
                int roll_number;
                cout << "Enter student roll number to display: " << endl;
                cin >> roll_number;

                display_student(roll_number);
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                cout << "Invalid choice!" << endl;
                break;
            }
        }
        cout << endl << endl;
    }
}
