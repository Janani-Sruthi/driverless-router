#include "FileHandler.h"
#include "ShuttleFactory.h"
#include "Location.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <iostream>

void FileHandler::setDataFolderPath(const std::string& path) {
    dataFolderPath = path;
}

const std::string& FileHandler::getDataFolderPath() const {
    return dataFolderPath;
}

std::vector<std::string> FileHandler::splitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        // Strip stray \r (CRLF files) and surrounding whitespace.
        while (!token.empty() && (token.back() == '\r' || token.back() == ' ')) {
            token.pop_back();
        }
        size_t start = token.find_first_not_of(' ');
        token = (start == std::string::npos) ? "" : token.substr(start);
        tokens.push_back(token);
    }
    return tokens;
}

// Parses times like "7:45pm" / "11:00am" into a 24-hour Time.
Time FileHandler::parseTime(const std::string& text) {
    std::string s = text;
    bool pm = false, am = false;
    if (s.size() >= 2) {
        std::string suffix = s.substr(s.size() - 2);
        std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
        if (suffix == "pm") { pm = true; s = s.substr(0, s.size() - 2); }
        else if (suffix == "am") { am = true; s = s.substr(0, s.size() - 2); }
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
    if (am && hours == 12) hours = 0;

    return Time(hours, minutes);
}

std::string FileHandler::formatTime(const Time& t) {
    int hours = t.getHours();
    std::string suffix = (hours >= 12) ? "pm" : "am";
    int displayHours = hours % 12;
    if (displayHours == 0) displayHours = 12;

    std::ostringstream oss;
    oss << displayHours << ":";
    if (t.getMinutes() < 10) oss << "0";
    oss << t.getMinutes() << suffix;
    return oss.str();
}

std::vector<Shuttle> FileHandler::loadShuttles(const std::string& path) const {
    std::vector<Shuttle> shuttles;
    std::ifstream file(path);
    if (!file.is_open()) {
        return shuttles;
    }

    // Local dedup so multiple shuttles at the same charging point within
    // THIS file share one Location instance.
    std::unordered_map<std::string, std::shared_ptr<Location>> knownLocations;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitLine(line, ',');
        if (fields.size() < 3) continue;

        const std::string& label = fields[0];
        const std::string& locName = fields[1];
        Time time = parseTime(fields[2]);
        std::string type = (fields.size() >= 4) ? fields[3] : "Family";

        auto it = knownLocations.find(locName);
        std::shared_ptr<Location> point;
        if (it != knownLocations.end()) {
            point = it->second;
        }
        else {
            point = std::make_shared<Location>(locName);
            knownLocations[locName] = point;
        }

        try {
            shuttles.push_back(ShuttleFactory::createShuttle(type, label, point, time));
        }
        catch (const std::invalid_argument& e) {
            // Req 3 violation (outside 6:00am-11:59pm) - skip this row
            // rather than aborting the whole file load.
            std::cerr << "Skipping shuttle " << label << ": " << e.what() << "\n";
        }
    }
    return shuttles;
}

std::vector<Passenger> FileHandler::loadPassengers(const std::string& path) const {
    std::vector<Passenger> passengers;
    std::ifstream file(path);
    if (!file.is_open()) {
        return passengers;
    }

    std::unordered_map<std::string, std::shared_ptr<Location>> knownLocations;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = splitLine(line, ',');
        if (fields.size() < 3) continue;

        const std::string& qNum = fields[0];
        const std::string& locName = fields[1];
        Time time = parseTime(fields[2]);
        int groupSize = (fields.size() >= 4) ? std::atoi(fields[3].c_str()) : 1;
        if (groupSize <= 0) groupSize = 1;

        auto it = knownLocations.find(locName);
        std::shared_ptr<Location> dest;
        if (it != knownLocations.end()) {
            dest = it->second;
        }
        else {
            dest = std::make_shared<Location>(locName);
            knownLocations[locName] = dest;
        }

        passengers.emplace_back(qNum, dest, time, groupSize);
    }
    return passengers;
}

void FileHandler::saveSchedule(const std::string& path, const std::vector<ScheduleEntry>& schedules) const {
    std::ofstream file(path);
    if (!file.is_open()) return;

    for (const auto& entry : schedules) {
        const Passenger& p = entry.getPassenger();
        const Shuttle& s = entry.getShuttle();
        file << p.getQNumber() << " -> Shuttle " << s.getLabel()
            << " (" << s.getChargingPoint()->getName() << ", " << formatTime(s.getArrivalTime()) << ")"
            << " group=" << p.getGroupSize()
            << " matched=" << (entry.isMatched() ? "yes" : "no") << "\n";
    }
}

// Req 10: writes shuttle data back out in the same CSV format it was
// loaded in, so the file can be re-loaded later. Always a NEW file -
// callers choose the path, this never touches the original.
void FileHandler::saveShuttles(const std::string& path, const std::vector<Shuttle>& shuttles) const {
    std::ofstream file(path);
    if (!file.is_open()) return;

    for (const auto& s : shuttles) {
        file << s.getLabel() << "," << s.getChargingPoint()->getName() << ","
            << formatTime(s.getArrivalTime()) << "," << s.getModelType() << "\n";
    }
}

void FileHandler::savePassengers(const std::string& path, const std::vector<Passenger>& passengers) const {
    std::ofstream file(path);
    if (!file.is_open()) return;

    for (const auto& p : passengers) {
        file << p.getQNumber() << "," << p.getDestination()->getName() << ","
            << formatTime(p.getArrivalTime()) << "," << p.getGroupSize() << "\n";
    }
}
