#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

// Base class for all people in the hospital
class Person {
public:
    string id;
    string first;
    string last;
    string gender;
};

#endif