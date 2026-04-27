#include "psp/network_model.h"

#include <complex>

namespace psp {

    SequenceImpedances compute_sequence_impedances(const NetworkParameters& network){
        
        SequenceImpedances seq_impedances;

        seq_impedances.Z1 = network.Z1_source + network.Z1_trafo + network.Z1_line;
        seq_impedances.Z2 = network.Z2_source + network.Z2_trafo + network.Z2_line;
        seq_impedances.Z0 = network.Z0_source + network.Z0_trafo + network.Z0_line;

        return seq_impedances;
    }

} // namespace psp