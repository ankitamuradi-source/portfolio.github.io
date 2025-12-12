#include <bits/stdc++.h>
using namespace std;

struct User {
    string name;
    string passHash;
};

struct Node {
    int id;
    vector<int> edges;
};

struct KeyNode {
    int key;
    KeyNode *l, *r;
    KeyNode(int k):key(k),l(NULL),r(NULL){}
};

vector<User> users;
vector<Node> net;
vector<int> visited1, visited2;

string hashString(string s){
    long long h=0, mod=1e9+7, base=257;
    for(char c:s) h=(h*base+c)%mod;
    return to_string(h);
}

bool authenticate(string name,string pass){
    for(auto &u:users){
        if(u.name==name){
            if(u.passHash==hashString(pass)) return true;
            return false;
        }
    }
    return false;
}

vector<int> buildLPS(string pat){
    vector<int>l(pat.size(),0);
    int i=1,k=0;
    while(i<pat.size()){
        if(pat[i]==pat[k]) l[i++]=++k;
        else if(k) k=l[k-1];
        else l[i++]=0;
    }
    return l;
}

vector<int> KMPmatch(string txt,string pat){
    vector<int>l=buildLPS(pat),res;
    int i=0,j=0;
    while(i<txt.size()){
        if(txt[i]==pat[j]) i++,j++;
        if(j==pat.size()){
            res.push_back(i-j);
            j=l[j-1];
        } else if(i<txt.size() && txt[i]!=pat[j]){
            if(j) j=l[j-1];
            else i++;
        }
    }
    return res;
}

vector<int> boyer(string txt,string pat){
    vector<int>res;
    int n=txt.size(), m=pat.size();
    vector<int>bc(256,-1);
    for(int i=0;i<m;i++) bc[(unsigned char)pat[i]]=i;
    int s=0;
    while(s<=n-m){
        int j=m-1;
        while(j>=0 && pat[j]==txt[s+j]) j--;
        if(j<0){
            res.push_back(s);
            s+=(s+m<n)?m-bc[txt[s+m]]:1;
        } else {
            s+=max(1,j-bc[txt[s+j]]);
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
    long long b=257,mod=1e9+7;
    int n=t.size(), m=p.size();
    if(m>n) return res;
    long long ph=rhash(p,b,mod), th=rhash(t.substr(0,m),b,mod),bp=1;
    for(int i=1;i<m;i++) bp=(bp*b)%mod;
    for(int i=0;i<=n-m;i++){
        if(ph==th && t.substr(i,m)==p) res.push_back(i);
        if(i<n-m){
            th=(th - t[i]*bp)%mod;
            if(th<0) th+=mod;
            th=(th*b + t[i+m])%mod;
        }
    }
    return res;
}

void dfs(int u){
    visited1[u]=1;
    for(int v:net[u].edges)
        if(!visited1[v]) dfs(v);
}

void bfs(int s){
    visited2.assign(net.size(),0);
    queue<int>q;
    visited2[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:net[u].edges){
            if(!visited2[v]){
                visited2[v]=1;
                q.push(v);
            }
        }
    }
}

KeyNode* insertKey(KeyNode* root,int k){
    if(!root) return new KeyNode(k);
    if(k<root->key) root->l=insertKey(root->l,k);
    else root->r=insertKey(root->r,k);
    return root;
}

void inorderKeys(KeyNode* root, vector<int> &res){
    if(!root) return;
    inorderKeys(root->l,res);
    res.push_back(root->key);
    inorderKeys(root->r,res);
}

string genLog(){
    vector<string> t={"attack","login","fail","success","malware","scan","alert","trace"};
    string s="";
    int len=rand()%60+40;
    for(int i=0;i<len;i++){
        s+=t[rand()%t.size()];
        s+=" ";
    }
    return s;
}

int main(){
    srand(time(NULL));

    users.push_back({"admin",hashString("strongpass")});
    users.push_back({"user",hashString("pass123")});

    net.resize(8);
    for(int i=0;i<8;i++) net[i].id=i;

    net[0].edges={1,2};
    net[1].edges={0,3};
    net[2].edges={0,4};
    net[3].edges={1,5};
    net[4].edges={2,6,7};
    net[5].edges={3};
    net[6].edges={4};
    net[7].edges={4};

    visited1.assign(8,0);
    dfs(0);
    bfs(0);

    KeyNode* root=NULL;
    for(int k:{50,20,70,10,30,60,90})
        root=insertKey(root,k);

    vector<int> keys;
    inorderKeys(root,keys);

    string log = genLog();
    string pat = "malware";

    vector<int> km = KMPmatch(log,pat);
    vector<int> bm = boyer(log,pat);
    vector<int> rk = rabin(log,pat);

    cout<<authenticate("admin","strongpass")<<"\n";
    cout<<authenticate("admin","wrong")<<"\n";

    for(int x:visited1) cout<<x<<" ";
    cout<<"\n";

    for(int x:visited2) cout<<x<<" ";
    cout<<"\n";

    for(int x:keys) cout<<x<<" ";
    cout<<"\n";

    for(int x:km) cout<<x<<" ";
    cout<<"\n";

    for(int x:bm) cout<<x<<" ";
    cout<<"\n";

    for(int x:rk) cout<<x<<" ";
    cout<<"\n";

    cout<<log<<"\n";

    return 0;
}
