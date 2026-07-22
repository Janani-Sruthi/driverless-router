#include "Time.h"

Time::Time(int hours, int minutes) : hours(hours), minutes(minutes) {}

int Time::getHours() const {
    return hours;
}

int Time::getMinutes() const {
    return minutes;
}

bool Time::isWithinOperatingHours() const {
    int total = hours * 60 + minutes;
    return total >= 6 * 60 && total <= 23 * 60 + 59;
}

int Time::minutesEarly(const Time& requiredTime) const {
    int thisTotal = hours * 60 + minutes;
    int requiredTotal = requiredTime.getHours() * 60 + requiredTime.getMinutes();
    // +1440 before the modulo keeps the result positive regardless of
    // which side of midnight either time falls on.
    return ((requiredTotal - thisTotal) % 1440 + 1440) % 1440;
}
