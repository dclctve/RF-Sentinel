#pragma once

#include <string>
#include <vector>

namespace sentinel {

struct MovementEvent {
    double distance;
    double elapsed_seconds;
    bool authorized_transition;
};

struct Finding {
    std::string rule_id;
    std::string severity;
    std::string message;
};

class Engine {
public:
    std::vector<Finding> inspect(
        const MovementEvent& event
    ) const;
};

}
