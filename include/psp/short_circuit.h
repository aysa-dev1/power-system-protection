#pragma once

#include "psp/network_model.h"

#include <complex>

namespace psp {
    
    struct ShortCircuitResult
    {
        std::complex<double> I_fault;
        double I_magnitude;
    };

    ShortCircuitResult calculate_fault_3phase(const SequenceImpedances& Z, double V_source);
    ShortCircuitResult calculate_fault_1phase_ground(const SequenceImpedances& Z, double V_source);
    ShortCircuitResult calculate_fault_2phase(const SequenceImpedances& Z, double V_source);
    ShortCircuitResult calculate_fault_2phase_ground(const SequenceImpedances& Z, double V_source);
    
} // namespace psp