🌐 [Deutsche Version](README.de.md)

# Power System Protection Analysis Demo (PSP)


## 1. Project Description
This C++ project is an analysis tool for electrical power engineering. It calculates symmetrical components and short-circuit currents in power grids and evaluates the response of overcurrent protection relays. It is designed for engineers and developers working in the field of power system protection and grid automation.

## 2. Features
*  **Symmetrical Components:** Transformation of phase quantities into positive, negative, and zero sequence (Fortescue Transformation).
* **Network Modeling:** Modeling of sources, transformers, and lines including automatic impedance aggregation.
* **Short Circuit Calculation:** Calculation of four different short circuit current faults.
* **Overcurrent Protection:** Logic for evaluating relay trip decisions (instantaneous/delayed).

## 3. Technologies
* **C++17**
* **CMake**
* **GoogleTest**

## 4. Project Structure

```text
power_system_protection/
├── include/psp/            
│   ├── symmetrical_components.h
│   ├── network_model.h
│   ├── short_circuit.h
│   └── overcurrent_relay.h
├── src/                   
│   ├── symmetrical_components.cpp
│   ├── network_model.cpp
│   ├── short_circuit.cpp
│   └── overcurrent_relay.cpp
├── tests/                      # Unit-Tests (GTest)
├── app/                        # main-Application (main.cpp)
├── CMakeLists.txt              # build configuration
└── README.md
```

## 5. Build & Run
Use the following commands to build and run the analysis tool and demo application

```bash
# project configuration
cmake -S . -B build

# Compile
cmake --build build

# start Demo app
./build/psp_demo

# run tests
./build/psp_tests
```

## 6. Example Output

```text
========================================================
     POWER SYSTEM PROTECTION DEMO - 20 kV NETWORK
========================================================
[Relay Settings]
I pickup        : 500.00 A
I instantaneous : 2000.00 A
Time delay      : 0.30 s

[Network Impedances]
Z1 = (0.90 + 3.30j) Ohm
Z2 = (0.70 + 3.10j) Ohm
Z0 = (2.70 + 8.80j) Ohm

[Short Circuit Calculations]
3-Phase Fault (L1-L2-L3) :    3375.80 A | STATUS: INSTANTANEOUS TRIP (0.0s)
1-Phase Ground (L1-E)    :    2192.95 A | STATUS: INSTANTANEOUS TRIP (0.0s)
2-Phase Fault (L2-L3)    :    3031.70 A | STATUS: INSTANTANEOUS TRIP (0.0s)
2-Phase Ground (L2-L3-E) :    1537.98 A | STATUS: DELAYED TRIP (0.30s)
```
## 7. Background
The short-circuit calculation is based on the method of symmetrical components (Fortescue-Transformation), which decomposes an unbalanced three-phase system into three decoupled symmetrical component systems. It is used to calculate fault types like single-phase-to-ground faults and the correct setting of protection relays based on the resulting zero-sequence currents.

**Reference:** IEC 60909-0:2016