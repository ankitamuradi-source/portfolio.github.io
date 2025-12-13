#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// --------------------- Student Node ---------------------
struct Student {
    int id;
    string name;
    string course;
    int attendance;
    double feePaid;
    Student* next;

    Student(int i, string n, string c) {
        id = i;
        name = n;
        course = c;
        attendance = 0;
        feePaid = 0;
        next = nullptr;
    }
};

// --------------------- Linked List for Students ---------------------
class StudentList {
private:
    Student* head;
public:
    StudentList() { head = nullptr; }

    void addStudent(int id, string name, string course) {
        Student* newStudent = new Student(id, name, course);
        if (!head) {
            head = newStudent;
        } else {
            Student* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newStudent;
        }
        cout << "Student " << name << " added to course " << course << ".\n";
    }

    void displayStudents() {
        if (!head) { cout << "No students enrolled.\n"; return; }
        Student* temp = head;
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(15)
             << "Course" << setw(10) << "Attendance" << setw(10) << "Fee Paid" << "\n";
        cout << "--------------------------------------------------------------\n";
        while (temp) {
            cout << setw(5) << temp->id << setw(20) << temp->name << setw(15)
                 << temp->course << setw(10) << temp->attendance << setw(10) << temp->feePaid << "\n";
            temp = temp->next;
        }
    }

    Student* findStudent(int id) {
        Student* temp = head;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void removeStudent(int id) {
        if (!head) return;
        if (head->id == id) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student removed.\n";
            return;
        }
        Student* prev = head;
        Student* curr = head->next;
        while (curr) {
            if (curr->id == id) {
                prev->next = curr->next;
                delete curr;
                cout << "Student removed.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Student not found.\n";
    }
};

// --------------------- Course Management ---------------------
class Course {
private:
    string name;
    double fee;
public:
    Course(string n, double f) { name = n; fee = f; }
    string getName() { return name; }
    double getFee() { return fee; }
};

// --------------------- IT Training Center ---------------------
class ITTrainingCenter {
private:
    StudentList students;
    Course courses[5];
public:
    ITTrainingCenter() {
        courses[0] = Course("Programming", 5000);
        courses[1] = Course("Cloud Computing", 7000);
        courses[2] = Course("Cybersecurity", 6000);
        courses[3] = Course("Web Development", 4500);
        courses[4] = Course("Data Science", 8000);
    }

    void enrollStudent() {
        int id;
        string name, course;
        cout << "Enter student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter student Name: ";
        getline(cin, name);
        cout << "Available Courses:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << courses[i].getName() << " (Fee: " << courses[i].getFee() << ")\n";
        }
        int choice;
        cout << "Select course (1-5): ";
        cin >> choice;
        if (choice < 1 || choice > 5) { cout << "Invalid choice.\n"; return; }
        course = courses[choice - 1].getName();
        students.addStudent(id, name, course);
    }

    void markAttendance() {
        int id;
        cout << "Enter student ID to mark attendance: ";
        cin >> id;
        Student* s = students.findStudent(id);
        if (s) {
            s->attendance++;
            cout << "Attendance marked for " << s->name << ". Total attendance: " << s->attendance << "\n";
        } else cout << "Student not found.\n";
    }

    void payFee() {
        int id;
        double amount;
        cout << "Enter student ID to pay fee: ";
        cin >> id;
        Student* s = students.findStudent(id);
        if (!s) { cout << "Student not found.\n"; return; }
        cout << "Enter fee amount to pay: ";
        cin >> amount;
        s->feePaid += amount;
        cout << "Fee updated. Total fee paid: " << s->feePaid << "\n";
    }

    void removeStudent() {
        int id;
        cout << "Enter student ID to remove: ";
        cin >> id;
        students.removeStudent(id);
    }

    void displayAllStudents() {
        students.displayStudents();
    }

    void displayMenu() {
        cout << "\n===== IT Training Center Management =====\n";
        cout << "1. Enroll Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. Pay Fee\n";
        cout << "4. Remove Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Exit\n";
    }

    void run() {
        int choice;
        while (true) {
            displayMenu();
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: enrollStudent(); break;
                case 2: markAttendance(); break;
                case 3: payFee(); break;
                case 4: removeStudent(); break;
                case 5: displayAllStudents(); break;
                case 6: cout << "Exiting...\n"; return;
                default: cout << "Invalid choice.\n";
            }
        }
    }
};

// --------------------- Main ---------------------
int main() {
    ITTrainingCenter center;
    center.run();
    return 0;
}
