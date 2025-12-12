#include <bits/stdc++.h>
using namespace std;

struct Zone {
    int id;
    int energy;
    vector<int> neighbors;
};

vector<Zone> zones;
vector<int> visited;
vector<int> segtree, arr;

int n = 10;

void buildSeg(int idx,int l,int r){
    if(l==r){
        segtree[idx]=arr[l];
        return;
    }
    int m=(l+r)/2;
    buildSeg(idx*2,l,m);
    buildSeg(idx*2+1,m+1,r);
    segtree[idx]=segtree[idx*2]+segtree[idx*2+1];
}

void updateSeg(int idx,int l,int r,int pos,int val){
    if(l==r){
        segtree[idx]=val;
        return;
    }
    int m=(l+r)/2;
    if(pos<=m) updateSeg(idx*2,l,m,pos,val);
    else updateSeg(idx*2+1,m+1,r,pos,val);
    segtree[idx]=segtree[idx*2]+segtree[idx*2+1];
}

int querySeg(int idx,int l,int r,int ql,int qr){
    if(qr<l || ql>r) return 0;
    if(ql<=l && r<=qr) return segtree[idx];
    int m=(l+r)/2;
    return querySeg(idx*2,l,m,ql,qr)+
           querySeg(idx*2+1,m+1,r,ql,qr);
}

void bfs(int s){
    visited.assign(n,0);
    queue<int>q;
    visited[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:zones[u].neighbors){
            if(!visited[v]){
                visited[v]=1;
                q.push(v);
            }
        }
    }
}

vector<int> greedyLighting(vector<Zone> &z,int needed){
    vector<pair<int,int>> a;
    for(auto &x:z) a.push_back({x.energy,x.id});
    sort(a.rbegin(),a.rend());
    vector<int> res;
    int sum=0;
    for(auto &p:a){
        if(sum>=needed) break;
        sum+=p.first;
        res.push_back(p.second);
    }
    return res;
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

long long rhash(string s,long long b,long long m){
    long long h=0;
    for(char c:s) h=(h*b+c)%m;
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
        if(ph==th && t.substr(i,k)==p) res.push_back(i);
        if(i<n-k){
            th=(th - t[i]*bp)%m;
            if(th<0) th+=m;
            th=(th*b + t[i+k])%m;
        }
    }
    return res;
}

string genEvent(){
    vector<string> e={"light","dim","bright","motion","alert","safe","unsafe"};
    string s="";
    int L=rand()%50+50;
    for(int i=0;i<L;i++)
        s+=e[rand()%e.size()]+" ";
    return s;
}

int main(){
    srand(time(NULL));

    for(int i=0;i<n;i++){
        Zone z;
        z.id=i;
        z.energy=rand()%50+10;
        zones.push_back(z);
    }

    zones[0].neighbors={1,2};
    zones[1].neighbors={0,3};
    zones[2].neighbors={0,4};
    zones[3].neighbors={1,5};
    zones[4].neighbors={2,6};
    zones[5].neighbors={3,7};
    zones[6].neighbors={4,8};
    zones[7].neighbors={5,9};
    zones[8].neighbors={6};
    zones[9].neighbors={7};

    arr.resize(n);
    for(int i=0;i<n;i++) arr[i]=zones[i].energy;
    segtree.resize(4*n);
    buildSeg(1,0,n-1);

    bfs(0);

    vector<int> g = greedyLighting(zones,120);

    string ev = genEvent();
    string pat = "alert";
    vector<int> km = KMP(ev,pat);
    vector<int> rk = rabin(ev,pat);

    cout<<querySeg(1,0,n-1,0,5)<<"\n";

    for(int x:g) cout<<x<<" ";
    cout<<"\n";

    for(int x:visited) cout<<x<<" ";
    cout<<"\n";

    for(int x:km) cout<<x<<" ";
    cout<<"\n";

    for(int x:rk) cout<<x<<" ";
    cout<<"\n";

    cout<<ev<<"\n";

    return 0;
}
