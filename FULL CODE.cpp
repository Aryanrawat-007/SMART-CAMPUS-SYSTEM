#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;



// ==================== campus navigation.cpp MODULE ====================
namespace Campus {
#define MAX 10
#define INF 99999

class Campus
{
    string place[MAX];
    int graph[MAX][MAX];
    int n;

public:
    // Constructor
    Campus()
    {
        loadData();
    }
    // Initialize sample campus data
    void sampleData()
    {
        n = 10;
        place[0] = "Main Gate";
        place[1] = "Campus Building";
        place[2] = "Open Audi";
        place[3] = "Library";
        place[4] = "CSE Department";
        place[5] = "Gate 2";
        place[6] = "Parking";
        place[7] = "Canteen";
        place[8] = "Sports Ground";
        place[9] = "volleyball court";

        for(int i = 0; i < MAX; i++)
        {
            for(int j = 0; j < MAX; j++)
            {
                graph[i][j] = 0;
            }
        }
        addRoad(0, 1, 200);
        addRoad(1, 2, 150);
        addRoad(1, 3, 250);
        addRoad(2, 3, 100);
        addRoad(2, 4, 300);
        addRoad(3, 7, 150);
        addRoad(4, 8, 200);
        addRoad(5, 7, 180);
        addRoad(6, 7, 220);
        addRoad(0, 5, 350);
        addRoad(0, 6, 400);
        addRoad(1, 9, 180);
        addRoad(8, 9, 250);
    }
    // Add road between two locations
    void addRoad(int u, int v, int distance)
    {
        graph[u][v] = distance;
        graph[v][u] = distance;
    }
    // Save campus and road data into files
    void saveData()
    {
        ofstream fout("campus.txt");

        fout << n << endl;

        for(int i = 0; i < n; i++)
        {
            fout << place[i] << endl;
        }

        fout.close();
        ofstream roadFile("roads.txt");
        int count = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(graph[i][j] != 0)
                    count++;
            }
        }
        roadFile << count << endl;

        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)
            {
                if(graph[i][j] != 0)
                {
                    roadFile << i << " "
                             << j << " "
                             << graph[i][j] << endl;
                }
            }
        }
        roadFile.close();
        cout << "\nData saved successfully!";
    }
    // Load data from files
    void loadData()
    {
        ifstream fin("campus.txt");
        if(!fin || !(fin >> n) || n < 1 || n > MAX)
        {
            fin.close();
            cout << "\nSample data initialized.";
            sampleData();
            saveData();
            return;
        }
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool valid = true;

        for(int i = 0; i < n; i++)
        {
            if(!getline(fin, place[i]))
            {
                valid = false;
                break;
            }
        }
        fin.close();
        if(!valid)
        {
            sampleData();
            saveData();
            return;
        }
        // Initialize graph
        for(int i = 0; i < MAX; i++)
        {
            for(int j = 0; j < MAX; j++)
            {
                graph[i][j] = 0;
            }
        }
        // Load roads
        ifstream roadFile("roads.txt");
        int count, u, v, distance;
        if(!roadFile || !(roadFile >> count) || count < 0)
        {
            sampleData();
            saveData();
            return;
        }
        for(int i = 0; i < count; i++)
        {
            if(!(roadFile >> u >> v >> distance))
                break;

            if(u >= 0 && u < n &&
               v >= 0 && v < n &&
               u != v && distance > 0)
            {
                addRoad(u, v, distance);
            }
        }

        roadFile.close();

        cout << "\nCampus data loaded successfully!";
    }
    // Display campus locations
    void displayPlaces()
    {
        cout << "\n----- CAMPUS LOCATIONS -----\n";
        for(int i = 0; i < n; i++)
        {
            cout << i << " : " << place[i] << endl;
        }
    }
    // Display shortest route using Dijkstra
    void shortestPath(int source, int destination)
    {
        int dist[MAX];
        int visited[MAX] = {0};
        int parent[MAX];
        for(int i = 0; i < n; i++)
        {
            dist[i] = INF;
            parent[i] = -1;
        }
        dist[source] = 0;

        for(int count = 0; count < n - 1; count++)
        {
            int min = INF;
            int u = -1;
            for(int i = 0; i < n; i++)
            {
                if(!visited[i] && dist[i] < min)
                {
                    min = dist[i];
                    u = i;
                }
            }
            if(u == -1)
                break;
            visited[u] = 1;
            for(int v = 0; v < n; v++)
            {
                if(graph[u][v] != 0 && !visited[v])
                {
                    if(dist[u] + graph[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
        if(dist[destination] == INF)
        {
            cout << "\nNo route available!";
            return;
        }
        int path[MAX];
        int size = 0;
        int current = destination;
        while(current != -1)
        {
            path[size] = current;
            size++;
            current = parent[current];
        }
        cout << "\n----- SHORTEST ROUTE -----\n";

        for(int i = size - 1; i >= 0; i--)
        {
            cout << place[path[i]];

            if(i != 0)
                cout << " -> ";
        }
        cout << "\nTotal Distance: "
             << dist[destination] << " metres\n";
    }
    // Find route
    void navigation()
    {
        int source, destination;
        displayPlaces();
        cout << "\nEnter starting location number: ";
        cin >> source;

        cout << "Enter destination number: ";
        cin >> destination;

        if(source < 0 || source >= n ||
           destination < 0 || destination >= n)
        {
            cout << "\nInvalid location!";
            return;
        }
        shortestPath(source, destination);
    }
    // Add a new road
    void addNewRoad()
    {
        int u, v, distance;

        displayPlaces();

        cout << "\nEnter first location number: ";
        cin >> u;
        cout << "Enter second location number: ";
        cin >> v;
        cout << "Enter distance in metres: ";
        cin >> distance;
        if(u < 0 || u >= n ||
           v < 0 || v >= n ||
           u == v || distance <= 0)
        {
            cout << "\nInvalid road details!";
            return;
        }

        addRoad(u, v, distance);
        cout << "\nRoad added successfully!";
        saveData();
    }
};

}


// ==================== TEACHER DETAILS.cpp MODULE ====================
namespace Teacher {
struct Teacher {
    string name;
    string department;
    string room;
    string subject;
    string mobile;
};

class PasswordStack {
private:
    char items[100];
    int top;

public:
    PasswordStack() {
        top = -1;
    }

    void push(char ch) {
        if (top < 99) {
            items[++top] = ch;
        }
    }

    char pop() {
        if (top == -1) {
            return '\0';
        }
        return items[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

class TeacherDetails {
private:
    Teacher teachers[100];
    int count;
    string correctPassword = "gehu";

    // Save all teacher records in a file
    void saveToFile() {
        ofstream file("teachers.txt");

        if (!file) {
            cout << "Error opening file for saving.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            file << teachers[i].name << "|"
                 << teachers[i].department << "|"
                 << teachers[i].room << "|"
                 << teachers[i].subject << "|"
                 << teachers[i].mobile << "\n";
        }
        file.close();
        cout << "Teacher records saved to file.\n";
    }

    // Load teacher records from a file
    void loadFromFile() {
        ifstream file("teachers.txt");
        count = 0;

        if (!file) {
            // File does not exist, so create initial records
            teachers[0] = {"Dr. Deepak Singh Rana", "CSE",
                           "CS-329", "C Language", "9719924551"};
            teachers[1] = {"Prof. Ajay Shukla", "CSE",
                           "CS-05", "Data Structure", "8541682295"};
            teachers[2] = {"Dr. V P Dubey", "ECE",
                           "M-204", "Logic Design", "6398388206"};
            teachers[3] = {"Prof. Sunil Negi", "ECE",
                           "EC-110", "Digital Electronics", "9862446362"};
            teachers[4] = {"Ms. Sonali Gupta", "CSE",
                           "CS-101", "OOPs in Cpp", "8923400421"};
            teachers[5] = {"Dr. Mohit Payal", "ECE",
                           "M-204", "Logic Lab", "8958138501"};
            teachers[6] = {"Mr. Ajay Kumar Singh", "CIVIL",
                           "C-103", "Civil Lab", "9082373578"};
            count = 7;
            saveToFile();
            return;
        }
        string line;
        while (count < 100 && getline(file, line)) {
            Teacher t;
            int pos;
            pos = line.find('|');
            if (pos == string::npos) continue;
            t.name = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.department = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.room = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find('|');
            if (pos == string::npos) continue;
            t.subject = line.substr(0, pos);
            t.mobile = line.substr(pos + 1);

            teachers[count] = t;
            count++;
        }
        file.close();

        // Restore sample records if the file is empty
        if (count == 0) {
            teachers[0] = {"Dr. Deepak Singh Rana", "CSE",
                           "CS-329", "C Language", "9719924551"};
            teachers[1] = {"Prof. Ajay Shukla", "CSE",
                           "CS-05", "Data Structure", "8541682295"};
            teachers[2] = {"Dr. V P Dubey", "ECE",
                           "M-204", "Logic Design", "6398388206"};
            teachers[3] = {"Prof. Sunil Negi", "ECE",
                           "EC-110", "Digital Electronics", "9862446362"};
            teachers[4] = {"Ms. Sonali Gupta", "CSE",
                           "CS-101", "OOPs in Cpp", "8923400421"};
            teachers[5] = {"Dr. Mohit Payal", "ECE",
                           "M-204", "Logic Lab", "8958138501"};
            teachers[6] = {"Mr. Ajay Kumar Singh", "CIVIL",
                           "C-103", "Civil Lab", "9082373578"};
            count = 7;
            saveToFile();
        }
    }

    void printTeacher(const Teacher &t) {
        cout << "\nName: " << t.name
             << "\nDepartment: " << t.department
             << "\nRoom: " << t.room
             << "\nSubject: " << t.subject
             << "\nMobile: " << t.mobile << "\n";
        cout << "--------------------------\n";
    }

    bool checkPassword(string enteredPassword) {
        PasswordStack st;

        if (enteredPassword.length() != correctPassword.length()) {
            return false;
        }
        for (int i = 0; i < enteredPassword.length(); i++) {
            st.push(enteredPassword[i]);
        }
        for (int i = correctPassword.length() - 1; i >= 0; i--) {
            if (st.isEmpty() || st.pop() != correctPassword[i]) {
                return false;
            }
        }
        return st.isEmpty();
    }

public:
    TeacherDetails() {
        count = 0;
        loadFromFile();
    }
    void showTeachers() {
        cout << "\n--- ALL TEACHERS ---\n";

        for (int i = 0; i < count; i++) {
            printTeacher(teachers[i]);
        }
    }

    void searchTeacher() {
        string name;
        cout << "Enter teacher name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Please enter a name.\n";
            return;
        }
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (teachers[i].name.find(name) != string::npos) {
                printTeacher(teachers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Teacher not found.\n";
        }
    }

    void searchDepartment() {
        string department;

        cout << "Enter department: ";
        getline(cin, department);
        if (department.empty()) {
            cout << "Please enter a department.\n";
            return;
        }
        for (int i = 0; i < department.length(); i++) {
            if (department[i] >= 'a' && department[i] <= 'z') {
                department[i] = department[i] - 32;
            }
        }
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (teachers[i].department.find(department) != string::npos) {
                printTeacher(teachers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "No teacher found in this department.\n";
        }
    }

    void addTeacher() {
        string password;

        cout << "Enter password: ";
        getline(cin, password);
        if (!checkPassword(password)) {
            cout << "Wrong password! Access denied.\n";
            return;
        }
        cout << "Correct password! Access granted.\n";
        if (count >= 100) {
            cout << "Teacher list is full.\n";
            return;
        }
        Teacher t;
        cout << "Enter teacher name: ";
        getline(cin, t.name);
        cout << "Enter department: ";
        getline(cin, t.department);
        for (int i = 0; i < t.department.length(); i++) {
            if (t.department[i] >= 'a' && t.department[i] <= 'z') {
                t.department[i] = t.department[i] - 32;
            }
        }
        cout << "Enter room: ";
        getline(cin, t.room);
        cout << "Enter subject: ";
        getline(cin, t.subject);
        cout << "Enter mobile number: ";
        getline(cin, t.mobile);
        if (t.name.empty() || t.department.empty() || t.room.empty() || t.subject.empty() || t.mobile.empty()) {
            cout << "Details cannot be empty. Teacher not added.\n";
            return;
        }
        teachers[count] = t;
        count++;
        saveToFile();
        cout << "New teacher added successfully!\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== TEACHER DETAILS =====\n";
            cout << "1. View all teachers\n";
            cout << "2. Search by name\n";
            cout << "3. Search by department\n";
            cout << "4. Add new teacher\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter a valid number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
                case 1:
                    showTeachers();
                    break;
                case 2:
                    searchTeacher();
                    break;
                case 3:
                    searchDepartment();
                    break;
                case 4:
                    addTeacher();
                    break;
                case 0:
                    cout << "Program ended.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }
};

}


// ==================== NOTICE SYSTEM.cpp MODULE ====================
namespace Notice {
struct Notice {
    int id;
    string title;
    string category;
    string date;
    string message;
    Notice* next;
};
class NoticeSystem {
private:
    Notice* head;
    int nextId;
    void addToList(int id, string title, string category,string date, string message) {
        Notice* newNotice = new Notice;
        newNotice->id = id;
        newNotice->title = title;
        newNotice->category = category;
        newNotice->date = date;
        newNotice->message = message;
        newNotice->next = NULL;

        if (head == NULL) {
            head = newNotice;
        } else {
            Notice* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNotice;
        }
    }
    void saveNotices() {
        ofstream file("notices.txt");
        if (!file) {
            cout << "Error saving notices!\n";
            return;
        }

        Notice* temp = head;
        while (temp != NULL) {
            file << temp->id << '\n';
            file << temp->title << '\n';
            file << temp->category << '\n';
            file << temp->date << '\n';
            file << temp->message << '\n';
            temp = temp->next;
        }
        file.close();
    }
    void loadNotices() {
        ifstream file("notices.txt");
        if (!file) {
            return;
        }
        int id;
        string title, category, date, message;
        while (file >> id) {
            file.ignore();

            if (!getline(file, title) ||
                !getline(file, category) ||
                !getline(file, date) ||
                !getline(file, message)) {
                cout << "Incomplete notice data found.\n";
                break;
            }
            addToList(id, title, category, date, message);
            if (id >= nextId) {
                nextId = id + 1;
            }
        }
        file.close();
    }
    void addNotice() {
        int id = nextId++;
        string title, category, date, message;

        cout << "\nEnter notice title: ";
        getline(cin >> ws, title);
        cout << "Enter category: ";
        getline(cin, category);
        cout << "Enter date: ";
        getline(cin, date);
        cout << "Enter notice message: ";
        getline(cin, message);
        addToList(id, title, category, date, message);
        saveNotices();
        cout << "\nNotice saved successfully!\n";
        cout << "Notice ID: " << id << '\n';
    }

    void displayNotices() {
        if (head == NULL) {
            cout << "\nNo notices available.\n";
            return;
        }

        Notice* temp = head;
        cout << "\n CAMPUS NOTICES \n";
        while (temp != NULL) {
            cout << "\nID: " << temp->id;
            cout << "\nTitle: " << temp->title;
            cout << "\nCategory: " << temp->category;
            cout << "\nDate: " << temp->date;
            cout << "\nMessage: " << temp->message;
            cout << "\n--------------------------\n";
            temp = temp->next;
        }
    }
    void searchNotice() {
        string title;
        bool found = false;
        cout << "\nEnter title to search: ";
        getline(cin >> ws, title);

        Notice* temp = head;

        while (temp != NULL) {
            if (temp->title == title) {
                cout << "\nNotice found!\n";
                cout << "ID: " << temp->id << '\n';
                cout << "Category: " << temp->category << '\n';
                cout << "Date: " << temp->date << '\n';
                cout << "Message: " << temp->message << '\n';
                found = true;
            }

            temp = temp->next;
        }
        if (!found) {
            cout << "\nNotice not found.\n";
        }
    }
    void deleteNotice() {
        int id;
        cout << "\nEnter notice ID to delete: ";
        if (!(cin >> id)) {
            cout << "Invalid ID.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        Notice* temp = head;
        Notice* previous = NULL;

        while (temp != NULL && temp->id != id) {
            previous = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "\nNotice not found.\n";
            return;
        }
        if (previous == NULL) {
            head = temp->next;
        } else {
            previous->next = temp->next;
        }
        delete temp;
        saveNotices();
        cout << "\nNotice deleted successfully!\n";
    }
    void clearNotices() {
        while (head != NULL) {
            Notice* temp = head;
            head = head->next;
            delete temp;
        }
    }
void addSampleData()
{
    addToList(1, "Internal Examination",
              "Academic", "20-11-2026",
              "Examinations begin from 25 November.");

    addToList(2, "Annual Sports Meet",
              "Sports", "22-11-2026",
              "Sports registrations are open.");

    addToList(3, "Coding Competition",
              "Events", "23-11-2026",
              "Coding competition in computer lab.");

    saveNotices();
}
public:
    NoticeSystem() {
        head = NULL;
        nextId = 1;
        loadNotices();
    }
    void menu() {
        int choice;
        do {
            cout << "\nSMART CAMPUS NOTICE SYSTEM \n";
            cout << "1. Add Notice\n";
            cout << "2. Display Notices\n";
            cout << "3. Search Notice\n";
            cout << "4. Delete Notice\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";

            if (!(cin >> choice)) {
                cout << "Enter a valid number.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            switch (choice) {
                case 1:
                    addNotice();
                    break;
                case 2:
                    displayNotices();
                    break;
                case 3:
                    searchNotice();
                    break;
                case 4:
                    deleteNotice();
                    break;
                case 0:
                    cout << "\nBYE!\n";
                    break;
                default:
                    cout << "\nInvalid choice.\n";
            }
        } while (choice != 0);
    }
    ~NoticeSystem() {
        clearNotices();
    }
};

}


// ==================== LOST AND FOUND.cpp MODULE ====================
namespace LostFound {
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char ch) {
                  return tolower(ch);
              });

    return str;
}
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

        loadFromFile();
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

    void saveToFile() {
        ofstream file("lostfound.txt");

        if (!file) {
            cout << "Error opening file!\n";
            return;
        }

        LostItem *current = head;

        while (current != NULL) {
            file << current->itemName << "|"
                 << current->place << "|"
                 << current->status << "\n";

            current = current->next;
        }

        file.close();
    }
    void loadFromFile() {
        ifstream file("lostfound.txt");

        if (!file)
            return;

        string line;

        while (getline(file, line)) {
            stringstream ss(line);

            LostItem *node = new LostItem;

            getline(ss, node->itemName, '|');
            getline(ss, node->place, '|');
            getline(ss, node->status);

            node->next = NULL;

            if (head == NULL) {
                head = node;
                tail = node;
            }
            else {
                tail->next = node;
                tail = node;
            }

            count++;
        }

        file.close();

        if (count > 0) {
            cout << count
                 << " previous records loaded successfully!\n";
        }
    }
    void reportItem() {
        LostItem *node = new LostItem;

        cout << "Enter item name: ";
        getline(cin, node->itemName);

        cout << "Enter place where it was lost/found: ";
        getline(cin, node->place);

        do {
            cout << "Enter status (LOST or FOUND): ";
            getline(cin, node->status);

            node->status = toLower(node->status);

            if (node->status != "lost" &&
                node->status != "found") {
                cout << "Enter LOST or FOUND only!\n";
            }

        } while (node->status != "lost" &&
                 node->status != "found");

        node->next = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }

        count++;

        saveToFile();

        cout << "Item report added successfully!\n";
    }

   
    void showItems() {
        if (count == 0) {
            cout << "No lost or found items reported yet.\n";
            return;
        }

        cout << "\n-LOST AND FOUND RECORDS-\n";

        LostItem *current = head;
        int number = 1;

        while (current != NULL) {
            cout << number << ". Item: "
                 << current->itemName
                 << " | Place: " << current->place
                 << " | Status: "
                 << (current->status == "lost" ? "LOST" : "FOUND")
                 << '\n';

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

        cout << "\n- NEWEST REPORTS FIRST-\n";

        int number = 1;

        while (top >= 0) {
            LostItem *item = stack[top];
            top--;

            cout << number << ". Item: "
                 << item->itemName
                 << " | Place: " << item->place
                 << " | Status: "
                 << (item->status == "lost" ? "LOST" : "FOUND")
                 << '\n';

            number++;
        }

        delete[] stack;
    }
    void searchItem() {
        if (head == NULL) {
            cout << "No records available!\n";
            return;
        }

        string name;

        cout << "Enter item name to search: ";
        getline(cin, name);

        LostItem *current = head;
        bool found = false;
        int number = 1;

        while (current != NULL) {

            if (toLower(current->itemName) == toLower(name)) {

                cout << "\nItem found!\n";

                cout << "Record number: " << number << endl;
                cout << "Item: " << current->itemName << endl;
                cout << "Place: " << current->place << endl;

                cout << "Status: "
                     << (current->status == "lost" ? "LOST" : "FOUND")
                     << endl;

                found = true;
            }

            current = current->next;
            number++;
        }

        if (!found) {
            cout << "Item not found!\n";
        }
    }
    void updateStatus() {
        if (head == NULL) {
            cout << "No records available!\n";
            return;
        }

        string name;

        cout << "Enter item name to update: ";
        getline(cin, name);

        LostItem *current = head;
        
        bool found = false;

        while (current != NULL) {

            if (toLower(current->itemName) == toLower(name)) {

                found = true;

                cout << "\nItem: " << current->itemName << endl;
                cout << "Place: " << current->place << endl;

                cout << "Current status: "
                     << (current->status == "lost" ? "LOST" : "FOUND")
                     << endl;

                cout << "Enter new status (LOST or FOUND): ";

                string newStatus;
                getline(cin, newStatus);

                newStatus = toLower(newStatus);

                while (newStatus != "lost" &&
                       newStatus != "found") {

                    cout << "Invalid status! Enter LOST or FOUND: ";
                    getline(cin, newStatus);

                    newStatus = toLower(newStatus);
                }

                current->status = newStatus;

                saveToFile();

                cout << "Status updated successfully!\n";
            }

            current = current->next;
        }

        if (!found) {
            cout << "Item not found!\n";
        }
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
            cout << "\n- LOST AND FOUND -\n";

            cout << "1. Report a lost/found item\n";
            cout << "2. View all reports\n";
            cout << "3. View newest reports first\n";
            cout << "4. Search an item\n";
            cout << "5. Update item status\n";
            cout << "6. Help / Contact Information\n";
            cout << "0. Back\n";

            if (!readChoice("Enter choice: ", choice)) {
                choice = -1;
                continue;
            }

            if (choice == 1)
                reportItem();

            else if (choice == 2)
                showItems();

            else if (choice == 3)
                showNewestFirst();

            else if (choice == 4)
                searchItem();

            else if (choice == 5)
                updateStatus();

            else if (choice == 6)
                showHelp();

            else if (choice != 0)
                cout << "Invalid choice.\n";

        } while (choice != 0);
    }
};

}


// ==================== LIBRARY MANAGEMENT SYSTEM.cpp MODULE ====================
namespace LibraryModule {
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

}


// ==================== HOSTEL_MANAGEMENT.cpp MODULE ====================
namespace Hostel {
struct Student
{
    int id;
    string name;
    string branch;
    int year;
    int roomNo;
    Student *next;
};

struct Room
{
    int roomNo;
    int year;
    int capacity;
    int occupied;
};

Student *head = NULL;
Room rooms[40];

int readInt(string message)
{
    int value;

    while(true)
    {
        cout << message;

        if(cin >> value)
            return value;

        cout << "Invalid input! Enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Initialize rooms
void initializeRooms()
{
    int k = 0;

    for(int i = 1; i <= 4; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            rooms[k].roomNo = i * 100 + j;
            rooms[k].year = i;

            if(i == 1)
                rooms[k].capacity = 3;
            else if(i == 2)
                rooms[k].capacity = 2;
            else
                rooms[k].capacity = 1;

            rooms[k].occupied = 0;
            k++;
        }
    }
}

int findRoom(int roomNo)
{
    for(int i = 0; i < 40; i++)
    {
        if(rooms[i].roomNo == roomNo)
            return i;
    }

    return -1;
}

Student* searchStudent(int id)
{
    Student *temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

void saveData()
{
    ofstream file("hostel.txt");

    if(!file)
    {
        cout << "Error saving data!\n";
        return;
    }

    Student *temp = head;

    while(temp != NULL)
    {
        file << temp->id << "|"
             << temp->name << "|"
             << temp->branch << "|"
             << temp->year << "|"
             << temp->roomNo << endl;

        temp = temp->next;
    }

    file.close();
}
void loadData()
{
    ifstream file("hostel.txt");

    if(!file)
        return;

    string line;

    while(getline(file, line))
    {
        stringstream ss(line);

        string id, name, branch, year, roomNo;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, branch, '|');
        getline(ss, year, '|');
        getline(ss, roomNo, '|');

        try
        {
            int studentID = stoi(id);
            int studentYear = stoi(year);
            int studentRoom = stoi(roomNo);

            if(studentYear < 1 || studentYear > 4 ||
               studentRoom < 0 ||
               searchStudent(studentID) != NULL)
            {
                continue;
            }

            int index = -1;

            if(studentRoom != 0)
            {
                index = findRoom(studentRoom);

                if(index == -1 ||
                   rooms[index].year != studentYear ||
                   rooms[index].occupied >= rooms[index].capacity)
                {
                    continue;
                }

                rooms[index].occupied++;
            }

            Student *newnode = new Student;

            newnode->id = studentID;
            newnode->name = name;
            newnode->branch = branch;
            newnode->year = studentYear;
            newnode->roomNo = studentRoom;

            newnode->next = head;
            head = newnode;
        }
        catch(...)
        {
            continue;
        }
    }

    file.close();
}

void addStudent()
{
    Student *newnode = new Student;

    newnode->id = readInt("\nEnter Student ID: ");

    if(searchStudent(newnode->id) != NULL)
    {
        cout << "Student ID already exists!\n";
        delete newnode;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Student Name: ";
    getline(cin, newnode->name);

    cout << "Enter Branch: ";
    getline(cin, newnode->branch);

    newnode->year = readInt("Enter Year (1-4): ");

    if(newnode->year < 1 || newnode->year > 4)
    {
        cout << "Invalid year!\n";
        delete newnode;
        return;
    }

    newnode->roomNo = 0;

    newnode->next = head;
    head = newnode;

    saveData();

    cout << "\nStudent registered successfully!";
    cout << "\nPlease allocate a room using Option 2.\n";
}

void allocateRoom()
{
    int id = readInt("\nEnter Student ID: ");

    Student *temp = searchStudent(id);

    if(temp == NULL)
    {
        cout << "Student not found!\n";
        return;
    }

    if(temp->roomNo != 0)
    {
        cout << "Student already has Room "
             << temp->roomNo << endl;
        return;
    }

    cout << "\n1. Automatic Allocation";
    cout << "\n2. Manual Allocation\n";

    int choice = readInt("Enter choice: ");

    int index = -1;

    if(choice == 1)
    {
        for(int i = 0; i < 40; i++)
        {
            if(rooms[i].year == temp->year &&
               rooms[i].occupied < rooms[i].capacity)
            {
                index = i;
                break;
            }
        }
    }

    else if(choice == 2)
    {
        int roomNo = readInt("Enter Room Number: ");

        index = findRoom(roomNo);

        if(index != -1)
        {
            if(rooms[index].year != temp->year ||
               rooms[index].occupied >= rooms[index].capacity)
            {
                index = -1;
            }
        }
    }

    else
    {
        cout << "Invalid choice!\n";
        return;
    }

    if(index == -1)
    {
        cout << "No suitable room available!\n";
        return;
    }

    temp->roomNo = rooms[index].roomNo;
    rooms[index].occupied++;

    saveData();

    cout << "\nRoom allocated successfully!";
    cout << "\nAllocated Room: " << temp->roomNo << endl;
}

void vacantRooms()
{
    bool found = false;

    cout << "\n-- VACANT ROOMS --\n";

    for(int i = 0; i < 40; i++)
    {
        if(rooms[i].occupied < rooms[i].capacity)
        {
            found = true;

            cout << "\nRoom Number: " << rooms[i].roomNo;
            cout << "\nYear: " << rooms[i].year;
            cout << "\nAvailable Beds: "
                 << rooms[i].capacity - rooms[i].occupied;
            cout << "\n----------------------\n";
        }
    }

    if(!found)
        cout << "No vacant beds available!\n";
}

void searchByID()
{
    int id = readInt("\nEnter Student ID: ");

    Student *temp = searchStudent(id);

    if(temp == NULL)
    {
        cout << "Student not found!\n";
        return;
    }

    cout << "\n--- STUDENT DETAILS ---";
    cout << "\nID: " << temp->id;
    cout << "\nName: " << temp->name;
    cout << "\nBranch: " << temp->branch;
    cout << "\nYear: " << temp->year;

    if(temp->roomNo == 0)
        cout << "\nRoom: Not Allocated\n";
    else
        cout << "\nRoom: " << temp->roomNo << endl;
}
void roomDetails()
{
    int roomNo = readInt("\nEnter Room Number: ");

    int index = findRoom(roomNo);

    if(index == -1)
    {
        cout << "Room not found!\n";
        return;
    }

    cout << "\n--- ROOM DETAILS ---";
    cout << "\nRoom Number: " << rooms[index].roomNo;
    cout << "\nYear: " << rooms[index].year;
    cout << "\nCapacity: " << rooms[index].capacity;
    cout << "\nOccupied: " << rooms[index].occupied;
    cout << "\nAvailable Beds: "
         << rooms[index].capacity - rooms[index].occupied;

    cout << "\n\nStudents in this room:\n";
    Student *temp = head;
    bool found = false;

    while(temp != NULL)
    {
        if(temp->roomNo == roomNo)
        {
            cout << "ID: " << temp->id
                 << " | Name: " << temp->name << endl;

            found = true;
        }

        temp = temp->next;
    }

    if(!found)
        cout << "No students allocated.\n";
}

void checkOut()
{
    int id = readInt("\nEnter Student ID: ");

    Student *temp = head;
    Student *prev = NULL;

    while(temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        cout << "Student not found!\n";
        return;
    }

    if(temp->roomNo != 0)
    {
        int index = findRoom(temp->roomNo);

        if(index != -1)
            rooms[index].occupied--;
    }

    if(prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    delete temp;

    saveData();

    cout << "Student checked out successfully!\n";
}


void displayStudents()
{
    Student *temp = head;

    if(temp == NULL)
    {
        cout << "\nNo students registered!\n";
        return;
    }
    cout << "\n--- ALL HOSTEL STUDENTS ---\n";

    while(temp != NULL)
    {
        cout << "\nStudent ID: " << temp->id;
        cout << "\nName: " << temp->name;
        cout << "\nBranch: " << temp->branch;
        cout << "\nYear: " << temp->year;

        if(temp->roomNo == 0)
            cout << "\nRoom: Not Allocated\n";
        else
            cout << "\nRoom: " << temp->roomNo << endl;

        temp = temp->next;
    }
}

}


// ==================== COMPLAINTS CODE.cpp MODULE ====================
namespace Complaints {
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

}


// ==================== CLUB INFORMATION.cpp MODULE ====================
namespace Clubs {
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
    const string ADMIN_PASSWORD = "admin123";
    const string FILE_NAME = "clubs.txt";

    string toLowerCase(string text) {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) {
                      return tolower(c);
                  });
        return text;
    }

    void displayClub(const Club &c) {
        cout << "\nClub: " << c.name;
        cout << "\nActivities: " << c.activity;
        cout << "\nContact: " << c.contact << "\n";
    }

    void saveToFile() {
        ofstream file(FILE_NAME);

        if (!file) {
            cout << "Error: Could not save club data to file.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            file << clubs[i].name << '\n';
            file << clubs[i].activity << '\n';
            file << clubs[i].contact << '\n';
        }

        file.close();
    }

    bool loadFromFile() {
        ifstream file(FILE_NAME);

        if (!file) {
            return false;
        }

        string name, activity, contact;

        while (count < MAX_CLUBS &&
               getline(file, name) &&
               getline(file, activity) &&
               getline(file, contact)) {
            clubs[count].name = name;
            clubs[count].activity = activity;
            clubs[count].contact = contact;
            count++;
        }

        file.close();
        return count > 0;
    }

    void loadDefaultClubs() {
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

        saveToFile();
    }

public:
    ClubInformation() {
        count = 0;

        if (!loadFromFile()) {
            loadDefaultClubs();
        }
    }

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

    void addNewClub() {
        string password;

        cout << "Enter admin password: ";
        getline(cin, password);

        if (password != ADMIN_PASSWORD) {
            cout << "Access denied! Only admin can add clubs.\n";
            return;
        }

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
        saveToFile();

        cout << "Club added and saved successfully!\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== CLUB INFORMATION SYSTEM =====\n";
            cout << "1. View All Clubs\n";
            cout << "2. Search by Club Name\n";
            cout << "3. Search by Activity\n";
            cout << "4. Add New Club (Admin Only)\n";
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

}


// ==================== MODULE ENTRY FUNCTIONS ====================

void campusMenu()
{
    Campus::Campus c;
    int choice;
    do
    {
        cout << "\n\n===== GEHU CAMPUS NAVIGATION =====\n";
        cout << "1. View Campus Locations\n";
        cout << "2. Find Shortest Route\n";
        cout << "3. Add New Road\n";
        cout << "4. Save Campus Data\n";
        cout << "5. Reload Campus Data\n";
        cout << "6. Back to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1: c.displayPlaces(); break;
            case 2: c.navigation(); break;
            case 3: c.addNewRoad(); break;
            case 4: c.saveData(); break;
            case 5: c.loadData(); break;
            case 6: cout << "\nReturning to Smart Campus menu."; break;
            default: cout << "\nInvalid choice!";
        }
    } while(choice != 6);
}

void teacherMenu()
{
    Teacher::TeacherDetails module;
    module.menu();
}
void noticeMenu()
{
    Notice::NoticeSystem module;
    module.menu();
}
void lostFoundMenu()
{
    LostFound::LostAndFound module;
    module.menu();
}
void libraryMenu()
{
    LibraryModule::Library module;
    module.menu();
}
void hostelMenu()
{
    static bool initialized = false;
    if (!initialized)
    {
        Hostel::initializeRooms();
        Hostel::loadData();
        initialized = true;
    }
    int choice;
    do
    {
        cout << "\n      HOSTEL MANAGEMENT SYSTEM";
        cout << "\n1. Add Student";
        cout << "\n2. Room Allocation";
        cout << "\n3. Display Vacant Rooms";
        cout << "\n4. Search Student";
        cout << "\n5. Room Details";
        cout << "\n6. Check Out Student";
        cout << "\n7. Display All Students";
        cout << "\n8. Back to Main Menu";
        cout << "\n================================\n";
        choice = Hostel::readInt("Enter your choice: ");
        switch(choice)
        {
            case 1: Hostel::addStudent(); break;
            case 2: Hostel::allocateRoom(); break;
            case 3: Hostel::vacantRooms(); break;
            case 4: Hostel::searchByID(); break;
            case 5: Hostel::roomDetails(); break;
            case 6: Hostel::checkOut(); break;
            case 7: Hostel::displayStudents(); break;
            case 8:
                Hostel::saveData();
                cout << "\nData saved successfully!";
                cout << "\nReturning to main menu...\n";
                break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 8);
}
void complaintMenu()
{
    Complaints::ComplaintPortal module;
    module.menu();
}
void clubMenu()
{
    Clubs::ClubInformation module;
    module.menu();
}

int main()
{
    int choice;
    do
    {
        cout << "\n==============================================\n";
        cout << "       SMART CAMPUS SERVICE SYSTEM\n";
        cout << "==============================================\n";
        cout << "1. Campus Navigation\n";
        cout << "2. Teacher Details\n";
        cout << "3. Notice System\n";
        cout << "4. Lost and Found\n";
        cout << "5. Library Management\n";
        cout << "6. Hostel Management\n";
        cout << "7. Complaint and Anti-Ragging Portal\n";
        cout << "8. Club Information\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice)
        {
            case 1: campusMenu(); break;
            case 2: teacherMenu(); break;
            case 3: noticeMenu(); break;
            case 4: lostFoundMenu(); break;
            case 5: libraryMenu(); break;
            case 6: hostelMenu(); break;
            case 7: complaintMenu(); break;
            case 8: clubMenu(); break;
            case 0:
                cout << "\nThank you for using Smart Campus Service System!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 0);

    return 0;
}
