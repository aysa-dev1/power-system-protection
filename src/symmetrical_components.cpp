#include "psp/symmetrical_components.h"
#include <complex>
#include <cmath>
#include <limits>

namespace psp {
    // definition of the operator a
    static const std::complex<double> alpha_operator(-0.5, std::sqrt(3.0) / 2.0);
    static const std::complex<double> alpha_sq = alpha_operator * alpha_operator;
    static const std::complex<double> one_third(1.0 / 3.0, 0.0);

    SequenceComponents fortescue_transform(
        std::complex<double> L1,
        std::complex<double> L2,
        std::complex<double> L3
     ){
        SequenceComponents sequence_components;

        sequence_components.zero_sequence = one_third * (L1 + L2 + L3);

        sequence_components.positive_sequence = one_third * (L1 + alpha_operator * L2 + alpha_sq * L3);

        sequence_components.negative_sequence = one_third * (L1 + alpha_sq * L2 + alpha_operator * L3);

        return sequence_components;

    }

    PhaseComponents inverse_fortescue_transform(const SequenceComponents& seq){
        PhaseComponents phase_components;
        phase_components.L1 = seq.zero_sequence + seq.positive_sequence + seq.negative_sequence;
        phase_components.L2 = seq.zero_sequence + (alpha_sq * seq.positive_sequence) + (alpha_operator * seq.negative_sequence);
        phase_components.L3 = seq.zero_sequence + (alpha_operator * seq.positive_sequence) + (alpha_sq * seq.negative_sequence);

        return phase_components;
    }

    UnbalanceFactors compute_unbalance_factors(const SequenceComponents& seq) 
    {
        UnbalanceFactors unbalance_factors;
        
        double pos_magnitude = std::abs(seq.positive_sequence);

        unbalance_factors.negative_sequence_factor = (pos_magnitude > 1e-10)
        ? (std::abs(seq.negative_sequence) / pos_magnitude ) 
        : std::numeric_limits<double>::quiet_NaN();

        unbalance_factors.zero_sequence_factor = (pos_magnitude > 1e-10) 
        ? (std::abs(seq.zero_sequence) / pos_magnitude) 
        : std::numeric_limits<double>::quiet_NaN();
        
        return unbalance_factors;
    }

} // namespace psp