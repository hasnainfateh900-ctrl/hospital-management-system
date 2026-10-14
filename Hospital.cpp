#include "Hospital.h"
#include "Visit.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/* ================= CONSTRUCTOR / DESTRUCTOR ================= */

Hospital::Hospital() {
    load();
}

Hospital::~Hospital() {
    // Destructor - save is now called after each operation
}

/* ================= FIND FUNCTIONS ================= */

Doctor* Hospital::findDoctor(string id) {
    for (int i = 0; i < doctors.size(); i++)
        if (doctors[i].id == id)
            return &doctors[i];
    return NULL;
}

Nurse* Hospital::findNurse(string id) {
    for (int i = 0; i < nurses.size(); i++)
        if (nurses[i].id == id)
            return &nurses[i];
    return NULL;
}

Patient* Hospital::findPatient(string id) {
    for (int i = 0; i < patients.size(); i++)
        if (patients[i].id == id)
            return &patients[i];
    return NULL;
}

/* ================= NEW PATIENT ================= */

void Hospital::newPatient() {
    Patient p;

    cout << "Patient ID: ";
    getline(cin, p.id);

    cout << "First Name: ";
    getline(cin, p.first);

    cout << "Last Name: ";
    getline(cin, p.last);

    cout << "Gender: ";
    getline(cin, p.gender);

    cout << "Insurance Name: ";
    getline(cin, p.insuranceName);

    cout << "Insurance ID: ";
    getline(cin, p.insuranceID);

    p.admissionDateTime = nowTime();

    patients.push_back(p);

    cout << "Patient admitted at " << p.admissionDateTime << "\n";

    save();  // Save immediately after adding patient
}

/* ================= MANAGE DOCTOR SLOTS ================= */

void Hospital::manageDoctorSlots() {
    string did;
    cout << "Doctor ID: ";
    getline(cin, did);

    Doctor* d = findDoctor(did);
    if (!d) {
        cout << "Invalid doctor.\n";
        return;
    }

    cout << "\n1. Add Available Slot\n"
         << "2. View Available Slots\n"
         << "3. View Booked Slots\n"
         << "Choice: ";

    string choice;
    getline(cin, choice);

    if (choice == "1") {
        cout << "Enter slot (e.g., 2024-12-15 10:00): ";
        string slot;
        getline(cin, slot);
        d->availableSlots.push_back(slot);
        cout << "Slot added.\n";
        save();  // Save immediately after adding slot
    }
    else if (choice == "2") {
        cout << "\nAvailable Slots for Dr. " << d->first << " " << d->last << ":\n";
        for (int i = 0; i < d->availableSlots.size(); i++)
            cout << (i + 1) << ". " << d->availableSlots[i] << "\n";
    }
    else if (choice == "3") {
        cout << "\nBooked Slots for Dr. " << d->first << " " << d->last << ":\n";
        for (int i = 0; i < d->bookedSlots.size(); i++)
            cout << (i + 1) << ". " << d->bookedSlots[i] << "\n";
    }
}

/* ================= SCHEDULE APPOINTMENT ================= */

void Hospital::scheduleAppointment() {
    string pid, did;

    cout << "Patient ID: ";
    getline(cin, pid);

    Patient* p = findPatient(pid);
    if (!p) {
        cout << "Invalid patient.\n";
        return;
    }

    cout << "Doctor ID: ";
    getline(cin, did);

    Doctor* d = findDoctor(did);
    if (!d) {
        cout << "Invalid doctor.\n";
        return;
    }

    // Check insurance coverage
    bool covered = false;
    for (int i = 0; i < d->acceptedInsurances.size(); i++)
        if (d->acceptedInsurances[i] == p->insuranceName)
            covered = true;

    if (!covered) {
        char c;
        while (true) {
            cout << "Out of network ($60). Continue? (y/n): ";
            cin >> c;
            cin.ignore();

            if (c == 'y' || c == 'Y') {
                break;  // Continue with appointment
            }
            else if (c == 'n' || c == 'N') {
                return;  // Cancel appointment
            }
            else {
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }

    // Show available slots
    if (d->availableSlots.empty()) {
        cout << "No available slots for this doctor.\n";
        return;
    }

    cout << "\nAvailable Slots:\n";
    for (int i = 0; i < d->availableSlots.size(); i++)
        cout << (i + 1) << ". " << d->availableSlots[i] << "\n";

    cout << "\nSelect slot number: ";
    string slotChoice;
    getline(cin, slotChoice);

    int slotIndex = -1;
    stringstream ss(slotChoice);
    ss >> slotIndex;
    slotIndex--;  // Convert to 0-based index

    if (slotIndex < 0 || slotIndex >= d->availableSlots.size()) {
        cout << "Invalid slot selection.\n";
        return;
    }

    // Book the slot
    string selectedSlot = d->availableSlots[slotIndex];

    // Move slot from available to booked
    d->bookedSlots.push_back(selectedSlot);
    d->availableSlots.erase(d->availableSlots.begin() + slotIndex);

    // Add to patient's appointments
    p->appointments.push_back(selectedSlot);

    cout << "Appointment scheduled for " << selectedSlot << "\n";

    save();  // Save immediately after scheduling appointment
}

/* ================= RECORD VISIT ================= */

void Hospital::addVisit() {
    string pid, did, nid;

    cout << "Patient ID: ";
    getline(cin, pid);

    Patient* p = findPatient(pid);
    if (!p) {
        cout << "Invalid patient.\n";
        return;
    }

    cout << "Doctor ID: ";
    getline(cin, did);

    Doctor* d = findDoctor(did);
    if (!d) {
        cout << "Invalid doctor.\n";
        return;
    }

    cout << "Nurse ID: ";
    getline(cin, nid);

    Nurse* n = findNurse(nid);
    if (!n) {
        cout << "Invalid nurse.\n";
        return;
    }

    string sickness, medicine;
    cout << "Sickness: ";
    getline(cin, sickness);

    cout << "Medication: ";
    getline(cin, medicine);

    p->history.push_back(
        Visit(d->first + " " + d->last,
              n->first + " " + n->last,
              sickness,
              medicine)
    );

    cout << "Visit recorded.\n";

    save();  // Save immediately after recording visit
}

/* ================= SHOW PATIENT DETAILS ================= */

void Hospital::showPatientDetails() {
    string pid;
    cout << "Patient ID: ";
    getline(cin, pid);

    Patient* p = findPatient(pid);
    if (!p) {
        cout << "Invalid patient.\n";
        return;
    }

    cout << "\nPatient: " << p->first << " " << p->last << "\n";
    cout << "Admitted: " << p->admissionDateTime << "\n";
    cout << "Insurance: " << p->insuranceName
         << " (" << p->insuranceID << ")\n";

    cout << "\nAppointments:\n";
    for (int i = 0; i < p->appointments.size(); i++)
        cout << "- " << p->appointments[i] << "\n";

    cout << "\nMedical History (Read-only):\n";
    for (int i = 0; i < p->history.size(); i++)
        cout << p->history[i].serialize() << "\n";
}

/* ================= VIEW VISIT HISTORY ONLY ================= */

void Hospital::viewPatientHistory() {
    string pid;
    cout << "Patient ID: ";
    getline(cin, pid);

    Patient* p = findPatient(pid);
    if (!p) {
        cout << "Invalid patient.\n";
        return;
    }

    cout << "\nVisit History:\n";
    for (int i = 0; i < p->history.size(); i++)
        cout << p->history[i].serialize() << "\n";
}

/* ================= FOLLOW-UP APPOINTMENTS ================= */

void Hospital::followUps() {
    cout << "\nAll Follow-Up Appointments:\n";

    for (int i = 0; i < patients.size(); i++) {
        for (int j = 0; j < patients[i].appointments.size(); j++) {
            cout << patients[i].first << " "
                 << patients[i].last << " - "
                 << patients[i].appointments[j] << "\n";
        }
    }
}

/* ================= MENU ================= */

void Hospital::menu() {
    while (true) {
        cout << "\n1 New Patient\n"
             << "2 Schedule Appointment\n"
             << "3 Record Visit\n"
             << "4 Show Patient Details\n"
             << "5 View Patient History\n"
             << "6 View All Follow-Ups\n"
             << "7 Manage Doctor Slots\n"
             << "0 Exit\n"
             << "Choice: ";

        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << "Invalid option.\n";
            continue;
        }

        char choice = input[0];

        switch (choice) {
            case '1':
                newPatient();
            break;

            case '2':
                scheduleAppointment();
            break;

            case '3':
                addVisit();
            break;

            case '4':
                showPatientDetails();
            break;

            case '5':
                viewPatientHistory();
            break;

            case '6':
                followUps();
            break;

            case '7':
                manageDoctorSlots();
            break;

            case '0':
                cout << "Exiting...\n";
            return;

            default:
                cout << "Invalid option.\n";
        }
    }
}


/* ================= SAVE ================= */

void Hospital::save() {
    ofstream out(DB.c_str());
    if (!out) return;

    for (int i = 0; i < doctors.size(); i++)
        out << "D|" << doctors[i].serialize() << "\n";

    for (int i = 0; i < nurses.size(); i++)
        out << "N|" << nurses[i].serialize() << "\n";

    for (int i = 0; i < patients.size(); i++)
        out << patients[i].serialize();
}

/* ================= LOAD ================= */

void Hospital::load() {
    ifstream in(DB.c_str());
    if (!in) return;

    string line;
    Patient* currentPatient = NULL;

    while (getline(in, line)) {
        if (line.empty()) continue;  // Skip empty lines

        if (line.rfind("D|", 0) == 0) {
            currentPatient = NULL;  // No longer processing a patient
            Doctor d;
            d.deserialize(line.substr(2));
            doctors.push_back(d);
        }
        else if (line.rfind("N|", 0) == 0) {
            currentPatient = NULL;  // No longer processing a patient
            Nurse n;
            n.deserialize(line.substr(2));
            nurses.push_back(n);
        }
        else if (line.rfind("P|", 0) == 0) {
            // Save previous patient if exists
            if (currentPatient != NULL) {
                patients.push_back(*currentPatient);
                delete currentPatient;
            }

            // Start new patient
            currentPatient = new Patient();
            stringstream ss(line.substr(2));

            getline(ss, currentPatient->id, '|');
            getline(ss, currentPatient->first, '|');
            getline(ss, currentPatient->last, '|');
            getline(ss, currentPatient->gender, '|');
            getline(ss, currentPatient->insuranceName, '|');
            getline(ss, currentPatient->insuranceID, '|');
            getline(ss, currentPatient->admissionDateTime, '|');
        }
        else if (line.rfind("V|", 0) == 0 && currentPatient != NULL) {
            Visit v;
            v.deserialize(line.substr(2));
            currentPatient->history.push_back(v);
        }
        else if (line.rfind("A|", 0) == 0 && currentPatient != NULL) {
            currentPatient->appointments.push_back(line.substr(2));
        }
    }

    // Don't forget the last patient
    if (currentPatient != NULL) {
        patients.push_back(*currentPatient);
        delete currentPatient;
    }
}