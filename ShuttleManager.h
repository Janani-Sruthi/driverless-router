#ifndef SHUTTLE_MANAGER_H
#define SHUTTLE_MANAGER_H

#include <vector>
#include "Shuttle.h"

// Owns the in-RAM collection of Shuttle objects and CRUD operations on
// them, indexed by position (no more label-based lookup - callers that
// need a label match should scan getCopy() results themselves).
class ShuttleManager {
private:
    std::vector<Shuttle> shuttles;

public:
    void addShuttle(const Shuttle& s);
    void editShuttle(int index, const Shuttle& s);
    void deleteShuttle(int index);

    Shuttle getCopy(int index) const;
    int getSize() const;
};

#endif
