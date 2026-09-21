# Smart EV Charging Station Optimizer (3-Bay Management System)

An Edge AI and IoT-based multi-bay electric vehicle (EV) charging station power management system powered by ESP32 microcontrollers. This project optimizes power distribution across three concurrent charging bays (`BAY 1`, `BAY 2`, and `BAY 3`) using real-time telemetry, state management, and edge optimization algorithms to balance load demand, prevent grid overloading, and maximize charging efficiency.

---

## 📌 Features

- **Multi-Bay Power Distribution**: Independent real-time management and monitoring of 3 charging bays (`BAY 1`, `BAY 2`, `BAY 3`).
- **Edge AI Load Optimization**: On-device algorithmic allocation of dynamic power limits based on grid capacity and vehicle priority.
- **Microcontroller Integration**: Built for ESP32 devices running optimized C++ firmware.
- **Telemetry & RPC Remote Control**: Real-time attribute reporting and Remote Procedure Calls (RPC) over IoT protocols (MQTT / ThingsBoard).
- **Simulation-Ready**: Includes pre-configured [Wokwi](https://wokwi.com/) simulation environments (`diagram.json`, `wokwi.toml`) for offline development and testing without physical hardware.

---

## 📁 Repository Structure

text
smart-ev-charging-station-optimizer-using-3-Bays/
├── BAY 1/                     # Firmware & configuration for Charging Bay 1
│   ├── src/                   # C++ source code (main.cpp, Peripherals, Network, etc.)
│   └── test/                  # Wokwi simulation config & hardware diagram
├── BAY 2/                     # Firmware & configuration for Charging Bay 2
│   ├── src/                   # C++ source code & system attributes
│   └── test/                  # Wokwi simulation config & hardware diagram
├── BAY 3/                     # Firmware & configuration for Charging Bay 3
│   ├── src/                   # C++ source code, Edge AI model & optimization logic
│   └── test/                  # Wokwi simulation config & hardware diagram
├── .gitignore                 # File exclusion configuration for Git
└── README.md                  # Project documentation


---

## 🛠 Tech Stack & Hardware Requirements

- **Microcontroller**: ESP32
- **Programming Language**: C / C++ (PlatformIO / VS Code framework)
- **Communication Protocols**: MQTT, Wi-Fi, RPC
- **IoT Platform**: ThingsBoard / Custom MQTT Broker
- **Simulation Platform**: Wokwi Simulator

---

## 🚀 Getting Started

### Prerequisites

1. **VS Code** with the **PlatformIO IDE** extension or **Wokwi Simulator** extension installed.
2. **Git** installed on your machine.

### Local Setup

1. **Clone the repository:**
bash
git clone https://github.com/Amna-Khan-hub/smart-ev-charging-station-optimizer-using-3-Bays.git


2. **Open in VS Code:**
Open VS Code and navigate to `File > Open Folder...`, then select the `smart-ev-charging-station-optimizer-using-3-Bays` directory.

3. **Running Wokwi Simulations:**
- Navigate to the `test/` folder of any bay (e.g., `BAY 1/test/diagram.json`).
- Press `F1` in VS Code and select **Wokwi: Start Simulator** to test the circuit and logic virtually.