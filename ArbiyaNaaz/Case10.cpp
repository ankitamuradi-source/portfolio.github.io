#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

// Product class
class Product {
private:
    int id;
    string name;
    double price;
    int stock;

public:
    Product(int id, string name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    bool purchase(int quantity) {
        if (quantity <= stock) {
            stock -= quantity;
            return true;
        }
        return false;
    }

    void display() {
        cout << setw(5) << id
             << setw(25) << name
             << setw(10) << price
             << setw(10) << stock << endl;
    }

    double getPrice() const { return price; }
    string getName() const { return name; }
    int getStock() const { return stock; }
};

// Customer class
class Customer {
private:
    int id;
    string name;
    vector<pair<int, int>> cart; // productId, quantity

public:
    Customer(int id, string name) : id(id), name(name) {}

    void addToCart(int productId, int quantity) {
        cart.push_back({productId, quantity});
    }

    vector<pair<int,int>> getCart() { return cart; }

    void display() {
        cout << setw(5) << id << setw(20) << name << setw(20);
        for (auto &item : cart) cout << "(" << item.first << "," << item.second << ") ";
        cout << endl;
    }
};

// E-Commerce Platform
class ECommercePlatform {
private:
    vector<Product> products;
    vector<Customer> customers;
    double totalRevenue;

public:
    ECommercePlatform() { totalRevenue = 0; }

    void setupProducts() {
        products.push_back(Product(1, "Organic Honey", 500, 50));
        products.push_back(Product(2, "Handmade Soap", 200, 100));
        products.push_back(Product(3, "Eco Bag", 300, 75));
        products.push_back(Product(4, "Organic Tea", 150, 80));
        products.push_back(Product(5, "Reusable Bottle", 250, 60));
        products.push_back(Product(6, "Solar Lamp", 1200, 30));
        products.push_back(Product(7, "Laptop Stand", 800, 40));
        products.push_back(Product(8, "Wireless Charger", 600, 50));
        products.push_back(Product(9, "Yoga Mat", 350, 70));
        products.push_back(Product(10, "Bluetooth Speaker", 1500, 25));
    }

    void setupCustomers() {
        customers.push_back(Customer(101, "Alice"));
        customers.push_back(Customer(102, "Bob"));
        customers.push_back(Customer(103, "Charlie"));
        customers.push_back(Customer(104, "Diana"));
        customers.push_back(Customer(105, "Eve"));
        customers.push_back(Customer(106, "Frank"));
        customers.push_back(Customer(107, "Grace"));
        customers.push_back(Customer(108, "Hank"));
    }

    void simulatePurchases() {
        srand(time(0));
        for (auto &customer : customers) {
            int itemsToBuy = 1 + rand() % 5;
            for (int i = 0; i < itemsToBuy; i++) {
                int productId = rand() % products.size();
                int quantity = 1 + rand() % 3;
                if (products[productId].purchase(quantity)) {
                    customer.addToCart(productId + 1, quantity);
                    totalRevenue += products[productId].getPrice() * quantity;
                }
            }
        }
    }

    void displayProducts() {
        cout << "\n--- Product List ---\n";
        cout << setw(5) << "ID" << setw(25) << "Name" 
             << setw(10) << "Price" << setw(10) << "Stock" << endl;
        for (auto &p : products) p.display();
    }

    void displayCustomers() {
        cout << "\n--- Customers ---\n";
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Cart" << endl;
        for (auto &c : customers) c.display();
    }

    void generateSalesReport() {
        cout << "\n--- Sales Report ---\n";
        cout << setw(25) << "Product" << setw(10) << "Sold" << setw(15) << "Revenue" << endl;
        for (auto &p : products) {
            int sold = p.getStock() < 0 ? 0 : 0 + (p.getStock() - p.getStock());
            cout << setw(25) << p.getName() << setw(10) << sold << setw(15) << (sold * p.getPrice()) << endl;
        }
        cout << "\nTotal Revenue: ₹" << totalRevenue << endl;
    }

    void runSimulation() {
        setupProducts();
        setupCustomers();
        simulatePurchases();
        displayProducts();
        displayCustomers();
        generateSalesReport();
    }
};

int main() {
    ECommercePlatform platform;
    platform.runSimulation();
    return 0;
}

