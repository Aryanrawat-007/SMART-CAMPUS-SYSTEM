// ---------------- CLUB INFORMATION (Array) ----------------
struct Club {
    string name;
    string activity;
    string contact;
};

class ClubInformation {
private:
    Club clubs[4] = {
        {"Co-Dev Club", "Programming contests and coding practice", "codingclub@gmail.com"},
        {"Rangdarpan", "Music, dance, drama, and college events", "culturalclub@gmail.com"},
        {"Aryavart", "Management and event hosting ", "aryavart@college.edu"},
        {"Vedic Science Club", "self improvement ,knowledge along with spirituality", "ved@gmail.com"}
    };
    int count = 4;

public:
    void showClubs() {
        cout << "\n    CLUB INFORMATION    \n";
        for (int i = 0; i < count; i++) {
            cout << "\nClub: " << clubs[i].name
                 << "\nActivities: " << clubs[i].activity
                 << "\nContact: " << clubs[i].contact << "\n";
        }
    }
};
