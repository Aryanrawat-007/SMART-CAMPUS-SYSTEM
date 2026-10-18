
#include <iostream>
#include <string>
#include <limits>
using namespace std;

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

    void reportItem() {
        LostItem *node = new LostItem;

        cout << "Enter item name: ";
        getline(cin, node->itemName);

        cout << "Enter place where it was lost/found: ";
        getline(cin, node->place);

        cout << "Enter status (LOST or FOUND): ";
        getline(cin, node->status);

        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        count++;
        cout << "Item report added successfully!\n";
    }

    void showItems() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        cout<<"\n-LOST AND FOUND RECORDS-\n";

        LostItem *current = head;
        int number = 1;

        while (current != NULL) {
            cout << number << ". Item: " << current->itemName
                 << "  Place: " << current->place
                 << "  Status: " << current->status << '\n';

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

        cout << "\n- NEWEST REPORTS FIRST- \n";

        int number = 1;

        while (top >= 0) {
            LostItem *item = stack[top];
            top--;

            cout << number << ". Item: " << item->itemName
                 << " | Place: " << item->place
                 << " | Status: " << item->status << '\n';

            number++;
        }

        delete[] stack;
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
            cout << "\n--- LOST AND FOUND ---\n";
            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "3. View newest reports first\n";
            cout << "4. Help / Contact Information\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)){
                choice=-1;
                continue;
            }

            if (choice == 1)
                reportItem();
            else if (choice == 2)
                showItems();
            else if (choice == 3)
                showNewestFirst();
            else if (choice == 4)
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
