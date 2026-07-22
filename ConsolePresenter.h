#ifndef CONSOLE_PRESENTER_H
#define CONSOLE_PRESENTER_H

#include <vector>
#include "Shuttle.h"
#include "Passenger.h"
#include "Location.h"
#include "Schedule.h"

// All console output lives here, kept out of the core entity classes so
// Shuttle/Passenger/Location/Schedule stay reusable in a GUI, web, or
// file-export context later without dragging UI code along with them.
class ConsolePresenter {
public:
    ConsolePresenter();

    void displayShuttle(const Shuttle& s) const;
    void displayPassenger(const Passenger& p) const;
    void displayLocation(const Location& l) const;

    void displayShuttleList(const std::vector<Shuttle>& shuttles) const;
    void displayPassengerList(const std::vector<Passenger>& passengers) const;

    // Prints matched pairs plus unmatched shuttles/passengers.
    void displaySchedule(const Schedule& schedule,
        const std::vector<Shuttle>& allShuttles,
        const std::vector<Passenger>& allPassengers) const;

    void printMenu() const;
    void printMessage(const std::string& msg) const;
    void printError(const std::string& msg) const;
};

#endif