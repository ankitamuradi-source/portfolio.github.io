/***************************************************************
 BUSINESS IDEA  : Simulation Pods
 DOMAIN         : Education, Smart Training
 ALGORITHMS     : Queue Scheduling (FCFS), Simulation
 DATA STRUCTURE : Queue, Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store user session details
-------------------------------------------------------------*/
struct User {
    int id;
    string name;
    int sessionTime;   // in minutes
};

/*-------------------------------------------------------------
 Function to display user details
-------------------------------------------------------------*/
void displayUser(const User& u) {
    cout << left << setw(5) << u.id
         << setw(15) << u.name
         << setw(15) << u.sessionTime << endl;
}

/*-------------------------------------------------------------
 Function to display queue status
-------------------------------------------------------------*/
void displayQueue(queue<User> q) {
    cout << "\nCurrent Simulation Queue:\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Session(min)\n";
    cout << "--------------------------------------\n";

    while (!q.empty()) {
        displayUser(q.front());
        q.pop();
    }
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "           SIMULATION POD MANAGEMENT\n";
    cout << "=============================================\n";

    queue<User> simulationQueue;

    // Adding users to queue (FCFS)
    simulationQueue.push({1, "Ananya", 30});
    simulationQueue.push({2, "Rahul", 45});
    simulationQueue.push({3, "Meera", 20});
    simulationQueue.push({4, "Vikram", 25});

    displayQueue(simulationQueue);

    int totalTime = 0;
    int podNumber = 1;

    cout << "\nSimulation Execution:\n";
    cout << "--------------------------------------\n";

    while (!simulationQueue.empty()) {
        User current = simulationQueue.front();
        simulationQueue.pop();

        cout << "Pod " << podNumber
             << " assigned to " << current.name << endl;
        cout << "Session Duration: "
             << current.sessionTime << " minutes\n";

        totalTime += current.sessionTime;

        cout << "Session Completed for "
             << current.name << endl;
        cout << "--------------------------------------\n";

        podNumber++;
    }

    cout << "\n--------------------------------------\n";
    cout << "Simulation Summary:\n";
    cout << "--------------------------------------\n";
    cout << "Total Users Served: 4\n";
    cout << "Total Simulation Time: "
         << totalTime << " minutes\n";

    double avgTime = totalTime / 4.0;
    cout << "Average Session Time: "
         << fixed << setprecision(2)
         << avgTime << " minutes\n";

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "FCFS Scheduling ensures fairness.\n";
    cout << "Time Complexity: O(n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 4  : Quality Education\n";
    cout << "SDG 8  : Decent Work & Skills\n";
    cout << "SDG 9  : Innovation & Infrastructure\n";

    cout << "\nSimulation Pods Management Completed.\n";

    return 0;
}

