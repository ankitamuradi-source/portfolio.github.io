#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int x, y;
};

struct Node {
    int x, y, g, h, f;
};

struct cmp {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};

int n = 15, m = 15;
vector<vector<int>> gridMap;
vector<vector<int>> distD;
vector<vector<int>> visitedB, visitedD;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool valid(int x, int y) {
    return x>=0 && y>=0 && x<n && y<m && gridMap[x][y]==0;
}

int hcost(int x1,int y1,int x2,int y2){
    return abs(x1-x2)+abs(y1-y2);
}

vector<Cell> reconstruct(map<pair<int,int>, pair<int,int>> parent, Cell end){
    vector<Cell> path;
    pair<int,int> cur = {end.x, end.y};
    while(parent.count(cur)){
        path.push_back({cur.first, cur.second});
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Cell> astar(Cell start, Cell end){
    priority_queue<Node, vector<Node>, cmp> pq;
    map<pair<int,int>, int> cost;
    map<pair<int,int>, pair<int,int>> parent;

    cost[{start.x,start.y}] = 0;
    pq.push({start.x,start.y,0,hcost(start.x,start.y,end.x,end.y),0});

    while(!pq.empty()){
        Node cur = pq.top(); pq.pop();
        if(cur.x == end.x && cur.y == end.y)
            return reconstruct(parent,end);

        for(int k=0;k<4;k++){
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if(!valid(nx,ny)) continue;

            int ng = cur.g + 1;
            int nh = hcost(nx,ny,end.x,end.y);
            int nf = ng + nh;

            if(!cost.count({nx,ny}) || ng < cost[{nx,ny}]){
                cost[{nx,ny}] = ng;
                parent[{nx,ny}] = {cur.x,cur.y};
                pq.push({nx,ny,ng,nh,nf});
            }
        }
    }
    return {};
}

void bfs(int sx,int sy){
    visitedB.assign(n,vector<int>(m,0));
    queue<pair<int,int>> q;
    visitedB[sx][sy]=1;
    q.push({sx,sy});
    while(!q.empty()){
        auto [x,y]=q.front(); q.pop();
        for(int k=0;k<4;k++){
            int nx=x+dx[k], ny=y+dy[k];
            if(valid(nx,ny) && !visitedB[nx][ny]){
                visitedB[nx][ny]=1;
                q.push({nx,ny});
            }
        }
    }
}

void dfsUtil(int x,int y){
    visitedD[x][y]=1;
    for(int k=0;k<4;k++){
        int nx=x+dx[k], ny=y+dy[k];
        if(valid(nx,ny) && !visitedD[nx][ny])
            dfsUtil(nx,ny);
    }
}

void dfs(int sx,int sy){
    visitedD.assign(n,vector<int>(m,0));
    dfsUtil(sx,sy);
}

vector<Cell> dijkstraPath(Cell s, Cell e){
    distD.assign(n,vector<int>(m,1e9));
    priority_queue<pair<int,pair<int,int>>, 
        vector<pair<int,pair<int,int>>>, greater<>> pq;

    map<pair<int,int>, pair<int,int>> parent;

    distD[s.x][s.y]=0;
    pq.push({0,{s.x,s.y}});

    while(!pq.empty()){
        auto [d, pr] = pq.top(); pq.pop();
        int x=pr.first, y=pr.second;
        if(d!=distD[x][y]) continue;
        if(x==e.x && y==e.y) break;

        for(int k=0;k<4;k++){
            int nx=x+dx[k], ny=y+dy[k];
            if(!valid(nx,ny)) continue;
            int nd=d+1;
            if(nd<distD[nx][ny]){
                distD[nx][ny]=nd;
                parent[{nx,ny}]={x,y};
                pq.push({nd,{nx,ny}});
            }
        }
    }

    vector<Cell> path;
    pair<int,int> cur={e.x,e.y};
    while(parent.count(cur)){
        path.push_back({cur.first,cur.second});
        cur=parent[cur];
    }
    reverse(path.begin(),path.end());
    return path;
}

struct Task {
    int id, priority;
};

struct cmp2 {
    bool operator()(Task a, Task b){
        return a.priority < b.priority;
    }
};

string genPattern(){
    vector<string> v={"pod","move","halt","turn","charge","error","update"};
    string s="";
    int len=rand()%50+50;
    for(int i=0;i<len;i++){
        s+=v[rand()%v.size()]+" ";
    }
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
    vector<int>res,l=buildLPS(p);
    int i=0,j=0;
    while(i<t.size()){
        if(t[i]==p[j]) i++,j++;
        if(j==p.size()){
            res.push_back(i-j);
            j=l[j-1];
        } else if(i<t.size()&&t[i]!=p[j]){
            if(j) j=l[j-1];
            else i++;
        }
    }
    return res;
}

int main(){
    srand(time(NULL));
    gridMap.assign(n,vector<int>(m,0));

    for(int i=0;i<40;i++){
        int x=rand()%n, y=rand()%m;
        gridMap[x][y]=1;
    }

    Cell start={0,0}, end={14,14};
    gridMap[0][0]=0;
    gridMap[14][14]=0;

    bfs(0,0);
    dfs(0,0);

    vector<Cell> pathA = astar(start,end);
    vector<Cell> pathD = dijkstraPath(start,end);

    priority_queue<Task,vector<Task>,cmp2> pq;
    pq.push({1,5});
    pq.push({2,2});
    pq.push({3,9});
    pq.push({4,1});

    string log = genPattern();
    string pattern = "error";
    vector<int> match = KMP(log,pattern);

    cout<<pathA.size()<<"\n";
    cout<<pathD.size()<<"\n";

    while(!pq.empty()){
        cout<<pq.top().id<<" "<<pq.top().priority<<"\n";
        pq.pop();
    }

    for(int x:match) cout<<x<<" ";
    cout<<"\n";

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cout<<visitedB[i][j]<<" ";
        cout<<"\n";
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            cout<<visitedD[i][j]<<" ";
        cout<<"\n";
    }

    cout<<log<<"\n";
    return 0;
}
