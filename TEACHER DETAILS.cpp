#include <iostream>
#include <string>
#include <limits>
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
    Teacher teachers[100] = {
        {"Dr. Deepak Singh Rana", "CSE", "CS-329","C Language", "9719924551"},
        {"Prof. Ajay Shukla", "CSE", "CS-05","Data Structure", "8541682295"},
        {"Dr. V P Dubey", "ECE", "M-204","Logic Design", "6398388206"},
        {"Prof. Sunil Negi", "ECE", "EC-110","Digital Electronics", "9862446362"},
        {"Ms. Sonali Gupta", "CSE", "CS-101","OOPs in Cpp", "8923400421"},
        {"Dr. Mohit Payal", "ECE", "M-204","Logic Lab", "8958138501"},
        {"Mr. Ajay Kumar Singh", "CIVIL", "C-103","Civil Lab", "9082373578"}
    };
    int count = 7;
    // Password for adding a new teacher
    string correctPassword = "gehu";
    
    void printTeacher(const Teacher &t) {
        cout << "\nName: " << t.name
             << "\nDepartment: " << t.department
             << "\nRoom: " << t.room
             << "\nSubject: " << t.subject
             << "\nMobile: " << t.mobile << "\n";
        cout << "--------------------------\n";
    }
    bool checkPassword(string entered_Password) {
        PasswordStack st;
        if (entered_Password.length() != correctPassword.length()) {
            return false;
        }
        // Push each character into the stack
        for (int i = 0; i < entered_Password.length(); i++) {
            st.push(entered_Password[i]);
        }

        // Pop characters in reverse order and compare
        for (int i = correctPassword.length() - 1; i >= 0; i--) {
            if (st.isEmpty() || st.pop() != correctPassword[i]) {
                return false;
            }
        }
        return st.isEmpty();
    }
public:
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
        // Convert input to uppercase
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
    // Add a teacher only after correct password
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

        // Store department in uppercase
        for (int i = 0; i < t.department.length(); i++) {
            if (t.department[i] >= 'a' &&
                t.department[i] <= 'z') {
                t.department[i] = t.department[i] - 32;
            }
        }
        
        cout << "Enter room: ";
        getline(cin, t.room);
        cout << "Enter subject: ";
        getline(cin, t.subject);
        cout << "Enter mobile number: ";
        getline(cin, t.mobile);

        if (t.name.empty() || t.department.empty() ||t.room.empty() || t.subject.empty() || t.mobile.empty()) {
            cout << "Details cannot be empty. Teacher not added.\n";
            return;
        }
        teachers[count] = t;
        count++;
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
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Enter a valid number.\n";
                continue;
            }

            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
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
