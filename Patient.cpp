#include "Patient.h"

string Patient::serialize() const {
    string s = "P|" + id + "|" + first + "|" + last + "|" + gender + "|" + insuranceName + "|" + insuranceID + "|" + admissionDateTime + "\n";

    for (int i = 0; i < history.size(); i++)
        s += "V|" + history[i].serialize() + "\n";

    for (int i = 0; i < appointments.size(); i++)
        s += "A|" + appointments[i] + "\n";

    return s;
}