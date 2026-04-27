#include "psp/short_circuit.h"

#include <cmath>

namespace psp{
    
    // help function to calculate magnitude of complex current
    static ShortCircuitResult make_result(std::complex<double> I_vector){
        return {I_vector, std::abs(I_vector)};
    }

    // 3 phase short circuit failure
    ShortCircuitResult calculate_fault_3phase(const SequenceImpedances& Z, double V_source){
        
        if (std::abs(Z.Z1) < 1e-12) return {{0,0}, 0};

        std::complex<double> I_f = V_source / Z.Z1;
        
        return make_result(I_f);
    }

    // 1 phase ground failure
    ShortCircuitResult calculate_fault_1phase_ground(const SequenceImpedances& Z, double V_source){
        std::complex<double> denominator = Z.Z1 + Z.Z2 + Z.Z0;
        
        // avoiding division by zero
        if (std::abs(denominator) < 1e-12) return {{0,0}, 0}; 

        std::complex<double> I_f = (3.0 * V_source) / denominator;
        return make_result(I_f);
    }

    // 2 phase short circuit failure
    ShortCircuitResult calculate_fault_2phase(const SequenceImpedances& Z, double V_source){
        std::complex<double> denominator = Z.Z1 + Z.Z2;

        // avoiding division by zero
        if (std::abs(denominator) < 1e-12) return {{0,0}, 0};

        static const double sqrt3 = std::sqrt(3.0);
        std::complex<double> j(0.0, 1.0);

        std::complex<double> I_f = (j * sqrt3 * V_source) / denominator;

        return make_result(I_f);
    }

    // 2 phase ground failure
    ShortCircuitResult calculate_fault_2phase_ground(const SequenceImpedances& Z, double V_source){
        std::complex<double> denominator = (Z.Z1 * Z.Z2) + (Z.Z1 * Z.Z0) + (Z.Z2 * Z.Z0);
        if (std::abs(denominator) < 1e-12) return {{0,0}, 0};

        std::complex<double> I_f = (3.0 * V_source * Z.Z2) / denominator;

        return make_result(I_f);
    }

} // namespace psp