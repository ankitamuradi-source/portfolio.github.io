/***************************************************************
 BUSINESS IDEA  : Drone Dining
 DOMAIN         : Smart Delivery, Automation
 ALGORITHMS     : Greedy Scheduling, Priority Queue
 DATA STRUCTURE : Priority Queue, Vector, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to store order details
-------------------------------------------------------------*/
struct Order {
    int orderId;
    string customerName;
    int deliveryTime;   // in minutes
};

/*-------------------------------------------------------------
 Comparator for priority queue (min delivery time)
-------------------------------------------------------------*/
struct CompareOrder {
    bool operator()(Order a, Order b) {
        return a.deliveryTime > b.deliveryTime;
    }
};

/*-------------------------------------------------------------
 Function to display an order
-------------------------------------------------------------*/
void displayOrder(const Order& o) {
    cout << left << setw(10) << o.orderId
         << setw(15) << o.customerName
         << setw(15) << o.deliveryTime << endl;
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "              DRONE DINING SYSTEM\n";
    cout << "=============================================\n";

    priority_queue<Order, vector<Order>, CompareOrder> deliveryQueue;

    // Adding food orders
    deliveryQueue.push({101, "Rohit", 25});
    deliveryQueue.push({102, "Sneha", 15});
    deliveryQueue.push({103, "Aman", 30});
    deliveryQueue.push({104, "Priya", 10});
    deliveryQueue.push({105, "Kunal", 20});

    cout << "\nPending Orders (Priority Based):\n";
    cout << left << setw(10) << "OrderID"
         << setw(15) << "Customer"
         << setw(15) << "Time(min)\n";
    cout << "--------------------------------------\n";

    priority_queue<Order, vector<Order>, CompareOrder> tempQueue = deliveryQueue;
    while (!tempQueue.empty()) {
        displayOrder(tempQueue.top());
        tempQueue.pop();
    }

    int droneNumber = 1;
    int totalTime = 0;

    cout << "\nDelivery Process:\n";
    cout << "--------------------------------------\n";

    while (!deliveryQueue.empty()) {
        Order current = deliveryQueue.top();
        deliveryQueue.pop();

        cout << "Drone " << droneNumber
             << " delivering Order " << current.orderId
             << " to " << current.customerName << endl;

        cout << "Estimated Delivery Time: "
             << current.deliveryTime << " minutes\n";

        totalTime += current.deliveryTime;

        cout << "Order " << current.orderId
             << " delivered successfully.\n";
        cout << "--------------------------------------\n";

        droneNumber++;
    }

    cout << "\n--------------------------------------\n";
    cout << "Delivery Summary:\n";
    cout << "--------------------------------------\n";
    cout << "Total Orders Delivered: 5\n";
    cout << "Total Delivery Time: "
         << totalTime << " minutes\n";

    double avgTime = totalTime / 5.0;
    cout << "Average Delivery Time: "
         << fixed << setprecision(2)
         << avgTime << " minutes\n";

    cout << "\n--------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Priority Queue ensures fastest delivery first.\n";
    cout << "Time Complexity: O(n log n)\n";
    cout << "Space Complexity: O(n)\n";

    cout << "\n--------------------------------------\n";
    cout << "SDG Mapping:\n";
    cout << "SDG 9  : Industry & Innovation\n";
    cout << "SDG 11 : Smart Cities\n";
    cout << "SDG 12 : Responsible Consumption\n";

    cout << "\nDrone Dining System Completed Successfully.\n";

    return 0;
}

