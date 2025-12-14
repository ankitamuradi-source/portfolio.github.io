/***************************************************************
 BUSINESS IDEA  : AI Sound Trails
 DOMAIN         : Smart Navigation, Assistive Technology
 ALGORITHM      : Dijkstra's Shortest Path Algorithm
 DATA STRUCTURE : Graph (Adjacency List), Priority Queue
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to represent an edge
-------------------------------------------------------------*/
struct Edge {
    int destination;
    int weight;
};

/*-------------------------------------------------------------
 Class to represent Graph
-------------------------------------------------------------*/
class Graph {
private:
    int vertices;
    vector<vector<Edge>> adjList;

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(v);
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight});
    }

    void displayGraph() {
        cout << "\nSound Trail Graph Representation:\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Node " << i << " -> ";
            for (auto e : adjList[i]) {
                cout << "(" << e.destination
                     << ", sound=" << e.weight << ") ";
            }
            cout << endl;
        }
    }

    void dijkstra(int source) {
        vector<int> distance(vertices, INT_MAX);
        vector<int> parent(vertices, -1);

        priority_queue<pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>> pq;

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentNode = pq.top().second;
            pq.pop();

            for (auto edge : adjList[currentNode]) {
                int nextNode = edge.destination;
                int weight = edge.weight;

                if (distance[nextNode] > distance[currentNode] + weight) {
                    distance[nextNode] = distance[currentNode] + weight;
                    parent[nextNode] = currentNode;
                    pq.push({distance[nextNode], nextNode});
                }
            }
        }

        cout << "\nShortest Sound Distances from Source Node "
             << source << ":\n";

        for (int i = 0; i < vertices; i++) {
            cout << "Node " << i
                 << " -> Distance: " << distance[i] << endl;
        }

        cout << "\nSound Navigation Paths:\n";
        for (int i = 0; i < vertices; i++) {
            if (i != source) {
                cout << "Path to Node " << i << ": ";
                printPath(parent, i);
                cout << endl;
            }
        }
    }

    void printPath(vector<int>& parent, int node) {
        if (node == -1)
            return;
        printPath(parent, parent[node]);
        cout << node << " ";
    }
};

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "           AI SOUND TRAILS SIMULATION\n";
    cout << "=============================================\n";

    int nodes = 6;
    Graph soundGraph(nodes);

    soundGraph.addEdge(0, 1, 4);
    soundGraph.addEdge(0, 2, 2);
    soundGraph.addEdge(1, 2, 1);
    soundGraph.addEdge(1, 3, 5);
    soundGraph.addEdge(2, 3, 8);
    soundGraph.addEdge(2, 4, 10);
    soundGraph.addEdge(3, 5, 6);
    soundGraph.addEdge(4, 5, 3);

    soundGraph.displayGraph();

    int sourceNode = 0;
    soundGraph.dijkstra(sourceNode);

    cout << "\n---------------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Dijkstra's Algorithm ensures optimal\n";
    cout << "audio path selection using minimum sound cost.\n";
    cout << "Time Complexity: O(E log V)\n";
    cout << "Space Complexity: O(V + E)\n";

    cout << "\n---------------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 9  : Innovation & Infrastructure\n";
    cout << "SDG 10 : Reduced Inequalities\n";
    cout << "SDG 11 : Sustainable Cities\n";

    cout << "\nAI Sound Trails Simulation Completed.\n";

    return 0;
}

