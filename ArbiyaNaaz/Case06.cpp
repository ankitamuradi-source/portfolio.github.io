#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Enum for consultation type
enum ConsultationType { VIDEO, CHAT, CALL };

// Class for Patient
class Patient {
private:
    int id;
    string name;
    int age;
    string gender;
    string healthRecord;
public:
    Patient(int id, string name, int age, string gender, string healthRecord) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->healthRecord = healthRecord;
    }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(5) << age
             << setw(10) << gender
             << setw(30) << healthRecord
             << endl;
    }

    string getName() const { return name; }
    int getId() const { return id; }
};

// Class for Doctor
class Doctor {
private:
    int id;
    string name;
    string specialization;
    int experience; // in years
public:
    Doctor(int id, string name, string specialization, int experience) {
        this->id = id;
        this->name = name;
        this->specialization = specialization;
        this->experience = experience;
    }

    void display() const {
        cout << setw(5) << id
             << setw(20) << name
             << setw(20) << specialization
             << setw(5) << experience
             << endl;
    }

    string getName() const { return name; }
    int getId() const { return id; }
};

// Appointment class
class Appointment {
private:
    int id;
    int patientId;
    int doctorId;
    string date;
    ConsultationType type;
    double fee;
public:
    Appointment(int id, int patientId, int doctorId, string date, ConsultationType type, double fee) {
        this->id = id;
        this->patientId = patientId;
        this->doctorId = doctorId;
        this->date = date;
        this->type = type;
        this->fee = fee;
    }

    void display() const {
        string typeStr = (type == VIDEO) ? "Video" : (type == CHAT) ? "Chat" : "Call";
        cout << setw(5) << id
             << setw(10) << patientId
             << setw(10) << doctorId
             << setw(15) << date
             << setw(10) << typeStr
             << setw(10) << fee
             << endl;
    }

    double getFee() const { return fee; }
};

// Telemedicine Platform Class
class TelemedicinePlatform {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int nextPatientId;
    int nextDoctorId;
    int nextAppointmentId;
    double totalRevenue;

public:
    TelemedicinePlatform() {
        nextPatientId = 1;
        nextDoctorId = 1;
        nextAppointmentId = 1;
        totalRevenue = 0;
    }

    void addPatient(string name, int age, string gender, string healthRecord) {
        patients.push_back(Patient(nextPatientId++, name, age, gender, healthRecord));
        cout << "Patient added successfully.\n";
    }

    void addDoctor(string name, string specialization, int experience) {
        doctors.push_back(Doctor(nextDoctorId++, name, specialization, experience));
        cout << "Doctor added successfully.\n";
    }

    void scheduleAppointment(int patientId, int doctorId, string date, ConsultationType type, double fee) {
        appointments.push_back(Appointment(nextAppointmentId++, patientId, doctorId, date, type, fee));
        totalRevenue += fee;
        cout << "Appointment scheduled successfully.\n";
    }

    void displayPatients() const {
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age" << setw(10) << "Gender" << setw(30) << "Health Record" << endl;
        cout << "-------------------------------------------------------------------------------\n";
        for (const auto &p : patients) p.display();
    }

    void displayDoctors() const {
        cout << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Specialization" << setw(5) << "Exp" << endl;
        cout << "------------------------------------------------------\n";
        for (const auto &d : doctors) d.display();
    }

    void displayAppointments() const {
        cout << setw(5) << "ID" << setw(10) << "PatientID" << setw(10) << "DoctorID" << setw(15) << "Date" << setw(10) << "Type" << setw(10) << "Fee" << endl;
        cout << "---------------------------------------------------------------\n";
        for (const auto &a : appointments) a.display();
    }

    void displayRevenue() const {
        cout << "Total Revenue: ₹" << totalRevenue << endl;
    }

    void simulateAppointments(int days = 10) {
        srand(time(0));
        for (int i = 1; i <= days; i++) {
            cout << "\n--- Day " << i << " Simulation ---\n";
            for (size_t j = 0; j < patients.size(); j++) {
                int doctorIndex = rand() % doctors.size();
                int type = rand() % 3;
                double fee = 500 + rand() % 1000;
                scheduleAppointment(patients[j].getId(), doctors[doctorIndex].getId(), "2025-12-" + to_string(i), static_cast<ConsultationType>(type), fee);
            }
            displayAppointments();
        }
    }

    void runDemo() {
        // Add doctors
        addDoctor("Dr. Smith", "Cardiology", 10);
        addDoctor("Dr. Alice", "Dermatology", 7);
        addDoctor("Dr. Bob", "Pediatrics", 5);

        // Add patients
        addPatient("John", 30, "Male", "No major illness");
        addPatient("Emma", 25, "Female", "Allergy to pollen");
        addPatient("Michael", 40, "Male", "Diabetic");

        // Simulate appointments
        simulateAppointments(10);

        // Display summary
        displayRevenue();
    }
};

int main() {
    TelemedicinePlatform platform;
    platform.runDemo();
    return 0;
}

