/***************************************************************
 BUSINESS IDEA  : Meditation Pods
 DOMAIN         : Mental Health, Smart Wellness
 ALGORITHMS     : Stack (LIFO), Simulation
 DATA STRUCTURE : Stack, Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store meditation session details
-------------------------------------------------------------*/
struct Session {
    int sessionId;
    string userName;
    int duration;     // minutes
};

/*-------------------------------------------------------------
 Display a session
-------------------------------------------------------------*/
void displaySession(const Session& s) {
    cout << left << setw(10) << s.sessionId
         << setw(15) << s.userName
         << setw(15) << s.duration << endl;
}

/*-------------------------------------------------------------
 Display all sessions in stack
-------------------------------------------------------------*/
void displayStack(stack<Session> s) {
    cout << "\nCurrent Meditation Sessions (Top First):\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "User"
         << setw(15) << "Duration\n";
    cout << "--------------------------------------\n";

    while (!s.empty()) {
        displaySession(s.top());
        s.pop();
    }
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "           MEDITATION POD SYSTEM\n";
    cout << "=============================================\n";

    stack<Session> sessionStack;

    // Adding meditation sessions
    sessionStack.push({1, "Ankit", 20});
    sessionStack.push({2, "Sanya", 15});
    sessionStack.push({3, "Ravi", 30});
    sessionStack.push({4, "Neha", 25});
    sessionStack.push({5, "Aarav", 10});

    displayStack(sessionStack);

    int totalTime = 0;
    int sessionCount = sessionStack.size();

    cout << "\nMeditation Session Execution:\n";
    cout << "--------------------------------------\n";

    while (!sessionStack.empty()) {
        Session current = sessionStack.top();
        sessionStack.pop();

        cout << "Starting Session for "
             << current.userName << endl;
        cout << "Session Duration: "
             << current.duration << " minutes\n";

        totalTime += current.duration;

        cout << "Session Completed for "
             << current.userName << endl;
        cout << "--------------------------------------\n";
    }

    cout << "\n--------------------------------------\n";
    cout << "Meditation Summary:\n";
    cout << "--------------------------------------\n";
    cout << "Total Sessions Conducted: "
         << sessionCount << endl;

    cout << "Total Meditation Time: "
         << totalTime << " minutes\n";

    double avgTime = totalTime / (double)sessionCount;
    cout << "Average Session Duration: "
         << fixed << setprecision(2)
         << avgTime << " minutes\n";

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Stack follows LIFO principle.\n";
    cout << "Time Complexity: O(n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 3  : Good Health & Well-being\n";
    cout << "SDG 11 : Sustainable Cities\n";
    cout << "SDG 8  : Decent Work & Mental Health\n";

    cout << "\nMeditation Pod Simulation Completed.\n";

    return 0;
}

