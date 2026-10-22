
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
struct Complaint {
    string name;
    string department;
    string details;
    Complaint *next;
};
class ComplaintPortal {
private:
    Complaint *head;
public:
    ComplaintPortal() {
        head = NULL;
    }
// Submit complaint and save it in file
    void submitComplaint() {
        Complaint *p = new Complaint;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter your name: ";
        getline(cin, p->name);
        cout << "Enter department: ";
        getline(cin, p->department);
        cout << "Enter complaint details: ";
        getline(cin, p->details);
        p->next = head;
        head = p;
        ofstream file("complaints.txt", ios::app);

      if (file.is_open()) {
            file << "Name: " << p->name << '\n';
            file << "Department: " << p->department << '\n';
            file << "Complaint: " << p->details << '\n';
            file << "-------------------------\n";
            file.close();
            cout << "Complaint saved successfully!\n";
        } else {
            cout << "Error opening file!\n";
        }
    }
 // Read complaints from file
    void showComplaints() {
        ifstream file("complaints.txt");

        if (!file.is_open()) {
            cout << "No complaint file found.\n";
            return;
        }
        string line;
        cout << "\n--- SAVED COMPLAINTS ---\n";
        while (getline(file, line)) {
            cout << line << '\n';
        }
        file.close();
    }

    // Anti-ragging information
    void antiRaggingInfo() {
    cout << "\n--- ANTI-RAGGING INFORMATION ---\n";
    cout << "1. Ragging is prohibited in educational institutions.\n";
    cout << "2. Every student deserves a safe campus.\n";
    cout << "3. Report incidents to college authorities.\n";
    cout << "4. Contact the Anti-Ragging Committee or warden.\n";
    cout << "5. Seek help from a trusted teacher or family member.\n";
    cout << "6. Preserve relevant evidence if it is safe to do so.\n";
    cout << "7. National Helpline: 1800-180-5522 (24x7)\n";
    cout << "8. Email: helpline@antiragging.in\n";
    cout << "9. Website: https://www.antiragging.in\n";
    cout << "10. Say NO to ragging. Respect every student.\n";
   }

    // Main portal menu
    void menu() {
        int choice;

        do {
            cout << "\n--- COMPLAINT PORTAL ---\n";
            cout << "1. Submit Complaint\n";
            cout << "2. View Saved Complaints\n";
            cout << "3. Anti-Ragging Information\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    submitComplaint();
                    break;

                case 2:
                    showComplaints();
                    break;

                case 3:
                    antiRaggingInfo();
                    break;

                case 0:
                    cout << "Returning to main menu.\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }

    // Free linked-list memory
    ~ComplaintPortal() {
        while (head != NULL) {
            Complaint *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ComplaintPortal portal;
    portal.menu();

    return 0;
}
