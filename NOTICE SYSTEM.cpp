struct Notice {
    string title;
    string message;
};

class NoticeSystem {
private:
    Notice notices[4] = {
        {"Exam Notice", "Check the official portal for examination dates."},
        {"Library Notice", "Please return borrowed books on time."},
        {"Event Notice", "College cultural event registrations are open."},
        {"Holiday Notice", "Check official college announcements for holidays."}
    };
    int count = 4;

public:
    void showNotices() {
        cout << "\n--- COLLEGE NOTICES ---\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << notices[i].title
                 << "\n   " << notices[i].message << "\n";
        }
    }
};

// ---------------- CLUB INFORMATION ----------------
struct Club {
    string name;
    string activity;
    string contact;
};

class ClubInformation {
private:
    Club clubs[4] = {
        {"Coding Club", "Programming contests and coding practice", "codingclub@college.edu"},
        {"Cultural Club", "Music, dance, drama, and college events", "culturalclub@college.edu"},
        {"Sports Club", "Sports competitions and fitness activities", "sportsclub@college.edu"},
        {"Robotics Club", "Robotics projects and technical workshops", "roboticsclub@college.edu"}
    };
    int count = 4;

public:
    void showClubs() {
        cout << "\n--- CLUB INFORMATION (SAMPLE DATA) ---\n";
        for (int i = 0; i < count; i++) {
            cout << "\nClub: " << clubs[i].name
                 << "\nActivities: " << clubs[i].activity
                 << "\nContact: " << clubs[i].contact << "\n";
        }
    }
};
