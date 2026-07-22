#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileHandler::FileHandler() : dataFolderPath("") {}

void FileHandler::setDataFolderPath(const std::string& path) {
    dataFolderPath = path;
}

std::string FileHandler::getDataFolderPath() const {
    return dataFolderPath;
}

std::vector<std::string> FileHandler::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Shuttle> FileHandler::loadShuttles(LocationManager& locationMgr) const {
    std::vector<Shuttle> shuttles;
    std::string filePath = dataFolderPath + "/shuttle.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filePath << std::endl;
        return shuttles;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> fields = splitLine(line, ',');
        if (fields.size() != 3) {
            std::cerr << "Skipping malformed shuttle line: " << line << std::endl;
            continue;
        }

        std::string label = fields[0];
        std::string pointName = fields[1];
        std::string time = fields[2];

        locationMgr.addLocation(pointName); // registers it if not already known
        Location point(pointName);

        shuttles.push_back(Shuttle(label, point, time));
    }

    file.close();
    return shuttles;
}

std::vector<Passenger> FileHandler::loadPassengers(LocationManager& locationMgr) const {
    std::vector<Passenger> passengers;
    std::string filePath = dataFolderPath + "/passenger.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filePath << std::endl;
        return passengers;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> fields = splitLine(line, ',');
        if (fields.size() != 3) {
            std::cerr << "Skipping malformed passenger line: " << line << std::endl;
            continue;
        }

        std::string qNum = fields[0];
        std::string destName = fields[1];
        std::string time = fields[2];

        locationMgr.addLocation(destName);
        Location dest(destName);

        passengers.push_back(Passenger(qNum, dest, time));
    }

    file.close();
    return passengers;
}

bool FileHandler::saveSchedule(const std::string& outputPath, const Schedule& schedule,
    const std::vector<Shuttle>& allShuttles,
    const std::vector<Passenger>& allPassengers) const {
    std::ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        std::cerr << "Error: could not open " << outputPath << " for writing." << std::endl;
        return false;
    }

    outFile << "=== Schedule ===" << std::endl;
    outFile << "ShuttleLabel,ChargingPoint,ShuttleTime,PassengerQNum,Destination,PassengerTime" << std::endl;

    for (const auto& pair : schedule.getMatchedPairs()) {
        const std::string& shuttleLabel = pair.first;
        const std::string& passengerQNum = pair.second;

        // Look up full details for the report line.
        const Shuttle* matchedShuttle = nullptr;
        for (const auto& s : allShuttles) {
            if (s.getLabel() == shuttleLabel) {
                matchedShuttle = &s;
                break;
            }
        }
        const Passenger* matchedPassenger = nullptr;
        for (const auto& p : allPassengers) {
            if (p.getQNumber() == passengerQNum) {
                matchedPassenger = &p;
                break;
            }
        }

        if (matchedShuttle && matchedPassenger) {
            outFile << matchedShuttle->getLabel() << ","
                << matchedShuttle->getChargingPoint().getName() << ","
                << matchedShuttle->getArrivalTime() << ","
                << matchedPassenger->getQNumber() << ","
                << matchedPassenger->getDestination().getName() << ","
                << matchedPassenger->getArrivalTime() << std::endl;
        }
    }

    outFile << std::endl << "=== Unmatched Shuttles ===" << std::endl;
    for (const auto& label : schedule.getUnmatchedShuttles(allShuttles)) {
        outFile << label << std::endl;
    }

    outFile << std::endl << "=== Unmatched Passengers ===" << std::endl;
    for (const auto& qNum : schedule.getUnmatchedPassengers(allPassengers)) {
        outFile << qNum << std::endl;
    }

    outFile.close();
    return true;
}