#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// -------------------- Course Class --------------------
class Course {
public:
    string name;
    double fee;
    int maxStudents;
    int enrolled;

    Course(string n, double f, int max) : name(n), fee(f), maxStudents(max), enrolled(0) {}
    void display() {
        cout << "Course: " << name 
             << ", Fee: ₹" << fixed << setprecision(2) << fee
             << ", Enrolled: " << enrolled << "/" << maxStudents << endl;
    }
};

// -------------------- Student Node (Linked List) --------------------
struct StudentNode {
    string name;
    string courseName;
    StudentNode* next;
    StudentNode(string n, string c) : name(n), courseName(c), next(nullptr) {}
};

// -------------------- IT Training Center --------------------
class ITTrainingCenter {
private:
    StudentNode* head;
    Course* courses;
    int courseCount;

public:
    ITTrainingCenter(int maxCourses) {
        head = nullptr;
        courses = new Course[maxCourses]{};
        courseCount = 0;
    }

    ~ITTrainingCenter() {
        StudentNode* curr = head;
        while (curr) {
            StudentNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete[] courses;
    }

    void addCourse(string name, double fee, int maxStudents) {
        courses[courseCount++] = Course(name, fee, maxStudents);
    }

    void listCourses() {
        cout << "\n--- Available Courses ---\n";
        for (int i = 0; i < courseCount; i++)
            courses[i].display();
    }

    void addStudent() {
        string sName, cName;
        cout << "Enter Student Name: "; cin.ignore(); getline(cin, sName);
        cout << "Enter Course Name: "; getline(cin, cName);

        // Find course
        Course* selectedCourse = nullptr;
        for (int i = 0; i < courseCount; i++)
            if (courses[i].name == cName)
                selectedCourse = &courses[i];

        if (!selectedCourse) {
            cout << "Course not found.\n";
            return;
        }

        if (selectedCourse->enrolled >= selectedCourse->maxStudents) {
            cout << "Course is full.\n";
            return;
        }

        // Add student to linked list
        StudentNode* newNode = new StudentNode(sName, cName);
        if (!head) head = newNode;
        else {
            StudentNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newNode;
        }

        selectedCourse->enrolled++;
        cout << "Student enrolled successfully!\n";
    }

    void listStudents() {
        cout << "\n--- Enrolled Students ---\n";
        StudentNode* curr = head;
        int count = 1;
        while (curr) {
            cout << count++ << ". " << curr->name << " -> " << curr->courseName << endl;
            curr = curr->next;
        }
        if (!head) cout << "No students enrolled yet.\n";
    }

    void calculateRevenue() {
        double total = 0;
        for (int i = 0; i < courseCount; i++)
            total += courses[i].enrolled * courses[i].fee;
        cout << "Total Revenue: ₹" << fixed << setprecision(2) << total << endl;
    }

    void menu() {
        while (true) {
            cout << "\n--- IT Training Center Menu ---\n";
            cout << "1. List Courses\n";
            cout << "2. Add Student\n";
            cout << "3. List Students\n";
            cout << "4. Calculate Revenue\n";
            cout << "5. Exit\n";
            cout << "Enter choice: ";
            int choice; cin >> choice;

            switch(choice) {
                case 1: listCourses(); break;
                case 2: addStudent(); break;
                case 3: listStudents(); break;
                case 4: calculateRevenue(); break;
                case 5: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

// -------------------- Main Function --------------------
int main() {
    cout << "=== Welcome to IT Training Center Management System ===\n";

    ITTrainingCenter center(5);

    // Add courses
    center.addCourse("C++ Programming", 15000, 30);
    center.addCourse("Python Programming", 14000, 30);
    center.addCourse("Web Development", 12000, 25);
    center.addCourse("Cloud Computing", 20000, 20);
    center.addCourse("Cybersecurity", 18000, 20);

    center.menu();

    return 0;
}

