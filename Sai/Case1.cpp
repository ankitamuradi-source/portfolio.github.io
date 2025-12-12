#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, w;
};

struct Node {
    int id;
    int renewableEnergy;
};

vector<vector<pair<int,int>>> adj;
vector<Edge> edges;
vector<Node> gridNodes;
int n, m;

vector<int> parentSet;
vector<int> setRank;

int findSet(int v) {
    if (v == parentSet[v]) return v;
    return parentSet[v] = findSet(parentSet[v]);
}

void unionSet(int a, int b) {
    a = findSet(a);
    b = findSet(b);
    if (a != b) {
        if (setRank[a] < setRank[b]) swap(a, b);
        parentSet[b] = a;
        if (setRank[a] == setRank[b]) setRank[a]++;
    }
}

void kruskalMST() {
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(), [](auto &a, auto &b){
        return a.w < b.w;
    });

    parentSet.resize(n+1);
    setRank.assign(n+1, 0);
    for (int i = 1; i <= n; i++) parentSet[i] = i;

    int mstCost = 0;
    cout << "Kruskal MST\n";

    for (auto &e : sortedEdges) {
        if (findSet(e.u) != findSet(e.v)) {
            unionSet(e.u, e.v);
            mstCost += e.w;
            cout << e.u << " - " << e.v << " | " << e.w << "\n";
        }
    }
    cout << "MST Cost: " << mstCost << "\n";
}

void primMST(int start) {
    vector<int> key(n+1, INF);
    vector<bool> inMST(n+1, false);
    key[start] = 0;
    int mstCost = 0;

    cout << "Prim MST\n";

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 1; i <= n; i++) {
            if (!inMST[i] && (u == -1 || key[i] < key[u])) u = i;
        }

        inMST[u] = true;
        mstCost += key[u];

        for (auto &p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (!inMST[v] && w < key[v]) key[v] = w;
        }
    }

    cout << "Prim MST Cost: " << mstCost << "\n";
}

void dijkstra(int src) {
    vector<int> dist(n+1, INF);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});

    cout << "Dijkstra\n";

    while (!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();

        if (d != dist[u]) continue;

        for (auto &[v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << "Node " << i << ": " << dist[i] << "\n";
}

void bellmanFord(int src) {
    vector<int> dist(n+1, INF);
    dist[src] = 0;

    cout << "Bellman-Ford\n";

    for (int i = 1; i < n; i++) {
        for (auto &e : edges) {
            if (dist[e.u] < INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << "Node " << i << ": " << dist[i] << "\n";
}

int knapsackOptimize(vector<int> &weights, vector<int> &benefits, int cap) {
    int dp[105][1005];

    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 1005; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= weights.size(); i++) {
        for (int w = 1; w <= cap; w++) {
            if (weights[i-1] <= w)
                dp[i][w] = max(benefits[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    return dp[weights.size()][cap];
}

void greedyEnergyAllocation(vector<Node> &stations, int required) {
    vector<pair<int,int>> renewable;

    for (auto &s : stations)
        renewable.push_back({s.renewableEnergy, s.id});

    sort(renewable.rbegin(), renewable.rend());

    int allocated = 0;

    cout << "Greedy Energy Allocation\n";

    for (auto &p : renewable) {
        if (allocated >= required) break;
        cout << "Allocating " << p.first << " from Node " << p.second << "\n";
        allocated += p.first;
    }

    cout << "Total Allocated: " << allocated << "\n";
}

int main() {
    n = 6;
    m = 7;

    adj.resize(n+1);

    vector<tuple<int,int,int>> inputEdges = {
        {1,2,4}, {1,3,2}, {2,3,1}, {2,4,7},
        {3,5,3}, {5,6,2}, {4,6,5}
    };

    for (auto &e : inputEdges) {
        int u, v, w;
        tie(u,v,w) = e;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        edges.push_back({u,v,w});
    }

    gridNodes = {
        {1,30}, {2,20}, {3,40}, {4,10}, {5,50}, {6,25}
    };

    kruskalMST();
    primMST(1);
    dijkstra(1);
    bellmanFord(1);

    vector<int> weights = {10,20,30,40};
    vector<int> benefits = {60,100,120,200};
    int cap = 50;

    cout << "Knapsack Optimal: " << knapsackOptimize(weights, benefits, cap) << "\n";

    greedyEnergyAllocation(gridNodes, 120);

    return 0;
}
