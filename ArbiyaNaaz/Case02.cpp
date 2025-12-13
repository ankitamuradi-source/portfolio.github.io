#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// -------------------- Room Class --------------------
class Room {
public:
    int id;
    string type;
    double price;
    bool occupied;
    vector<string> amenities;

    Room(int rid, string t, double p, vector<string> am)
        : id(rid), type(t), price(p), occupied(false), amenities(am) {}

    void display() {
        cout << "Room ID: " << id 
             << ", Type: " << type
             << ", Price: ₹" << fixed << setprecision(2) << price
             << ", Status: " << (occupied ? "Occupied" : "Available")
             << ", Amenities: ";
        for (auto &a : amenities) cout << a << " ";
        cout << endl;
    }
};

// -------------------- Guest Class --------------------
class Guest {
public:
    string name;
    int roomId;

    Guest(string n) : name(n), roomId(-1) {}

    void display() {
        cout << "Guest: " << name << ", Room ID: " 
             << (roomId == -1 ? 0 : roomId) << endl;
    }
};

// -------------------- Eco Resort Class --------------------
class EcoResort {
private:
    vector<Room> rooms;
    vector<Guest> guests;
    int nextRoomId;

public:
    EcoResort() : nextRoomId(1) {}

    void addRoom(string type, double price, vector<string> amenities) {
        rooms.push_back(Room(nextRoomId++, type, price, amenities));
        cout << "Room added successfully.\n";
    }

    void listRooms() {
        cout << "\n--- All Rooms ---\n";
        for (auto &r : rooms) r.display();
    }

    void listGuests() {
        cout << "\n--- All Guests ---\n";
        for (auto &g : guests) g.display();
    }

    void bookRoom() {
        string guestName;
        cout << "Enter Guest Name: "; cin.ignore(); getline(cin, guestName);

        cout << "Available Rooms:\n";
        for (auto &r : rooms) if (!r.occupied) r.display();

        int rid;
        cout << "Enter Room ID to book: "; cin >> rid;

        for (auto &r : rooms) {
            if (r.id == rid && !r.occupied) {
                r.occupied = true;
                Guest g(guestName);
                g.roomId = rid;
                guests.push_back(g);
                cout << "Room booked successfully!\n";
                return;
            }
        }
        cout << "Invalid Room ID or Room already occupied.\n";
    }

    void sortRoomsByPrice() {
        sort(rooms.begin(), rooms.end(), [](Room &a, Room &b){ return a.price < b.price; });
        cout << "Rooms sorted by price.\n";
    }

    void sortRoomsByOccupancy() {
        sort(rooms.begin(), rooms.end(), [](Room &a, Room &b){ return a.occupied < b.occupied; });
        cout << "Rooms sorted by occupancy.\n";
    }

    void calculateRevenue() {
        double total = 0;
        for (auto &r : rooms) if (r.occupied) total += r.price;
        cout << "Total revenue from booked rooms: ₹" << fixed << setprecision(2) << total << endl;
    }

    void menu() {
        while (true) {
            cout << "\n--- Eco Resort Menu ---\n";
            cout << "1. Add Room\n";
            cout << "2. List Rooms\n";
            cout << "3. Book Room\n";
            cout << "4. List Guests\n";
            cout << "5. Sort Rooms by Price\n";
            cout << "6. Sort Rooms by Occupancy\n";
            cout << "7. Calculate Revenue\n";
            cout << "8. Exit\n";
            cout << "Enter choice: ";
            int choice; cin >> choice;

            switch(choice) {
                case 1: {
                    string type; double price; int n;
                    cout << "Room Type (Single/Double/Suite): "; cin.ignore(); getline(cin, type);
                    cout << "Price: "; cin >> price;
                    cout << "Number of amenities: "; cin >> n;
                    vector<string> amenities;
                    cout << "Enter amenities: "; cin.ignore();
                    for(int i=0;i<n;i++) {
                        string am; getline(cin, am);
                        amenities.push_back(am);
                    }
                    addRoom(type, price, amenities);
                    break;
                }
                case 2: listRooms(); break;
                case 3: bookRoom(); break;
                case 4: listGuests(); break;
                case 5: sortRoomsByPrice(); break;
                case 6: sortRoomsByOccupancy(); break;
                case 7: calculateRevenue(); break;
                case 8: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

// -------------------- Main Function --------------------
int main() {
    cout << "=== Welcome to Eco Resort Management System ===\n";

    EcoResort resort;

    // Add some sample rooms
    resort.addRoom("Single", 2000, {"WiFi", "Eco-Friendly Toiletries"});
    resort.addRoom("Double", 3500, {"WiFi", "Balcony", "Solar AC"});
    resort.addRoom("Suite", 5000, {"WiFi", "Balcony", "Organic Breakfast"});

    resort.menu();

    return 0;
}

