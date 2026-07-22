#include "MinDispatchStrategy.h"
#include <unordered_map>

// Req 6: among eligible shuttles at the same charging point, prefer the
// one with the HIGHER seating capacity, so a single big shuttle absorbs
// as many passenger groups as possible before a second shuttle is ever
// needed - minimising the total number dispatched.
std::vector<ScheduleEntry> MinDispatchStrategy::computeSchedule(
    const std::vector<Shuttle>& shuttles,
    const std::vector<Passenger>& passengers) {

    std::vector<ScheduleEntry> results;
    std::unordered_map<std::string, int> seatsUsed;

    for (const auto& p : passengers) {
        int bestIndex = -1;
        int bestCapacity = -1;

        for (size_t i = 0; i < shuttles.size(); ++i) {
            const Shuttle& s = shuttles[i];
            if (!s.canServe(*p.getDestination(), p.getArrivalTime())) continue;

            int used = seatsUsed[s.getLabel()];
            if (used + p.getGroupSize() > s.getCapacity()) continue;

            if (s.getCapacity() > bestCapacity) {
                bestCapacity = s.getCapacity();
                bestIndex = static_cast<int>(i);
            }
        }

        if (bestIndex != -1) {
            const Shuttle& chosen = shuttles[bestIndex];
            seatsUsed[chosen.getLabel()] += p.getGroupSize();
            results.emplace_back(p, chosen, true);
        }
    }

    return results;
}
