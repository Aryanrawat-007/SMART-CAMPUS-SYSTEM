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

    // copying is not needed, so we switch it off
    LostAndFound(const LostAndFound &) = delete;
    LostAndFound &operator=(const LostAndFound &) = delete;

    // insert from end
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

    //  stack
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

        cout << "\n--- NEWEST REPORTS FIRST ---\n";
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

    void menu() {
        int choice;
        do {
            cout << "\n--- LOST AND FOUND ---\n";
            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "3. View newest reports first\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)) 
            continue;
            if (choice == 1) 
            reportItem();
            else if (choice == 2)
            showItems();
            else if (choice == 3)
            showNewestFirst();
            else if (choice != 0) 
            cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};
