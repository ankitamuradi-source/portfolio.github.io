#include <bits/stdc++.h>
using namespace std;

/*****************************
 * BOYER-MOORE STRING SEARCH
 *****************************/
unordered_map<char, int> buildBadCharTable(const string &pattern) {
    unordered_map<char, int> badChar;
    int m = pattern.size();
    for (int i = 0; i < m; i++) badChar[pattern[i]] = i;
    return badChar;
}

vector<int> preprocessSuffixes(const string &pattern) {
    int m = pattern.size();
    vector<int> suff(m, 0);
    suff[m-1] = m;
    int g = m-1, f = 0;
    for(int i=m-2;i>=0;i--){
        if(i>g && suff[i+m-1-f] < i-g)
            suff[i] = suff[i+m-1-f];
        else{
            if(i<g) g=i;
            f=i;
            while(g>=0 && pattern[g]==pattern[g+m-1-f]) g--;
            suff[i] = f-g;
        }
    }
    return suff;
}

vector<int> buildGoodSuffixTable(const string &pattern){
    int m = pattern.size();
    vector<int> suff = preprocessSuffixes(pattern);
    vector<int> good(m, m);
    for(int i=0;i<m-1;i++){
        good[m-1-suff[i]] = m-1-i;
    }
    return good;
}

vector<int> boyerMooreSearch(const string &text, const string &pattern){
    vector<int> res;
    int n = text.size(), m = pattern.size();
    if(m==0) return res;

    unordered_map<char,int> badChar = buildBadCharTable(pattern);
    vector<int> goodSuffix = buildGoodSuffixTable(pattern);

    int s=0;
    while(s<=n-m){
        int j = m-1;
        while(j>=0 && pattern[j]==text[s+j]) j--;
        if(j<0){
            res.push_back(s);
            s += goodSuffix[0];
        } else {
            int bcShift = badChar.count(text[s+j]) ? max(1,j-badChar[text[s+j]]) : j+1;
            int gsShift = goodSuffix[j];
            s += max(bcShift,gsShift);
        }
    }
    return res;
}

/*****************************
 * KMP ALGORITHM
 *****************************/
vector<int> computeLPS(const string &pattern){
    int m = pattern.size();
    vector<int> lps(m,0);
    int len=0,i=1;
    while(i<m){
        if(pattern[i]==pattern[len]){
            len++; lps[i]=len; i++;
        } else {
            if(len!=0) len=lps[len-1];
            else {lps[i]=0;i++;}
        }
    }
    return lps;
}

vector<int> kmpSearch(const string &text, const string &pattern){
    vector<int> res;
    int n = text.size(), m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    int i=0,j=0;
    while(i<n){
        if(pattern[j]==text[i]){i++; j++;}
        if(j==m){ res.push_back(i-j); j=lps[j-1]; }
        else if(i<n && pattern[j]!=text[i]){
            if(j!=0) j=lps[j-1];
            else i++;
        }
    }
    return res;
}

/*****************************
 * TRIE STRUCTURE FOR MULTIPLE WORDS
 *****************************/
struct TrieNode{
    unordered_map<char,TrieNode*> children;
    bool isEnd=false;
};

class Trie{
private:
    TrieNode* root;
public:
    Trie(){ root = new TrieNode(); }

    void insert(const string &word){
        TrieNode* node = root;
        for(char c: word){
            if(!node->children.count(c)) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string &word){
        TrieNode* node = root;
        for(char c: word){
            if(!node->children.count(c)) return false;
            node = node->children[c];
        }
        return node->isEnd;
    }

    void displayAll(TrieNode* node, string prefix){
        if(node->isEnd) cout << prefix << endl;
        for(auto &p: node->children){
            displayAll(p.second, prefix+p.first);
        }
    }

    void displayAllWords(){ displayAll(root,""); }
};

/*****************************
 * DIJKSTRA ALGORITHM (GRAPH)
 *****************************/
struct Edge{
    int to, weight;
};
vector<int> dijkstra(int n, int start, vector<vector<Edge>> &graph){
    vector<int> dist(n, INT_MAX);
    dist[start]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,start});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto &e: graph[u]){
            if(dist[u]+e.weight<dist[e.to]){
                dist[e.to]=dist[u]+e.weight;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

/*****************************
 * MAIN PROGRAM
 *****************************/
int main(){
    cout<<"=== Document Search & Graph Analysis Tool ===\n";

    // Example text
    string text = "THIS IS A SIMPLE EXAMPLE. THIS EXAMPLE SHOWS BOYER MOORE AND KMP.";
    string pattern1 = "EXAMPLE";
    string pattern2 = "THIS";

    // Boyer-Moore search
    vector<int> bmPos = boyerMooreSearch(text,pattern1);
    cout<<"\nBoyer-Moore positions for '"<<pattern1<<"': ";
    for(int p: bmPos) cout<<p<<" ";
    cout<<endl;

    // KMP search
    vector<int> kmpPos = kmpSearch(text,pattern2);
    cout<<"\nKMP positions for '"<<pattern2<<"': ";
    for(int p: kmpPos) cout<<p<<" ";
    cout<<endl;

    // Trie example
    Trie trie;
    trie.insert("THIS");
    trie.insert("THAT");
    trie.insert("THERE");
    trie.insert("EXAMPLE");
    cout<<"\nAll words in trie:\n";
    trie.displayAllWords();

    // Dijkstra example graph
    int n = 5;
    vector<vector<Edge>> graph(n);
    graph[0].push_back({1,2});
    graph[0].push_back({2,5});
    graph[1].push_back({2,1});
    graph[1].push_back({3,3});
    graph[2].push_back({3,2});
    graph[3].push_back({4,1});
    vector<int> distances = dijkstra(n,0,graph);
    cout<<"\nShortest distances from node 0: ";
    for(int i=0;i<n;i++) cout<<distances[i]<<" ";
    cout<<endl;

    return 0;
}

