/***************************************************************
 BUSINESS IDEA  : Eco-Bricks
 DOMAIN         : Sustainable Construction, Green Technology
 ALGORITHMS     : Merge Sort, Filtering
 DATA STRUCTURE : Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store eco-brick information
-------------------------------------------------------------*/
struct EcoBrick {
    int id;
    int strength;     // compressive strength
    int durability;  // years
};

/*-------------------------------------------------------------
 Display eco-bricks
-------------------------------------------------------------*/
void displayBricks(const vector<EcoBrick>& bricks) {
    cout << left << setw(10) << "ID"
         << setw(15) << "Strength"
         << setw(15) << "Durability\n";
    cout << "--------------------------------------\n";

    for (auto b : bricks) {
        cout << left << setw(10) << b.id
             << setw(15) << b.strength
             << setw(15) << b.durability << endl;
    }
}

/*-------------------------------------------------------------
 Merge function for Merge Sort
-------------------------------------------------------------*/
void merge(vector<EcoBrick>& bricks, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<EcoBrick> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = bricks[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = bricks[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].strength <= R[j].strength)
            bricks[k++] = L[i++];
        else
            bricks[k++] = R[j++];
    }

    while (i < n1)
        bricks[k++] = L[i++];

    while (j < n2)
        bricks[k++] = R[j++];
}

/*-------------------------------------------------------------
 Merge Sort Algorithm
-------------------------------------------------------------*/
void mergeSort(vector<EcoBrick>& bricks, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(bricks, left, mid);
        mergeSort(bricks, mid + 1, right);
        merge(bricks, left, mid, right);
    }
}

/*-------------------------------------------------------------
 Filter strong bricks
-------------------------------------------------------------*/
vector<EcoBrick> filterBricks(const vector<EcoBrick>& bricks) {
    vector<EcoBrick> selected;

    for (auto b : bricks) {
        if (b.strength >= 70 && b.durability >= 20)
            selected.push_back(b);
    }
    return selected;
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "             ECO-BRICKS QUALITY SYSTEM\n";
    cout << "=============================================\n";

    vector<EcoBrick> bricks = {
        {1, 85, 30},
        {2, 60, 18},
        {3, 90, 40},
        {4, 75, 25},
        {5, 55, 15},
        {6, 80, 35}
    };

    cout << "\nOriginal Eco-Bricks Data:\n";
    displayBricks(bricks);

    mergeSort(bricks, 0, bricks.size() - 1);

    cout << "\nEco-Bricks Sorted by Strength:\n";
    displayBricks(bricks);

    vector<EcoBrick> strongBricks = filterBricks(bricks);

    cout << "\nSelected Eco-Bricks for Construction:\n";
    displayBricks(strongBricks);

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Merge Sort Time Complexity: O(n log n)\n";
    cout << "Filtering Complexity: O(n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 11 : Sustainable Cities\n";
    cout << "SDG 12 : Responsible Consumption\n";
    cout << "SDG 13 : Climate Action\n";

    cout << "\nEco-Bricks System Completed Successfully.\n";

    return 0;
}

