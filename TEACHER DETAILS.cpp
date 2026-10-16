// ---------------- TEACHER DETAILS (Array + Searching) ----------------
struct Teacher {
    string name;
    string department;
    string room;
    string subject;
};

class TeacherDetails {
private:
    Teacher teachers[4] = {
        {"Dr. Deepak Singh Rana", "Computer Science", "CS-329", "c language"},
        {"Prof. Ajay Shukla", "Computer Science", "CS-05", "Data structure"},
        {"Dr. v p Dubey ","Electronics Engineering", "M-204", "Logic Design"},
        {"Prof. Sunil Negi", "Electronics", "EC-110", "Digital Electronics"}
    };
    int count = 4;

    void printTeacher(const Teacher &t) {
        cout << "\nName: " << t.name
             << "\nDepartment: " << t.department
             << "\nRoom: " << t.room
             << "\nSubject: " << t.subject << "\n";
    }

public:
    void showTeachers() {
        cout << "\n--- TEACHER DETAILS (SAMPLE DATA) ---\n";
        for (int i = 0; i < count; i++) {
            printTeacher(teachers[i]);
        }
    }

    // LINEAR SEARCH: check every element of the array one by one
    void searchTeacher() {
        string name;
        cout << "Enter teacher name: ";
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < count; i++) {
            if (teachers[i].name.find(name) != string::npos) {
                printTeacher(teachers[i]);
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

            if (!readChoice("Enter choice: ", choice))
            continue;

            if (choice == 1)
            showTeachers();
            else if (choice == 2)
            searchTeacher();
            else if (choice != 0)
            cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};
