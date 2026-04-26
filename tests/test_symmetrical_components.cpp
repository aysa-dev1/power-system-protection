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

TEST(SymmetricalComponents, BalancedSystem){
    
    std::complex<double> L1(1.0, 0.0);
    auto L2 = std::polar(1.0, -2.0 * M_PI / 3.0);
    auto L3 = std::polar(1.0, 2.0 * M_PI / 3.0);

    psp::SequenceComponents res = psp::fortescue_transform(L1, L2, L3);

    EXPECT_NEAR(std::abs(res.positive_sequence), 1.0, 1e-9);
    EXPECT_NEAR(std::abs(res.negative_sequence), 0.0, 1e-9);
    EXPECT_NEAR(std::abs(res.zero_sequence), 0.0, 1e-9);

    EXPECT_NEAR(std::arg(res.positive_sequence), 0.0, 1e-9);
}

TEST(SymmetricalComponents, ZeroSequenceFailure){
    std::complex<double> L1(1.0, 0.0);
    std::complex<double> L2(1.0, 0.0);
    std::complex<double> L3(1.0, 0.0);

    psp::SequenceComponents res = psp::fortescue_transform(L1, L2, L3);

    EXPECT_NEAR(res.zero_sequence.real(), L1.real(), TOLERANCE);
    EXPECT_NEAR(res.zero_sequence.imag(), L1.imag(), TOLERANCE);
    EXPECT_NEAR(std::abs(res.positive_sequence), 0.0, TOLERANCE);
    EXPECT_NEAR(std::abs(res.negative_sequence), 0.0, TOLERANCE);
}

TEST(SymmetricalComponents, RoundtripConsistency){
    std::complex<double> L1(1.2, 0.1);
    std::complex<double> L2(-0.5, -0.8);
    std::complex<double> L3(-0.4, 0.7);

    psp::SequenceComponents seq = psp::fortescue_transform(L1, L2, L3);
    psp::PhaseComponents phase = psp::inverse_fortescue_transform(seq);

    EXPECT_NEAR(phase.L1.real(), L1.real(), TOLERANCE);
    EXPECT_NEAR(phase.L1.imag(), L1.imag(), TOLERANCE);
    EXPECT_NEAR(phase.L2.real(), L2.real(), TOLERANCE);
    EXPECT_NEAR(phase.L2.imag(), L2.imag(), TOLERANCE);
    EXPECT_NEAR(phase.L3.real(), L3.real(), TOLERANCE);
    EXPECT_NEAR(phase.L3.imag(), L3.imag(), TOLERANCE);
}

TEST(SymmetricalComponents, UnbalanceFactorBalanced) {
    std::complex<double> L1(1.0, 0.0);
    auto L2 = std::polar(1.0, -2.0 * M_PI / 3.0);
    auto L3 = std::polar(1.0, 2.0 * M_PI / 3.0);

    psp::SequenceComponents seq = psp::fortescue_transform(L1, L2, L3);
    psp::UnbalanceFactors factors = psp::compute_unbalance_factors(seq);

    EXPECT_NEAR(factors.negative_sequence_factor, 0.0, TOLERANCE);
    EXPECT_NEAR(factors.zero_sequence_factor, 0.0, TOLERANCE);
}

TEST(SymmetricalComponents, UnbalanceFactorDivisionByZero){
    psp::SequenceComponents seq;
    seq.positive_sequence = {0.0, 0.0};
    seq.negative_sequence = {0.1, 0.0};
    seq.zero_sequence = {0.1, 0.0};

    psp::UnbalanceFactors factors = psp::compute_unbalance_factors(seq);

    EXPECT_TRUE(std::isnan(factors.negative_sequence_factor));
    EXPECT_TRUE(std::isnan(factors.zero_sequence_factor));

}