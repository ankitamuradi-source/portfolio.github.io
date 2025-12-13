#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Vertex represents a location in the city
struct Vertex {
    string name;
    Vertex(string n) : name(n) {}
};

// Edge represents a route between two locations with distance
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Graph class for route optimization using Dijkstra's algorithm
class Graph {
private:
    vector<Vertex> locations;
    vector<vector<Edge>> adjList;

public:
    void addLocation(string name) {
        locations.push_back(Vertex(name));
        adjList.push_back(vector<Edge>());
    }

    void addRoute(int from, int to, int distance) {
        adjList[from].push_back(Edge(to, distance));
        adjList[to].push_back(Edge(from, distance)); // bidirectional
    }

    void displayLocations() {
        cout << "City Locations:\n";
        for (size_t i = 0; i < locations.size(); i++) {
            cout << i << " - " << locations[i].name << endl;
        }
    }

    void displayRoutes() {
        cout << "\nCity Routes:\n";
        for (size_t i = 0; i < adjList.size(); i++) {
            cout << locations[i].name << " -> ";
            for (auto e : adjList[i])
                cout << locations[e.to].name << "(" << e.weight << "km) ";
            cout << endl;
        }
    }

    // Dijkstra's algorithm for shortest path
    vector<int> shortestPath(int src) {
        int n = locations.size();
        vector<int> dist(n, INT_MAX);
        vector<bool> visited(n, false);
        dist[src] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                    u = i;
            }

            if (dist[u] == INT_MAX) break;
            visited[u] = true;

            for (auto e : adjList[u]) {
                if (dist[u] + e.weight < dist[e.to])
                    dist[e.to] = dist[u] + e.weight;
            }
        }
        return dist;
    }

    void displayShortestPaths(int src) {
        vector<int> distances = shortestPath(src);
        cout << "\nShortest distances from " << locations[src].name << ":\n";
        for (size_t i = 0; i < distances.size(); i++) {
            cout << "To " << locations[i].name << " : " << distances[i] << " km\n";
        }
    }
};

// Vehicle class
class Vehicle {
private:
    int id;
    string type;
    int capacity;
    int currentLoad;
    string location;

public:
    Vehicle(int id, string type, int capacity, string loc)
        : id(id), type(type), capacity(capacity), location(loc), currentLoad(0) {}

    void display() {
        cout << setw(5) << id
             << setw(15) << type
             << setw(10) << capacity
             << setw(10) << currentLoad
             << setw(15) << location << endl;
    }

    int getId() const { return id; }
    string getLocation() const { return location; }

    void moveTo(string newLoc) { location = newLoc; }
    bool assignPassengers(int n) {
        if (currentLoad + n <= capacity) {
            currentLoad += n;
            return true;
        }
        return false;
    }

    void releasePassengers() { currentLoad = 0; }
};

// Customer class
class Customer {
private:
    int id;
    string name;
    string pickup;
    string drop;

public:
    Customer(int id, string name, string pickup, string drop)
        : id(id), name(name), pickup(pickup), drop(drop) {}

    void display() {
        cout << setw(5) << id
             << setw(15) << name
             << setw(15) << pickup
             << setw(15) << drop << endl;
    }

    string getPickup() { return pickup; }
    string getDrop() { return drop; }
    int getId() { return id; }
};

// Smart Transport Platform
class SmartTransportApp {
private:
    Graph cityGraph;
    vector<Vehicle> vehicles;
    vector<Customer> customers;
    double revenue;

public:
    SmartTransportApp() { revenue = 0; }

    void setupCity() {
        // Add locations
        cityGraph.addLocation("Downtown");
        cityGraph.addLocation("Uptown");
        cityGraph.addLocation("Station");
        cityGraph.addLocation("Airport");
        cityGraph.addLocation("Mall");
        cityGraph.addLocation("University");

        // Add routes
        cityGraph.addRoute(0, 1, 5);
        cityGraph.addRoute(0, 2, 3);
        cityGraph.addRoute(1, 3, 10);
        cityGraph.addRoute(2, 3, 6);
        cityGraph.addRoute(2, 4, 4);
        cityGraph.addRoute(4, 5, 7);
    }

    void setupVehicles() {
        vehicles.push_back(Vehicle(1, "Bus", 40, "Downtown"));
        vehicles.push_back(Vehicle(2, "Van", 12, "Station"));
        vehicles.push_back(Vehicle(3, "Taxi", 4, "Uptown"));
        vehicles.push_back(Vehicle(4, "Bus", 35, "Mall"));
    }

    void setupCustomers() {
        customers.push_back(Customer(1, "Alice", "Downtown", "Airport"));
        customers.push_back(Customer(2, "Bob", "Uptown", "Mall"));
        customers.push_back(Customer(3, "Charlie", "Station", "University"));
        customers.push_back(Customer(4, "Diana", "Mall", "Downtown"));
        customers.push_back(Customer(5, "Eve", "University", "Airport"));
    }

    void displayVehicles() {
        cout << setw(5) << "ID" << setw(15) << "Type" << setw(10) << "Capacity" 
             << setw(10) << "Load" << setw(15) << "Location" << endl;
        for (auto &v : vehicles) v.display();
    }

    void displayCustomers() {
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Pickup" 
             << setw(15) << "Drop" << endl;
        for (auto &c : customers) c.display();
    }

    Vehicle* findNearestVehicle(string location) {
        Vehicle* nearest = nullptr;
        for (auto &v : vehicles) {
            if (v.getLocation() == location) return &v;
            if (!nearest) nearest = &v;
        }
        return nearest;
    }

    void assignRides() {
        cout << "\n--- Assigning Rides ---\n";
        for (auto &c : customers) {
            Vehicle* v = findNearestVehicle(c.getPickup());
            if (v && v->assignPassengers(1)) {
                cout << "Assigned " << c.getId() << " to Vehicle " << v->getId() << endl;
                v->moveTo(c.getDrop());
                revenue += 50; // flat fare
            } else {
                cout << "No vehicle available for Customer " << c.getId() << endl;
            }
        }
    }

    void simulateDay() {
        cout << "\n--- Vehicles Status ---\n";
        displayVehicles();
        cout << "\n--- Customers ---\n";
        displayCustomers();

        assignRides();

        cout << "\n--- Revenue ---\n";
        cout << "Today's Revenue: ₹" << revenue << endl;

        for (auto &v : vehicles) v.releasePassengers();
    }

    void runDemo() {
        setupCity();
        setupVehicles();
        setupCustomers();
        cityGraph.displayLocations();
        cityGraph.displayRoutes();
        cityGraph.displayShortestPaths(0); // from Downtown
        simulateDay();
    }
};

int main() {
    SmartTransportApp app;
    app.runDemo();
    return 0;
}

