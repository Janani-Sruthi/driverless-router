#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string qNumber;
    std::string arrivalTime;

public:
    Person(const std::string& qNum, const std::string& time);
    virtual ~Person() = default; //virtual destructor: Person is a polymorphic base

    std::string getQNumber() const;
    std::string getArrivalTime() const;
};

#endif 