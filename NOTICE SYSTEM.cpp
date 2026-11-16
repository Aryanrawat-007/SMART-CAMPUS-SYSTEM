
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
struct Notice {
    int id;
    string title;
    string category;
    string date;
    string message;
    Notice* next;
};

class NoticeSystem {
private:
    Notice* head;
    int nextId;
    // Add a notice to the linked list
    void addToList(int id, string title, string category,
                   string date, string message) {
        Notice* newNotice = new Notice;

        newNotice->id = id;
        newNotice->title = title;
        newNotice->category = category;
        newNotice->date = date;
        newNotice->message = message;
        newNotice->next = NULL;
        if (head == NULL) {
            head = newNotice;
        }
        else {
            Notice* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNotice;
        }
    }
    // Save all notices in the file
    bool saveNotices() {
        ofstream file("notices.txt");
        if (!file) {
            cout << "\nError: Unable to save notices!\n";
            return false;
        }

        Notice* temp = head;
        while (temp != NULL) {
            file << temp->id << '\n';
            file << temp->title << '\n';
            file << temp->category << '\n';
            file << temp->date << '\n';
            file << temp->message << '\n';
            temp = temp->next;
        }
        file.close();
        if (!file) {
            cout << "\nError while writing to file!\n";
            return false;
        }
        return true;
    }
    // Load notices from the file
    void loadNotices() {
        ifstream file("notices.txt");
        if (!file) {
            return;
        }
        int id;
        string title, category, date, message;
        while (file >> id) {
            // Remove the remaining newline
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!getline(file, title) ||
                !getline(file, category) ||
                !getline(file, date) ||
                !getline(file, message)) {

                cout << "\nIncomplete notice data found in file.\n";
                break;
            }
            addToList(id, title, category, date, message);
            if (id >= nextId) {
                nextId = id + 1;
            }
        }
        file.close();
    }
    // Add a new notice
    void addNotice() {
        string title, category, date, message;

        cout << "\nEnter notice title: ";
        getline(cin >> ws, title);
        cout << "Enter category: ";
        getline(cin, category);
        cout << "Enter date: ";
        getline(cin, date);
        cout << "Enter notice message: ";
        getline(cin, message);
    
        if (title.empty() || category.empty() ||
            date.empty() || message.empty()) {
            cout << "\nNotice details cannot be empty!\n";
            return;
        }
        int id = nextId;
        addToList(id, title, category, date, message);
        if (saveNotices()) {
            nextId++;
            cout << "\nNotice added successfully!\n";
            cout << "Notice ID: " << id << '\n';
        }
    }
    // Display all notices
    void displayNotices() {
        if (head == NULL) {
            cout << "\nNo notices available.\n";
            return;
        }
        Notice* temp = head;
        cout << "\n========== CAMPUS NOTICES ==========\n";
        while (temp != NULL) {
            cout << "\nID: " << temp->id;
            cout << "\nTitle: " << temp->title;
            cout << "\nCategory: " << temp->category;
            cout << "\nDate: " << temp->date;
            cout << "\nMessage: " << temp->message;
            cout << "\n------------------------------------\n";
            temp = temp->next;
        }
    }
    // Search a notice by title
    void searchNotice() {
        string title;
        bool found = false;
        cout << "\nEnter notice title to search: ";
        getline(cin >> ws, title);
        Notice* temp = head;
        while (temp != NULL) {
            if (temp->title == title) {
                cout << "\nNotice found!\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Title: " << temp->title << '\n';
                cout << "Category: " << temp->category << '\n';
                cout << "Date: " << temp->date << '\n';
                cout << "Message: " << temp->message << '\n';
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "\nNotice not found.\n";
        }
    }
    // Delete a notice using its ID
    void deleteNotice() {
        int id;
        cout << "\nEnter notice ID to delete: ";
        if (!(cin >> id)) {
            cout << "\nInvalid ID. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Notice* temp = head;
        Notice* previous = NULL;
        while (temp != NULL && temp->id != id) {
            previous = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "\nNotice not found.\n";
            return;
        }
        // If the first node is deleted
        if (previous == NULL) {
            head = temp->next;
        }
        else {
            previous->next = temp->next;
        }
        delete temp;
        if (saveNotices()) {
            cout << "\nNotice deleted successfully!\n";
        }
    }
    // Free the linked list memory
    void clearNotices() {
        while (head != NULL) {
            Notice* temp = head;
            head = head->next;
            delete temp;
        }
    }
public:
    // Constructor
    NoticeSystem() {
        head = NULL;
        nextId = 1;

        loadNotices();
    }
    // Main menu
    void menu() {
        int choice;

        do {
            cout << "\n================================\n";
            cout << "       SMART CAMPUS NOTICE SYSTEM\n";
            cout << "================================\n";
            cout << "1. Add Notice\n";
            cout << "2. Display Notices\n";
            cout << "3. Search Notice\n";
            cout << "4. Delete Notice\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "\nPlease enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
                case 1:
                    addNotice();
                    break;
                case 2:
                    displayNotices();
                    break;
                case 3:
                    searchNotice();
                    break;
                case 4:
                    deleteNotice();
                    break;
                case 0:
                    cout << "\nThank you for using Notice System!\n";
                    break;
                default:
                    cout << "\nInvalid choice. Try again.\n";
            }
        } while (choice != 0);
    }
    // Destructor
    ~NoticeSystem() {
        clearNotices();
    }
};
int main() {
    NoticeSystem ns;
    ns.menu();
    return 0;
}
