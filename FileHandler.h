#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"
#include "ScheduleEntry.h"

// Handles all file I/O: parsing shuttle.txt / passenger.txt into value
// objects and writing a computed schedule back out to disk. Per the UML,
// FileHandler builds its own Location objects while parsing rather than
// going through LocationManager - so locations loaded from file are
// separate shared_ptr instances from anything added later via the UI,
// even if the names match.
class FileHandler {
private:
    std::string dataFolderPath;

    static std::vector<std::string> splitLine(const std::string& line, char delimiter);
    static Time parseTime(const std::string& text);
    static std::string formatTime(const Time& t);

public:
    void setDataFolderPath(const std::string& path);
    const std::string& getDataFolderPath() const;

    // Parses a CSV-style shuttle file: label,location,time[,type]
    std::vector<Shuttle> loadShuttles(const std::string& path) const;

    // Parses a CSV-style passenger file: qNum,location,time[,groupSize]
    std::vector<Passenger> loadPassengers(const std::string& path) const;

    void saveSchedule(const std::string& path, const std::vector<ScheduleEntry>& schedules) const;
    void saveShuttles(const std::string& path, const std::vector<Shuttle>& shuttles) const;
    void savePassengers(const std::string& path, const std::vector<Passenger>& passengers) const;
};

#endif
