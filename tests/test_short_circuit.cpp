#include <gtest/gtest.h>
#include "psp/short_circuit.h"

#include <complex>
#include <cmath>

class ShortCircuitTest : public ::testing::Test {
    protected:
        psp::SequenceImpedances Z;

        double V = 1000.0;

        const double TOLERANCE = 1e-6;

        void SetUp() override {
            Z.Z1 = {0.1, 0.5};
            Z.Z2 = {0.1, 0.5}; // symmetrical network for basic tests
            Z.Z0 = {0.3, 1.5};
        }
};

TEST_F(ShortCircuitTest, 3PhaseFault) {
    psp::ShortCircuitResult result = psp::calculate_fault_3phase(Z, V);

    double expected_mag = V / std::abs(Z.Z1);
    EXPECT_NEAR(result.I_magnitude, expected_mag, TOLERANCE);

}

TEST_F(ShortCircuitTest, 1PhaseToGroundFault){
    psp::ShortCircuitResult result = psp::calculate_fault_1phase_ground(Z, V);
    
    std::complex<double> z_sum = Z.Z1 + Z.Z2 + Z.Z0;
    double expected_mag = std::abs(3.0 * V / z_sum);

    EXPECT_NEAR(result.I_magnitude, expected_mag, TOLERANCE);
}

TEST_F(ShortCircuitTest, 2PhaseFault){
    psp::ShortCircuitResult result = psp::calculate_fault_2phase(Z, V);

    double expected_mag = std::sqrt(3.0) * std::abs(V / (Z.Z1 + Z.Z2));
    EXPECT_NEAR(result.I_magnitude, expected_mag, TOLERANCE);
}

TEST_F(ShortCircuitTest, 2PhaseToGroundFault){
    psp::ShortCircuitResult result = psp::calculate_fault_2phase_ground(Z, V);

    std::complex<double> denominator = (Z.Z1 * Z.Z2) + (Z.Z1 * Z.Z0) + (Z.Z2 * Z.Z0);
    double expected_mag = std::abs((3.0 * V * Z.Z2) / denominator);

    EXPECT_NEAR(result.I_magnitude, expected_mag, TOLERANCE);
}

TEST_F(ShortCircuitTest, DivisionByZeroReturnsZero){
    psp::SequenceImpedances Z_zero = {{0,0}, {0,0}, {0,0}};

    EXPECT_DOUBLE_EQ(psp::calculate_fault_3phase(Z_zero, V).I_magnitude, 0.0);

    EXPECT_DOUBLE_EQ(psp::calculate_fault_1phase_ground(Z_zero, V).I_magnitude, 0.0);

    EXPECT_DOUBLE_EQ(psp::calculate_fault_2phase(Z_zero, V).I_magnitude, 0.0);

    EXPECT_DOUBLE_EQ(psp::calculate_fault_2phase_ground(Z_zero, V).I_magnitude, 0.0);
}

TEST_F(ShortCircuitTest, MagnitudePlausibility){
    
    psp::ShortCircuitResult res3L = psp::calculate_fault_3phase(Z, V);

    psp::ShortCircuitResult res2L = psp::calculate_fault_2phase(Z, V);

    EXPECT_GT(res3L.I_magnitude, res2L.I_magnitude);
}