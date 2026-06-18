#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "Shuttle.h"
#include "Passenger.h"
#include "Schedule.h"
#include "LocationManager.h"

// Handles all file I/O: parsing shuttle.txt / passenger.txt into objects
// and writing a computed Schedule back out to disk. Knows nothing about
// matching logic or in-RAM storage beyond what it's asked to load/save —
// files are used only for archiving, never as the program's working memory.
class FileHandler {
private:
    std::string dataFolderPath;

public:
    FileHandler();

    void setDataFolderPath(const std::string& path);
    std::string getDataFolderPath() const;

    // Parses "shuttle.txt" from dataFolderPath. Any destination not already
    // known to locationMgr is registered there so it can still be matched.
    std::vector<Shuttle> loadShuttles(LocationManager& locationMgr) const;

    // Parses "passenger.txt" from dataFolderPath, same validation approach.
    std::vector<Passenger> loadPassengers(LocationManager& locationMgr) const;

    // Writes the schedule (plus any unmatched shuttles/passengers) to outputPath.
    bool saveSchedule(const std::string& outputPath, const Schedule& schedule,
        const std::vector<Shuttle>& allShuttles,
        const std::vector<Passenger>& allPassengers) const;

private:
    static std::vector<std::string> splitLine(const std::string& line, char delimiter);
};

#endif 