#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u,v,w;
};

struct DSU {
    vector<int> p,r;
    DSU(int n){
        p.resize(n+1);
        r.assign(n+1,0);
        for(int i=1;i<=n;i++) p[i]=i;
    }
    int find(int x){
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a!=b){
            if(r[a]<r[b]) swap(a,b);
            p[b]=a;
            if(r[a]==r[b]) r[a]++;
        }
    }
};

vector<vector<pair<int,int>>> adj;
vector<Edge> edges;
int n=8;

vector<int> primMST(){
    vector<int> key(n+1,1e9), used(n+1,0), parent(n+1,-1);
    key[1]=0;
    for(int i=1;i<=n;i++){
        int u=-1;
        for(int j=1;j<=n;j++)
            if(!used[j] && (u==-1 || key[j]<key[u])) u=j;
        used[u]=1;
        for(auto &p:adj[u]){
            int v=p.first, w=p.second;
            if(!used[v] && w<key[v]){
                key[v]=w;
                parent[v]=u;
            }
        }
    }
    return parent;
}

vector<Edge> kruskalMST(){
    DSU d(n);
    vector<Edge> e = edges, res;
    sort(e.begin(), e.end(), [](auto &a,auto &b){ return a.w < b.w; });
    for(auto &x:e){
        if(d.find(x.u)!=d.find(x.v)){
            d.unite(x.u,x.v);
            res.push_back(x);
        }
    }
    return res;
}

vector<int> dijkstra(int src){
    vector<int> dist(n+1,1e9);
    dist[src]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        for(auto &p:adj[u]){
            int v=p.first, w=p.second;
            if(dist[u]+w < dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

int knapsack(vector<int> &w, vector<int> &b, int cap){
    vector<vector<int>> dp(w.size()+1, vector<int>(cap+1,0));
    for(int i=1;i<=w.size();i++){
        for(int c=1;c<=cap;c++){
            if(w[i-1]<=c)
                dp[i][c] = max(b[i-1] + dp[i-1][c-w[i-1]], dp[i-1][c]);
            else dp[i][c] = dp[i-1][c];
        }
    }
    return dp[w.size()][cap];
}

vector<int> visited1, visited2;

void dfs(int u){
    visited1[u]=1;
    for(auto &p:adj[u]){
        int v=p.first;
        if(!visited1[v]) dfs(v);
    }
}

void bfs(int s){
    visited2.assign(n+1,0);
    queue<int> q;
    visited2[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto &p:adj[u]){
            int v=p.first;
            if(!visited2[v]){
                visited2[v]=1;
                q.push(v);
            }
        }
    }
}

struct Task {
    int id, priority;
};

struct cmpT {
    bool operator()(Task a, Task b){
        return a.priority < b.priority;
    }
};

string genCargoLog(){
    vector<string> v={"container","load","unload","delay","ship","dock","truck"};
    string s="";
    int L=rand()%40+40;
    for(int i=0;i<L;i++) s+=v[rand()%v.size()]+" ";
    return s;
}

vector<int> buildLPS(string p){
    vector<int>l(p.size(),0);
    int i=1,k=0;
    while(i<p.size()){
        if(p[i]==p[k]) l[i++]=++k;
        else if(k) k=l[k-1];
        else l[i++]=0;
    }
    return l;
}

vector<int> KMP(string t,string p){
    vector<int>l=buildLPS(p),res;
    int i=0,j=0;
    while(i<t.size()){
        if(t[i]==p[j]) i++,j++;
        if(j==p.size()){
            res.push_back(i-j);
            j=l[j-1];
        } else if(i<t.size() && t[i]!=p[j]){
            if(j) j=l[j-1];
            else i++;
        }
    }
    return res;
}

int main(){
    srand(time(NULL));

    adj.resize(n+1);

    vector<tuple<int,int,int>> in = {
        {1,2,4},{1,3,2},{2,4,7},{3,4,3},
        {3,5,6},{5,6,2},{4,7,5},{6,8,3}
    };

    for(auto &e:in){
        int u,v,w;
        tie(u,v,w)=e;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        edges.push_back({u,v,w});
    }

    vector<int> parent = primMST();
    vector<Edge> mstK = kruskalMST();
    vector<int> dist = dijkstra(1);

    vector<int> wt={10,20,30,40};
    vector<int> ben={60,90,120,150};
    int kn = knapsack(wt,ben,50);

    visited1.assign(n+1,0);
    dfs(1);
    bfs(1);

    priority_queue<Task,vector<Task>,cmpT> pq;
    pq.push({1,5});
    pq.push({2,9});
    pq.push({3,3});
    pq.push({4,1});

    string log = genCargoLog();
    string pat="load";
    vector<int> pos = KMP(log,pat);

    for(int i=1;i<=n;i++) cout<<dist[i]<<" ";
    cout<<"\n";

    cout<<kn<<"\n";

    for(auto &e:mstK) cout<<e.u<<" "<<e.v<<" "<<e.w<<"\n";

    for(int x:visited1) cout<<x<<" ";
    cout<<"\n";

    for(int x:visited2) cout<<x<<" ";
    cout<<"\n";

    while(!pq.empty()){
        cout<<pq.top().id<<" "<<pq.top().priority<<"\n";
        pq.pop();
    }

    for(int x:pos) cout<<x<<" ";
    cout<<"\n";

    cout<<log<<"\n";

    return 0;
}
