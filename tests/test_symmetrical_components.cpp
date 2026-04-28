#include <gtest/gtest.h>
#include "psp/symmetrical_components.h"
#include <complex>
#include <cmath>

namespace {
    const double TOLERANCE = 1e-9;
}

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// testcase: SymmetricalComponents_001_BalancedSystem
TEST(SymmetricalComponents, SymmetricalComponents_001_BalancedSystem){
    
    // Arrange
    std::complex<double> L1(1.0, 0.0);
    auto L2 = std::polar(1.0, -2.0 * M_PI / 3.0);
    auto L3 = std::polar(1.0, 2.0 * M_PI / 3.0);

    // Act
    psp::SequenceComponents res = psp::fortescue_transform(L1, L2, L3);

    // Expect
    EXPECT_NEAR(std::abs(res.positive_sequence), 1.0, 1e-9);
    EXPECT_NEAR(std::abs(res.negative_sequence), 0.0, 1e-9);
    EXPECT_NEAR(std::abs(res.zero_sequence), 0.0, 1e-9);

    EXPECT_NEAR(std::arg(res.positive_sequence), 0.0, 1e-9);
}

// testcase: SymmetricalComponents_002_ZeroSequenceFailure
TEST(SymmetricalComponents, SymmetricalComponents_002_ZeroSequenceFailure){
    
    // Arrange
    std::complex<double> L1(1.0, 0.0);
    std::complex<double> L2(1.0, 0.0);
    std::complex<double> L3(1.0, 0.0);

    // Act
    psp::SequenceComponents res = psp::fortescue_transform(L1, L2, L3);

    // Expect
    EXPECT_NEAR(res.zero_sequence.real(), L1.real(), TOLERANCE);
    EXPECT_NEAR(res.zero_sequence.imag(), L1.imag(), TOLERANCE);
    EXPECT_NEAR(std::abs(res.positive_sequence), 0.0, TOLERANCE);
    EXPECT_NEAR(std::abs(res.negative_sequence), 0.0, TOLERANCE);
}

// testcase: SymmetricalComponents_003_RoundtripConsistency
TEST(SymmetricalComponents, SymmetricalComponents_003_RoundtripConsistency){

    // Arrange
    std::complex<double> L1(1.2, 0.1);
    std::complex<double> L2(-0.5, -0.8);
    std::complex<double> L3(-0.4, 0.7);

    // Act
    psp::SequenceComponents seq = psp::fortescue_transform(L1, L2, L3);
    psp::PhaseComponents phase = psp::inverse_fortescue_transform(seq);

    // Expect
    EXPECT_NEAR(phase.L1.real(), L1.real(), TOLERANCE);
    EXPECT_NEAR(phase.L1.imag(), L1.imag(), TOLERANCE);
    EXPECT_NEAR(phase.L2.real(), L2.real(), TOLERANCE);
    EXPECT_NEAR(phase.L2.imag(), L2.imag(), TOLERANCE);
    EXPECT_NEAR(phase.L3.real(), L3.real(), TOLERANCE);
    EXPECT_NEAR(phase.L3.imag(), L3.imag(), TOLERANCE);
}


// testcase: SymmetricalComponents_004_UnbalanceFactorBalanced
TEST(SymmetricalComponents, SymmetricalComponents_004_UnbalanceFactorBalanced) {

    // Arrange
    std::complex<double> L1(1.0, 0.0);
    auto L2 = std::polar(1.0, -2.0 * M_PI / 3.0);
    auto L3 = std::polar(1.0, 2.0 * M_PI / 3.0);

    // Act
    psp::SequenceComponents seq = psp::fortescue_transform(L1, L2, L3);
    psp::UnbalanceFactors factors = psp::compute_unbalance_factors(seq);

    // Expect
    EXPECT_NEAR(factors.negative_sequence_factor, 0.0, TOLERANCE);
    EXPECT_NEAR(factors.zero_sequence_factor, 0.0, TOLERANCE);
}

// testcase: SymmetricalComponents_005_UnbalanceFactorDivisionByZero
TEST(SymmetricalComponents, SymmetricalComponents_005_UnbalanceFactorDivisionByZero){
    
    // Arrange
    psp::SequenceComponents seq;
    seq.positive_sequence = {0.0, 0.0};
    seq.negative_sequence = {0.1, 0.0};
    seq.zero_sequence = {0.1, 0.0};

    // Act
    psp::UnbalanceFactors factors = psp::compute_unbalance_factors(seq);

    // Expect
    EXPECT_TRUE(std::isnan(factors.negative_sequence_factor));
    EXPECT_TRUE(std::isnan(factors.zero_sequence_factor));

}