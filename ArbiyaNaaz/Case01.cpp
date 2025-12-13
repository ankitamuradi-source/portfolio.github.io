#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = numeric_limits<int>::max();

// -------------------- Package Class --------------------
class Package {
public:
    int id;
    string description;
    int source;
    int destination;
    bool delivered;

    Package(int pid, string desc, int src, int dest)
        : id(pid), description(desc), source(src), destination(dest), delivered(false) {}

    void display() {
        cout << "Package ID: " << id
             << ", Description: " << description
             << ", Source: " << source
             << ", Destination: " << destination
             << ", Status: " << (delivered ? "Delivered" : "Pending") << endl;
    }
};

// -------------------- Delivery Vehicle Class --------------------
class DeliveryVehicle {
public:
    string name;
    int capacity;
    vector<int> route; // Node IDs for current route

    DeliveryVehicle(string n, int cap) : name(n), capacity(cap) {}

    void display() {
        cout << "Vehicle: " << name << ", Capacity: " << capacity << ", Current Route: ";
        for (int node : route) cout << node << " ";
        cout << endl;
    }
};

// -------------------- Graph Class --------------------
class Graph {
public:
    int nodes;
    vector<vector<pair<int, int>>> adj; // node -> {neighbor, weight}

    Graph(int n) : nodes(n) {
        adj.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Assuming undirected graph
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(nodes, INF);
        dist[src] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            if (d > dist[u]) continue;

            for (auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    void displayGraph() {
        cout << "Graph Adjacency List:" << endl;
        for (int i = 0; i < nodes; i++) {
            cout << i << ": ";
            for (auto &edge : adj[i]) cout << "(" << edge.first << ", " << edge.second << ") ";
            cout << endl;
        }
    }
};

// -------------------- Logistics Hub --------------------
class LogisticsHub {
private:
    Graph graph;
    vector<Package> packages;
    vector<DeliveryVehicle> vehicles;
    int nextPackageId;

public:
    LogisticsHub(int n) : graph(n), nextPackageId(1) {}

    void addEdge(int u, int v, int w) {
        graph.addEdge(u, v, w);
    }

    void addPackage(string desc, int src, int dest) {
        packages.push_back(Package(nextPackageId++, desc, src, dest));
        cout << "Package added successfully.\n";
    }

    void addVehicle(string name, int capacity) {
        vehicles.push_back(DeliveryVehicle(name, capacity));
        cout << "Vehicle added successfully.\n";
    }

    void listPackages() {
        cout << "All Packages:\n";
        for (auto &p : packages) p.display();
    }

    void listVehicles() {
        cout << "All Vehicles:\n";
        for (auto &v : vehicles) v.display();
    }

    void displayGraph() {
        graph.displayGraph();
    }

    void deliverPackage(int packageId) {
        for (auto &p : packages) {
            if (p.id == packageId) {
                vector<int> dist = graph.dijkstra(p.source);
                if (dist[p.destination] == INF) {
                    cout << "No route available from " << p.source << " to " << p.destination << endl;
                    return;
                }
                cout << "Delivering package via shortest path. Distance: " << dist[p.destination] << endl;
                p.delivered = true;
                return;
            }
        }
        cout << "Package ID not found.\n";
    }

    void menu() {
        while (true) {
            cout << "\n----- Logistics Hub Menu -----\n";
            cout << "1. Add Package\n";
            cout << "2. Add Delivery Vehicle\n";
            cout << "3. List Packages\n";
            cout << "4. List Vehicles\n";
            cout << "5. Display Graph\n";
            cout << "6. Deliver Package\n";
            cout << "7. Exit\n";
            cout << "Choose an option: ";
            int choice; cin >> choice;

            if (choice == 1) {
                string desc; int src, dest;
                cout << "Package Description: "; cin.ignore(); getline(cin, desc);
                cout << "Source Node: "; cin >> src;
                cout << "Destination Node: "; cin >> dest;
                addPackage(desc, src, dest);
            } else if (choice == 2) {
                string name; int cap;
                cout << "Vehicle Name: "; cin.ignore(); getline(cin, name);
                cout << "Capacity: "; cin >> cap;
                addVehicle(name, cap);
            } else if (choice == 3) {
                listPackages();
            } else if (choice == 4) {
                listVehicles();
            } else if (choice == 5) {
                displayGraph();
            } else if (choice == 6) {
                int pid;
                cout << "Enter Package ID to deliver: "; cin >> pid;
                deliverPackage(pid);
            } else if (choice == 7) {
                cout << "Exiting Logistics Hub...\n";
                break;
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

// -------------------- Main Function --------------------
int main() {
    cout << "=== Welcome to Logistics Hub Simulation ===\n";
    int n;
    cout << "Enter number of nodes in city graph: ";
    cin >> n;

    LogisticsHub hub(n);

    cout << "Enter number of edges: ";
    int e;
    cin >> e;
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        hub.addEdge(u, v, w);
    }

    hub.menu();

    return 0;
}

