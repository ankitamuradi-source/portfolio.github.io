/***************************************************************
 BUSINESS IDEA  : Energy-Bike Café
 DOMAIN         : Renewable Energy, Smart Cities
 ALGORITHMS     : Greedy Allocation, Accumulation
 DATA STRUCTURE : Vector, Structure, Map
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store cyclist information
-------------------------------------------------------------*/
struct Cyclist {
    string name;
    int minutesCycled;
    int energyGenerated; // in watts
};

/*-------------------------------------------------------------
 Structure to store appliance information
-------------------------------------------------------------*/
struct Appliance {
    string name;
    int powerRequired; // watts
};

/*-------------------------------------------------------------
 Function to display cyclist data
-------------------------------------------------------------*/
void displayCyclists(const vector<Cyclist>& cyclists) {
    cout << "\nCyclist Energy Data:\n";
    cout << left << setw(15) << "Name"
         << setw(15) << "Minutes"
         << setw(15) << "Energy(W)\n";
    cout << "--------------------------------------\n";

    for (auto c : cyclists) {
        cout << left << setw(15) << c.name
             << setw(15) << c.minutesCycled
             << setw(15) << c.energyGenerated << endl;
    }
}

/*-------------------------------------------------------------
 Function to calculate energy generated
-------------------------------------------------------------*/
int calculateEnergy(int minutes) {
    // Average 10 watts per minute
    return minutes * 10;
}

/*-------------------------------------------------------------
 Greedy comparator for appliances
-------------------------------------------------------------*/
bool compareAppliance(Appliance a, Appliance b) {
    return a.powerRequired < b.powerRequired;
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "            ENERGY-BIKE CAFÉ SYSTEM\n";
    cout << "=============================================\n";

    // Cyclist list
    vector<Cyclist> cyclists = {
        {"Amit", 20, 0},
        {"Riya", 30, 0},
        {"Karan", 25, 0},
        {"Neha", 15, 0}
    };

    // Calculate energy for each cyclist
    for (auto &c : cyclists) {
        c.energyGenerated = calculateEnergy(c.minutesCycled);
    }

    displayCyclists(cyclists);

    // Calculate total energy
    int totalEnergy = 0;
    for (auto c : cyclists)
        totalEnergy += c.energyGenerated;

    cout << "\nTotal Energy Generated: "
         << totalEnergy << " watts\n";

    // Café appliances
    vector<Appliance> appliances = {
        {"Coffee Machine", 200},
        {"Blender", 150},
        {"Lights", 100},
        {"Music System", 80},
        {"Charging Station", 120}
    };

    // Sort appliances using Greedy Algorithm
    sort(appliances.begin(), appliances.end(), compareAppliance);

    cout << "\nAppliance Power Allocation:\n";
    cout << "--------------------------------------\n";

    int remainingEnergy = totalEnergy;

    for (auto a : appliances) {
        if (remainingEnergy >= a.powerRequired) {
            remainingEnergy -= a.powerRequired;
            cout << a.name << " powered ON ("
                 << a.powerRequired << "W)\n";
        } else {
            cout << a.name << " powered OFF (Not enough energy)\n";
        }
    }

    cout << "\nRemaining Energy: "
         << remainingEnergy << " watts\n";

    // Cost saving simulation
    double costPerWatt = 0.02;
    double moneySaved = totalEnergy * costPerWatt;

    cout << "\n--------------------------------------\n";
    cout << "Energy Cost Savings:\n";
    cout << "--------------------------------------\n";
    cout << "Money Saved Today: ₹"
         << fixed << setprecision(2)
         << moneySaved << endl;

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Accumulation: O(n)\n";
    cout << "Greedy Allocation: O(n log n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 7  : Affordable & Clean Energy\n";
    cout << "SDG 11 : Sustainable Cities\n";
    cout << "SDG 13 : Climate Action\n";

    cout << "\nEnergy-Bike Café Simulation Completed.\n";

    return 0;
}

