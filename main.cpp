#include <iostream>
#include <limits>
#include "RoutePlanner.h"
#include "ConsolePresenter.h"

// Reads a full line of input safely, clearing any leftover input state
// from a previous std::cin >> read.
static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

static int readMenuChoice() {
    std::string input;
    std::getline(std::cin, input);
    try {
        return std::stoi(input);
    }
    catch (...) {
        return -1; // invalid input sentinel; menu loop will report it
    }
}

int main() {
    RoutePlanner planner;
    ConsolePresenter presenter;

    presenter.printMessage("Welcome to the Driverless Public Transportation Route-Planner.");

    bool running = true;
    while (running) {
        presenter.printMenu();
        int choice = readMenuChoice();

        switch (choice) {
        case 1: {
            std::string path = readLine("Enter folder path containing shuttle.txt and passenger.txt: ");
            planner.setDataFolderPath(path);
            presenter.printMessage("Data folder path set to: " + path);
            break;
        }
        case 2: {
            bool ok = planner.loadData();
            if (ok) {
                presenter.printMessage("Files loaded into RAM.");
                presenter.printMessage("Shuttles loaded: " + std::to_string(planner.getShuttleManager().getAll().size()));
                presenter.printMessage("Passengers loaded: " + std::to_string(planner.getPassengerManager().getAll().size()));
            }
            else {
                presenter.printError("Set the data folder path first (option 1).");
            }
            break;
        }
        case 3: {
            planner.computeSchedule();
            presenter.printMessage("Schedule computed.");
            break;
        }
        case 4: {
            presenter.displaySchedule(planner.getSchedule(),
                planner.getShuttleManager().getAll(),
                planner.getPassengerManager().getAll());
            break;
        }
        case 5: {
            std::string outPath = readLine("Enter output file path (e.g. schedule_output.txt): ");
            bool ok = planner.saveSchedule(outPath);
            if (ok) {
                presenter.printMessage("Schedule saved to " + outPath);
            }
            else {
                presenter.printError("Failed to save schedule. Check the path and try again.");
            }
            break;
        }
        case 6: {
            presenter.displayShuttleList(planner.getShuttleManager().getAll());
            break;
        }
        case 7: {
            presenter.displayPassengerList(planner.getPassengerManager().getAll());
            break;
        }
        case 8: {
            std::string label = readLine("Shuttle label (e.g. S99): ");
            std::string point = readLine("Charging point (e.g. Mall): ");
            std::string time = readLine("Arrival time (e.g. 9:00am): ");
            planner.getShuttleManager().addShuttle(label, Location(point), time);
            planner.getLocationManager().addLocation(point);
            presenter.printMessage("Shuttle " + label + " added.");
            break;
        }
        case 9: {
            std::string label = readLine("Shuttle label to edit: ");
            std::string newPoint = readLine("New charging point: ");
            std::string newTime = readLine("New arrival time: ");
            bool ok = planner.getShuttleManager().editShuttle(label, Location(newPoint), newTime);
            if (ok) {
                planner.getLocationManager().addLocation(newPoint);
                presenter.printMessage("Shuttle " + label + " updated.");
            }
            else {
                presenter.printError("Shuttle " + label + " not found.");
            }
            break;
        }
        case 10: {
            std::string label = readLine("Shuttle label to delete: ");
            bool ok = planner.getShuttleManager().deleteShuttle(label);
            if (ok) {
                presenter.printMessage("Shuttle " + label + " deleted.");
            }
            else {
                presenter.printError("Shuttle " + label + " not found.");
            }
            break;
        }
        case 11: {
            std::string qNum = readLine("Passenger Q-number (e.g. P99): ");
            std::string dest = readLine("Destination (e.g. Bank): ");
            std::string time = readLine("Arrival time (e.g. 9:00am): ");
            planner.getPassengerManager().addPassenger(qNum, Location(dest), time);
            planner.getLocationManager().addLocation(dest);
            presenter.printMessage("Passenger " + qNum + " added.");
            break;
        }
        case 12: {
            std::string qNum = readLine("Passenger Q-number to edit: ");
            std::string newDest = readLine("New destination: ");
            std::string newTime = readLine("New arrival time: ");
            bool ok = planner.getPassengerManager().editPassenger(qNum, Location(newDest), newTime);
            if (ok) {
                planner.getLocationManager().addLocation(newDest);
                presenter.printMessage("Passenger " + qNum + " updated.");
            }
            else {
                presenter.printError("Passenger " + qNum + " not found.");
            }
            break;
        }
        case 13: {
            std::string qNum = readLine("Passenger Q-number to delete: ");
            bool ok = planner.getPassengerManager().deletePassenger(qNum);
            if (ok) {
                presenter.printMessage("Passenger " + qNum + " deleted.");
            }
            else {
                presenter.printError("Passenger " + qNum + " not found.");
            }
            break;
        }
        case 0: {
            running = false;
            presenter.printMessage("Exiting Route-Planner. Goodbye!");
            break;
        }
        default: {
            presenter.printError("Invalid choice. Please enter a number from the menu.");
            break;
        }
        }
    }

    return 0;
}