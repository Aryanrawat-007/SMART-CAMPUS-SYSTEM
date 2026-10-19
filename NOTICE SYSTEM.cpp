
#include <iostream>
#include <fstream>
#include <string>
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
    void addToList(int id, string title, string category,string date, string message) {
        Notice* newNotice = new Notice;
        newNotice->id = id;
        newNotice->title = title;
        newNotice->category = category;
        newNotice->date = date;
        newNotice->message = message;
        newNotice->next = NULL;

        if (head == NULL) {
            head = newNotice;
        } else {
            Notice* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNotice;
        }
    }
    void saveNotices() {
        ofstream file("notices.txt");
        if (!file) {
            cout << "Error saving notices!\n";
            return;
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
    }
    void loadNotices() {
        ifstream file("notices.txt");
        if (!file) {
            return;
        }
        int id;
        string title, category, date, message;
        while (file >> id) {
            file.ignore();

            if (!getline(file, title) ||
                !getline(file, category) ||
                !getline(file, date) ||
                !getline(file, message)) {
                cout << "Incomplete notice data found.\n";
                break;
            }
            addToList(id, title, category, date, message);
            if (id >= nextId) {
                nextId = id + 1;
            }
        }
        file.close();
    }
    void addNotice() {
        int id = nextId++;
        string title, category, date, message;

        cout << "\nEnter notice title: ";
        getline(cin >> ws, title);
        cout << "Enter category: ";
        getline(cin, category);
        cout << "Enter date: ";
        getline(cin, date);
        cout << "Enter notice message: ";
        getline(cin, message);
        addToList(id, title, category, date, message);
        saveNotices();
        cout << "\nNotice saved successfully!\n";
        cout << "Notice ID: " << id << '\n';
    }

    void displayNotices() {
        if (head == NULL) {
            cout << "\nNo notices available.\n";
            return;
        }

        Notice* temp = head;
        cout << "\n CAMPUS NOTICES \n";
        while (temp != NULL) {
            cout << "\nID: " << temp->id;
            cout << "\nTitle: " << temp->title;
            cout << "\nCategory: " << temp->category;
            cout << "\nDate: " << temp->date;
            cout << "\nMessage: " << temp->message;
            cout << "\n--------------------------\n";
            temp = temp->next;
        }
    }
    void searchNotice() {
        string title;
        bool found = false;
        cout << "\nEnter title to search: ";
        getline(cin >> ws, title);

        Notice* temp = head;

        while (temp != NULL) {
            if (temp->title == title) {
                cout << "\nNotice found!\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Category: " << temp->category << '\n';
                cout << "Date: " << temp->date << '\n';
                cout << "Message: " << temp->message << '\n';
                found = true;
            }

            temp = temp->next;
        }
        if (!found) {
            cout << "\nNotice not found.\n";
        }
    }
    void deleteNotice() {
        int id;
        cout << "\nEnter notice ID to delete: ";
        if (!(cin >> id)) {
            cout << "Invalid ID.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

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
        if (previous == NULL) {
            head = temp->next;
        } else {
            previous->next = temp->next;
        }
        delete temp;
        saveNotices();
        cout << "\nNotice deleted successfully!\n";
    }
    void clearNotices() {
        while (head != NULL) {
            Notice* temp = head;
            head = head->next;
            delete temp;
        }
    }
public:
    NoticeSystem() {
        head = NULL;
        nextId = 1;
        loadNotices();
    }
    void menu() {
        int choice;
        do {
            cout << "\nSMART CAMPUS NOTICE SYSTEM \n";
            cout << "1. Add Notice\n";
            cout << "2. Display Notices\n";
            cout << "3. Search Notice\n";
            cout << "4. Delete Notice\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cout << "Enter a valid number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
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
                    cout << "\nBYE!\n";
                    break;
                default:
                    cout << "\nInvalid choice.\n";
            }
        } while (choice != 0);
    }
    ~NoticeSystem() {
        clearNotices();
    }
};
int main() {
    NoticeSystem ns;
    ns.menu();
    return 0;
}
