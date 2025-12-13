#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

// --------------------------- Waste Bin Class ---------------------------
class WasteBin {
public:
    int id;
    double capacity;  // total capacity
    double currentWaste;
    bool alert;       // overflow alert
    double x, y;      // coordinates for routing

    WasteBin(int id, double cap, double x, double y) {
        this->id = id;
        capacity = cap;
        currentWaste = rand() % (int)(cap / 2); // random initial waste
        alert = false;
        this->x = x;
        this->y = y;
    }

    void updateWaste() {
        // Waste accumulation per time step
        double delta = rand() % 10 + 1; 
        currentWaste += delta;
        if(currentWaste > capacity) {
            alert = true;
            currentWaste = capacity;
        } else {
            alert = false;
        }
    }
};

// --------------------------- Truck Class ---------------------------
class Truck {
public:
    int id;
    double capacity;
    double load;
    vector<int> route; // sequence of bin IDs
    double distanceTraveled;

    Truck(int id, double cap) {
        this->id = id;
        capacity = cap;
        load = 0;
        distanceTraveled = 0;
    }

    void reset() {
        load = 0;
        route.clear();
        distanceTraveled = 0;
    }
};

// --------------------------- Distance Function ---------------------------
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

// --------------------------- Smart Waste Collection System ---------------------------
class WasteSystem {
public:
    vector<WasteBin> bins;
    vector<Truck> trucks;
    double depotX, depotY; // Truck depot coordinates
    int totalAlerts;
    double totalDistanceTraveled;

    WasteSystem(int binCount, int truckCount) {
        depotX = 0; depotY = 0; // depot at origin
        totalAlerts = 0;
        totalDistanceTraveled = 0;
        for(int i=0;i<binCount;i++) {
            bins.push_back(WasteBin(i, 50 + rand()%50, rand()%100, rand()%100));
        }
        for(int i=0;i<truckCount;i++) {
            trucks.push_back(Truck(i, 100 + rand()%50));
        }
    }

    // ---------------- Update Bin Waste ----------------
    void updateBins() {
        for(auto &b: bins) b.updateWaste();
    }

    // ---------------- First-Fit Decreasing Bin Packing for Trucks ----------------
    void assignBinsToTrucks() {
        vector<WasteBin*> sortedBins;
        for(auto &b: bins) sortedBins.push_back(&b);
        sort(sortedBins.begin(), sortedBins.end(), [](WasteBin* a, WasteBin* b) {
            return a->currentWaste > b->currentWaste;
        });

        for(auto &t: trucks) t.reset();
        totalAlerts = 0;

        for(auto bptr: sortedBins) {
            bool assigned = false;
            for(auto &t: trucks) {
                if(t.load + bptr->currentWaste <= t.capacity) {
                    t.route.push_back(bptr->id);
                    t.load += bptr->currentWaste;
                    assigned = true;
                    break;
                }
            }
            if(!assigned) {
                bptr->alert = true;
                totalAlerts++;
            }
        }
    }

    // ---------------- Nearest Neighbor Route Optimization ----------------
    void optimizeRoutes() {
        for(auto &t: trucks) {
            vector<int> optimized;
            double currX = depotX, currY = depotY;
            vector<int> remaining = t.route;
            while(!remaining.empty()) {
                double minDist = 1e9;
                int minIdx = 0;
                for(int i=0;i<remaining.size();i++) {
                    WasteBin &b = bins[remaining[i]];
                    double d = distance(currX,currY,b.x,b.y);
                    if(d<minDist) {
                        minDist = d;
                        minIdx = i;
                    }
                }
                int nextBin = remaining[minIdx];
                optimized.push_back(nextBin);
                currX = bins[nextBin].x;
                currY = bins[nextBin].y;
                t.distanceTraveled += minDist;
                remaining.erase(remaining.begin()+minIdx);
            }
            t.distanceTraveled += distance(currX,currY,depotX,depotY);
            t.route = optimized;
            totalDistanceTraveled += t.distanceTraveled;
        }
    }

    // ---------------- Collect Waste ----------------
    void collectWaste() {
        for(auto &t: trucks) {
            for(int binID: t.route) {
                WasteBin &b = bins[binID];
                b.currentWaste = 0;
                b.alert = false;
            }
            t.load = 0;
        }
    }

    // ---------------- Simulate Random Road Block ----------------
    void simulateRoadBlocks() {
        if(rand()%5==0) {
            int b = rand()%bins.size();
            cout << "Road Block near Bin " << b << "! Truck routes may be delayed." << endl;
        }
    }

    // ---------------- Print Status ----------------
    void printStatus(int timestep) {
        cout << "----- Waste Collection Status (Timestep " << timestep << ") -----" << endl;
        for(auto &b: bins) {
            cout << "Bin " << setw(2) << b.id 
                 << " Waste=" << setw(5) << b.currentWaste 
                 << "/" << setw(5) << b.capacity
                 << (b.alert ? " [ALERT]" : "") << endl;
        }
        for(auto &t: trucks) {
            cout << "Truck " << setw(2) << t.id 
                 << " Load=" << setw(5) << t.load 
                 << " Route=";
            for(auto rid: t.route) cout << rid << " ";
            cout << " Distance=" << fixed << setprecision(2) << t.distanceTraveled << endl;
        }
        cout << "Total Alerts: " << totalAlerts << ", Total Distance Traveled: " << totalDistanceTraveled << endl;
        cout << "--------------------------------------------------------" << endl;
    }

    // ---------------- Print ASCII Map ----------------
    void printMap() {
        const int size = 20;
        char map[size][size];
        for(int i=0;i<size;i++) for(int j=0;j<size;j++) map[i][j]='.';
        for(auto &b: bins) {
            int x = min(size-1,(int)(b.x/5));
            int y = min(size-1,(int)(b.y/5));
            map[y][x] = b.alert ? '!' : 'B';
        }
        int depotXmap = min(size-1,(int)(depotX/5));
        int depotYmap = min(size-1,(int)(depotY/5));
        map[depotYmap][depotXmap] = 'D';
        cout << "ASCII Map (B=Bin, !=Overflow, D=Depot)" << endl;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++) cout << map[i][j];
            cout << endl;
        }
    }

    // ---------------- Simulate Step ----------------
    void simulateStep() {
        updateBins();
        assignBinsToTrucks();
        simulateRoadBlocks();
        optimizeRoutes();
        collectWaste();
    }

    // ---------------- Display Statistics ----------------
    void displayStatistics() {
        double avgTruckUtil = 0;
        double avgRouteDist = 0;
        for(auto &t: trucks) {
            avgTruckUtil += t.load / t.capacity;
            avgRouteDist += t.distanceTraveled;
        }
        avgTruckUtil /= trucks.size();
        avgRouteDist /= trucks.size();
        cout << "=== System Statistics ===" << endl;
        cout << "Average Truck Utilization: " << avgTruckUtil*100 << "%" << endl;
        cout << "Average Truck Route Distance: " << avgRouteDist << endl;
        cout << "Total Alerts: " << totalAlerts << endl;
        cout << "=========================" << endl;
    }
};

// --------------------------- Main Simulation ---------------------------
int main() {
    srand(time(0));
    WasteSystem system(15, 5); // 15 bins, 5 trucks

    for(int t=0; t<25; t++) {
        cout << endl;
        system.simulateStep();
        system.printStatus(t);
        system.printMap();
    }

    system.displayStatistics();
    return 0;
}

