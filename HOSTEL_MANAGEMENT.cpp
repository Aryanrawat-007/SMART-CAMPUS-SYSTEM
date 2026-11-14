
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

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
int main()
{
    initializeRooms();
    loadData();

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
        cout << "\n8. Exit";

        cout << "\n================================\n";

        choice = readInt("Enter your choice: ");

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                allocateRoom();
                break;

            case 3:
                vacantRooms();
                break;

            case 4:
                searchByID();
                break;

            case 5:
                roomDetails();
                break;

            case 6:
                checkOut();
                break;

            case 7:
                displayStudents();
                break;

            case 8:
                saveData();
                cout << "\nData saved successfully!";
                cout << "\nExiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    }while(choice != 8);

    return 0;
}
