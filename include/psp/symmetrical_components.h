#pragma once

#include <complex>

namespace psp{

    struct SequenceComponents
    {
        std::complex<double> zero_sequence;
        std::complex<double> positive_sequence;
        std::complex<double> negative_sequence;
    };

    struct PhaseComponents
    {
        std::complex<double> L1;
        std::complex<double> L2;
        std::complex<double> L3;
    };

    struct UnbalanceFactors
    {
        double negative_sequence_factor;
        double zero_sequence_factor;
    };
    

    SequenceComponents fortescue_transform(
        std::complex<double> L1,
        std::complex<double> L2,
        std::complex<double> L3
    );

    PhaseComponents inverse_fortescue_transform(const SequenceComponents& seq);

    UnbalanceFactors compute_unbalance_factors(const SequenceComponents& seq);

} // namespace psp