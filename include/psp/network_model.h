#pragma once

#include <complex>

namespace psp {
    struct NetworkParameters
    {
        //positive sequence
        std::complex<double> Z1_source;
        std::complex<double> Z1_trafo;
        std::complex<double> Z1_line;

        //negative sequence
        std::complex<double> Z2_source;
        std::complex<double> Z2_trafo;
        std::complex<double> Z2_line;

        // zero sequence
        std::complex<double> Z0_source;
        std::complex<double> Z0_trafo;
        std::complex<double> Z0_line;
    };

    struct SequenceImpedances
    {
        std::complex<double> Z1;
        std::complex<double> Z2;
        std::complex<double> Z0;
    };
    
    SequenceImpedances compute_sequence_impedances(const NetworkParameters& network);

} // namespace psp