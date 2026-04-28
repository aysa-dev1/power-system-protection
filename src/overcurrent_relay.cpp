#include "psp/overcurrent_relay.h"
#include <limits>


namespace psp{
    RelayResult evaluate_overcurrent(const RelaySettings& settings, double I_measured){

        if(I_measured >= settings.I_instantaneous)
            return {TripDecision::TRIP_INSTANTANEOUS, 0.0};
            
        if (I_measured >= settings.I_pickup)
            return {TripDecision::TRIP_DELAYED, settings.time_delay};
        
        return {TripDecision::NO_TRIP, std::numeric_limits<double>::infinity()};
    
    }
} // namespace psp
