#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// ---------------- CLUB INFORMATION (Array) ----------------

struct Club {
    string name;
    string activity;
    string contact;
};

class ClubInformation {
private:
    static const int MAX_CLUBS = 100;

    Club clubs[MAX_CLUBS];
    int count;

    // Convert text to lowercase
    string toLowerCase(string text) {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) {
                      return tolower(c);
                  });

        return text;
    }

    // Display one club
    void displayClub(const Club &c) {
        cout << "\nClub: " << c.name;
        cout << "\nActivities: " << c.activity;
        cout << "\nContact: " << c.contact << "\n";
    }

public:
    // Constructor: add five default clubs
    ClubInformation() {
        count = 0;

        addClub("Co-Dev Club",
                "Programming contests and coding practice",
                "codingclub@gmail.com");

        addClub("Rangdarpan",
                "Music, dance, drama, and college events",
                "culturalclub@gmail.com");

        addClub("Aryavart",
                "Management and event hosting",
                "aryavart@college.edu");

        addClub("Vedic Science Club",
                "Self improvement, knowledge along with spirituality",
                "ved@gmail.com");

        addClub("Himpravah",
                "Online Film Festival",
                "Contact details not provided");
    }

    // Add club details to the array
    void addClub(string name, string activity, string contact) {
        if (count >= MAX_CLUBS) {
            cout << "Club list is full!\n";
            return;
        }

        clubs[count].name = name;
        clubs[count].activity = activity;
        clubs[count].contact = contact;

        count++;
    }

    // Display all clubs
    void showClubs() {
        if (count == 0) {
            cout << "\nNo clubs available.\n";
            return;
        }

        cout << "\n===== ALL COLLEGE CLUBS =====\n";

        for (int i = 0; i < count; i++) {
            cout << "\n" << i + 1 << ".";
            displayClub(clubs[i]);
        }
    }

    // Search by club name
    void searchByName() {
        string searchText;
        bool found = false;

        cout << "Enter club name to search: ";
        getline(cin, searchText);

        if (searchText.empty()) {
            cout << "Please enter a club name.\n";
            return;
        }

        searchText = toLowerCase(searchText);

        for (int i = 0; i < count; i++) {
            if (toLowerCase(clubs[i].name).find(searchText)
                != string::npos) {
                displayClub(clubs[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "No matching club found.\n";
        }
    }

    // Search by activity
    void searchByActivity() {
        string searchText;
        bool found = false;

        cout << "Enter activity to search: ";
        getline(cin, searchText);

        if (searchText.empty()) {
            cout << "Please enter an activity.\n";
            return;
        }

        searchText = toLowerCase(searchText);

        for (int i = 0; i < count; i++) {
            if (toLowerCase(clubs[i].activity).find(searchText)
                != string::npos) {
                displayClub(clubs[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "No club found for this activity.\n";
        }
    }

    // Search by contact email
    void searchByContact() {
        string searchText;
        bool found = false;

        cout << "Enter contact email to search: ";
        getline(cin, searchText);

        if (searchText.empty()) {
            cout << "Please enter a contact email.\n";
            return;
        }

        searchText = toLowerCase(searchText);

        for (int i = 0; i < count; i++) {
            if (toLowerCase(clubs[i].contact).find(searchText)
                != string::npos) {
                displayClub(clubs[i]);
                found = true;
            }
        }

        if (!found) {
            cout << "No matching contact found.\n";
        }
    }

    // Add a new club using user input
    void addNewClub() {
        string name, activity, contact;

        if (count >= MAX_CLUBS) {
            cout << "Club list is full!\n";
            return;
        }

        cout << "Enter club name: ";
        getline(cin, name);

        cout << "Enter club activities: ";
        getline(cin, activity);

        cout << "Enter contact email: ";
        getline(cin, contact);

        if (name.empty() || activity.empty() || contact.empty()) {
            cout << "All fields are required.\n";
            return;
        }

        addClub(name, activity, contact);

        cout << "Club added successfully!\n";
    }

    // Club information menu
    void menu() {
        int choice;

        do {
            cout << "\n===== CLUB INFORMATION SYSTEM =====\n";
            cout << "1. View All Clubs\n";
            cout << "2. Search by Club Name\n";
            cout << "3. Search by Activity\n";
            cout << "4. Search by Contact\n";
            cout << "5. Add New Club\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    showClubs();
                    break;

                case 2:
                    searchByName();
                    break;

                case 3:
                    searchByActivity();
                    break;

                case 4:
                    searchByContact();
                    break;

                case 5:
                    addNewClub();
                    break;

                case 0:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 0);
    }
};
int main() {
    ClubInformation clubInfo;
    int choice;

    do {
        cout << "\n===== COLLEGE MANAGEMENT SYSTEM =====\n";
        cout << "1. Club Information\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            choice = -1;   // keep the loop running
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clubInfo.menu();
                break;

            case 0:
                cout << "Thank you for using the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
