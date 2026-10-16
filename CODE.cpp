/*
    SMART CAMPUS - SIMPLE C++ PROJECT
    Modules:
    1. Lost and Found
    2. Teacher Details
    3. Notice System
    4. Club Information

    Concepts: classes, structures, arrays, loops, and searching.
    All information is sample data and is stored only while the program runs.
*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------------- LOST AND FOUND ----------------
struct LostItem {
    string itemName;
    string place;
    string status;   // LOST or FOUND
};

class LostAndFound {
private:
    LostItem items[50];
    int count = 0;

public:
    void reportItem() {
        if (count >= 50) {
            cout << "The list is full.\n";
            return;
        }

        cout << "Enter item name: ";
        getline(cin, items[count].itemName);

        cout << "Enter place where it was lost/found: ";
        getline(cin, items[count].place);

        cout << "Enter status (LOST or FOUND): ";
        getline(cin, items[count].status);

        count++;
        cout << "Item report added successfully!\n";
    }

    void showItems() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        cout << "\n--- LOST AND FOUND RECORDS ---\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". Item: " << items[i].itemName
                 << " | Place: " << items[i].place
                 << " | Status: " << items[i].status << '\n';
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- LOST AND FOUND ---\n";
            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                clearInput();
                cout << "Please enter a number.\n";
                continue;
            }
            clearInput();

            if (choice == 1) reportItem();
            else if (choice == 2) showItems();
            else if (choice != 0) cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};

// ---------------- TEACHER DETAILS ----------------
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

// ---------------- NOTICE SYSTEM ----------------
struct Notice {
    string title;
    string message;
};

class NoticeSystem {
private:
    Notice notices[4] = {
        {"Exam Notice", "Check the official portal for examination dates."},
        {"Library Notice", "Please return borrowed books on time."},
        {"Event Notice", "College cultural event registrations are open."},
        {"Holiday Notice", "Check official college announcements for holidays."}
    };
    int count = 4;

public:
    void showNotices() {
        cout << "\n--- COLLEGE NOTICES ---\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << notices[i].title
                 << "\n   " << notices[i].message << "\n";
        }
    }
};

// ---------------- CLUB INFORMATION ----------------
struct Club {
    string name;
    string activity;
    string contact;
};

class ClubInformation {
private:
    Club clubs[4] = {
        {"Coding Club", "Programming contests and coding practice", "codingclub@college.edu"},
        {"Cultural Club", "Music, dance, drama, and college events", "culturalclub@college.edu"},
        {"Sports Club", "Sports competitions and fitness activities", "sportsclub@college.edu"},
        {"Robotics Club", "Robotics projects and technical workshops", "roboticsclub@college.edu"}
    };
    int count = 4;

public:
    void showClubs() {
        cout << "\n--- CLUB INFORMATION (SAMPLE DATA) ---\n";
        for (int i = 0; i < count; i++) {
            cout << "\nClub: " << clubs[i].name
                 << "\nActivities: " << clubs[i].activity
                 << "\nContact: " << clubs[i].contact << "\n";
        }
    }
};

// ---------------- MAIN PROGRAM ----------------
int main() {
    LostAndFound lostFound;
    TeacherDetails teachers;
    NoticeSystem notices;
    ClubInformation clubs;

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       SMART CAMPUS SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Lost and Found\n";
        cout << "2. Teacher Details\n";
        cout << "3. Notice System\n";
        cout << "4. Club Information\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Please enter a number.\n";
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: lostFound.menu(); break;
            case 2: teachers.menu(); break;
            case 3: notices.showNotices(); break;
            case 4: clubs.showClubs(); break;
            case 0: cout << "Thank you for using Smart Campus!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}