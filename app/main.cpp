#include "psp/symmetrical_components.h"
#include "psp/network_model.h"
#include "psp/short_circuit.h"
#include "psp/overcurrent_relay.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>


// help function

void print_fault_report(const std::string& fault_name, 
                        const psp::ShortCircuitResult& res,
                        const psp::RelaySettings& settings){

    psp::RelayResult relay = psp::evaluate_overcurrent(settings, res.I_magnitude);

    std::cout << std::left << std::setw(25) << fault_name
             << ": " << std::right << std::setw(10) << res.I_magnitude << " A | ";

    if(relay.decision == psp::TripDecision::TRIP_INSTANTANEOUS)
      std::cout << "STATUS: INSTANTANEOUS TRIP (0.0s)";
    else if (relay.decision == psp::TripDecision::TRIP_DELAYED)
      std::cout << "STATUS: DELAYED TRIP (" << relay.trip_time << "s)";
    else
      std::cout << "STATUS: NO TRIP";

    std::cout << std::endl;  

}


int main() {

    // define net
    const double V_nominal = 20000.0;
    const double V_source = V_nominal / std::sqrt(3.0);

    psp::NetworkParameters net;

    // source
    net.Z1_source = {0.5, 2.0};
    net.Z2_source = {0.3, 1.8};
    net.Z0_source = {1.5, 5.7};

    // transformer
    net.Z1_trafo = {0.1, 0.8};
    net.Z2_trafo = net.Z1_trafo;
    net.Z0_trafo = {0.3, 1.6};

    // line
    net.Z1_line = {0.3, 0.5};
    net.Z2_line = net.Z1_line;
    net.Z0_line = {0.9, 1.5};

    // calculate impedances
    psp::SequenceImpedances Z_seq = psp::compute_sequence_impedances(net);   
    
    // calculate short circuit currents
    psp::ShortCircuitResult fault_3ph = psp::calculate_fault_3phase(Z_seq, V_source);
    psp::ShortCircuitResult fault_1ph_ground = psp::calculate_fault_1phase_ground(Z_seq, V_source);
    psp::ShortCircuitResult fault_2ph = psp::calculate_fault_2phase(Z_seq, V_source);
    psp::ShortCircuitResult fault_2ph_ground = psp::calculate_fault_2phase_ground(Z_seq, V_source);

    psp::RelaySettings settings;

    settings.I_pickup = 500.0; // A
    settings.I_instantaneous = 2000.0; // A
    settings.time_delay = 0.3; // s


    // report
    std::cout << "========================================================" << std::endl;
    std::cout << "     POWER SYSTEM PROTECTION DEMO - 20 kV NETWORK" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "[Relay Settings]" << "\n"
              << "I pickup        : " << settings.I_pickup        << " A\n"
              << "I instantaneous : " << settings.I_instantaneous << " A\n"
              << "Time delay      : " << settings.time_delay      << " s\n" << std::endl;

    std::cout << "[Network Impedances]" << "\n"
              << "Z1 = (" << Z_seq.Z1.real() << " + " << Z_seq.Z1.imag() << "j) Ohm\n"
              << "Z2 = (" << Z_seq.Z2.real() << " + " << Z_seq.Z2.imag() << "j) Ohm\n"
              << "Z0 = (" << Z_seq.Z0.real() << " + " << Z_seq.Z0.imag() << "j) Ohm\n" << std::endl;

    std::cout << "[Short Circuit Calculations]" << std::endl;
    print_fault_report("3-Phase Fault (L1-L2-L3)", fault_3ph, settings);
    print_fault_report("1-Phase Ground (L1-E)", fault_1ph_ground, settings);
    print_fault_report("2-Phase Fault (L2-L3)", fault_2ph, settings);
    print_fault_report("2-Phase Ground (L2-L3-E)", fault_2ph_ground, settings);

    return 0;
}