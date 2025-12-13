#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Product class
class Product {
private:
    int id;
    string name;
    double price;
    int stock;
public:
    Product(int id, string name, double price, int stock) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(10) << price
             << setw(10) << stock << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void reduceStock(int quantity) {
        if (quantity <= stock)
            stock -= quantity;
        else
            cout << "Not enough stock for " << name << endl;
    }
};

// Customer class
class Customer {
private:
    int id;
    string name;
    string address;
public:
    Customer(int id, string name, string address) {
        this->id = id;
        this->name = name;
        this->address = address;
    }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(30) << address << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
};

// Order class
class Order {
private:
    int id;
    int customerId;
    int productId;
    int quantity;
    double totalPrice;
public:
    Order(int id, int customerId, int productId, int quantity, double totalPrice) {
        this->id = id;
        this->customerId = customerId;
        this->productId = productId;
        this->quantity = quantity;
        this->totalPrice = totalPrice;
    }

    void display() const {
        cout << setw(5) << id
             << setw(10) << customerId
             << setw(10) << productId
             << setw(10) << quantity
             << setw(10) << totalPrice << endl;
    }

    double getTotalPrice() const { return totalPrice; }
};

// Organic Food Delivery Platform
class OrganicFoodDelivery {
private:
    vector<Product> products;
    vector<Customer> customers;
    vector<Order> orders;
    int nextProductId;
    int nextCustomerId;
    int nextOrderId;
    double totalRevenue;

public:
    OrganicFoodDelivery() {
        nextProductId = 1;
        nextCustomerId = 1;
        nextOrderId = 1;
        totalRevenue = 0;
    }

    void addProduct(string name, double price, int stock) {
        products.push_back(Product(nextProductId++, name, price, stock));
    }

    void addCustomer(string name, string address) {
        customers.push_back(Customer(nextCustomerId++, name, address));
    }

    void placeOrder(int customerId, int productId, int quantity) {
        if (productId > products.size() || customerId > customers.size()) {
            cout << "Invalid customer or product ID.\n";
            return;
        }
        Product &p = products[productId - 1];
        if (quantity > p.getStock()) {
            cout << "Not enough stock for " << p.getName() << endl;
            return;
        }
        double totalPrice = quantity * p.getPrice();
        orders.push_back(Order(nextOrderId++, customerId, productId, quantity, totalPrice));
        totalRevenue += totalPrice;
        p.reduceStock(quantity);
        cout << "Order placed successfully.\n";
    }

    void displayProducts() const {
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        cout << "------------------------------------------------\n";
        for (const auto &p : products) p.display();
    }

    void displayCustomers() const {
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(30) << "Address" << endl;
        cout << "--------------------------------------------------------\n";
        for (const auto &c : customers) c.display();
    }

    void displayOrders() const {
        cout << setw(5) << "ID" << setw(10) << "CustID" << setw(10) << "ProdID" << setw(10) << "Qty" << setw(10) << "Total" << endl;
        cout << "------------------------------------------------\n";
        for (const auto &o : orders) o.display();
    }

    void displayRevenue() const {
        cout << "Total Revenue: ₹" << totalRevenue << endl;
    }

    void simulateOrders(int days = 10) {
        srand(time(0));
        for (int d = 1; d <= days; d++) {
            cout << "\n--- Day " << d << " Orders ---\n";
            for (size_t i = 0; i < customers.size(); i++) {
                int productIndex = rand() % products.size();
                int quantity = 1 + rand() % 5;
                placeOrder(customers[i].getId(), products[productIndex].getId(), quantity);
            }
            displayOrders();
        }
    }

    void runDemo() {
        // Add products
        addProduct("Organic Apples", 150, 50);
        addProduct("Organic Milk", 50, 100);
        addProduct("Organic Spinach", 30, 200);
        addProduct("Organic Eggs", 10, 300);
        addProduct("Organic Honey", 200, 40);

        // Add customers
        addCustomer("John", "123 Main St");
        addCustomer("Emma", "456 Oak Ave");
        addCustomer("Michael", "789 Pine Rd");
        addCustomer("Sophia", "321 Elm St");

        // Display products and customers
        displayProducts();
        displayCustomers();

        // Simulate orders
        simulateOrders(10);

        // Display revenue
        displayRevenue();
    }
};

int main() {
    OrganicFoodDelivery platform;
    platform.runDemo();
    return 0;
}

