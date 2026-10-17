
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Teacher {
    string name;
    string department;
    string room;
    string subject;
};

class TeacherDetails {
private:
    Teacher teachers[7] = {
        {"Dr. Deepak Singh Rana", "CSE", "CS-329", "C Language"},
        {"Prof. Ajay Shukla", "CSE", "CS-05", "Data Structure"},
        {"Dr. V P Dubey", "ECE", "M-204", "Logic Design"},
        {"Prof. Sunil Negi", "ECE", "EC-110", "Digital Electronics"},
        {"Ms. Sonali Gupta","CSE","CS-101","OOPs in Cpp"},
        {"Dr. Mohit Payal","ECE","M-204","Logic Lab"},
        {"Mr. Ajay Kumar Singh","Civil","C-103","Civil Lab"},
    };

    int count = 7;

    void printTeacher(const Teacher &t) {
        cout << "\nName: " << t.name
             << "\nDepartment: " << t.department
             << "\nRoom: " << t.room
             << "\nSubject: " << t.subject << "\n";
        cout << "------------------------------\n";
    }

public:
    // Display all teachers
    void showTeachers() {
        cout << "\n--- ALL TEACHERS ---\n";

        for (int i = 0; i < count; i++) {
            printTeacher(teachers[i]);
        }
    }

    // Search teacher by name
    void searchTeacher() {
        string name;

        cout << "\nEnter teacher name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Please enter a teacher name.\n";
            return;
        }

        bool found = false;

        for (int i = 0; i < count; i++) {
            if (teachers[i].name.find(name) != string::npos) {
                printTeacher(teachers[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "Teacher not found.\n";
        }
    }

    // Search teachers by department
    void searchDepartment() {
        string department;

        cout << "\nEnter department name: ";
        getline(cin, department);

        if (department.empty()) {
            cout << "Please enter a department name.\n";
            return;
        }

        bool found = false;

        for (int i = 0; i < count; i++) {
            if (teachers[i].department.find(department)
                != string::npos) {
                printTeacher(teachers[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "No teacher found in this department.\n";
        }
    }

    // Display menu
    void menu() {
        int choice;

        do {
            cout << "\n========== TEACHER DETAILS ==========\n";
            cout << "1. View all teachers\n";
            cout << "2. Search teacher by name\n";
            cout << "3. Search teachers by department\n";
            cout << "0. Exit\n";
            cout << "=====================================\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    showTeachers();
                    break;

                case 2:
                    searchTeacher();
                    break;

                case 3:
                    searchDepartment();
                    break;

                case 0:
                    cout << "Exiting Teacher Details System.\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    TeacherDetails td;
    td.menu();

    return 0;
}
