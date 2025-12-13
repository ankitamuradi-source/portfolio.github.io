#include <bits/stdc++.h>
using namespace std;

/*************************************************************
 * 1. RABIN-KARP ALGORITHM
 *************************************************************/
const int PRIME = 101;

vector<int> rabinKarpSearch(const string &text, const string &pattern){
    vector<int> positions;
    int n = text.size(), m = pattern.size();
    if(m==0 || n<m) return positions;

    long long patternHash=0, textHash=0, h=1;
    for(int i=0;i<m-1;i++) h = (h*256)%PRIME;
    for(int i=0;i<m;i++){
        patternHash = (256*patternHash + pattern[i])%PRIME;
        textHash = (256*textHash + text[i])%PRIME;
    }

    for(int i=0;i<=n-m;i++){
        if(patternHash == textHash && text.substr(i,m) == pattern) positions.push_back(i);
        if(i<n-m) textHash = (256*(textHash - text[i]*h) + text[i+m])%PRIME;
        if(textHash<0) textHash+=PRIME;
    }
    return positions;
}

/*************************************************************
 * 2. TRIE
 *************************************************************/
struct TrieNode{
    map<char,TrieNode*> children;
    bool isEnd;
    TrieNode(): isEnd(false){}
};

class Trie{
public:
    TrieNode* root;
    Trie(){ root=new TrieNode(); }
    void insert(const string &word){
        TrieNode* node=root;
        for(char c: word){
            if(!node->children[c]) node->children[c]=new TrieNode();
            node=node->children[c];
        }
        node->isEnd=true;
    }
    vector<string> autocomplete(const string &prefix){
        TrieNode* node=root;
        vector<string> results;
        for(char c: prefix){
            if(!node->children[c]) return results;
            node=node->children[c];
        }
        function<void(TrieNode*, string)> dfs=[&](TrieNode* n,string s){
            if(n->isEnd) results.push_back(s);
            for(auto &p:n->children) dfs(p.second,s+p.first);
        };
        dfs(node,prefix);
        return results;
    }
};

/*************************************************************
 * 3. FENWICK TREE
 *************************************************************/
class FenwickTree{
public:
    vector<int> BIT;
    int n;
    FenwickTree(int size){ n=size; BIT.assign(n+1,0);}
    void update(int idx,int val){ for(;idx<=n;idx+=idx&-idx) BIT[idx]+=val; }
    int query(int idx){ int sum=0; for(;idx>0;idx-=idx&-idx) sum+=BIT[idx]; return sum; }
    int rangeQuery(int l,int r){ return query(r)-query(l-1); }
};

/*************************************************************
 * 4. SPARSE TABLE / ARRAY QUERIES
 *************************************************************/
class SparseTable{
public:
    vector<vector<int>> st;
    vector<int> log;
    int n;
    SparseTable(const vector<int> &arr){
        n=arr.size();
        log.assign(n+1,0);
        for(int i=2;i<=n;i++) log[i]=log[i/2]+1;
        int K=log[n]+1;
        st.assign(n,vector<int>(K));
        for(int i=0;i<n;i++) st[i][0]=arr[i];
        for(int j=1;j<K;j++){
            for(int i=0;i+(1<<j)<=n;i++){
                st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int queryMin(int l,int r){
        int j=log[r-l+1];
        return min(st[l][j],st[r-(1<<j)+1][j]);
    }
};

/*************************************************************
 * 5. DFS/BFS GRAPH
 *************************************************************/
void DFS(int u, vector<vector<int>> &adj, vector<bool> &visited){
    visited[u]=true;
    cout<<u<<" ";
    for(int v: adj[u]) if(!visited[v]) DFS(v,adj,visited);
}

void BFS(int start, vector<vector<int>> &adj){
    vector<bool> visited(adj.size(),false);
    queue<int> q; q.push(start); visited[start]=true;
    cout<<"BFS Traversal: ";
    while(!q.empty()){
        int u=q.front(); q.pop();
        cout<<u<<" ";
        for(int v: adj[u]){
            if(!visited[v]) { visited[v]=true; q.push(v); }
        }
    }
    cout<<endl;
}

/*************************************************************
 * Helper Functions
 *************************************************************/
vector<string> splitText(const string &text){
    stringstream ss(text); string word;
    vector<string> words;
    while(ss>>word) words.push_back(word);
    return words;
}

vector<vector<int>> buildWordGraph(const vector<string> &words){
    int n=words.size();
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++) adj[i].push_back(i+1);
    return adj;
}

/*************************************************************
 * REPORTING FUNCTIONS
 *************************************************************/
void reportRabinKarp(const vector<string> &docs, const vector<string> &patterns){
    cout<<"\n--- Rabin-Karp Search ---\n";
    for(auto &p: patterns){
        cout<<"Pattern '"<<p<<"' positions:\n";
        for(int i=0;i<docs.size();i++){
            vector<int> pos=rabinKarpSearch(docs[i],p);
            cout<<"Doc "<<i+1<<": ";
            if(pos.empty()) cout<<"None";
            else for(int x: pos) cout<<"["<<x<<"] ";
            cout<<endl;
        }
    }
}

void reportTrie(Trie &trie,const string &prefix){
    cout<<"\n--- Trie Autocomplete for '"<<prefix<<"' ---\n";
    vector<string> res=trie.autocomplete(prefix);
    if(res.empty()) cout<<"No suggestions\n";
    else for(auto &s: res) cout<<s<<" "; cout<<endl;
}

void reportFenwick(FenwickTree &ft,int l,int r){
    cout<<"\nFenwick Tree: Sum of word lengths "<<l<<"-"<<r<<": "<<ft.rangeQuery(l,r)<<endl;
}

void reportSparseTable(SparseTable &st,int l,int r){
    cout<<"\nSparse Table: Min word length "<<l<<"-"<<r<<": "<<st.queryMin(l,r)<<endl;
}

void reportGraph(vector<vector<int>> &adj){
    cout<<"\nDFS Traversal: ";
    vector<bool> visited(adj.size(),false);
    DFS(0,adj,visited); cout<<endl;
    BFS(0,adj);
}

/*************************************************************
 * MAIN PROGRAM
 *************************************************************/
int main(){
    cout<<"=== Document Analytics Tool (Rabin-Karp + Trie + Fenwick + Sparse Table + Graph) ===\n";

    vector<string> documents={
        "Rabin-Karp efficiently finds patterns in text.",
        "Trie supports prefix search and autocomplete.",
        "Fenwick Tree allows cumulative queries on word lengths.",
        "DFS/BFS explore word relations as a graph."
    };

    vector<string> allWords;
    Trie trie;
    vector<int> wordLengths;

    for(auto &doc: documents){
        vector<string> words=splitText(doc);
        allWords.insert(allWords.end(),words.begin(),words.end());
        for(auto &w: words){ trie.insert(w); wordLengths.push_back(w.size()); }
    }

    // Rabin-Karp patterns
    vector<string> patterns={"Rabin","Trie","DFS"};
    reportRabinKarp(documents,patterns);

    // Trie autocomplete
    reportTrie(trie,"Tr");
    reportTrie(trie,"F");

    // Fenwick Tree
    FenwickTree ft(wordLengths.size());
    for(int i=0;i<wordLengths.size();i++) ft.update(i+1,wordLengths[i]);
    reportFenwick(ft,2,6);

    // Sparse Table
    SparseTable st(wordLengths);
    reportSparseTable(st,1,5);

    // Graph
    vector<vector<int>> adj=buildWordGraph(allWords);
    reportGraph(adj);

    // Extended statistics
    cout<<"\n--- Extended Word Stats ---\n";
    cout<<"Total words: "<<allWords.size()<<endl;
    set<string> unique(allWords.begin(),allWords.end());
    cout<<"Unique words: "<<unique.size()<<endl;
    int maxLen=*max_element(wordLengths.begin(),wordLengths.end());
    int minLen=*min_element(wordLengths.begin(),wordLengths.end());
    double avg=accumulate(wordLengths.begin(),wordLengths.end(),0.0)/wordLengths.size();
    cout<<"Max word length: "<<maxLen<<", Min: "<<minLen<<", Avg: "<<avg<<endl;

    return 0;
}
