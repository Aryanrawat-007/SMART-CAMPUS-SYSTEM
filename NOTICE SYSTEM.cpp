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
