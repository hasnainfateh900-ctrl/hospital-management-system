#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include <string>
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"

using namespace std;

class Hospital {
private:
    vector<Doctor> doctors;
    vector<Nurse> nurses;
    vector<Patient> patients;

    const string DB = "hospital_db.txt";

public:
    Hospital();
    ~Hospital();

    void menu();

private:
    Doctor* findDoctor(string id);
    Nurse* findNurse(string id);
    Patient* findPatient(string id);

    void newPatient();
    void scheduleAppointment();
    void addVisit();
    void showPatientDetails();
    void viewPatientHistory();
    void followUps();
    void manageDoctorSlots();  // New function to manage doctor availability

    void save();
    void load();
};

#endif