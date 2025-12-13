// ================================================================
// SMART TRAFFIC AUTOMATION & INCIDENT DETECTION SYSTEM
// Author: Ankita
// Language: C++
// Purpose: Academic / DAA Project (Smart City Business Idea)
// Algorithms Covered:
//   1. Dijkstra's Algorithm (Shortest Path / Routing)
//   2. Prim's Algorithm (Minimum Spanning Tree - Signal Connectivity)
//   3. Greedy Algorithm (Traffic Signal Timing Optimization)
//   4. BFS / DFS (Incident Detection & Zone Analysis)
// ================================================================

#include <bits/stdc++.h>
using namespace std;

// ================================================================
// DATA STRUCTURES
// ================================================================

struct Road {
    int to;
    int distance;
    int trafficDensity;
};

struct Incident {
    int node;
    string type;
};

const int INF = 1e9;

// ================================================================
// GRAPH CLASS FOR CITY ROAD NETWORK
// ================================================================

class CityGraph {
private:
    int V; // number of intersections
    vector<vector<Road>> adj;

public:
    CityGraph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addRoad(int u, int v, int distance, int trafficDensity) {
        adj[u].push_back({v, distance, trafficDensity});
        adj[v].push_back({u, distance, trafficDensity});
    }

    vector<vector<Road>>& getAdjList() {
        return adj;
    }

    int vertices() {
        return V;
    }
};

// ================================================================
// ALGORITHM 1: DIJKSTRA'S ALGORITHM
// Purpose: Find shortest path for emergency vehicles
// ================================================================

vector<int> dijkstra(CityGraph &graph, int src) {
    int V = graph.vertices();
    vector<int> dist(V, INF);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &road : graph.getAdjList()[u]) {
            int v = road.to;
            int weight = road.distance + road.trafficDensity;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// ================================================================
// ALGORITHM 2: PRIM'S ALGORITHM
// Purpose: Optimize traffic signal network wiring
// ================================================================

int primMST(CityGraph &graph) {
    int V = graph.vertices();
    vector<int> key(V, INF);
    vector<bool> inMST(V, false);
    key[0] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 0});

    int totalCost = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += cost;

        for (auto &road : graph.getAdjList()[u]) {
            int v = road.to;
            int weight = road.distance;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    return totalCost;
}

// ================================================================
// ALGORITHM 3: GREEDY ALGORITHM
// Purpose: Traffic signal timing based on density
// ================================================================

struct Signal {
    int intersection;
    int density;
};

bool compareSignal(Signal a, Signal b) {
    return a.density > b.density;
}

void optimizeSignals(vector<Signal> &signals) {
    sort(signals.begin(), signals.end(), compareSignal);

    cout << "\nOptimized Signal Priority Order:\n";
    for (auto &s : signals) {
        cout << "Intersection " << s.intersection
             << " | Density: " << s.density << endl;
    }
}

// ================================================================
// ALGORITHM 4: BFS & DFS
// Purpose: Incident detection & affected zone analysis
// ================================================================

void bfs(CityGraph &graph, int start) {
    vector<bool> visited(graph.vertices(), false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nBFS Traversal (Incident Spread Analysis): ";

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (auto &road : graph.getAdjList()[u]) {
            int v = road.to;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

void dfsUtil(CityGraph &graph, int u, vector<bool> &visited) {
    visited[u] = true;
    cout << u << " ";

    for (auto &road : graph.getAdjList()[u]) {
        int v = road.to;
        if (!visited[v]) {
            dfsUtil(graph, v, visited);
        }
    }
}

void dfs(CityGraph &graph, int start) {
    vector<bool> visited(graph.vertices(), false);
    cout << "\nDFS Traversal (Zone Connectivity): ";
    dfsUtil(graph, start, visited);
    cout << endl;
}

// ================================================================
// INCIDENT MANAGEMENT MODULE
// ================================================================

void detectIncidents(vector<Incident> &incidents) {
    cout << "\nDetected Traffic Incidents:\n";
    for (auto &i : incidents) {
        cout << "Location: " << i.node
             << " | Type: " << i.type << endl;
    }
}

// ================================================================
// MAIN FUNCTION
// ================================================================

int main() {
    int intersections = 8;
    CityGraph city(intersections);

    // Adding roads (u, v, distance, trafficDensity)
    city.addRoad(0, 1, 4, 2);
    city.addRoad(0, 2, 3, 3);
    city.addRoad(1, 3, 5, 4);
    city.addRoad(2, 3, 6, 2);
    city.addRoad(3, 4, 2, 1);
    city.addRoad(4, 5, 4, 5);
    city.addRoad(5, 6, 3, 3);
    city.addRoad(6, 7, 2, 2);

    // ---------------- Dijkstra ----------------
    cout << "Shortest paths from Emergency Center (0):\n";
    vector<int> dist = dijkstra(city, 0);
    for (int i = 0; i < intersections; i++) {
        cout << "To " << i << " = " << dist[i] << endl;
    }

    // ---------------- Prim ----------------
    int mstCost = primMST(city);
    cout << "\nMinimum Cost for Signal Network (MST): " << mstCost << endl;

    // ---------------- Greedy ----------------
    vector<Signal> signals = {
        {0, 20}, {1, 45}, {2, 30}, {3, 60},
        {4, 25}, {5, 50}, {6, 35}, {7, 40}
    };
    optimizeSignals(signals);

    // ---------------- BFS & DFS ----------------
    bfs(city, 0);
    dfs(city, 0);

    // ---------------- Incident Detection ----------------
    vector<Incident> incidents = {
        {3, "Accident"},
        {5, "Signal Failure"},
        {6, "Heavy Congestion"}
    };
    detectIncidents(incidents);

    cout << "\nSmart Traffic Automation System Simulation Complete." << endl;

    return 0;
}

