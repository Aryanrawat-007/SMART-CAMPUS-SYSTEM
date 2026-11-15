
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

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
        place[1] = "Admin Block";
        place[2] = "CSE Department";
        place[3] = "Library";
        place[4] = "Auditorium";
        place[5] = "Boys Hostel";
        place[6] = "Girls Hostel";
        place[7] = "Canteen";
        place[8] = "Sports Ground";
        place[9] = "Medical Centre";

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

int main()
{
    Campus c;

    int choice;

    do
    {
        cout << "\n\n===== GEHU CAMPUS NAVIGATION =====\n";

        cout << "1. View Campus Locations\n";
        cout << "2. Find Shortest Route\n";
        cout << "3. Add New Road\n";
        cout << "4. Save Campus Data\n";
        cout << "5. Reload Campus Data\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                c.displayPlaces();
                break;

            case 2:
                c.navigation();
                break;

            case 3:
                c.addNewRoad();
                break;

            case 4:
                c.saveData();
                break;

            case 5:
                c.loadData();
                break;

            case 6:
                cout << "\nThank you for using GEHU Navigation!";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while(choice != 6);

    return 0;
}
