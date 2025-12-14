/***************************************************************
 BUSINESS IDEA  : Scent Navigation Maps
 DOMAIN         : Smart Navigation, Assistive Technology
 ALGORITHMS     : Breadth First Search (BFS)
 DATA STRUCTURE : Graph, Queue, Vector
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to represent a navigation node
-------------------------------------------------------------*/
struct Node {
    int id;
    string scentType;
};

/*-------------------------------------------------------------
 Class to represent scent navigation graph
-------------------------------------------------------------*/
class ScentGraph {
private:
    int nodes;
    vector<vector<int>> adjList;
    vector<Node> nodeInfo;

public:
    ScentGraph(int n) {
        nodes = n;
        adjList.resize(n);
        nodeInfo.resize(n);
    }

    void addNode(int id, string scent) {
        nodeInfo[id] = {id, scent};
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void displayNodes() {
        cout << "\nScent Nodes Information:\n";
        cout << left << setw(10) << "Node"
             << setw(20) << "Scent Type\n";
        cout << "-------------------------------\n";

        for (auto n : nodeInfo) {
            cout << left << setw(10) << n.id
                 << setw(20) << n.scentType << endl;
        }
    }

    void displayGraph() {
        cout << "\nNavigation Paths:\n";
        for (int i = 0; i < nodes; i++) {
            cout << "Node " << i << " -> ";
            for (int v : adjList[i])
                cout << v << " ";
            cout << endl;
        }
    }

    void bfs(int start, int destination) {
        vector<bool> visited(nodes, false);
        vector<int> parent(nodes, -1);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destination)
                break;

            for (int next : adjList[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        cout << "\nShortest Scent Path from "
             << start << " to " << destination << ":\n";

        printPath(parent, destination);
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
    cout << "          SCENT NAVIGATION MAP SYSTEM\n";
    cout << "=============================================\n";

    int totalNodes = 7;
    ScentGraph graph(totalNodes);

    // Adding nodes with scent types
    graph.addNode(0, "Lavender");
    graph.addNode(1, "Rose");
    graph.addNode(2, "Lemon");
    graph.addNode(3, "Mint");
    graph.addNode(4, "Jasmine");
    graph.addNode(5, "Sandalwood");
    graph.addNode(6, "Vanilla");

    // Adding paths
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 6);
    graph.addEdge(5, 6);

    graph.displayNodes();
    graph.displayGraph();

    int startNode = 0;
    int destinationNode = 6;

    graph.bfs(startNode, destinationNode);

    cout << "\n\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "BFS guarantees shortest path in\n";
    cout << "unweighted scent graph.\n";
    cout << "Time Complexity: O(V + E)\n";
    cout << "Space Complexity: O(V)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 9  : Innovation & Infrastructure\n";
    cout << "SDG 10 : Reduced Inequalities\n";
    cout << "SDG 11 : Sustainable Cities\n";

    cout << "\nScent Navigation Map Simulation Completed.\n";

    return 0;
}

