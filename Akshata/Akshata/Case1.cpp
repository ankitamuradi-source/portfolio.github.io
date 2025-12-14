/***************************************************************
 BUSINESS IDEA  : Floating Micro-Farms
 DOMAIN         : Smart Agriculture, Sustainable Cities
 ALGORITHM USED : Greedy Algorithm + Sorting
 DATA STRUCTURE : Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store crop information
-------------------------------------------------------------*/
struct Crop {
    string name;
    int waterRequired;
    int yield;
};

/*-------------------------------------------------------------
 Function to display available crops
-------------------------------------------------------------*/
void displayCrops(const vector<Crop>& crops) {
    cout << "\nAvailable Crops on Floating Farm:\n";
    cout << left << setw(15) << "Crop"
         << setw(15) << "Water Needed"
         << setw(10) << "Yield\n";
    cout << "-------------------------------------------\n";

    for (const Crop& c : crops) {
        cout << left << setw(15) << c.name
             << setw(15) << c.waterRequired
             << setw(10) << c.yield << endl;
    }
}

/*-------------------------------------------------------------
 Greedy Comparator (Yield per Water)
-------------------------------------------------------------*/
bool compare(Crop a, Crop b) {
    double r1 = (double)a.yield / a.waterRequired;
    double r2 = (double)b.yield / b.waterRequired;
    return r1 > r2;
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "        FLOATING MICRO-FARMS SIMULATION\n";
    cout << "=============================================\n";

    // Total available water units
    int totalWater = 100;

    // Crop database
    vector<Crop> crops = {
        {"Lettuce", 20, 60},
        {"Spinach", 15, 45},
        {"Tomato", 30, 90},
        {"Strawberry", 25, 80},
        {"Herbs", 10, 30},
        {"Cucumber", 35, 100}
    };

    // Display crops before selection
    displayCrops(crops);

    // Sort crops using Greedy approach
    sort(crops.begin(), crops.end(), compare);

    cout << "\nCrops sorted by Yield/Water ratio (Greedy):\n";
    displayCrops(crops);

    int usedWater = 0;
    int totalYield = 0;

    cout << "\nCrop Allocation Process:\n";
    cout << "-------------------------------------------\n";

    for (const Crop& c : crops) {
        if (usedWater + c.waterRequired <= totalWater) {
            usedWater += c.waterRequired;
            totalYield += c.yield;

            cout << "Planted " << c.name
                 << " | Water Used: " << c.waterRequired
                 << " | Yield Gained: " << c.yield << endl;
        }
        else {
            cout << "Skipped " << c.name
                 << " (Not enough water)\n";
        }
    }

    cout << "\n=============================================\n";
    cout << "FINAL FARM STATUS\n";
    cout << "=============================================\n";

    cout << "Total Water Available : " << totalWater << endl;
    cout << "Total Water Used      : " << usedWater << endl;
    cout << "Remaining Water       : " << totalWater - usedWater << endl;
    cout << "Total Crop Yield      : " << totalYield << endl;

    cout << "\n---------------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "---------------------------------------------\n";
    cout << "Greedy Strategy: Select crops with maximum\n";
    cout << "yield per unit water to maximize output.\n";
    cout << "Time Complexity: O(n log n) due to sorting.\n";
    cout << "Space Complexity: O(n).\n";

    cout << "\n---------------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "---------------------------------------------\n";
    cout << "SDG 2  : Zero Hunger\n";
    cout << "SDG 11 : Sustainable Cities\n";
    cout << "SDG 12 : Responsible Consumption\n";
    cout << "SDG 13 : Climate Action\n";

    cout << "\nSimulation Completed Successfully.\n";

    return 0;
}
