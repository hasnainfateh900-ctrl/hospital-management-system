#include "Doctor.h"
#include <sstream>

string Doctor::serialize() const {
    string s = id + "|" + first + "|" + last + "|" + gender + "|";

    // Serialize accepted insurances
    for (int i = 0; i < acceptedInsurances.size(); i++) {
        s += acceptedInsurances[i];
        if (i + 1 < acceptedInsurances.size()) s += ",";
    }
    s += "|";

    // Serialize available slots
    for (int i = 0; i < availableSlots.size(); i++) {
        s += availableSlots[i];
        if (i + 1 < availableSlots.size()) s += ",";
    }
    s += "|";

    // Serialize booked slots
    for (int i = 0; i < bookedSlots.size(); i++) {
        s += bookedSlots[i];
        if (i + 1 < bookedSlots.size()) s += ",";
    }

    return s;
}

void Doctor::deserialize(const string &line) {
    stringstream ss(line);
    string ins, avail, booked, token;

    getline(ss, id, '|');
    getline(ss, first, '|');
    getline(ss, last, '|');
    getline(ss, gender, '|');
    getline(ss, ins, '|');
    getline(ss, avail, '|');
    getline(ss, booked, '|');

    // Deserialize insurances
    stringstream ss2(ins);
    while (getline(ss2, token, ',')) acceptedInsurances.push_back(token);

    // Deserialize available slots
    stringstream ss3(avail);
    while (getline(ss3, token, ','))
        if (!token.empty()) availableSlots.push_back(token);

    // Deserialize booked slots
    stringstream ss4(booked);
    while (getline(ss4, token, ','))
        if (!token.empty()) bookedSlots.push_back(token);
}