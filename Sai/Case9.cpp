#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie* child[256];
    bool end;
    Trie(){
        end=false;
        for(int i=0;i<256;i++) child[i]=NULL;
    }
};

Trie* rootTrie;

void insertTrie(string s){
    Trie* cur=rootTrie;
    for(char c:s){
        if(!cur->child[(unsigned char)c])
            cur->child[(unsigned char)c]=new Trie();
        cur=cur->child[(unsigned char)c];
    }
    cur->end=true;
}

bool searchTrie(string s){
    Trie* cur=rootTrie;
    for(char c:s){
        if(!cur->child[(unsigned char)c]) return false;
        cur=cur->child[(unsigned char)c];
    }
    return cur->end;
}

void autoComplete(Trie* cur,string pref,vector<string>&res){
    if(cur->end) res.push_back(pref);
    for(int i=0;i<256;i++){
        if(cur->child[i])
            autoComplete(cur->child[i],pref+char(i),res);
    }
}

string hashKey(string s){
    long long h=0,base=257,mod=1e9+7;
    for(char c:s) h=(h*base+c)%mod;
    return to_string(h);
}

unordered_map<string,string> dataStore;

void mergeArr(vector<string>&a,int l,int m,int r){
    int n1=m-l+1,n2=r-m;
    vector<string>L(n1),R(n2);
    for(int i=0;i<n1;i++) L[i]=a[l+i];
    for(int j=0;j<n2;j++) R[j]=a[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2){
        if(L[i]<R[j]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    while(i<n1) a[k++]=L[i++];
    while(j<n2) a[k++]=R[j++];
}

void mergeSort(vector<string>&a,int l,int r){
    if(l>=r) return;
    int m=(l+r)/2;
    mergeSort(a,l,m);
    mergeSort(a,m+1,r);
    mergeArr(a,l,m,r);
}

int partitionQS(vector<string>&a,int l,int r){
    string p=a[r];
    int i=l;
    for(int j=l;j<r;j++){
        if(a[j]<p){
            swap(a[i],a[j]);
            i++;
        }
    }
    swap(a[i],a[r]);
    return i;
}

void quickSort(vector<string>&a,int l,int r){
    if(l<r){
        int p=partitionQS(a,l,r);
        quickSort(a,l,p-1);
        quickSort(a,p+1,r);
    }
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

string randomRecord(){
    vector<string> w={"population","traffic","sensor","energy","health","crime","water","land"};
    string s="";
    int L=rand()%40+40;
    for(int i=0;i<L;i++) s+=w[rand()%w.size()]+" ";
    return s;
}

int main(){
    srand(time(NULL));

    rootTrie=new Trie();

    vector<string> dataset;
    for(int i=0;i<20;i++){
        string rec=randomRecord();
        dataset.push_back(rec);
        string key=hashKey("rec"+to_string(i));
        dataStore[key]=rec;
        insertTrie(rec.substr(0,5));
    }

    vector<string> sorted1 = dataset;
    vector<string> sorted2 = dataset;

    mergeSort(sorted1,0,sorted1.size()-1);
    quickSort(sorted2,0,sorted2.size()-1);

    string query = dataset[rand()%dataset.size()];
    string prefix = query.substr(0,3);

    vector<string> autoList;
    autoComplete(rootTrie,prefix,autoList);

    string text = randomRecord();
    string pat = "traffic";

    vector<int> km = KMP(text,pat);
    vector<int> rk = rabin(text,pat);

    for(auto &s:sorted1) cout<<s<<"\n";
    cout<<"--\n";

    for(auto &s:sorted2) cout<<s<<"\n";
    cout<<"--\n";

    for(auto &s:autoList) cout<<s<<"\n";
    cout<<"--\n";

    for(int x:km) cout<<x<<" ";
    cout<<"\n";

    for(int x:rk) cout<<x<<" ";
    cout<<"\n";

    cout<<text<<"\n";

    return 0;
}
