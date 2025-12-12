#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    vector<int> neighbors;
};

struct Huff {
    char c;
    int f;
    Huff *l, *r;
    Huff(char c,int f):c(c),f(f),l(NULL),r(NULL){}
};

struct cmp {
    bool operator()(Huff* a, Huff* b){
        return a->f > b->f;
    }
};

vector<Node> graphNodes;
vector<int> visited, visited2;
unordered_map<char,string> codes;
int dpHaz[205][205];

void dfs(int u){
    visited[u]=1;
    for(int v:graphNodes[u].neighbors)
        if(!visited[v]) dfs(v);
}

void bfs(int s){
    queue<int>q;
    visited2.assign(graphNodes.size(),0);
    visited2[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:graphNodes[u].neighbors){
            if(!visited2[v]){
                visited2[v]=1;
                q.push(v);
            }
        }
    }
}

int hazard(int d,int x){
    for(int i=0;i<=d;i++)
        for(int j=0;j<=x;j++)
            dpHaz[i][j]=0;
    dpHaz[0][0]=1;
    for(int i=1;i<=d;i++){
        for(int j=0;j<=x;j++){
            int a=dpHaz[i-1][j];
            int b=j>0?dpHaz[i-1][j-1]:0;
            dpHaz[i][j]=a+b;
        }
    }
    return dpHaz[d][x];
}

void buildHuff(Huff* r,string s){
    if(!r) return;
    if(!r->l && !r->r) codes[r->c]=s;
    buildHuff(r->l,s+"0");
    buildHuff(r->r,s+"1");
}

string huffEncode(string t){
    unordered_map<char,int>f;
    for(char c:t) f[c]++;
    priority_queue<Huff*,vector<Huff*>,cmp> pq;
    for(auto &p:f) pq.push(new Huff(p.first,p.second));
    while(pq.size()>1){
        Huff* a=pq.top(); pq.pop();
        Huff* b=pq.top(); pq.pop();
        Huff* m=new Huff('*',a->f+b->f);
        m->l=a; m->r=b;
        pq.push(m);
    }
    Huff* root=pq.top();
    buildHuff(root,"");
    string s="";
    for(char c:t) s+=codes[c];
    return s;
}

vector<int> buildLPS(string p){
    vector<int> l(p.size(),0);
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
        } else if(i<t.size() && t[i]!=p[j]){
            if(j) j=l[j-1];
            else i++;
        }
    }
    return res;
}

long long rhash(string s,long long b,long long mod){
    long long h=0;
    for(char c:s) h=(h*b+c)%mod;
    return h;
}

vector<int> rabin(string t,string p){
    vector<int>res;
    long long b=257,m=1e9+7;
    int n=t.size(), k=p.size();
    if(k>n) return res;
    long long ph=rhash(p,b,m), th=rhash(t.substr(0,k),b,m), bp=1;
    for(int i=1;i<k;i++) bp=(bp*b)%m;
    for(int i=0;i<=n-k;i++){
        if(ph==th){
            if(t.substr(i,k)==p) res.push_back(i);
        }
        if(i<n-k){
            th=(th - t[i]*bp)%m;
            if(th<0) th+=m;
            th=(th*b + t[i+k])%m;
        }
    }
    return res;
}

string genSatelliteData(){
    vector<string> a={"storm","wind","rain","dry","cloud","heat","flood"};
    string s="";
    int len=rand()%50+50;
    for(int i=0;i<len;i++){
        s+=a[rand()%a.size()];
        s+=" ";
    }
    return s;
}

int main(){
    srand(time(NULL));

    graphNodes.resize(7);
    for(int i=0;i<7;i++) graphNodes[i].id=i;

    graphNodes[0].neighbors={1,2};
    graphNodes[1].neighbors={0,3};
    graphNodes[2].neighbors={0,4};
    graphNodes[3].neighbors={1,5};
    graphNodes[4].neighbors={2,6};
    graphNodes[5].neighbors={3};
    graphNodes[6].neighbors={4};

    visited.assign(7,0);
    dfs(0);

    bfs(0);

    int risk=hazard(5,3);

    string data=genSatelliteData();
    string pat="flood";
    vector<int> k1=KMP(data,pat);
    vector<int> k2=rabin(data,pat);

    string encoded=huffEncode(data);

    cout<<risk<<"\n";
    cout<<encoded<<"\n";
    for(int x:k1) cout<<x<<" ";
    cout<<"\n";
    for(int x:k2) cout<<x<<" ";
    cout<<"\n";
    for(int i=0;i<visited.size();i++) cout<<visited[i]<<" ";
    cout<<"\n";
    for(int i=0;i<visited2.size();i++) cout<<visited2[i]<<" ";
    cout<<"\n";
    cout<<data<<"\n";

    return 0;
}
