#include "ArrivalTimeStrategy.h"
#include <unordered_map>

// Req 7: among shuttles that can serve a passenger (same destination,
// arriving 0-10 minutes early, never late - see Shuttle::canServe), pick
// the one whose actual arrival is EARLIEST, not the one closest to the
// passenger's requested time. A shuttle arriving right on time loses out
// to one arriving a few minutes earlier, as long as both qualify.
std::vector<ScheduleEntry> ArrivalTimeStrategy::computeSchedule(
    const std::vector<Shuttle>& shuttles,
    const std::vector<Passenger>& passengers) {

    std::vector<ScheduleEntry> results;
    // Seats used per shuttle label - tracked locally since Shuttle no
    // longer carries its own occupancy state.
    std::unordered_map<std::string, int> seatsUsed;

    for (const auto& p : passengers) {
        int bestIndex = -1;
        int bestLead = -1; // higher lead = arrives earlier -> prefer it

        for (size_t i = 0; i < shuttles.size(); ++i) {
            const Shuttle& s = shuttles[i];
            if (!s.canServe(*p.getDestination(), p.getArrivalTime())) continue;

            int used = seatsUsed[s.getLabel()];
            if (used + p.getGroupSize() > s.getCapacity()) continue;

            int lead = s.getArrivalTime().minutesEarly(p.getArrivalTime());
            if (lead > bestLead) {
                bestLead = lead;
                bestIndex = static_cast<int>(i);
            }
        }

        if (bestIndex != -1) {
            const Shuttle& chosen = shuttles[bestIndex];
            seatsUsed[chosen.getLabel()] += p.getGroupSize();
            results.emplace_back(p, chosen, true);
        }
        // Passengers with no eligible shuttle simply produce no entry -
        // ScheduleEntry has no way to represent "matched to nothing".
    }

    return results;
}
