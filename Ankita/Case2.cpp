#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;

// --------------------------- Zone Class ---------------------------
class Zone {
public:
    int id;
    double waterDemand;   // liters per hour
    double energyDemand;  // kWh per hour
    double waterSupply;
    double energySupply;
    bool alert;

    Zone(int id) {
        this->id = id;
        waterDemand = 50 + rand()%50;   // random demand
        energyDemand = 10 + rand()%20;  // random demand
        waterSupply = 0;
        energySupply = 0;
        alert = false;
    }

    void updateDemands() {
        waterDemand = max(20.0, waterDemand + rand()%21 - 10);
        energyDemand = max(5.0, energyDemand + rand()%11 - 5);
    }
};

// --------------------------- Max Flow Simulation ---------------------------
class WaterFlowNetwork {
public:
    int N; // number of zones + source + sink
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    int source, sink;

    WaterFlowNetwork(int zoneCount) {
        N = zoneCount + 2; // extra for source and sink
        capacity.assign(N, vector<int>(N,0));
        flow.assign(N, vector<int>(N,0));
        source = 0;
        sink = N-1;
    }

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }

    int bfs(vector<int> &parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        queue<pair<int,int>> q;
        q.push({source, INT_MAX});

        while(!q.empty()) {
            int cur = q.front().first;
            int curFlow = q.front().second;
            q.pop();

            for(int next=0; next<N; next++) {
                if(parent[next]==-1 && capacity[cur][next]-flow[cur][next]>0) {
                    parent[next] = cur;
                    int newFlow = min(curFlow, capacity[cur][next]-flow[cur][next]);
                    if(next==sink) return newFlow;
                    q.push({next,newFlow});
                }
            }
        }
        return 0;
    }

    int maxFlow() {
        int totalFlow = 0;
        vector<int> parent(N);
        int newFlow;

        while((newFlow = bfs(parent))>0) {
            totalFlow += newFlow;
            int cur = sink;
            while(cur!=source) {
                int prev = parent[cur];
                flow[prev][cur] += newFlow;
                flow[cur][prev] -= newFlow;
                cur = prev;
            }
        }
        return totalFlow;
    }
};

// --------------------------- Smart Grid Class ---------------------------
class SmartGrid {
public:
    vector<Zone> zones;
    double totalWaterSupply;
    double totalEnergySupply;

    SmartGrid(int zoneCount) {
        for(int i=0;i<zoneCount;i++) zones.push_back(Zone(i));
        totalWaterSupply = 500; // liters
        totalEnergySupply = 200; // kWh
    }

    // ---------------- Water Distribution (Max-Flow Simulation) ----------------
    void distributeWater() {
        int Z = zones.size();
        WaterFlowNetwork net(Z);
        // Source to zones edges
        for(int i=0;i<Z;i++) net.addEdge(0,i+1,(int)zones[i].waterDemand);
        // Zones to sink edges
        for(int i=0;i<Z;i++) net.addEdge(i+1,Z+1,(int)zones[i].waterDemand);
        // Compute max flow
        int supplied = net.maxFlow();
        // Distribute water proportionally
        for(int i=0;i<Z;i++) {
            zones[i].waterSupply = min(zones[i].waterDemand, (double)net.flow[0][i+1]);
            zones[i].alert = zones[i].waterSupply < zones[i].waterDemand;
        }
        cout << "Total Water Supplied (Max-Flow): " << supplied << " liters" << endl;
    }

    // ---------------- Energy Distribution (Greedy Algorithm) ----------------
    void distributeEnergy() {
        double remaining = totalEnergySupply;
        // Sort zones by descending demand
        vector<pair<double,int>> order;
        for(int i=0;i<zones.size();i++) order.push_back({zones[i].energyDemand,i});
        sort(order.rbegin(), order.rend());
        for(auto &p: order) {
            int i = p.second;
            zones[i].energySupply = min(zones[i].energyDemand, remaining);
            remaining -= zones[i].energySupply;
            zones[i].alert = zones[i].energySupply < zones[i].energyDemand;
        }
    }

    // ---------------- Predictive Load Forecasting (EMA) ----------------
    void forecastLoad(vector<double> &waterHistory, vector<double> &energyHistory) {
        double alpha = 0.5;
        double waterEMA = waterHistory[0];
        double energyEMA = energyHistory[0];
        for(int i=1;i<waterHistory.size();i++) {
            waterEMA = alpha*waterHistory[i] + (1-alpha)*waterEMA;
            energyEMA = alpha*energyHistory[i] + (1-alpha)*energyEMA;
        }
        cout << "Forecast next hour - Water Demand: " << waterEMA
             << " liters, Energy Demand: " << energyEMA << " kWh" << endl;
    }

    // ---------------- Update Demands ----------------
    void updateZones() {
        for(auto &z: zones) z.updateDemands();
    }

    // ---------------- Print Status ----------------
    void printStatus(int timestep) {
        cout << "----- Smart Grid Status (Timestep " << timestep << ") -----" << endl;
        for(auto &z: zones) {
            cout << "Zone " << z.id
                 << ": Water=" << z.waterSupply << "/" << z.waterDemand
                 << " liters, Energy=" << z.energySupply << "/" << z.energyDemand
                 << " kWh"
                 << (z.alert ? " [ALERT]" : "") << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    // ---------------- Random Incident Detection ----------------
    void randomIncident() {
        int z = rand()%zones.size();
        cout << "Incident: Zone " << z << " has a leak or overload!" << endl;
        zones[z].alert = true;
        zones[z].waterSupply *= 0.7;
        zones[z].energySupply *= 0.7;
    }
};

// --------------------------- Main Simulation ---------------------------
int main() {
    srand(time(0));
    SmartGrid grid(5);

    vector<double> waterHistory = {250, 300, 280};
    vector<double> energyHistory = {120, 140, 130};

    for(int t=0; t<20; t++) {
        cout << endl;
        grid.updateZones();
        grid.distributeWater();
        grid.distributeEnergy();
        grid.printStatus(t);

        waterHistory.push_back(0);
        energyHistory.push_back(0);
        for(auto &z:grid.zones) {
            waterHistory.back() += z.waterDemand;
            energyHistory.back() += z.energyDemand;
        }

        if(t>=3) grid.forecastLoad(waterHistory, energyHistory);

        if(rand()%6==0) grid.randomIncident();
    }

    return 0;
}

