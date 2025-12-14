
/***************************************************************
 BUSINESS IDEA  : Smart Sidewalks
 DOMAIN         : Smart Infrastructure, Urban Mobility
 ALGORITHMS     : Dynamic Programming, Optimization
 DATA STRUCTURE : Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store sidewalk segment information
-------------------------------------------------------------*/
struct Segment {
    int id;
    int distance;      // meters
    int crowdLevel;    // 1 (low) to 5 (high)
};

/*-------------------------------------------------------------
 Function to calculate energy cost
-------------------------------------------------------------*/
int calculateEnergy(int distance, int crowdLevel) {
    return distance + (crowdLevel * 10);
}

/*-------------------------------------------------------------
 Function to display segments
-------------------------------------------------------------*/
void displaySegments(const vector<Segment>& segments) {
    cout << left << setw(10) << "Segment"
         << setw(15) << "Distance"
         << setw(15) << "CrowdLevel\n";
    cout << "--------------------------------------\n";

    for (auto s : segments) {
        cout << left << setw(10) << s.id
             << setw(15) << s.distance
             << setw(15) << s.crowdLevel << endl;
    }
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "           SMART SIDEWALKS SYSTEM\n";
    cout << "=============================================\n";

    vector<Segment> segments = {
        {1, 50, 3},
        {2, 40, 2},
        {3, 60, 4},
        {4, 30, 1},
        {5, 45, 2}
    };

    cout << "\nSidewalk Segments Data:\n";
    displaySegments(segments);

    int n = segments.size();
    vector<int> dp(n);

    // Energy cost for first segment
    dp[0] = calculateEnergy(
        segments[0].distance,
        segments[0].crowdLevel
    );

    // Dynamic Programming to minimize energy
    for (int i = 1; i < n; i++) {
        int energy = calculateEnergy(
            segments[i].distance,
            segments[i].crowdLevel
        );

        dp[i] = min(dp[i - 1] + energy, energy);
    }

    cout << "\nEnergy Cost Calculation:\n";
    for (int i = 0; i < n; i++) {
        cout << "Segment " << segments[i].id
             << " -> Energy: " << dp[i] << endl;
    }

    cout << "\nMinimum Energy Required to Walk: "
         << dp[n - 1] << " units\n";

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Dynamic Programming avoids repeated\n";
    cout << "energy calculations.\n";
    cout << "Time Complexity: O(n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 11 : Sustainable Cities\n";
    cout << "SDG 3  : Good Health & Well-being\n";
    cout << "SDG 9  : Innovation & Infrastructure\n";

    cout << "\nSmart Sidewalks Simulation Completed.\n";

    return 0;
}
