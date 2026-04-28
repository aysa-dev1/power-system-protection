#pragma once

namespace psp{
    
    struct RelaySettings
    {
        double I_pickup;
        double I_instantaneous;
        double time_delay;
    };

    enum class TripDecision {
        NO_TRIP,
        TRIP_DELAYED,
        TRIP_INSTANTANEOUS
    };

    struct RelayResult {
        TripDecision decision;
        double trip_time;
    };
    
    RelayResult evaluate_overcurrent(const RelaySettings& settings, double I_measured);

} // namespace psp