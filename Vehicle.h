#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

//any vehicle entity in the system
class Vehicle {
protected:
    std::string label;
    std::string arrivalTime;

public:
    Vehicle(const std::string& label, const std::string& time);
    virtual ~Vehicle() = default; // virtual destructor: Vehicle is a polymorphic base

    std::string getLabel() const;
    std::string getArrivalTime() const;
};

#endif