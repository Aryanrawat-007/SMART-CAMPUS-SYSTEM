
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

struct Teacher {
    string name;
    string department;
    string room;
    string subject;
    string mobile;
};

class PasswordStack {
private:
    char items[100];
    int top;

public:
    PasswordStack() {
        top = -1;
    }

    void push(char ch) {
        if (top < 99) {
            items[++top] = ch;
        }
    }

    char pop() {
        if (top == -1) {
            return '\0';
        }
        return items[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

class TeacherDetails {
private:
    Teacher teachers[100];
    int count;
    string correctPassword = "gehu";

    // Save all teacher records in a file
    void saveToFile() {
        ofstream file("teachers.txt");

        if (!file) {
            cout << "Error opening file for saving.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            file << teachers[i].name << "|"
                 << teachers[i].department << "|"
                 << teachers[i].room << "|"
                 << teachers[i].subject << "|"
                 << teachers[i].mobile << "\n";
        }
        file.close();
        cout << "Teacher records saved to file.\n";
    }

    // Load teacher records from a file
    void loadFromFile() {
        ifstream file("teachers.txt");
        count = 0;

        if (!file) {
            // File does not exist, so create initial records
            teachers[0] = {"Dr. Deepak Singh Rana", "CSE",
                           "CS-329", "C Language", "9719924551"};
            teachers[1] = {"Prof. Ajay Shukla", "CSE",
                           "CS-05", "Data Structure", "8541682295"};
            teachers[2] = {"Dr. V P Dubey", "ECE",
                           "M-204", "Logic Design", "6398388206"};
            teachers[3] = {"Prof. Sunil Negi", "ECE",
                           "EC-110", "Digital Electronics", "9862446362"};
            teachers[4] = {"Ms. Sonali Gupta", "CSE",
                           "CS-101", "OOPs in Cpp", "8923400421"};
            teachers[5] = {"Dr. Mohit Payal", "ECE",
                           "M-204", "Logic Lab", "8958138501"};
            teachers[6] = {"Mr. Ajay Kumar Singh", "CIVIL",
                           "C-103", "Civil Lab", "9082373578"};
            count = 7;
            saveToFile();
            return;
        }
        string line;
        while (count < 100 && getline(file, line)) {
            Teacher t;
            int pos;
            pos = line.find('|');
            if (pos == string::npos) continue;
            t.name = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.department = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.room = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.subject = line.substr(0, pos);
            t.mobile = line.substr(pos + 1);

            teachers[count] = t;
            count++;
        }
        file.close();

        // Restore sample records if the file is empty
        if (count == 0) {
            teachers[0] = {"Dr. Deepak Singh Rana", "CSE",
                           "CS-329", "C Language", "9719924551"};
            teachers[1] = {"Prof. Ajay Shukla", "CSE",
                           "CS-05", "Data Structure", "8541682295"};
            teachers[2] = {"Dr. V P Dubey", "ECE",
                           "M-204", "Logic Design", "6398388206"};
            teachers[3] = {"Prof. Sunil Negi", "ECE",
                           "EC-110", "Digital Electronics", "9862446362"};
            teachers[4] = {"Ms. Sonali Gupta", "CSE",
                           "CS-101", "OOPs in Cpp", "8923400421"};
            teachers[5] = {"Dr. Mohit Payal", "ECE",
                           "M-204", "Logic Lab", "8958138501"};
            teachers[6] = {"Mr. Ajay Kumar Singh", "CIVIL",
                           "C-103", "Civil Lab", "9082373578"};
            count = 7;
            saveToFile();
        }
    }

    void printTeacher(const Teacher &t) {
        cout << "\nName: " << t.name
             << "\nDepartment: " << t.department
             << "\nRoom: " << t.room
             << "\nSubject: " << t.subject
             << "\nMobile: " << t.mobile << "\n";
        cout << "--------------------------\n";
    }

    bool checkPassword(string enteredPassword) {
        PasswordStack st;

        if (enteredPassword.length() != correctPassword.length()) {
            return false;
        }
        for (int i = 0; i < enteredPassword.length(); i++) {
            st.push(enteredPassword[i]);
        }
        for (int i = correctPassword.length() - 1; i >= 0; i--) {
            if (st.isEmpty() || st.pop() != correctPassword[i]) {
                return false;
            }
        }
        return st.isEmpty();
    }

public:
    TeacherDetails() {
        count = 0;
        loadFromFile();
    }
    void showTeachers() {
        cout << "\n--- ALL TEACHERS ---\n";

        for (int i = 0; i < count; i++) {
            printTeacher(teachers[i]);
        }
    }

    void searchTeacher() {
        string name;
        cout << "Enter teacher name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Please enter a name.\n";
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

    void searchDepartment() {
        string department;

        cout << "Enter department: ";
        getline(cin, department);
        if (department.empty()) {
            cout << "Please enter a department.\n";
            return;
        }
        for (int i = 0; i < department.length(); i++) {
            if (department[i] >= 'a' && department[i] <= 'z') {
                department[i] = department[i] - 32;
            }
        }
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (teachers[i].department.find(department) != string::npos) {
                printTeacher(teachers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "No teacher found in this department.\n";
        }
    }

    void addTeacher() {
        string password;

        cout << "Enter password: ";
        getline(cin, password);
        if (!checkPassword(password)) {
            cout << "Wrong password! Access denied.\n";
            return;
        }
        cout << "Correct password! Access granted.\n";
        if (count >= 100) {
            cout << "Teacher list is full.\n";
            return;
        }
        Teacher t;
        cout << "Enter teacher name: ";
        getline(cin, t.name);
        cout << "Enter department: ";
        getline(cin, t.department);
        for (int i = 0; i < t.department.length(); i++) {
            if (t.department[i] >= 'a' && t.department[i] <= 'z') {
                t.department[i] = t.department[i] - 32;
            }
        }
        cout << "Enter room: ";
        getline(cin, t.room);
        cout << "Enter subject: ";
        getline(cin, t.subject);
        cout << "Enter mobile number: ";
        getline(cin, t.mobile);
        if (t.name.empty() || t.department.empty() || t.room.empty() || t.subject.empty() || t.mobile.empty()) {
            cout << "Details cannot be empty. Teacher not added.\n";
            return;
        }
        teachers[count] = t;
        count++;
        saveToFile();
        cout << "New teacher added successfully!\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== TEACHER DETAILS =====\n";
            cout << "1. View all teachers\n";
            cout << "2. Search by name\n";
            cout << "3. Search by department\n";
            cout << "4. Add new teacher\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a valid number.\n";
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
                case 4:
                    addTeacher();
                    break;
                case 0:
                    cout << "Program ended.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }
};

int main() {
    TeacherDetails td;
    td.menu();
    return 0;
}
