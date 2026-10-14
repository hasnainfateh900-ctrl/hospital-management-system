#include "Visit.h"
#include <ctime>
#include <sstream>

string nowTime() {
    time_t t = time(NULL);
    tm *lt = localtime(&t);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", lt);
    return buf;
}

Visit::Visit() {}

Visit::Visit(string d, string n, string s, string m) {
    timestamp = nowTime();
    doctorName = d;
    nurseName = n;
    sickness = s;
    medicine = m;
}

string Visit::serialize() const {
    return timestamp + "|" + doctorName + "|" + nurseName + "|" + sickness + "|" + medicine;
}

void Visit::deserialize(const string &line) {
    stringstream ss(line);
    getline(ss, timestamp, '|');
    getline(ss, doctorName, '|');
    getline(ss, nurseName, '|');
    getline(ss, sickness, '|');
    getline(ss, medicine, '|');
}