#ifndef NURSE_H
#define NURSE_H

#include "Person.h"
#include <string>
using namespace std;

class Nurse : public Person {
public:
    string ward;

    string serialize() const;
    void deserialize(const string &line);
};

#endif