#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include "Visit.h"
#include <vector>
#include <string>
using namespace std;

class Patient : public Person {
public:
    string insuranceName;
    string insuranceID;
    string admissionDateTime;

    vector<string> appointments;
    vector<Visit> history;

    string serialize() const;
};

#endif