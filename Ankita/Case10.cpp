#include <bits/stdc++.h>
using namespace std;

/*************************************************************
 * 1. HEAP / PRIORITY QUEUE: Top-k products by sales
 *************************************************************/
class SalesAnalytics {
public:
    vector<string> products;
    vector<int> sales;

    SalesAnalytics(vector<string> p, vector<int> s) : products(p), sales(s) {}

    vector<pair<int,string>> topK(int k) {
        priority_queue<pair<int,string>> pq;
        for(int i=0;i<products.size();i++) pq.push({sales[i],products[i]});
        vector<pair<int,string>> result;
        for(int i=0;i<k && !pq.empty();i++){
            result.push_back(pq.top()); pq.pop();
        }
        return result;
    }

    void printTopK(int k){
        vector<pair<int,string>> top=topK(k);
        cout<<"\nTop "<<k<<" Products by Sales:\n";
        for(auto &p: top) cout<<p.second<<" with "<<p.first<<" sales\n";
    }
};

/*************************************************************
 * 2. MERGE SORT: Sorting products by sales
 *************************************************************/
void merge(vector<int> &arr,int l,int m,int r){
    vector<int> L(arr.begin()+l,arr.begin()+m+1);
    vector<int> R(arr.begin()+m+1,arr.begin()+r+1);
    int i=0,j=0,k=l;
    while(i<L.size() && j<R.size()){
        if(L[i]<=R[j]) arr[k++]=L[i++];
        else arr[k++]=R[j++];
    }
    while(i<L.size()) arr[k++]=L[i++];
    while(j<R.size()) arr[k++]=R[j++];
}

void mergeSort(vector<int> &arr,int l,int r){
    if(l>=r) return;
    int m=(l+r)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

/*************************************************************
 * 3. DIJKSTRA'S ALGORITHM: Delivery route optimization
 *************************************************************/
class DeliveryNetwork {
public:
    int n;
    vector<vector<pair<int,int>>> adj;

    DeliveryNetwork(int nodes): n(nodes) { adj.resize(n); }

    void addEdge(int u,int v,int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<int> shortestPaths(int src){
        vector<int> dist(n,INT_MAX);
        dist[src]=0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            int u=pq.top().second; int d=pq.top().first; pq.pop();
            if(d>dist[u]) continue;
            for(auto &edge: adj[u]){
                int v=edge.first, w=edge.second;
                if(dist[u]+w<dist[v]){
                    dist[v]=dist[u]+w;
                    pq.push({dist[v],v});
                }
            }
        }
        return dist;
    }

    void printShortestPaths(int src){
        vector<int> dist=shortestPaths(src);
        cout<<"\nShortest paths from node "<<src<<":\n";
        for(int i=0;i<dist.size();i++) cout<<"Node "<<i<<": "<<dist[i]<<endl;
    }
};

/*************************************************************
 * 4. BACKTRACKING: Task scheduling
 *************************************************************/
class TaskScheduler {
public:
    vector<int> tasks;
    int maxTime;
    vector<vector<int>> allSchedules;

    TaskScheduler(vector<int> t,int mt): tasks(t), maxTime(mt) {}

    void schedule(int idx, vector<int> &current){
        if(idx==tasks.size()){
            int sum=accumulate(current.begin(),current.end(),0);
            if(sum<=maxTime) allSchedules.push_back(current);
            return;
        }
        // Include
        current.push_back(tasks[idx]);
        schedule(idx+1,current);
        current.pop_back();
        // Exclude
        schedule(idx+1,current);
    }

    void computeSchedules(){
        vector<int> current;
        schedule(0,current);
    }

    void printSchedules(){
        cout<<"\nPossible schedules within max time "<<maxTime<<":\n";
        for(auto &sched: allSchedules){
            for(int t:sched) cout<<t<<" ";
            cout<<endl;
        }
    }
};

/*************************************************************
 * 5. HELPER: Generate random sales data for scalability
 *************************************************************/
vector<string> generateProducts(int n){
    vector<string> products;
    for(int i=1;i<=n;i++) products.push_back("Product_"+to_string(i));
    return products;
}

vector<int> generateSales(int n){
    vector<int> sales;
    srand(time(0));
    for(int i=0;i<n;i++) sales.push_back(rand()%1000 + 50);
    return sales;
}

vector<int> generateTasks(int n){
    vector<int> tasks;
    srand(time(0)+1);
    for(int i=0;i<n;i++) tasks.push_back(rand()%5 + 1);
    return tasks;
}

/*************************************************************
 * MAIN PROGRAM
 *************************************************************/
int main(){
    cout<<"=== Expanded Business Analytics Tool (Heap + Dijkstra + MergeSort + Backtracking) ===\n";

    // Generate large product catalog
    int numProducts=20; // can be increased
    vector<string> products=generateProducts(numProducts);
    vector<int> sales=generateSales(numProducts);

    SalesAnalytics sa(products,sales);
    sa.printTopK(5); // Top 5 products

    // MergeSort for sales
    vector<int> sortedSales=sales;
    mergeSort(sortedSales,0,sortedSales.size()-1);
    cout<<"\nSales sorted ascending: ";
    for(int x: sortedSales) cout<<x<<" ";
    cout<<endl;

    // Delivery network example
    DeliveryNetwork dn(numProducts);
    // Randomly generate edges
    for(int i=0;i<numProducts-1;i++){
        dn.addEdge(i,i+1,rand()%10+1);
    }
    dn.printShortestPaths(0);

    // Task scheduling
    vector<int> tasks=generateTasks(8); // 8 tasks
    int maxTime=10;
    TaskScheduler ts(tasks,maxTime);
    ts.computeSchedules();
    ts.printSchedules();

    // Extended statistics
    cout<<"\n--- Extended Sales Statistics ---\n";
    cout<<"Total products: "<<products.size()<<endl;
    int totalSales=accumulate(sales.begin(),sales.end(),0);
    int maxSale=*max_element(sales.begin(),sales.end());
    int minSale=*min_element(sales.begin(),sales.end());
    double avgSale=(double)totalSales/sales.size();
    cout<<"Total sales: "<<totalSales<<", Max sale: "<<maxSale<<", Min sale: "<<minSale<<", Avg sale: "<<avgSale<<endl;

    return 0;
}

