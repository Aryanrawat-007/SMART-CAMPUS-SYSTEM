int main() {
    LostAndFound lostFound;
    TeacherDetails teachers;
    NoticeSystem notices;
    ClubInformation clubs;

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "       SMART CAMPUS SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Lost and Found\n";
        cout << "2. Teacher Details\n";
        cout << "3. Notice System\n";
        cout << "4. Club Information\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Please enter a number.\n";
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: lostFound.menu(); break;
            case 2: teachers.menu(); break;
            case 3: notices.showNotices(); break;
            case 4: clubs.showClubs(); break;
            case 0: cout << "Thank you for using Smart Campus!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}
