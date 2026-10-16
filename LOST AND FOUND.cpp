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
