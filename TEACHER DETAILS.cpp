struct Teacher {
    string name;
    string department; 
     string room;
    string subject;
};

class TeacherDetails {
private:
    Teacher teachers[4] = {
        {"Dr. Anita Sharma", "Computer Science", "CS-101", "Data Structures"},
        {"Prof. Rakesh Verma", "Computer Science", "CS-105", "Operating Systems"},
        {"Dr. Meera Joshi", "Mathematics", "M-204", "Discrete Mathematics"},
        {"Prof. Sunil Negi", "Electronics", "EC-110", "Digital Electronics"}
    };
    int count = 4;

public:
    void showTeachers() {
        cout << "\n--- TEACHER DETAILS (SAMPLE DATA) ---\n";
        for (int i = 0; i < count; i++) {
            cout << "\nName: " << teachers[i].name
                 << "\nDepartment: " << teachers[i].department
                 << "\nRoom: " << teachers[i].room
                 << "\nSubject: " << teachers[i].subject << "\n";
        }
    }

    void searchTeacher() {
        string name;
        cout << "Enter teacher name: ";
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < count; i++) {
    if (teachers[i].name.find(name) != string::npos) {
                cout << "\nName: " << teachers[i].name
                     << "\nDepartment: " << teachers[i].department
                     << "\nRoom: " << teachers[i].room
                     << "\nSubject: " << teachers[i].subject << "\n";
                found = true;
            }
        }

        if (!found) cout << "Teacher not found.\n";
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- TEACHER DETAILS ---\n";
            cout << "1. View all teachers\n";
            cout << "2. Search teacher by name\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                clearInput();
                cout << "Please enter a number.\n";
                continue;
            }
            clearInput();

            if (choice == 1) showTeachers();
            else if (choice == 2) searchTeacher();
            else if (choice != 0) cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};
