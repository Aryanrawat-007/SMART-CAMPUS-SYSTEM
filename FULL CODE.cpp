#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Reads a menu choice into "choice".
// Returns false if the user typed something that is not a number
// (in that case choice is set to 0, so the current menu closes).
bool readChoice(string prompt, int &choice) {
    cout << prompt;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number.\n";
        choice = 0;
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

// ---------------- LOST AND FOUND (Linked List + Stack) ----------------
// Each report is one node of a singly linked list.
struct LostItem {
    string itemName;
    string place;
    string status;     // LOST or FOUND
    LostItem *next;    // points to the next report
};

class LostAndFound {
private:
    LostItem *head;    // first node
    LostItem *tail;    // last node (makes adding at the end quick)
    int count;

public:
    LostAndFound() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    // destructor: delete every node so no memory is leaked
    ~LostAndFound() {
        while (head != NULL) {
            LostItem *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // copying is not needed, so we switch it off
    LostAndFound(const LostAndFound &) = delete;
    LostAndFound &operator=(const LostAndFound &) = delete;

    // INSERT at the end of the linked list
    void reportItem() {
        LostItem *node = new LostItem;

        cout << "Enter item name: ";
        getline(cin, node->itemName);

        cout << "Enter place where it was lost/found: ";
        getline(cin, node->place);

        cout << "Enter status (LOST or FOUND): ";
        getline(cin, node->status);

        node->next = NULL;
        if (head == NULL) {          // list was empty
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        count++;
        cout << "Item report added successfully!\n";
    }

    // TRAVERSE the linked list from head to tail (oldest first)
    void showItems() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        cout << "\n--- LOST AND FOUND RECORDS ---\n";
        LostItem *current = head;
        int number = 1;
        while (current != NULL) {
            cout << number << ". Item: " << current->itemName
                 << " | Place: " << current->place
                 << " | Status: " << current->status << '\n';
            current = current->next;
            number++;
        }
    }

    // STACK: push every node, then pop them -> last report comes out first
    void showNewestFirst() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        LostItem **stack = new LostItem*[count];   // array used as a stack
        int top = -1;

        LostItem *current = head;
        while (current != NULL) {
            top++;
            stack[top] = current;                  // push
            current = current->next;
        }

        cout << "\n--- NEWEST REPORTS FIRST ---\n";
        int number = 1;
        while (top >= 0) {
            LostItem *item = stack[top];           // pop
            top--;
            cout << number << ". Item: " << item->itemName
                 << " | Place: " << item->place
                 << " | Status: " << item->status << '\n';
            number++;
        }

        delete[] stack;
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- LOST AND FOUND ---\n";
            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "3. View newest reports first\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)) continue;

            if (choice == 1) reportItem();
            else if (choice == 2) showItems();
            else if (choice == 3) showNewestFirst();
            else if (choice != 0) cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};

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

// ---------------- NOTICE SYSTEM (Queue) ----------------
struct Notice {
    string title;
    string message;
};

// Circular queue made with an array: first notice in = first notice out (FIFO)
class NoticeSystem {
private:
    static const int SIZE = 10;
    Notice queue[SIZE];
    int front;     // index of the oldest notice
    int count;     // how many notices are in the queue

    // ENQUEUE: add at the rear
    bool enqueue(string title, string message) {
        if (count == SIZE)
        return false;          // queue is full
        int rear = (front + count) % SIZE;
        queue[rear].title = title;
        queue[rear].message = message;
        count++;
        return true;
    }

public:
    NoticeSystem() {
        front = 0;
        count = 0;
        enqueue("Exam Notice",    "Check the official portal for examination dates.");
        enqueue("Library Notice", "Please return borrowed books on time.");
        enqueue("Event Notice",   "College cultural event registrations are open.");
        enqueue("Holiday Notice", "Check official college announcements for holidays.");
    }

    // show from front to rear (oldest first)
    void showNotices() {
        cout << "\n--- COLLEGE NOTICES ---\n";
        if (count == 0) {
            cout << "No notices right now.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            Notice n = queue[(front + i) % SIZE];
            cout << i + 1 << ". " << n.title
                 << "\n   " << n.message << "\n";
        }
    }

    void postNotice() {
        string title, message;
        cout << "Enter notice title: ";
        getline(cin, title);
        cout << "Enter notice message: ";
        getline(cin, message);

        if (enqueue(title, message)) cout << "Notice posted successfully!\n";
        else cout << "The notice board is full.\n";
    }

    // DEQUEUE: remove from the front (the oldest notice)
    void removeOldest() {
        if (count == 0) {
            cout << "No notices to remove.\n";
            return;
        }
        cout << "Removed: " << queue[front].title << "\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- NOTICE SYSTEM ---\n";
            cout << "1. View notices\n";
            cout << "2. Post a notice\n";
            cout << "3. Remove oldest notice\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)) continue;

            if (choice == 1) showNotices();
            else if (choice == 2) postNotice();
            else if (choice == 3) removeOldest();
            else if (choice != 0) cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};

// ---------------- CLUB INFORMATION (Array) ----------------
struct Club {
    string name;
    string activity;
    string contact;
};

class ClubInformation {
private:
    Club clubs[4] = {
        {"Co-Dev Club", "Programming contests and coding practice", "codingclub@gmail.com"},
        {"Rangdarpan", "Music, dance, drama, and college events", "culturalclub@gmail.com"},
        {"Aryavart", "Management and event hosting ", "aryavart@college.edu"},
        {"Vedic Science Club", "self improvement ,knowledge along with spirituality", "ved@gmail.com"}
    };
    int count = 4;

public:
    void showClubs() {
        cout << "\n    CLUB INFORMATION    \n";
        for (int i = 0; i < count; i++) {
            cout << "\nClub: " << clubs[i].name
                 << "\nActivities: " << clubs[i].activity
                 << "\nContact: " << clubs[i].contact << "\n";
        }
    }
};

int main() {
    LostAndFound lostFound;
    TeacherDetails teachers;
    NoticeSystem notices;
    ClubInformation clubs;

    int choice;

    do {
        cout << "     SMART CAMPUS SYSTEM\n";
        cout << "1. Lost and Found\n";
        cout << "2. Teacher Details\n";
        cout << "3. Notice System\n";
        cout << "4. Club Information\n";
        cout << "0. Exit\n";

        if (!readChoice("Enter your choice: ", choice))
        continue;

        switch (choice) {
            case 1: lostFound.menu(); 
            break;
            case 2: teachers.menu();
            break;
            case 3: notices.menu();
            break;
            case 4: clubs.showClubs();
            break;
            case 0:
            cout << "Thank you for using Smart Campus!\n"; 
            break;
            default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
