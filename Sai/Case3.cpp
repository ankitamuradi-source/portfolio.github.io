#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, w;
};

vector<vector<pair<int,int>>> adj;
vector<Edge> edges;
vector<int> visited;
vector<int> trafficData;
vector<int> segtree;
int n, m;

void buildSegTree(int idx, int l, int r) {
    if (l == r) {
        segtree[idx] = trafficData[l];
        return;
    }
    int mid = (l+r)/2;
    buildSegTree(idx*2, l, mid);
    buildSegTree(idx*2+1, mid+1, r);
    segtree[idx] = segtree[idx*2] + segtree[idx*2+1];
}

void updateSegTree(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        segtree[idx] = val;
        return;
    }
    int mid = (l+r)/2;
    if (pos <= mid) updateSegTree(idx*2, l, mid, pos, val);
    else updateSegTree(idx*2+1, mid+1, r, pos, val);
    segtree[idx] = segtree[idx*2] + segtree[idx*2+1];
}

int querySegTree(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return segtree[idx];
    int mid = (l+r)/2;
    return querySegTree(idx*2, l, mid, ql, qr) +
           querySegTree(idx*2+1, mid+1, r, ql, qr);
}

void bfs(int start) {
    queue<int> q;
    visited.assign(n+1,0);
    visited[start] = 1;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &p : adj[u]) {
            int v = p.first;
            if (!visited[v]) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
}

void dfs(int u) {
    visited[u] = 1;
    for (auto &p : adj[u]) {
        int v = p.first;
        if (!visited[v]) dfs(v);
    }
}

vector<int> dijkstra(int src) {
    vector<int> dist(n+1, INF);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d,u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto &p : adj[u]) {
            int v = p.first, w = p.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u]+w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

vector<vector<int>> floydWarshall() {
    vector<vector<int>> dist(n+1, vector<int>(n+1, INF));
    for (int i = 1; i <= n; i++) dist[i][i] = 0;
    for (auto &e : edges) {
        dist[e.u][e.v] = min(dist[e.u][e.v], e.w);
        dist[e.v][e.u] = min(dist[e.v][e.u], e.w);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

vector<int> emergencyRoute(int src, int priorityNode) {
    vector<int> dist(n+1, INF);
    vector<int> isPriority(n+1,0);
    isPriority[priorityNode] = 1;

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    dist[src] = 0;
    pq.push({0,1,src});

    while (!pq.empty()) {
        auto [d,flag,u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (auto &p : adj[u]) {
            int v = p.first, w = p.second;
            int priorityFactor = isPriority[v] ? -5 : 0;
            int newDist = dist[u] + w + priorityFactor;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                pq.push({dist[v], isPriority[v], v});
            }
        }
    }
    return dist;
}

string simulateTrafficPattern() {
    vector<string> events = {"car","bus","bike","truck","signal","turn"};
    string s = "";
    int len = rand() % 50 + 50;
    for (int i = 0; i < len; i++) {
        s += events[rand() % events.size()];
        s += " ";
    }
    return s;
}

vector<int> buildLPS(string pat) {
    vector<int> lps(pat.size(),0);
    int len = 0, i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len-1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMP(string txt, string pat) {
    vector<int> res;
    vector<int> lps = buildLPS(pat);
    int i = 0, j = 0;
    while (i < txt.size()) {
        if (txt[i] == pat[j]) {
            i++; j++;
        }
        if (j == pat.size()) {
            res.push_back(i - j);
            j = lps[j-1];
        } else if (i < txt.size() && txt[i] != pat[j]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }
    return res;
}

long long rabinHash(string s, long long base, long long mod) {
    long long h = 0;
    for (char c : s) h = (h * base + c) % mod;
    return h;
}

vector<int> rabinKarp(string txt, string pat) {
    vector<int> res;
    long long base = 257, mod = 1000000007;
    int n2 = txt.size(), m2 = pat.size();
    if (m2 > n2) return res;
    long long patHash = rabinHash(pat, base, mod);
    long long txtHash = rabinHash(txt.substr(0,m2), base, mod);
    long long basePow = 1;
    for (int i = 1; i < m2; i++) basePow = (basePow * base) % mod;
    for (int i = 0; i <= n2 - m2; i++) {
        if (txtHash == patHash) {
            if (txt.substr(i,m2) == pat) res.push_back(i);
        }
        if (i < n2 - m2) {
            txtHash = (txtHash - txt[i] * basePow) % mod;
            if (txtHash < 0) txtHash += mod;
            txtHash = (txtHash * base + txt[i+m2]) % mod;
        }
    }
    return res;
}

int main() {
    srand(time(NULL));

    n = 8;
    m = 10;

    adj.resize(n+1);

    vector<tuple<int,int,int>> input = {
        {1,2,5},{1,3,2},{2,4,7},{3,4,3},
        {3,5,4},{4,6,1},{5,7,6},{6,7,2},
        {7,8,3},{5,8,5}
    };

    for (auto &e : input) {
        int u,v,w;
        tie(u,v,w) = e;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        edges.push_back({u,v,w});
    }

    trafficData = {5,3,7,2,9,4,6,8};
    segtree.resize(4*trafficData.size());
    buildSegTree(1,0,trafficData.size()-1);

    bfs(1);
    dfs(1);

    vector<int> dist = dijkstra(1);
    vector<vector<int>> fw = floydWarshall();
    vector<int> emergency = emergencyRoute(1,6);

    string traffic = simulateTrafficPattern();
    string patt = "car";
    vector<int> kmpres = KMP(traffic, patt);
    vector<int> rkres = rabinKarp(traffic, patt);

    cout << "Dijkstra\n";
    for (int i = 1; i <= n; i++) cout << dist[i] << " ";
    cout << "\n";

    cout << "FloydWarshall\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << (fw[i][j] == INF ? -1 : fw[i][j]) << " ";
        cout << "\n";
    }

    cout << "Emergency\n";
    for (int i = 1; i <= n; i++) cout << emergency[i] << " ";
    cout << "\n";

    cout << "TrafficPattern\n";
    cout << traffic << "\n";

    cout << "KMP\n";
    for (int x : kmpres) cout << x << " ";
    cout << "\n";

    cout << "RabinKarp\n";
    for (int x : rkres) cout << x << " ";
    cout << "\n";

    cout << "SegmentTreeQuery ";
    cout << querySegTree(1,0,trafficData.size()-1,2,6) << "\n";

    return 0;
}
