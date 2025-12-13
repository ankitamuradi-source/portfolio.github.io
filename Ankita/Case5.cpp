#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// --------------------------- Lesson Class ---------------------------
class Lesson {
public:
    int id;
    double difficulty; // 0 to 100
    string topic;

    Lesson(int id, double diff, string topic) {
        this->id = id;
        difficulty = diff;
        this->topic = topic;
    }
};

// --------------------------- Student Class ---------------------------
class Student {
public:
    int id;
    string name;
    double skillLevel; // 0 to 100
    vector<int> completedLessons;
    vector<double> scores;
    bool alert; // falling behind

    Student(int id, string name) {
        this->id = id;
        this->name = name;
        skillLevel = rand() % 50 + 25; // initial skill between 25-75
        alert = false;
    }

    void completeLesson(int lessonID, double score) {
        completedLessons.push_back(lessonID);
        scores.push_back(score);
        skillLevel = min(100.0, skillLevel + score*0.1); // increase skill based on performance
    }

    double averageScore() {
        if(scores.empty()) return 0;
        double sum = 0;
        for(double s: scores) sum += s;
        return sum / scores.size();
    }
};

// --------------------------- KNN Recommendation ---------------------------
vector<int> recommendLessons(Student &s, vector<Lesson> &lessons, int k=3) {
    vector<pair<double,int>> diff;
    for(auto &l: lessons) {
        double d = abs(l.difficulty - s.skillLevel);
        diff.push_back({d,l.id});
    }
    sort(diff.begin(), diff.end());
    vector<int> recommended;
    for(int i=0;i<min(k,(int)diff.size());i++) recommended.push_back(diff[i].second);
    return recommended;
}

// --------------------------- Adaptive Learning Path ---------------------------
int selectNextLesson(Student &s, vector<Lesson> &lessons) {
    // Greedy: choose lesson closest to student's skill level that is not completed
    double minDiff = 1e9;
    int nextLessonID = -1;
    for(auto &l: lessons) {
        if(find(s.completedLessons.begin(), s.completedLessons.end(), l.id) != s.completedLessons.end()) continue;
        double diff = abs(l.difficulty - s.skillLevel);
        if(diff < minDiff) {
            minDiff = diff;
            nextLessonID = l.id;
        }
    }
    return nextLessonID;
}

// --------------------------- Difficulty Matching ---------------------------
int findLessonByDifficulty(vector<Lesson> &lessons, double targetSkill) {
    // Binary Search to find closest difficulty
    int left = 0, right = lessons.size()-1;
    int bestID = -1;
    double bestDiff = 1e9;
    while(left <= right) {
        int mid = (left+right)/2;
        double diff = abs(lessons[mid].difficulty - targetSkill);
        if(diff < bestDiff) {
            bestDiff = diff;
            bestID = lessons[mid].id;
        }
        if(lessons[mid].difficulty < targetSkill) left = mid+1;
        else right = mid-1;
    }
    return bestID;
}

// --------------------------- Personalized Learning Platform ---------------------------
class EduTech {
public:
    vector<Student> students;
    vector<Lesson> lessons;
    int timeStep;

    EduTech() { timeStep = 0; }

    void generateStudents(int n) {
        for(int i=0;i<n;i++) {
            students.push_back(Student(i,"Student_"+to_string(i+1)));
        }
    }

    void generateLessons(int n) {
        string topics[] = {"Math","Science","Programming","History","Art"};
        for(int i=0;i<n;i++) {
            double diff = rand()%101;
            string topic = topics[rand()%5];
            lessons.push_back(Lesson(i,diff,topic));
        }
        sort(lessons.begin(), lessons.end(), [](Lesson a, Lesson b){return a.difficulty < b.difficulty;});
    }

    // ---------------- Simulate Student Learning ----------------
    void simulateLearning() {
        for(auto &s: students) {
            vector<int> rec = recommendLessons(s, lessons, 2);
            for(int lid: rec) {
                double score = rand()%51 + 50; // 50-100
                s.completeLesson(lid, score);
            }
            int nextLesson = selectNextLesson(s, lessons);
            if(nextLesson != -1) {
                double score = rand()%51 + 50;
                s.completeLesson(nextLesson, score);
            }
            // Check alert
            s.alert = s.averageScore() < 65;
        }
    }

    // ---------------- Print Status ----------------
    void printStatus() {
        cout << "----- Personalized Learning Status (TimeStep " << timeStep << ") -----" << endl;
        for(auto &s: students) {
            cout << s.name << " Skill: " << fixed << setprecision(2) << s.skillLevel
                 << " AvgScore: " << s.averageScore()
                 << (s.alert ? " [ALERT: Falling behind]" : "")
                 << " Completed Lessons: ";
            for(int l: s.completedLessons) cout << l << " ";
            cout << endl;
        }
        cout << "--------------------------------------------------------" << endl;
    }

    // ---------------- Student Performance Analytics ----------------
    void printAnalytics() {
        double avgSkill = 0;
        int alertCount = 0;
        for(auto &s: students) {
            avgSkill += s.skillLevel;
            if(s.alert) alertCount++;
        }
        avgSkill /= students.size();
        cout << "=== Analytics ===" << endl;
        cout << "Average Skill Level: " << avgSkill << endl;
        cout << "Students Falling Behind: " << alertCount << "/" << students.size() << endl;
        cout << "=================" << endl;
    }

    // ---------------- Run Simulation ----------------
    void runSimulation(int steps) {
        for(int t=0;t<steps;t++) {
            timeStep++;
            simulateLearning();
            printStatus();
        }
        printAnalytics();
    }
};

// --------------------------- Main Function ---------------------------
int main() {
    srand(time(0));
    EduTech platform;
    platform.generateStudents(8);
    platform.generateLessons(20);
    platform.runSimulation(20);
    return 0;
}

