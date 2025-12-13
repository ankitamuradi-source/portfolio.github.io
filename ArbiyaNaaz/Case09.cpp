#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;

// Course class
class Course {
private:
    int id;
    string name;
    int maxStudents;
    int enrolledStudents;
    double fee;

public:
    Course(int id, string name, int maxStudents, double fee)
        : id(id), name(name), maxStudents(maxStudents), fee(fee), enrolledStudents(0) {}

    bool enrollStudent() {
        if (enrolledStudents < maxStudents) {
            enrolledStudents++;
            return true;
        }
        return false;
    }

    void display() {
        cout << setw(5) << id
             << setw(25) << name
             << setw(10) << enrolledStudents
             << setw(10) << maxStudents
             << setw(10) << fee << endl;
    }

    double getRevenue() const { return enrolledStudents * fee; }
    string getName() const { return name; }
};

// Student class
class Student {
private:
    int id;
    string name;
    vector<int> enrolledCourseIds;

public:
    Student(int id, string name) : id(id), name(name) {}

    void enroll(int courseId) { enrolledCourseIds.push_back(courseId); }

    void display() {
        cout << setw(5) << id << setw(20) << name << setw(15);
        for (auto c : enrolledCourseIds) cout << c << " ";
        cout << endl;
    }

    vector<int> getCourses() { return enrolledCourseIds; }
};

// Skill Development Hub
class SkillDevelopmentHub {
private:
    vector<Course> courses;
    vector<Student> students;
    double totalRevenue;

public:
    SkillDevelopmentHub() { totalRevenue = 0; }

    void setupCourses() {
        courses.push_back(Course(1, "Programming Basics", 50, 2000));
        courses.push_back(Course(2, "Web Development", 40, 3000));
        courses.push_back(Course(3, "Data Science", 30, 5000));
        courses.push_back(Course(4, "Cyber Security", 25, 4000));
        courses.push_back(Course(5, "Cloud Computing", 35, 4500));
        courses.push_back(Course(6, "AI & Machine Learning", 20, 6000));
        courses.push_back(Course(7, "App Development", 30, 3500));
        courses.push_back(Course(8, "Digital Marketing", 40, 2500));
    }

    void setupStudents() {
        students.push_back(Student(101, "Alice"));
        students.push_back(Student(102, "Bob"));
        students.push_back(Student(103, "Charlie"));
        students.push_back(Student(104, "Diana"));
        students.push_back(Student(105, "Eve"));
        students.push_back(Student(106, "Frank"));
        students.push_back(Student(107, "Grace"));
        students.push_back(Student(108, "Hank"));
        students.push_back(Student(109, "Ivy"));
        students.push_back(Student(110, "Jack"));
    }

    void enrollStudentsRandomly() {
        srand(time(0));
        for (auto &student : students) {
            int coursesToEnroll = 1 + rand() % 3;
            vector<int> enrolled;
            while (enrolled.size() < coursesToEnroll) {
                int courseId = rand() % courses.size();
                if (find(enrolled.begin(), enrolled.end(), courseId) == enrolled.end()) {
                    if (courses[courseId].enrollStudent()) {
                        student.enroll(courseId + 1);
                        enrolled.push_back(courseId);
                        totalRevenue += courses[courseId].getRevenue()/courses[courseId].enrolledStudents;
                    }
                }
            }
        }
    }

    void displayCourses() {
        cout << "\n--- Courses ---\n";
        cout << setw(5) << "ID" << setw(25) << "Name" << setw(10) << "Enrolled" 
             << setw(10) << "Capacity" << setw(10) << "Fee" << endl;
        for (auto &c : courses) c.display();
    }

    void displayStudents() {
        cout << "\n--- Students ---\n";
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Courses" << endl;
        for (auto &s : students) s.display();
    }

    void scheduleCourses() {
        cout << "\n--- Course Schedule ---\n";
        string days[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};
        string times[] = {"9AM-11AM", "11AM-1PM", "2PM-4PM", "4PM-6PM"};
        for (size_t i = 0; i < courses.size(); i++) {
            string day = days[i % 5];
            string time = times[i % 4];
            cout << courses[i].getName() << " : " << day << " " << time << endl;
        }
    }

    void runSimulation() {
        setupCourses();
        setupStudents();
        enrollStudentsRandomly();
        displayCourses();
        displayStudents();
        scheduleCourses();
        cout << "\nTotal Revenue Generated: ₹" << totalRevenue << endl;
    }
};

int main() {
    SkillDevelopmentHub hub;
    hub.runSimulation();
    return 0;
}

