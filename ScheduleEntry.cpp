#include "ScheduleEntry.h"

ScheduleEntry::ScheduleEntry(const Passenger& p, const Shuttle& s, bool matched)
    : passengerItem(p), shuttleItem(s), matchStatus(matched) {
}

bool ScheduleEntry::isMatched() const {
    return matchStatus;
}

const Passenger& ScheduleEntry::getPassenger() const {
    return passengerItem;
}

const Shuttle& ScheduleEntry::getShuttle() const {
    return shuttleItem;
}
