#include "ConsolePresenter.h"
#include <iostream>
#include <iomanip>

ConsolePresenter::ConsolePresenter() {}

void ConsolePresenter::displayShuttle(const Shuttle& s) const {
    std::cout << std::left << std::setw(8) << s.getLabel()
        << std::setw(18) << s.getChargingPoint().getName()
        << std::setw(10) << s.getArrivalTime()
        << (s.getIsMatched() ? ("-> Passenger " + s.getAssignedPassengerId()) : "(unmatched)")
        << std::endl;
}

void ConsolePresenter::displayPassenger(const Passenger& p) const {
    std::cout << std::left << std::setw(8) << p.getQNumber()
        << std::setw(18) << p.getDestination().getName()
        << std::setw(10) << p.getArrivalTime()
        << (p.getIsMatched() ? ("-> Shuttle " + p.getAssignedShuttleId()) : "(unmatched)")
        << std::endl;
}

void ConsolePresenter::displayLocation(const Location& l) const {
    std::cout << "- " << l.getName() << std::endl;
}

void ConsolePresenter::displayShuttleList(const std::vector<Shuttle>& shuttles) const {
    if (shuttles.empty()) {
        std::cout << "  (no shuttles loaded)" << std::endl;
        return;
    }
    std::cout << std::left << std::setw(8) << "Label" << std::setw(18) << "Charging Point"
        << std::setw(10) << "Time" << "Status" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    for (const auto& s : shuttles) {
        displayShuttle(s);
    }
}

void ConsolePresenter::displayPassengerList(const std::vector<Passenger>& passengers) const {
    if (passengers.empty()) {
        std::cout << "  (no passengers loaded)" << std::endl;
        return;
    }
    std::cout << std::left << std::setw(8) << "QNum" << std::setw(18) << "Destination"
        << std::setw(10) << "Time" << "Status" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    for (const auto& p : passengers) {
        displayPassenger(p);
    }
}

void ConsolePresenter::displaySchedule(const Schedule& schedule,
    const std::vector<Shuttle>& allShuttles,
    const std::vector<Passenger>& allPassengers) const {
    auto pairs = schedule.getMatchedPairs();

    std::cout << "\n=== Matched Schedule (" << pairs.size() << " pair(s)) ===\n";
    if (pairs.empty()) {
        std::cout << "  (no matches yet — run Compute Schedule first)\n";
    }
    else {
        std::cout << std::left << std::setw(10) << "Shuttle" << std::setw(18) << "Point/Dest"
            << std::setw(10) << "Time" << "Passenger" << std::endl;
        std::cout << std::string(55, '-') << std::endl;
        for (const auto& pair : pairs) {
            const Shuttle* sPtr = nullptr;
            for (const auto& s : allShuttles) {
                if (s.getLabel() == pair.first) { sPtr = &s; break; }
            }
            if (sPtr) {
                std::cout << std::left << std::setw(10) << sPtr->getLabel()
                    << std::setw(18) << sPtr->getChargingPoint().getName()
                    << std::setw(10) << sPtr->getArrivalTime()
                    << pair.second << std::endl;
            }
        }
    }

    auto unmatchedShuttles = schedule.getUnmatchedShuttles(allShuttles);
    std::cout << "\n=== Unmatched Shuttles (" << unmatchedShuttles.size() << ") ===\n";
    if (unmatchedShuttles.empty()) {
        std::cout << "  (none)\n";
    }
    else {
        for (const auto& label : unmatchedShuttles) {
            std::cout << "  - " << label << std::endl;
        }
    }

    auto unmatchedPassengers = schedule.getUnmatchedPassengers(allPassengers);
    std::cout << "\n=== Unmatched Passengers (" << unmatchedPassengers.size() << ") ===\n";
    if (unmatchedPassengers.empty()) {
        std::cout << "  (none)\n";
    }
    else {
        for (const auto& qNum : unmatchedPassengers) {
            std::cout << "  - " << qNum << std::endl;
        }
    }
    std::cout << std::endl;
}

void ConsolePresenter::printMenu() const {
    std::cout << "\n============================================\n";
    std::cout << "   ROUTE-PLANNER - Driverless Shuttle System\n";
    std::cout << "============================================\n";
    std::cout << " 1. Set data folder path\n";
    std::cout << " 2. Load shuttle & passenger files\n";
    std::cout << " 3. Compute schedule\n";
    std::cout << " 4. Display schedule (matched + unmatched)\n";
    std::cout << " 5. Save schedule to file\n";
    std::cout << " 6. View all shuttles\n";
    std::cout << " 7. View all passengers\n";
    std::cout << " 8. Add shuttle\n";
    std::cout << " 9. Edit shuttle\n";
    std::cout << "10. Delete shuttle\n";
    std::cout << "11. Add passenger\n";
    std::cout << "12. Edit passenger\n";
    std::cout << "13. Delete passenger\n";
    std::cout << " 0. Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter choice: ";
}

void ConsolePresenter::printMessage(const std::string& msg) const {
    std::cout << "[INFO] " << msg << std::endl;
}

void ConsolePresenter::printError(const std::string& msg) const {
    std::cout << "[ERROR] " << msg << std::endl;
}