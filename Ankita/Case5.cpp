#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>

using namespace std;

// --------------------------- Camera Class ---------------------------
class Camera {
public:
    int id;
    double x, y;
    double radius;
    bool active;

    Camera(int id, double x, double y, double r) {
        this->id = id;
        this->x = x;
        this->y = y;
        radius = r;
        active = true;
    }

    double distance(double px, double py) {
        return sqrt(pow(px-x,2) + pow(py-y,2));
    }

    bool covers(double px, double py) {
        return distance(px, py) <= radius;
    }
};

// --------------------------- Event Class ---------------------------
class Event {
public:
    int id;
    double x, y;
    double severity; // 0-100
    int timestamp;
    int clusterID;

    Event(int id, double x, double y, double severity, int ts) {
        this->id = id;
        this->x = x;
        this->y = y;
        this->severity = severity;
        timestamp = ts;
        clusterID = -1;
    }
};

// --------------------------- Alert Class ---------------------------
class Alert {
public:
    int eventID;
    double riskScore;
    int level;

    Alert(int eid, double score) {
        eventID = eid;
        riskScore = score;
        level = score > 80 ? 3 : score > 60 ? 2 : 1;
    }

    bool operator<(const Alert &other) const {
        return level < other.level; // Higher alert level = higher priority
    }
};

// --------------------------- Security Hub ---------------------------
class SecurityHub {
public:
    vector<Camera> cameras;
    vector<Event> events;
    priority_queue<Alert> alertsQueue;
    int timeStep;

    SecurityHub() { timeStep = 0; }

    void deployCameras(int n) {
        for(int i=0;i<n;i++) {
            double x = rand()%100;
            double y = rand()%100;
            double radius = 10 + rand()%15;
            cameras.push_back(Camera(i,x,y,radius));
        }
    }

    void generateEvents(int n) {
        for(int i=0;i<n;i++) {
            double x = rand()%100;
            double y = rand()%100;
            double severity = rand()%101;
            events.push_back(Event(events.size(),x,y,severity,timeStep));
        }
    }

    // ---------------- Sliding Window + EMA Risk Scoring ----------------
    void detectIntrusions() {
        for(auto &e: events) {
            int coverageCount = 0;
            for(auto &c: cameras) if(c.active && c.covers(e.x,e.y)) coverageCount++;
            double baseRisk = coverageCount==0 ? min(100.0,e.severity+50) : max(0.0,e.severity-coverageCount*10);
            double emaRisk = 0.3*baseRisk + 0.7*(timeStep>0 ? e.severity : baseRisk);
            alertsQueue.push(Alert(e.id, emaRisk));
        }
    }

    // ---------------- Zone-based Camera Optimization ----------------
    void optimizeCameras() {
        map<int,int> coverageCount;
        for(auto &c: cameras) coverageCount[c.id]=0;
        for(auto &c: cameras) {
            for(auto &e: events) if(c.covers(e.x,e.y)) coverageCount[c.id]++;
        }
        vector<int> counts;
        for(auto &kv: coverageCount) counts.push_back(kv.second);
        sort(counts.begin(), counts.end());
        int median = counts[counts.size()/2];
        for(auto &c: cameras) if(coverageCount[c.id]<median) c.active=false;
    }

    // ---------------- Event Clustering (Distance-based) ----------------
    void clusterEvents(double threshold=10.0) {
        int clusterID = 0;
        for(auto &e: events) {
            if(e.clusterID != -1) continue;
            e.clusterID = clusterID;
            for(auto &other: events) {
                if(other.clusterID == -1 && e.distance(other.x,other.y)<threshold) other.clusterID = clusterID;
            }
            clusterID++;
        }
    }

    // ---------------- Process Alerts ----------------
    void processAlerts() {
        cout << "Processing Alerts:" << endl;
        while(!alertsQueue.empty()) {
            Alert a = alertsQueue.top(); alertsQueue.pop();
            Event &e = events[a.eventID];
            cout << "Event " << e.id << " at (" << e.x << "," << e.y << ") Severity=" << e.severity 
                 << " RiskScore=" << a.riskScore << " Level=" << a.level 
                 << " ClusterID=" << e.clusterID << endl;
        }
    }

    // ---------------- Simulate Random Events ----------------
    void simulateRandomEvents() {
        int n = 1 + rand()%3;
        generateEvents(n);
        cout << n << " new events generated." << endl;
    }

    // ---------------- Print Camera Status ----------------
    void printCameraStatus() {
        cout << "Cameras Status:" << endl;
        for(auto &c: cameras) {
            cout << "Camera " << c.id << " (" << c.x << "," << c.y << ") Radius=" 
                 << c.radius << (c.active?" Active":" Inactive") << endl;
        }
    }

    // ---------------- Print Hotspot Map ----------------
    void printHotspotMap() {
        const int size = 20;
        char map[size][size];
        for(int i=0;i<size;i++) for(int j=0;j<size;j++) map[i][j]='.';
        for(auto &e: events) {
            int x = min(size-1,(int)(e.x/5));
            int y = min(size-1,(int)(e.y/5));
            map[y][x] = 'E';
        }
        for(auto &c: cameras) {
            int x = min(size-1,(int)(c.x/5));
            int y = min(size-1,(int)(c.y/5));
            map[y][x] = c.active ? 'C' : 'c';
        }
        cout << "Hotspot Map (E=Event, C=Active Camera, c=Inactive Camera)" << endl;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++) cout<<map[i][j];
            cout<<endl;
        }
    }

    // ---------------- Run Simulation Step ----------------
    void simulateStep() {
        timeStep++;
        simulateRandomEvents();
        detectIntrusions();
        optimizeCameras();
        clusterEvents();
        processAlerts();
        printCameraStatus();
        printHotspotMap();
        cout << "---------------------------------------------" << endl;
    }

    // ---------------- Run Simulation ----------------
    void runSimulation(int steps) {
        for(int t=0;t<steps;t++) simulateStep();
    }
};

// --------------------------- Main Function ---------------------------
int main() {
    srand(time(0));
    SecurityHub hub;
    hub.deployCameras(12);
    hub.generateEvents(5);
    hub.runSimulation(20);
    return 0;
}
