#include "sentinel.hpp"

#include <cassert>
#include <iostream>

int main() {
    sentinel::Engine engine;

    // Normal movement: 10 units/sec.
    auto normal = engine.inspect({10.0, 1.0, false});
    assert(normal.empty());

    // Suspicious movement: 30 units/sec.
    auto suspicious = engine.inspect({30.0, 1.0, false});
    assert(suspicious.size() == 1);
    assert(suspicious[0].rule_id == "MOV-001");

    // Authorized transition is exempt from this
    // prototype speed check.
    auto teleport = engine.inspect({1000.0, 0.1, true});
    assert(teleport.empty());

    // Invalid elapsed time.
    auto invalid = engine.inspect({10.0, 0.0, false});
    assert(invalid.size() == 1);
    assert(invalid[0].rule_id == "MOV-000");

    std::cout << "All Sentinel core tests passed.\n";
    return 0;
}
