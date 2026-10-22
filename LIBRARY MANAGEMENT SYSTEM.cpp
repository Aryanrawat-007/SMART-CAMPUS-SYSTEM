#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
struct Book {
    int id;
    string title;
    string branch;
    int semester;
    string subject;
    bool issued;
};
class Library {
private:
    Book books[100];
    int count;
    const string adminPassword = "gehu";
    bool matchesBranch(string bookBranch, string branch) {
        return bookBranch == "Common" || bookBranch == branch;
    }

    int getYear(int semester) {
        return (semester + 1) / 2;
    }
    // Add sample books
    void addSampleBooks() {
        count = 0;

        // First year: Common books
        books[count++] = {101, "Engineering Mathematics-I", "Common", 1, "Mathematics", false};
        books[count++] = {102, "Engineering Physics", "Common", 1, "Physics", false};
        books[count++] = {103, "Engineering Chemistry", "Common", 1, "Chemistry", false};
        books[count++] = {104, "Programming in C", "Common", 1, "Programming", false};
        books[count++] = {105, "Basic Electrical Engineering", "Common", 2, "Electrical", false};
        books[count++] = {106, "Engineering Graphics", "Common", 2, "Graphics", false};
        books[count++] = {107, "Communication Skills", "Common", 2, "English", false};
        books[count++] = {108, "Engineering Mechanics", "Common", 2, "Mechanics", false};

        // CSE: Second year
        books[count++] = {201, "Data Structures", "CSE", 3, "DS", false};
        books[count++] = {202, "Object Oriented Programming", "CSE", 3, "OOP", false};
        books[count++] = {203, "Discrete Mathematics", "CSE", 3, "Mathematics", false};
        books[count++] = {204, "Digital Logic Design", "CSE", 3, "Digital Electronics", false};
        books[count++] = {205, "Database Management Systems", "CSE", 4, "DBMS", false};
        books[count++] = {206, "Computer Organization", "CSE", 4, "COA", false};
        books[count++] = {207, "Operating Systems Basics", "CSE", 4, "OS", false};
        books[count++] = {208, "Probability and Statistics", "CSE", 4, "Mathematics", false};

        // CSE: Third year
        books[count++] = {301, "Operating Systems", "CSE", 5, "OS", false};
        books[count++] = {302, "Computer Networks", "CSE", 5, "CN", false};
        books[count++] = {303, "Theory of Computation", "CSE", 5, "TOC", false};
        books[count++] = {304, "Design and Analysis of Algorithms", "CSE", 6, "DAA", false};
        books[count++] = {305, "Software Engineering", "CSE", 6, "SE", false};
        books[count++] = {306, "Compiler Design", "CSE", 6, "Compiler", false};

        // CSE: Fourth year
        books[count++] = {401, "Artificial Intelligence", "CSE", 7, "AI", false};
        books[count++] = {402, "Machine Learning", "CSE", 7, "ML", false};
        books[count++] = {403, "Cloud Computing", "CSE", 7, "Cloud", false};
        books[count++] = {404, "Cyber Security", "CSE", 8, "Security", false};
        books[count++] = {405, "Big Data Analytics", "CSE", 8, "Big Data", false};
        books[count++] = {406, "Internet of Things", "CSE", 8, "IoT", false};

        // Electronics and Communication Engineering
        books[count++] = {501, "Electronic Devices and Circuits", "ECE", 3, "Electronics", false};
        books[count++] = {502, "Digital Electronics", "ECE", 3, "Digital Electronics", false};
        books[count++] = {503, "Signals and Systems", "ECE", 4, "Signals", false};
        books[count++] = {504, "Microprocessors", "ECE", 5, "Microprocessors", false};
        books[count++] = {505, "Control Systems", "ECE", 6, "Control Systems", false};
        books[count++] = {506, "VLSI Design", "ECE", 7, "VLSI", false};

        // Electrical Engineering
        books[count++] = {601, "Electrical Machines", "Electrical", 3, "Machines", false};
        books[count++] = {602, "Power Systems", "Electrical", 5, "Power Systems", false};
        books[count++] = {603, "Power Electronics", "Electrical", 6, "Power Electronics", false};
        books[count++] = {604, "Renewable Energy Systems", "Electrical", 7, "Renewable Energy", false};

        // Mechanical Engineering
        books[count++] = {701, "Thermodynamics", "Mechanical", 3, "Thermodynamics", false};
        books[count++] = {702, "Fluid Mechanics", "Mechanical", 4, "Fluid Mechanics", false};
        books[count++] = {703, "Theory of Machines", "Mechanical", 5, "Machines", false};
        books[count++] = {704, "Machine Design", "Mechanical", 6, "Machine Design", false};

        // Civil Engineering
        books[count++] = {801, "Surveying", "Civil", 3, "Surveying", false};
        books[count++] = {802, "Structural Analysis", "Civil", 4, "Structures", false};
        books[count++] = {803, "Geotechnical Engineering", "Civil", 5, "Geotechnical", false};
        books[count++] = {804, "Transportation Engineering", "Civil", 6, "Transportation", false};
    }

    // Save all book information
    void saveBooks() {
        ofstream file("library_books.txt");
        if (!file.is_open()) {
            cout << "Error saving library file!\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            file << books[i].id << "|"
                 << books[i].title << "|"
                 << books[i].branch << "|"
                 << books[i].semester << "|"
                 << books[i].subject << "|"
                 << books[i].issued << "\n";
        }
        file.close();
    }

    // Load books from file
    void loadBooks() {
        ifstream file("library_books.txt");

        if (!file.is_open()) {
            addSampleBooks();
            saveBooks();
            return;
        }
        count = 0;
        string line;
        while (getline(file, line) && count < 100) {
            string fields[6];
            string value = "";
            int field = 0;
            for (int i = 0; i <= (int)line.length(); i++) {
                if (i == (int)line.length() || line[i] == '|') {
                    if (field < 6)
                        fields[field++] = value;
                    value = "";
                } else {
                    value += line[i];
                }
            }
            if (field != 6)
                continue;
                try {
                books[count].id = stoi(fields[0]);
                books[count].title = fields[1];
                books[count].branch = fields[2];
                books[count].semester = stoi(fields[3]);
                books[count].subject = fields[4];
                books[count].issued = (fields[5] == "1");
                count++;
            } catch (...) {
                cout << "Skipping an invalid book record.\n";
            }
        }
        file.close();
        if (count == 0) {
            addSampleBooks();
            saveBooks();
        }
    }
public:
    Library() {
        count = 0;
        loadBooks();
    }
    // Display one book
    void displayOneBook(int i) {
        cout << "\nBook ID: " << books[i].id;
        cout << "\nTitle: " << books[i].title;
        cout << "\nBranch: " << books[i].branch;
        cout << "\nYear: " << getYear(books[i].semester);
        cout << "\nSemester: " << books[i].semester;
        cout << "\nSubject: " << books[i].subject;
        cout << "\nStatus: "
             << (books[i].issued ? "Issued" : "Available");
        cout << "\n----------------------------\n";
    }
    // Display all books
    void displayBooks() {
        cout << "\n========== ALL LIBRARY BOOKS ==========\n";
        for (int i = 0; i < count; i++)
            displayOneBook(i);
        cout << "\nTotal books: " << count << "\n";
    }

    // Search by branch, year and semester
    void searchCourse() {
        string branch;
        int year, semester;
        bool found = false;
        cout << "Enter branch (CSE/ECE/Electrical/Mechanical/Civil): ";
        cin >> branch;
        cout << "Enter year (1-4): ";
        cin >> year;
        cout << "Enter semester (1-8): ";
        cin >> semester;
        if (year < 1 || year > 4 ||semester < 1 || semester > 8 ||getYear(semester) != year) {
            cout << "Invalid year or semester combination.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            if (matchesBranch(books[i].branch, branch) &&
                books[i].semester == semester) {
                displayOneBook(i);
                found = true;
            }
        }
        if (!found)
            cout << "No books found for these details.\n";
    }

    // Case-sensitive subject or title search
    void searchSubject() {
        string subject;
        bool found = false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter subject name or keyword (case-sensitive): ";
        getline(cin, subject);
        for (int i = 0; i < count; i++) {
            if (books[i].subject.find(subject) != string::npos ||
                books[i].title.find(subject) != string::npos) {
                displayOneBook(i);
                found = true;
            }
        }
        if (!found)
            cout << "No matching books found.\n";
    }

    // Issue a book
    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        for (int i = 0; i < count; i++) {
            if (books[i].id == id) {
                if (!books[i].issued) {
                    books[i].issued = true;
                    saveBooks();
                    cout << "Book issued successfully!\n";
                } else {
                    cout << "This book is already issued.\n";
                }
                return;
            }
        }
        cout << "Book ID not found.\n";
    }

    // Return a book
    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;
        for (int i = 0; i < count; i++) {
            if (books[i].id == id) {
                if (books[i].issued) {
                    books[i].issued = false;
                    saveBooks();
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "This book is already available.\n";
                }
                return;
            }
        }
        cout << "Book ID not found.\n";
    }

    // Add a new book - password protected
    void addBook() {
        string password;
        cout << "\nEnter administrator password: ";
        cin >> password;
        if (password != adminPassword) {
            cout << "Incorrect password! Access denied.\n";
            return;
        }
        cout << "Password accepted.\n";
        if (count >= 100) {
            cout << "Library is full.\n";
            return;
        }
        Book b;
        cout << "Enter Book ID: ";
        cin >> b.id;
        for (int i = 0; i < count; i++) {
            if (books[i].id == b.id) {
                cout << "This Book ID already exists.\n";
                return;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter book title: ";
        getline(cin, b.title);
        cout << "Enter branch (CSE/ECE/Electrical/Mechanical/Civil/Common): ";
        getline(cin, b.branch);
        cout << "Enter semester (1-8): ";
        cin >> b.semester;
        if (b.semester < 1 || b.semester > 8) {
            cout << "Invalid semester.\n";
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter subject: ";
        getline(cin, b.subject);
        b.issued = false;
        books[count++] = b;
        saveBooks();
        cout << "Book added and saved successfully!\n";
    }

    // Main menu
    void menu() {
        int choice;
        do {
            cout << "\n========== COLLEGE LIBRARY ==========\n";
            cout << "1. Display All Books\n";
            cout << "2. Search by Branch, Year and Semester\n";
            cout << "3. Search by Subject or Title\n";
            cout << "4. Issue Book\n";
            cout << "5. Return Book\n";
            cout << "6. Add New Book (Admin Only)\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter choice: ";
            
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }
            switch (choice) {
                case 1: displayBooks(); break;
                case 2: searchCourse(); break;
                case 3: searchSubject(); break;
                case 4: issueBook(); break;
                case 5: returnBook(); break;
                case 6: addBook(); break;
                case 0: cout << "Returning to Smart Campus menu.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    Library lib;
    lib.menu();
    return 0;
}
