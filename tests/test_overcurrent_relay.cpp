#include <gtest/gtest.h>
#include <cmath>
#include <limits>

#include "psp/overcurrent_relay.h"

class OverCurrentRelayTest : public ::testing::Test {
    protected:
        psp::RelaySettings settings;

        void SetUp() override {
            settings.I_pickup = 100.0; // A
            settings.I_instantaneous = 500.0; // A
            settings.time_delay = 0.3; // s
        }
};


// testcase: OverCurrentRelayTest_001_NoTripUnderPickup

TEST_F(OverCurrentRelayTest, OverCurrentRelayTest_001_NoTripUnderPickup) {
    // Arrange
    double I_measured = 50.0;
    
    // Act
    psp::RelayResult res = psp::evaluate_overcurrent(settings, I_measured);

    // Expect
    EXPECT_EQ(res.decision, psp::TripDecision::NO_TRIP);
    EXPECT_TRUE(std::isinf(res.trip_time));

}


// testcase: OverCurrentRelayTest_002_DelayedTripInBetween
TEST_F(OverCurrentRelayTest, OverCurrentRelayTest_002_DelayedTripInBetween){
    // Arrange
    double I_measured = 220.0;

    // Act
    psp::RelayResult res = psp::evaluate_overcurrent(settings, I_measured);
    
    // Expect
    EXPECT_EQ(res.decision, psp::TripDecision::TRIP_DELAYED);
    EXPECT_NEAR(res.trip_time, settings.time_delay, 1e-9);
}


// testcase: OverCurrentRelayTest_003_TripInstantaneous
TEST_F(OverCurrentRelayTest, OverCurrentRelayTest_003_TripInstantaneous){
    // Arrange
    double I_measured = 600.0;

    // Act
    psp::RelayResult res = psp::evaluate_overcurrent(settings, I_measured);

    // Expect
    EXPECT_EQ(res.decision, psp::TripDecision::TRIP_INSTANTANEOUS);
    EXPECT_NEAR(res.trip_time, 0.0, 1e-9);
}

// testcase: OverCurrentRelayTest_004_BoundaryAtPickup
TEST_F(OverCurrentRelayTest, OverCurrentRelayTest_004_BoundaryAtPickup){
    // Arrange
    double I_measured = settings.I_pickup;

    // Act
    psp::RelayResult res = psp::evaluate_overcurrent(settings, I_measured);

    // Expect
    EXPECT_EQ(res.decision, psp::TripDecision::TRIP_DELAYED);
    EXPECT_NEAR(res.trip_time, settings.time_delay, 1e-9);
}


// testcase: OverCurrentRelayTest_005_BoundaryAtInstantaneous
TEST_F(OverCurrentRelayTest, OverCurrentRelayTest_005_BoundaryAtInstantaneous){
    // Arrange
    double I_measured = settings.I_instantaneous;

    // Act
    psp::RelayResult res = psp::evaluate_overcurrent(settings, I_measured);

    // Expect
    EXPECT_EQ(res.decision, psp::TripDecision::TRIP_INSTANTANEOUS);
    EXPECT_NEAR(res.trip_time, 0.0, 1e-9);
}