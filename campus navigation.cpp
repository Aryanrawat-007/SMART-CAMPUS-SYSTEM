
#include <iostream>
#include <string>
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

        // Initialize graph with zero
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                graph[i][j] = 0;
            }
        }
        // Connecting campus locations
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
    // Display all campus locations
    void displayPlaces()
    {
        cout << "\n----- CAMPUS LOCATIONS -----\n";

        for(int i = 0; i < n; i++)
        {
            cout << i << " : " << place[i] << endl;
        }
    }
    // Find shortest route using Dijkstra
    void shortestPath(int source, int destination)
    {
        int dist[MAX];
        int visited[MAX] = {0};
        int parent[MAX];

        // Initialize distances
        for(int i = 0; i < n; i++)
        {
            dist[i] = INF;
            parent[i] = -1;
        }
        dist[source] = 0;

        // Dijkstra algorithm
        for(int count = 0; count < n - 1; count++)
        {
            int min = INF;
            int u = -1;

            // Find nearest unvisited location
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

            // Update neighbouring locations
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

        // Check if destination is reachable
        if(dist[destination] == INF)
        {
            cout << "\nNo route available!";
            return;
        }
        // Store route
        int path[MAX];
        int size = 0;

        int current = destination;
        while(current != -1)
        {
            path[size] = current;
            size++;
            current = parent[current];
        }

        // Display route in correct order
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
    // Navigation menu
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
        cout << "3. Exit\n";
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
                cout << "\nThank you!";
                break;
            default:
                cout << "\nInvalid choice!";
        }

    } while(choice != 3);

    return 0;
}
