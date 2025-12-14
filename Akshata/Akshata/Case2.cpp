/***************************************************************
 BUSINESS IDEA  : XR Hologram Shops
 DOMAIN         : Virtual Retail, Smart Cities
 ALGORITHMS     : Hashing, Binary Search, Sorting
 DATA STRUCTURE : Vector, unordered_map, Structure
 LANGUAGE       : C++
***************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
using namespace std;

/*-------------------------------------------------------------
 Structure to represent a product
-------------------------------------------------------------*/
struct Product {
    int id;
    string name;
    double price;
    int stock;
};

/*-------------------------------------------------------------
 Display all products
-------------------------------------------------------------*/
void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable XR Hologram Products:\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Product"
         << setw(10) << "Price"
         << setw(10) << "Stock\n";
    cout << "---------------------------------------------\n";

    for (const auto& p : products) {
        cout << left << setw(5) << p.id
             << setw(20) << p.name
             << setw(10) << p.price
             << setw(10) << p.stock << endl;
    }
}

/*-------------------------------------------------------------
 Comparator for sorting by price
-------------------------------------------------------------*/
bool compareByPrice(Product a, Product b) {
    return a.price < b.price;
}

/*-------------------------------------------------------------
 Binary Search for product by ID
-------------------------------------------------------------*/
int binarySearch(const vector<Product>& products, int key) {
    int low = 0, high = products.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (products[mid].id == key)
            return mid;
        else if (products[mid].id < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

/*-------------------------------------------------------------
 Main Function
-------------------------------------------------------------*/
int main() {

    cout << "=============================================\n";
    cout << "         XR HOLOGRAM SHOP SIMULATION\n";
    cout << "=============================================\n";

    vector<Product> products = {
        {101, "XR Shoes", 2999.0, 25},
        {102, "Smart Glasses", 4999.0, 15},
        {103, "Hologram Watch", 6999.0, 10},
        {104, "Virtual Jacket", 3999.0, 20},
        {105, "XR Headset", 8999.0, 8}
    };

    unordered_map<int, string> productMap;
    for (auto& p : products)
        productMap[p.id] = p.name;

    int choice;
    do {
        cout << "\n----------- XR SHOP MENU -----------\n";
        cout << "1. View All Products\n";
        cout << "2. Search Product by ID\n";
        cout << "3. Sort Products by Price\n";
        cout << "4. Buy Product (Simulation)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            displayProducts(products);
            break;

        case 2: {
            int id;
            cout << "Enter Product ID: ";
            cin >> id;

            if (productMap.find(id) != productMap.end())
                cout << "Product Found: " << productMap[id] << endl;
            else
                cout << "Product Not Found!\n";
            break;
        }

        case 3:
            sort(products.begin(), products.end(), compareByPrice);
            cout << "Products Sorted by Price.\n";
            displayProducts(products);
            break;

        case 4: {
            int id;
            cout << "Enter Product ID to Buy: ";
            cin >> id;

            sort(products.begin(), products.end(),
                 [](Product a, Product b) { return a.id < b.id; });

            int index = binarySearch(products, id);

            if (index != -1 && products[index].stock > 0) {
                products[index].stock--;
                cout << "Purchase Successful: "
                     << products[index].name << endl;
            } else {
                cout << "Product Out of Stock or Invalid ID\n";
            }
            break;
        }

        case 0:
            cout << "Exiting XR Hologram Shop...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    cout << "\n---------------------------------------------\n";
    cout << "Algorithm Analysis:\n";
    cout << "Hashing: O(1) average search\n";
    cout << "Binary Search: O(log n)\n";
    cout << "Sorting: O(n log n)\n";

    cout << "\nSDG Mapping:\n";
    cout << "SDG 9  : Industry & Innovation\n";
    cout << "SDG 11 : Smart Cities\n";
    cout << "SDG 12 : Responsible Consumption\n";

    cout << "\nXR Hologram Shop Simulation Completed.\n";

    return 0;
}

