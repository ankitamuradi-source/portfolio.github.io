#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

struct Item {
    string name;
    int quantity;
    double temperature; // required storage temperature
    time_t entryDate;
    int shelfLifeDays; // expiry in days

    Item(string n, int q, double t, int sLife) {
        name = n;
        quantity = q;
        temperature = t;
        shelfLifeDays = sLife;
        entryDate = time(0);
    }

    void display() {
        tm *ltm = localtime(&entryDate);
        cout << left << setw(20) << name
             << setw(10) << quantity
             << setw(10) << temperature
             << setw(15) << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year
             << setw(10) << shelfLifeDays << endl;
    }

    bool isExpired() {
        time_t now = time(0);
        double diff = difftime(now, entryDate) / (60 * 60 * 24);
        return diff > shelfLifeDays;
    }
};

class ColdStorage {
private:
    queue<Item> storageQueue;
    double currentTemp;
    double revenue;

public:
    ColdStorage() {
        currentTemp = 4.0; // default 4°C
        revenue = 0.0;
    }

    void setTemperature(double t) {
        currentTemp = t;
        cout << "Temperature set to " << currentTemp << "°C\n";
    }

    void addItem() {
        string name;
        int quantity, shelfLife;
        double temp;

        cout << "Enter item name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter required temperature (°C): ";
        cin >> temp;
        cout << "Enter shelf life in days: ";
        cin >> shelfLife;

        Item item(name, quantity, temp, shelfLife);
        storageQueue.push(item);
        cout << "Item added successfully!\n";
    }

    void dispatchItem() {
        if (storageQueue.empty()) {
            cout << "Storage is empty!\n";
            return;
        }

        Item item = storageQueue.front();
        storageQueue.pop();

        double cost = item.quantity * 50; // example revenue
        revenue += cost;

        cout << "Dispatched " << item.quantity << " of " << item.name << ". Revenue generated: ₹" << cost << endl;
    }

    void displayItems() {
        if (storageQueue.empty()) {
            cout << "No items in storage!\n";
            return;
        }

        queue<Item> tempQueue = storageQueue;
        cout << left << setw(20) << "Name" << setw(10) << "Qty" << setw(10) << "Temp" << setw(15) << "EntryDate" << setw(10) << "ShelfLife" << endl;
        cout << string(65, '-') << endl;
        while (!tempQueue.empty()) {
            Item item = tempQueue.front();
            item.display();
            tempQueue.pop();
        }
    }

    void checkExpired() {
        if (storageQueue.empty()) {
            cout << "No items to check!\n";
            return;
        }

        queue<Item> tempQueue;
        int expiredCount = 0;
        while (!storageQueue.empty()) {
            Item item = storageQueue.front();
            storageQueue.pop();
            if (item.isExpired()) {
                cout << "Expired: " << item.name << endl;
                expiredCount++;
            } else {
                tempQueue.push(item);
            }
        }
        storageQueue = tempQueue;
        cout << "Total expired items removed: " << expiredCount << endl;
    }

    void temperatureAlert() {
        if (currentTemp > 5.0) {
            cout << "Warning! Storage temperature too high: " << currentTemp << "°C\n";
        } else if (currentTemp < 0.0) {
            cout << "Warning! Storage temperature too low: " << currentTemp << "°C\n";
        } else {
            cout << "Temperature is optimal.\n";
        }
    }

    void generateReport() {
        cout << "\n--- Storage Report ---\n";
        displayItems();
        cout << "Current Temperature: " << currentTemp << "°C\n";
        cout << "Total Revenue: ₹" << revenue << "\n";
        cout << "---------------------\n";
    }
};

int main() {
    ColdStorage cs;
    int choice;
    double temp;

    while (true) {
        cout << "\nCold Storage Management System\n";
        cout << "1. Set Storage Temperature\n";
        cout << "2. Add Item\n";
        cout << "3. Dispatch Item (FIFO)\n";
        cout << "4. Display Items\n";
        cout << "5. Check & Remove Expired Items\n";
        cout << "6. Temperature Alert\n";
        cout << "7. Generate Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter temperature (°C): ";
            cin >> temp;
            cs.setTemperature(temp);
            break;
        case 2:
            cs.addItem();
            break;
        case 3:
            cs.dispatchItem();
            break;
        case 4:
            cs.displayItems();
            break;
        case 5:
            cs.checkExpired();
            break;
        case 6:
            cs.temperatureAlert();
            break;
        case 7:
            cs.generateReport();
            break;
        case 0:
            cout << "Exiting system...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
