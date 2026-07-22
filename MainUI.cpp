#include "MainUI.h"
#include "ShuttleFactory.h"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
    std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    int readMenuChoice() {
        std::string input;
        std::getline(std::cin, input);
        try {
            return std::stoi(input);
        }
        catch (...) {
            return -1;
        }
    }

    // Accepts "7:45pm" / "9:35" style input for simplicity in the menu.
    Time readTime(const std::string& prompt) {
        std::string s = readLine(prompt);
        bool pm = false;
        if (s.size() >= 2 && (s.substr(s.size() - 2) == "pm" || s.substr(s.size() - 2) == "PM")) {
            pm = true;
            s = s.substr(0, s.size() - 2);
        }
        else if (s.size() >= 2 && (s.substr(s.size() - 2) == "am" || s.substr(s.size() - 2) == "AM")) {
            s = s.substr(0, s.size() - 2);
        }
        int hours = 0, minutes = 0;
        size_t colon = s.find(':');
        if (colon != std::string::npos) {
            hours = std::atoi(s.substr(0, colon).c_str());
            minutes = std::atoi(s.substr(colon + 1).c_str());
        }
        else {
            hours = std::atoi(s.c_str());
        }
        if (pm && hours != 12) hours += 12;
        return Time(hours, minutes);
    }
}

void MainUI::printMenu() const {
    std::cout << "\n=== Driverless Public Transportation Route-Planner ===\n"
        << " 1) Load shuttle.txt/passenger.txt from folder\n"
        << " 2) Use Arrival-Time matching strategy\n"
        << " 3) Use Min-Dispatch matching strategy\n"
        << " 4) Recompute schedule (executeMatching)\n"
        << " 5) Display current schedule\n"
        << " 6) Save schedule to file\n"
        << " 7) Save shuttle & passenger data to new files\n"
        << " 8) Add / edit / delete shuttle or passenger\n"
        << " 0) Exit\n"
        << "Choice: ";
}

void MainUI::renderLoop() {
    std::cout << "Welcome to the Driverless Public Transportation Route-Planner.\n";
    bool running = true;

    while (running) {
        printMenu();
        int choice = readMenuChoice();

        switch (choice) {
        case 1: {
            std::string path = readLine("Enter folder path containing shuttle.txt and passenger.txt: ");
            planner.run(path);
            break;
        }
        case 2: {
            planner.useArrivalTimeStrategy();
            planner.executeMatching();
            std::cout << "Switched to Arrival-Time strategy and recomputed.\n";
            break;
        }
        case 3: {
            planner.useMinDispatchStrategy();
            planner.executeMatching();
            std::cout << "Switched to Min-Dispatch strategy and recomputed.\n";
            break;
        }
        case 4: {
            planner.executeMatching();
            std::cout << "Schedule recomputed.\n";
            break;
        }
        case 5: {
            planner.displayStuff();
            break;
        }
        case 6: {
            std::string path = readLine("Output path for schedule (e.g. schedule_output.txt): ");
            planner.saveSchedule(path);
            std::cout << "Schedule saved to " << path << "\n";
            break;
        }
        case 7: {
            std::string shuttlePath = readLine("Output path for shuttle data (e.g. shuttles_new.txt): ");
            std::string passengerPath = readLine("Output path for passenger data (e.g. passengers_new.txt): ");
            planner.saveShuttleAndPassengerData(shuttlePath, passengerPath);
            std::cout << "Shuttle data saved to " << shuttlePath << ", passenger data saved to " << passengerPath << "\n";
            break;
        }
        case 8: {
            handleAddEditDelete();
            break;
        }
        case 0: {
            running = false;
            std::cout << "Exiting Route-Planner. Goodbye!\n";
            break;
        }
        default: {
            std::cout << "Invalid choice. Please enter a number from the menu.\n";
            break;
        }
        }
    }
}

void MainUI::listShuttles() {
    ShuttleManager& mgr = planner.getShuttleManager();
    std::cout << "Shuttles:\n";
    for (int i = 0; i < mgr.getSize(); ++i) {
        Shuttle s = mgr.getCopy(i);
        std::cout << " [" << i << "] " << s.getLabel() << " @ " << s.getChargingPoint()->getName()
            << " capacity=" << s.getCapacity() << " type=" << s.getModelType() << "\n";
    }
}

void MainUI::listPassengers() {
    PassengerManager& mgr = planner.getPassengerManager();
    std::cout << "Passengers:\n";
    for (int i = 0; i < mgr.getSize(); ++i) {
        Passenger p = mgr.getCopy(i);
        std::cout << " [" << i << "] " << p.getQNumber() << " -> " << p.getDestination()->getName()
            << " group=" << p.getGroupSize() << "\n";
    }
}

void MainUI::handleAddEditDelete() {
    std::cout << "\n-- Add/Edit/Delete --\n"
        << " a) Add shuttle\n"
        << " b) Edit shuttle\n"
        << " c) Delete shuttle\n"
        << " d) Add passenger\n"
        << " e) Edit passenger\n"
        << " f) Delete passenger\n"
        << "Choice: ";

    std::string sub;
    std::getline(std::cin, sub);

    if (sub == "a" || sub == "b") {
        if (sub == "b") listShuttles();
        std::string label = readLine("Shuttle label (e.g. S99): ");
        std::string point = readLine("Charging point (e.g. Mall): ");
        Time time = readTime("Arrival time (e.g. 9:00pm): ");
        std::string type = readLine("Type (Small/Family/Premium): ");

        auto loc = planner.getLocationManager().addLocation(point);

        std::unique_ptr<Shuttle> shuttlePtr;
        try {
            shuttlePtr = std::make_unique<Shuttle>(ShuttleFactory::createShuttle(type, label, loc, time));
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Could not create shuttle: " << e.what() << "\n";
            return;
        }
        Shuttle& shuttle = *shuttlePtr;

        if (sub == "a") {
            planner.getShuttleManager().addShuttle(shuttle);
            std::cout << "Shuttle " << label << " added.\n";
        }
        else {
            int index = std::atoi(readLine("Index to edit: ").c_str());
            try {
                planner.getShuttleManager().editShuttle(index, shuttle);
                std::cout << "Shuttle updated.\n";
            }
            catch (const std::out_of_range&) {
                std::cout << "Invalid index.\n";
            }
        }
    }
    else if (sub == "c") {
        listShuttles();
        int index = std::atoi(readLine("Index to delete: ").c_str());
        try {
            planner.getShuttleManager().deleteShuttle(index);
            std::cout << "Shuttle deleted.\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Invalid index.\n";
        }
    }
    else if (sub == "d" || sub == "e") {
        if (sub == "e") listPassengers();
        std::string qNum = readLine("Passenger Q-number (e.g. P99): ");
        std::string dest = readLine("Destination (e.g. Bank): ");
        Time time = readTime("Arrival time (e.g. 9:00am): ");
        std::string sizeStr = readLine("Group size (default 1): ");
        int size = sizeStr.empty() ? 1 : std::atoi(sizeStr.c_str());
        if (size <= 0) size = 1;

        auto loc = planner.getLocationManager().addLocation(dest);
        Passenger passenger(qNum, loc, time, size);

        if (sub == "d") {
            planner.getPassengerManager().addPassenger(passenger);
            std::cout << "Passenger " << qNum << " added.\n";
        }
        else {
            int index = std::atoi(readLine("Index to edit: ").c_str());
            try {
                planner.getPassengerManager().editPassenger(index, passenger);
                std::cout << "Passenger updated.\n";
            }
            catch (const std::out_of_range&) {
                std::cout << "Invalid index.\n";
            }
        }
    }
    else if (sub == "f") {
        listPassengers();
        int index = std::atoi(readLine("Index to delete: ").c_str());
        try {
            planner.getPassengerManager().deletePassenger(index);
            std::cout << "Passenger deleted.\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Invalid index.\n";
        }
    }
    else {
        std::cout << "Unrecognised option.\n";
    }
}
