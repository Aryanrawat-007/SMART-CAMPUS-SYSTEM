
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char ch) {
                  return tolower(ch);
              });

    return str;
}
bool readChoice(string prompt, int &choice) {
    cout << prompt;

    if (cin >> choice) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    choice = -1;

    cout << "Invalid input. Please enter a number.\n";
    return false;
}
struct LostItem {
    string itemName;
    string place;
    string status;
    LostItem *next;
};

class LostAndFound {
private:
    LostItem *head;
    LostItem *tail;
    int count;

public:
    LostAndFound() {
        head = NULL;
        tail = NULL;
        count = 0;

        loadFromFile();
    }
    ~LostAndFound() {
        while (head != NULL) {
            LostItem *temp = head;
            head = head->next;
            delete temp;
        }
    }

    LostAndFound(const LostAndFound &) = delete;
    LostAndFound &operator=(const LostAndFound &) = delete;

    void saveToFile() {
        ofstream file("lostfound.txt");

        if (!file) {
            cout << "Error opening file!\n";
            return;
        }

        LostItem *current = head;

        while (current != NULL) {
            file << current->itemName << "|"
                 << current->place << "|"
                 << current->status << "\n";

            current = current->next;
        }

        file.close();
    }
    void loadFromFile() {
        ifstream file("lostfound.txt");

        if (!file)
            return;

        string line;

        while (getline(file, line)) {
            stringstream ss(line);

            LostItem *node = new LostItem;

            getline(ss, node->itemName, '|');
            getline(ss, node->place, '|');
            getline(ss, node->status);

            node->next = NULL;

            if (head == NULL) {
                head = node;
                tail = node;
            }
            else {
                tail->next = node;
                tail = node;
            }

            count++;
        }

        file.close();

        if (count > 0) {
            cout << count
                 << " previous records loaded successfully!\n";
        }
    }
    void reportItem() {
        LostItem *node = new LostItem;

        cout << "Enter item name: ";
        getline(cin, node->itemName);

        cout << "Enter place where it was lost/found: ";
        getline(cin, node->place);

        do {
            cout << "Enter status (LOST or FOUND): ";
            getline(cin, node->status);

            node->status = toLower(node->status);

            if (node->status != "lost" &&
                node->status != "found") {
                cout << "Enter LOST or FOUND only!\n";
            }

        } while (node->status != "lost" &&
                 node->status != "found");

        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        count++;

        saveToFile();

        cout << "Item report added successfully!\n";
    }

   
    void showItems() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        cout << "\n-LOST AND FOUND RECORDS-\n";

        LostItem *current = head;
        int number = 1;

        while (current != NULL) {
            cout << number << ". Item: "
                 << current->itemName
                 << " | Place: " << current->place
                 << " | Status: "
                 << (current->status == "lost" ? "LOST" : "FOUND")
                 << '\n';

            current = current->next;
            number++;
        }
    }
    void showNewestFirst() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        LostItem **stack = new LostItem*[count];
        int top = -1;

        LostItem *current = head;

        while (current != NULL) {
            top++;
            stack[top] = current;
            current = current->next;
        }

        cout << "\n- NEWEST REPORTS FIRST-\n";

        int number = 1;

        while (top >= 0) {
            LostItem *item = stack[top];
            top--;

            cout << number << ". Item: "
                 << item->itemName
                 << " | Place: " << item->place
                 << " | Status: "
                 << (item->status == "lost" ? "LOST" : "FOUND")
                 << '\n';

            number++;
        }

        delete[] stack;
    }
    void searchItem() {
        if (head == NULL) {
            cout << "No records available!\n";
            return;
        }

        string name;

        cout << "Enter item name to search: ";
        getline(cin, name);

        LostItem *current = head;
        bool found = false;
        int number = 1;

        while (current != NULL) {

            if (toLower(current->itemName) == toLower(name)) {

                cout << "\nItem found!\n";

                cout << "Record number: " << number << endl;
                cout << "Item: " << current->itemName << endl;
                cout << "Place: " << current->place << endl;

                cout << "Status: "
                     << (current->status == "lost" ? "LOST" : "FOUND")
                     << endl;

                found = true;
            }

            current = current->next;
            number++;
        }

        if (!found) {
            cout << "Item not found!\n";
        }
    }
    void updateStatus() {
        if (head == NULL) {
            cout << "No records available!\n";
            return;
        }

        string name;

        cout << "Enter item name to update: ";
        getline(cin, name);

        LostItem *current = head;
        
        bool found = false;

        while (current != NULL) {

            if (toLower(current->itemName) == toLower(name)) {

                found = true;

                cout << "\nItem: " << current->itemName << endl;
                cout << "Place: " << current->place << endl;

                cout << "Current status: "
                     << (current->status == "lost" ? "LOST" : "FOUND")
                     << endl;

                cout << "Enter new status (LOST or FOUND): ";

                string newStatus;
                getline(cin, newStatus);

                newStatus = toLower(newStatus);

                while (newStatus != "lost" &&
                       newStatus != "found") {

                    cout << "Invalid status! Enter LOST or FOUND: ";
                    getline(cin, newStatus);

                    newStatus = toLower(newStatus);
                }

                current->status = newStatus;

                saveToFile();

                cout << "Status updated successfully!\n";
            }

            current = current->next;
        }

        if (!found) {
            cout << "Item not found!\n";
        }
    }
    void showHelp() {
        cout << "\n-HELP / CONTACT INFORMATION-\n";

        cout << "\nPerson 1:\n";
        cout << "Contact Number: 9756473638\n";
        cout << "Email: addhyanpundir23@gmail.com\n";

        cout << "\nPerson 2:\n";
        cout << "Contact Number: 9528543042\n";
        cout << "Email: pr3237680@gmail.com\n";

        cout << "\nFor any lost and found related queries, "
             << "please contact the above persons.\n";
    }
    void menu() {
        int choice;

        do {
            cout << "\n- LOST AND FOUND -\n";

            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "3. View newest reports first\n";
            cout << "4. Search an item\n";
            cout << "5. Update item status\n";
            cout << "6. Help / Contact Information\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)) {
                choice = -1;
                continue;
            }

            if (choice == 1)
                reportItem();

            else if (choice == 2)
                showItems();

            else if (choice == 3)
                showNewestFirst();

            else if (choice == 4)
                searchItem();

            else if (choice == 5)
                updateStatus();

            else if (choice == 6)
                showHelp();

            else if (choice != 0)
                cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};


int main() {
    LostAndFound system;

    system.menu();

    return 0;
}
