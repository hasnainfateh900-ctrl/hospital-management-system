#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <vector>
#include <string>

using namespace std;

// Doctor inherits from Person
class Doctor : public Person {
public:
    vector<string> acceptedInsurances;
    vector<string> availableSlots;  // Available appointment slots
    vector<string> bookedSlots;     // Booked appointment slots

    string serialize() const;
    void deserialize(const string &line);
};

#endif