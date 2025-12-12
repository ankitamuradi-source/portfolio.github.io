#include <bits/stdc++.h>
using namespace std;

struct AVL {
    int key, h;
    AVL *l, *r;
    AVL(int k):key(k),h(1),l(NULL),r(NULL){}
};

int height(AVL* n){ return n? n->h : 0; }
int bal(AVL* n){ return n? height(n->l) - height(n->r) : 0; }

AVL* rotR(AVL* y){
    AVL* x=y->l;
    AVL* t=x->r;
    x->r=y;
    y->l=t;
    y->h=max(height(y->l),height(y->r))+1;
    x->h=max(height(x->l),height(x->r))+1;
    return x;
}

AVL* rotL(AVL* x){
    AVL* y=x->r;
    AVL* t=y->l;
    y->l=x;
    x->r=t;
    x->h=max(height(x->l),height(x->r))+1;
    y->h=max(height(y->l),height(y->r))+1;
    return y;
}

AVL* insertAVL(AVL* node,int k){
    if(!node) return new AVL(k);
    if(k<node->key) node->l=insertAVL(node->l,k);
    else node->r=insertAVL(node->r,k);
    node->h=max(height(node->l),height(node->r))+1;
    int b=bal(node);
    if(b>1 && k<node->l->key) return rotR(node);
    if(b<-1 && k>node->r->key) return rotL(node);
    if(b>1 && k>node->l->key){
        node->l=rotL(node->l);
        return rotR(node);
    }
    if(b<-1 && k<node->r->key){
        node->r=rotR(node->r);
        return rotL(node);
    }
    return node;
}

void inorderAVL(AVL* root, vector<int> &v){
    if(!root) return;
    inorderAVL(root->l,v);
    v.push_back(root->key);
    inorderAVL(root->r,v);
}

struct T23 {
    int val1,val2;
    bool two;
    T23* c1,*c2,*c3;
    T23(int v):val1(v),two(true),c1(NULL),c2(NULL),c3(NULL){}
};

T23* insert23(T23* node,int v){
    if(!node) return new T23(v);
    if(node->two){
        if(v<node->val1){
            node->val2=node->val1;
            node->val1=v;
        } else node->val2=v;
        node->two=false;
        return node;
    }
    if(v<node->val1) node->c1=insert23(node->c1,v);
    else if(v>node->val2) node->c3=insert23(node->c3,v);
    else node->c2=insert23(node->c2,v);
    return node;
}

void inorder23(T23* n, vector<int> &v){
    if(!n) return;
    if(n->two){
        inorder23(n->c1,v);
        v.push_back(n->val1);
        inorder23(n->c2,v);
    } else {
        inorder23(n->c1,v);
        v.push_back(n->val1);
        inorder23(n->c2,v);
        v.push_back(n->val2);
        inorder23(n->c3,v);
    }
}

vector<vector<int>> city;
int nsize=10;

vector<vector<int>> dpSim;

int simulateGrowth(int years){
    dpSim.assign(years+1, vector<int>(nsize,0));
    for(int i=0;i<nsize;i++) dpSim[0][i]=i+1;
    for(int y=1;y<=years;y++){
        for(int r=0;r<nsize;r++){
            int a = dpSim[y-1][r];
            int b = (r>0? dpSim[y-1][r-1]:0);
            int c = (r<nsize-1? dpSim[y-1][r+1]:0);
            dpSim[y][r] = a + max(b,c);
        }
    }
    int tot=0;
    for(int r=0;r<nsize;r++) tot+=dpSim[years][r];
    return tot;
}

vector<int> permutation;
int bestCost = 1e9;

int tspCost(vector<vector<int>> &dist){
    int c=0;
    for(int i=0;i<permutation.size()-1;i++)
        c+=dist[permutation[i]][permutation[i+1]];
    return c;
}

int runTSP(vector<vector<int>> &dist){
    int k = permutation.size();
    bestCost = 1e9;
    sort(permutation.begin(), permutation.end());
    do {
        bestCost = min(bestCost, tspCost(dist));
    } while(next_permutation(permutation.begin(), permutation.end()));
    return bestCost;
}

double predict(vector<double> &x, vector<double> &y, double val){
    int n=x.size();
    double sx=0, sy=0, sxy=0, sx2=0;
    for(int i=0;i<n;i++){
        sx+=x[i];
        sy+=y[i];
        sxy+=x[i]*y[i];
        sx2+=x[i]*x[i];
    }
    double m=(n*sxy - sx*sy)/(n*sx2 - sx*sx);
    double c=(sy - m*sx)/n;
    return m*val + c;
}

string randomEvent(){
    vector<string> ev={"traffic","pollution","growth","decline","shift","peak","drop"};
    string s="";
    int L=rand()%40+40;
    for(int i=0;i<L;i++) s+=ev[rand()%ev.size()]+" ";
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
        } else if(i<t.size() && t[i]!=p[j]){
            if(j) j=l[j-1];
            else i++;
        }
    }
    return res;
}

int main(){
    srand(time(NULL));

    AVL* root=NULL;
    for(int x:{10,20,5,15,30,25,35})
        root=insertAVL(root,x);
    vector<int> avlv;
    inorderAVL(root,avlv);

    T23* troot=NULL;
    for(int x:{5,2,8,1,3,7,9})
        troot=insert23(troot,x);
    vector<int> t23v;
    inorder23(troot,t23v);

    int growth = simulateGrowth(6);

    vector<vector<int>> dist(4, vector<int>(4,0));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dist[i][j]=abs(i-j)+1;

    permutation={0,1,2,3};
    int tspres = runTSP(dist);

    vector<double> x={1,2,3,4,5};
    vector<double> y={2,4,7,11,16};
    double pred = predict(x,y,6);

    string ev = randomEvent();
    string pat="traffic";
    vector<int> pos = KMP(ev,pat);

    cout<<growth<<"\n";
    cout<<tspres<<"\n";
    cout<<pred<<"\n";

    for(int a:avlv) cout<<a<<" ";
    cout<<"\n";

    for(int a:t23v) cout<<a<<" ";
    cout<<"\n";

    for(int p:pos) cout<<p<<" ";
    cout<<"\n";

    cout<<ev<<"\n";

    return 0;
}
