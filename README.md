# smart-agriculture-cpp
# 🌱 Smart Agriculture Monitoring System (C / C++)

A lightweight, purely software-based Smart Agriculture Monitoring and Automated Irrigation system built using **C** and **C++**. 

This project demonstrates inter-process communication (IPC) via shared data files between an environmental sensor simulator written in **C** and a control/monitoring dashboard written in **C++**.

---

## 📸 System Architecture

```text
 [ simulator.c ]  --- (Writes telemetry.dat) --->  [ dashboard.cpp ]
  (Virtual Sensor)                                  (Control Center)
        ^                                                  |
        |--------- (Reads pump_command.txt) ---------------|
​simulator.c (Virtual Sensor Engine): Simulates real-time environmental factors (soil moisture drying, temperature, humidity fluctuations) and responds to water pump status updates.
​dashboard.cpp (Control & UI Engine): Reads telemetry data, applies automated threshold logic (waters when soil moisture < 30%, stops when > 70%), updates the pump command file, and renders a live dynamic terminal interface.
​🚀 Features
​Real-Time Environmental Simulation: C-based engine simulating soil moisture evaporation and pump-assisted hydration.
​Automated Threshold Control: C++ decision engine that manages automated irrigation based on live soil moisture levels.
​Dynamic Terminal Dashboard: Auto-refreshing console dashboard displaying live metrics and a history log table.
​Zero Hardware Required: Purely software driven—runs directly on Windows (via WSL/MinGW), Linux, or macOS.
​🛠️ Prerequisites
​Ensure you have C and C++ compilers installed on your machine:
​GCC (for C compilation)
​G++ (for C++ compilation)
​Verify installation by running:
gcc --version
g++ --version

Building and Running
​1. Compile the Source Code
​Open your terminal in the project directory and run:
# Compile the C sensor simulator
gcc simulator.c -o simulator

# Compile the C++ dashboard engine
g++ dashboard.cpp -o dashboard

2. Run the System (Dual Terminal Setup)
​Step 1: Start the Virtual Sensor Simulator (Terminal 1)

./simulator

(Keep this terminal open—it runs continuously to generate live telemetry data).
​Step 2: Start the Live Terminal Dashboard (Terminal 2)
Open a second terminal tab and run:

./dashboard
📂 Project Structure
smart-agriculture-cpp/
├── simulator.c       # Virtual sensor generator in C
├── dashboard.cpp     # Control engine and terminal UI in C++
├── .gitignore        # Ignores compiled binaries & runtime data files
└── README.md         # Project documentation
📜 License
​This project is open source and available under the MIT License.






