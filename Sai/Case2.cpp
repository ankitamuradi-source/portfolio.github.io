#include <bits/stdc++.h>
using namespace std;

struct Patient {
    string name;
    int age;
    int fever;
    int cough;
    int fatigue;
    int riskScore;
};

struct Node {
    int id;
    vector<int> neighbors;
};

vector<Node> graphNodes;
vector<int> visitedRisk;
vector<Patient> patients;
unordered_map<string,int> hashTable;
vector<int> lps;

int classifyRisk(int fever, int cough, int fatigue) {
    if (fever > 80 && cough > 70 && fatigue > 60) return 3;
    if (fever > 60 && cough > 50) return 2;
    if (fever > 40) return 1;
    return 0;
}

int dpSpread[205][205];
int spreadModel(int days, int contacts) {
    for (int i = 0; i <= days; i++)
        for (int j = 0; j <= contacts; j++)
            dpSpread[i][j] = 0;
    dpSpread[0][0] = 1;
    for (int i = 1; i <= days; i++) {
        for (int j = 0; j <= contacts; j++) {
            int stay = dpSpread[i-1][j];
            int infect = j>0 ? dpSpread[i-1][j-1] : 0;
            dpSpread[i][j] = stay + infect;
        }
    }
    return dpSpread[days][contacts];
}

void buildHashTable() {
    for (int i = 0; i < patients.size(); i++)
        hashTable[patients[i].name] = i;
}

int searchPatient(string name) {
    if (hashTable.find(name) != hashTable.end())
        return hashTable[name];
    return -1;
}

void buildLPS(string pat) {
    lps.assign(pat.size(),0);
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
}

vector<int> KMP(string txt, string pat) {
    vector<int> matches;
    buildLPS(pat);
    int i = 0, j = 0;
    while (i < txt.size()) {
        if (txt[i] == pat[j]) {
            i++; j++;
        }
        if (j == pat.size()) {
            matches.push_back(i - j);
            j = lps[j-1];
        } else if (i < txt.size() && txt[i] != pat[j]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }
    return matches;
}

long long rabinHash(string s, long long base, long long mod) {
    long long h = 0;
    for (char c : s) h = (h * base + c) % mod;
    return h;
}

vector<int> rabinKarp(string txt, string pat) {
    vector<int> res;
    long long base = 257, mod = 1000000007;
    int n = txt.size(), m = pat.size();
    long long patHash = rabinHash(pat, base, mod);
    long long txtHash = rabinHash(txt.substr(0,m), base, mod);
    long long basePow = 1;
    for (int i = 1; i < m; i++) basePow = (basePow * base) % mod;

    for (int i = 0; i <= n - m; i++) {
        if (txtHash == patHash) {
            if (txt.substr(i,m) == pat) res.push_back(i);
        }
        if (i < n - m) {
            txtHash = (txtHash - txt[i] * basePow) % mod;
            if (txtHash < 0) txtHash += mod;
            txtHash = (txtHash * base + txt[i+m]) % mod;
        }
    }
    return res;
}

void dfsRisk(int u) {
    visitedRisk[u] = 1;
    for (int v : graphNodes[u].neighbors) {
        if (!visitedRisk[v]) dfsRisk(v);
    }
}

void bfsRisk(int start) {
    queue<int> q;
    visitedRisk.assign(graphNodes.size(),0);
    visitedRisk[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graphNodes[u].neighbors) {
            if (!visitedRisk[v]) {
                visitedRisk[v] = 1;
                q.push(v);
            }
        }
    }
}

string generateRandomRecord() {
    vector<string> symptoms = {"fever","cough","fatigue","pain","infection"};
    string s = "";
    int len = rand() % 50 + 50;
    for (int i = 0; i < len; i++) {
        s += symptoms[rand() % symptoms.size()];
        s += " ";
    }
    return s;
}

void printPatients() {
    for (auto &p : patients) {
        cout << p.name << " "
             << p.age << " "
             << p.fever << " "
             << p.cough << " "
             << p.fatigue << " "
             << p.riskScore << "\n";
    }
}

int main() {
    srand(time(0));

    patients.push_back({"Arun", 30, 70, 60, 40, 0});
    patients.push_back({"Meera", 22, 90, 80, 70, 0});
    patients.push_back({"Kiran", 45, 50, 40, 30, 0});
    patients.push_back({"Sara", 55, 85, 75, 65, 0});
    patients.push_back({"John", 29, 30, 20, 10, 0});

    for (auto &p : patients)
        p.riskScore = classifyRisk(p.fever, p.cough, p.fatigue);

    buildHashTable();

    graphNodes.resize(6);
    for (int i = 0; i < 6; i++) graphNodes[i].id = i;

    graphNodes[0].neighbors = {1,2};
    graphNodes[1].neighbors = {0,3};
    graphNodes[2].neighbors = {0,4};
    graphNodes[3].neighbors = {1,5};
    graphNodes[4].neighbors = {2};
    graphNodes[5].neighbors = {3};

    visitedRisk.assign(6,0);
    dfsRisk(0);

    bfsRisk(0);

    int spreadValue = spreadModel(5,3);

    string record = generateRandomRecord();
    string pattern = "fever";
    vector<int> matches1 = KMP(record, pattern);
    vector<int> matches2 = rabinKarp(record, pattern);

    printPatients();

    cout << "Search: " << searchPatient("Sara") << "\n";
    cout << "Risk Spread Value: " << spreadValue << "\n";

    cout << "KMP Matches: ";
    for (int x : matches1) cout << x << " ";
    cout << "\n";

    cout << "Rabin-Karp Matches: ";
    for (int x : matches2)
