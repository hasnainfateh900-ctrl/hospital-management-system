#ifndef VISIT_H
#define VISIT_H

#include <string>
using namespace std;

string nowTime();

class Visit {
public:
    string timestamp;
    string doctorName;
    string nurseName;
    string sickness;
    string medicine;

    Visit();
    Visit(string d, string n, string s, string m);

    string serialize() const;
    void deserialize(const string &line);
};

#endif