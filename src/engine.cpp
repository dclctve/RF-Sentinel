#include "sentinel.hpp"

namespace sentinel {

std::vector<Finding> Engine::inspect(
    const MovementEvent& event
) const {
    std::vector<Finding> findings;

    // Legitimate teleport/respawn transitions need
    // separate validation by trusted server logic.
    if (event.authorized_transition) {
        return findings;
    }

    if (event.distance < 0.0 ||
        event.elapsed_seconds <= 0.0) {
        findings.push_back({
            "MOV-000",
            "high",
            "Invalid movement measurement"
        });
        return findings;
    }

    // Prototype threshold only. NOT a validated
    // RF Online movement limit.
    constexpr double max_units_per_second = 18.0;

    const double speed =
        event.distance / event.elapsed_seconds;

    if (speed > max_units_per_second) {
        findings.push_back({
            "MOV-001",
            "medium",
            "Movement exceeds prototype threshold"
        });
    }

    return findings;
}

}
