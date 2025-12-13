#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Enum for energy type
enum EnergyType { SOLAR, WIND };

// Class for installation
class Installation {
private:
    int id;
    EnergyType type;
    double capacity; // in kW
    double generatedEnergy; // kWh
    string location;
    bool maintenanceDue;

public:
    Installation(int id, EnergyType type, double capacity, string location) {
        this->id = id;
        this->type = type;
        this->capacity = capacity;
        this->location = location;
        this->generatedEnergy = 0;
        this->maintenanceDue = false;
    }

    void generateEnergy() {
        // Simulate energy generation
        double factor = (type == SOLAR) ? ((rand() % 100) / 100.0) : ((rand() % 120) / 100.0);
        generatedEnergy += capacity * factor;
        if (generatedEnergy > capacity * 1000) {
            maintenanceDue = true;
        }
    }

    void performMaintenance() {
        if (maintenanceDue) {
            generatedEnergy = 0;
            maintenanceDue = false;
            cout << "Maintenance performed for installation ID " << id << endl;
        }
    }

    double getEnergy() const { return generatedEnergy; }
    string getTypeString() const { return (type == SOLAR) ? "Solar" : "Wind"; }
    bool isMaintenanceDue() const { return maintenanceDue; }
    int getId() const { return id; }

    void display() const {
        cout << setw(5) << id
             << setw(10) << getTypeString()
             << setw(10) << capacity
             << setw(15) << generatedEnergy
             << setw(15) << (maintenanceDue ? "Yes" : "No")
             << setw(20) << location
             << endl;
    }
};

// Class for customer subscription
class Customer {
private:
    int id;
    string name;
    int installationId;
    double monthlyBill;
public:
    Customer(int id, string name, int installationId, double monthlyBill) {
        this->id = id;
        this->name = name;
        this->installationId = installationId;
        this->monthlyBill = monthlyBill;
    }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(15) << installationId
             << setw(10) << monthlyBill
             << endl;
    }

    double getBill() const { return monthlyBill; }
};

// Class for Green Energy Startup
class GreenEnergyStartup {
private:
    vector<Installation> installations;
    vector<Customer> customers;
    int nextInstallationId;
    int nextCustomerId;
    double totalRevenue;

public:
    GreenEnergyStartup() {
        nextInstallationId = 1;
        nextCustomerId = 1;
        totalRevenue = 0;
    }

    void addInstallation(EnergyType type, double capacity, string location) {
        installations.push_back(Installation(nextInstallationId++, type, capacity, location));
        cout << "Installation added successfully." << endl;
    }

    void addCustomer(string name, int installationId, double monthlyBill) {
        customers.push_back(Customer(nextCustomerId++, name, installationId, monthlyBill));
        totalRevenue += monthlyBill;
        cout << "Customer added successfully." << endl;
    }

    void generateAllEnergy() {
        for (auto &inst : installations) {
            inst.generateEnergy();
        }
        cout << "Energy generation updated for all installations." << endl;
    }

    void performMaintenance() {
        for (auto &inst : installations) {
            if (inst.isMaintenanceDue()) {
                inst.performMaintenance();
            }
        }
    }

    void displayInstallations() const {
        cout << setw(5) << "ID"
             << setw(10) << "Type"
             << setw(10) << "Capacity"
             << setw(15) << "Generated"
             << setw(15) << "Maintenance"
             << setw(20) << "Location" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        for (const auto &inst : installations) {
            inst.display();
        }
    }

    void displayCustomers() const {
        cout << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(15) << "InstallationID"
             << setw(10) << "Bill" << endl;
        cout << "---------------------------------------------------------" << endl;
        for (const auto &cust : customers) {
            cust.display();
        }
    }

    void displayRevenue() const {
        cout << "Total Revenue: ₹" << totalRevenue << "k" << endl;
    }

    void simulateDay() {
        generateAllEnergy();
        performMaintenance();
        cout << "Simulation for the day completed." << endl;
    }

    void runDemo() {
        addInstallation(SOLAR, 50, "Downtown");
        addInstallation(WIND, 80, "Hillside");
        addCustomer("Alice", 1, 2000);
        addCustomer("Bob", 2, 3000);
        for(int i=0; i<10; i++) {
            cout << "\n--- Day " << i+1 << " Simulation ---\n";
            simulateDay();
            displayInstallations();
        }
        displayCustomers();
        displayRevenue();
    }
};

int main() {
    srand(time(0));
    GreenEnergyStartup startup;
    startup.runDemo();

    return 0;
}

