#include "Nurse.h"
#include <sstream>

string Nurse::serialize() const {
    return id + "|" + first + "|" + last + "|" + gender + "|" + ward;
}

void Nurse::deserialize(const string &line) {
    stringstream ss(line);
    getline(ss, id, '|');
    getline(ss, first, '|');
    getline(ss, last, '|');
    getline(ss, gender, '|');
    getline(ss, ward, '|');
}