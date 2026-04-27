#include <gtest/gtest.h>
#include "psp/network_model.h"

namespace {
    const double TOLERANCE = 1e-9; 
}

TEST(NetworkModelTest, ComputeSequenceImpedances){
    psp::NetworkParameters network;

    // positive sequence
    network.Z1_source = {0.1, 0.5};
    network.Z1_trafo = {0.05, 0.2};
    network.Z1_line = {0.2, 0.3};

    // negative sequence
    network.Z2_source = {0.08, 0.4};
    network.Z2_trafo = network.Z1_trafo;
    network.Z2_line = network.Z1_line;

    // zero sequence
    network.Z0_source = {0.02, 0.1};
    network.Z0_trafo = {0.1, 0.4};
    network.Z0_line = {0.6, 0.9};

    psp::SequenceImpedances results = psp::compute_sequence_impedances(network);

    EXPECT_NEAR(results.Z1.real(), 0.35, TOLERANCE);
    EXPECT_NEAR(results.Z1.imag(), 1.0, TOLERANCE);

    EXPECT_NEAR(results.Z2.real(), 0.33, TOLERANCE);
    EXPECT_NEAR(results.Z2.imag(), 0.9, TOLERANCE);

    EXPECT_NEAR(results.Z0.real(), 0.72, TOLERANCE);
    EXPECT_NEAR(results.Z0.imag(), 1.4, TOLERANCE);

}