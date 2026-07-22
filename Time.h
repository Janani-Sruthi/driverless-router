#ifndef TIME_H
#define TIME_H

// Simple 24-hour clock value type. Parsing of human strings like "7:45pm"
// happens outside this class (in FileHandler) so Time itself stays mostly
// a pure data type - the two methods below encode the spec's business
// rules for operating hours and arrival-time matching, since they're pure
// time arithmetic and belong here rather than duplicated in every caller.
class Time {
private:
    int hours;
    int minutes;

public:
    Time(int hours = 0, int minutes = 0);

    int getHours() const;
    int getMinutes() const;

    // Shuttles operate 6:00am up to (and including) 11:59pm - Req 3.
    bool isWithinOperatingHours() const;

    // How many minutes earlier this time is than requiredTime, treating
    // the clock as rolling over at midnight (so 11:59pm is 6 minutes
    // "early" relative to a required time of 00:05am). Always returns a
    // value in [0, 1439]; the caller decides what range counts as
    // acceptable (Req 5: 0-10 minutes early, never late).
    int minutesEarly(const Time& requiredTime) const;
};

#endif
