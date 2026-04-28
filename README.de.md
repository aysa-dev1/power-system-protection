🌐 [English Version](README.md) 

# Power System Protection Analysis Demo (PSP)

## 1. Projektbeschreibung
Dieses C++ Projekt ist ein Analyse-Tool für die elektrische Energietechnik. Es berechnet symmetrische Komponenten und Kurzschlussströme in Energieversorgungsnetzen und bewertet die Reaktion von Überstromzeitschutz-Relais. Für Ingenieure und Softwareentwickler in der Domäne der Netzschutztechnik und Netzleittechnik.

## 2. Features
*  **Symmetrical Components:** Transformation von Phasengrößen in Mit-, Gegen- und Nullsystem (Fortescue-Transformation)
* **Network Modeling:** Modellierung von Quellen, Transformatoren und Leitungen inkl. automatischer Impedanz-Aggregation.
* **Short Circuit Calculation:** Berechnungen von vier Kurzschluss-Fehlerarten.
* **Overcurrent Protection:** Logik zur Auswertung von Schutzrelais-entscheidungen (instantan/verzögert)

## 3. Technologien
* **C++17**
* **CMake**
* **GoogleTest**

## 4. Projektstruktur

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
├── tests/                  # Unit-Tests (GTest)
├── app/                    # Hauptanwendung (main.cpp)
├── CMakeLists.txt          # Build-Konfiguration
└── README.md
```

## 5. Build & Run
Um das Projekt zu bauen und auszuführen, nutzen Sie die folgenden Befehle:

```bash
# Projekt konfigurieren
cmake -S . -B build

# Kompilieren
cmake --build build

# Demo-Anwendung starten
./build/psp_demo

# Tests ausführen
./build/psp_tests
```

## 6. Beispiel-Output

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

## 7. Hintergrund
Die Kurzschlussberechnung basiert auf der Methode der symmetrischen Komponenten (Fortescue-Transformation), die ein unsymmetrisches Dreiphasensystem in drei entkoppelte symmetrische Komponentensysteme zerlegt. So können Fehlerarten wie einpolige Erdschlüsse berechnet und Schutzrelais korrekt eingestellt werden.

**Referenz:** IEC 60909-0:2016
