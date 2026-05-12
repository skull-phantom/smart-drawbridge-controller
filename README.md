# Smart Drawbridge Control System

An IoT-based smart drawbridge system using Raspberry Pi, Arduino, Blynk, and real-time sensor feedback.

---

# Overview

This project simulates an automated drawbridge system that can operate in both automatic and manual override modes. It integrates embedded systems, IoT communication, sensor fusion, and motor control.

The system uses:

- Raspberry Pi 4 Model B for high-level control and data processing
- Arduino for real-time motor and safety control
- Blynk IoT platform for mobile interaction
- Load cell sensor for weight detection
- H-Bridge motor driver for bidirectional motor control
- UART serial communication between Raspberry Pi and Arduino

---

# Key Features

- 📱 Mobile control via Blynk app
- ⚖️ Real-time weight measurement system
- 🔁 Automatic bridge movement logic
- 🕹️ Manual override mode for direct control
- 📡 UART communication between Raspberry Pi and Arduino
- 📊 Live data visualization (matplotlib graphing)
- 🛑 Safety system with limit switches
- ⚠️ Threshold-based warning system

---

# System Architecture

```
Blynk App (Mobile)
        ↓
Raspberry Pi 4 (Python Logic)
        ↓ UART (TX/RX)
Arduino Microcontroller
        ↓
H-Bridge Motor Driver
        ↓
DC Motor → Drawbridge Mechanism
```

---

# Hardware Components

- Raspberry Pi 4 Model B
- Arduino Uno
- H-Bridge motor driver
- DC motor
- Load cell + Qwiic Scale module
- Limit switches (top & bottom)
- Push buttons
- External motor power supply

---

# Software Stack

- Python 3
- Arduino C++
- Blynk IoT Library
- RPi.GPIO
- PySerial
- Matplotlib
- NumPy

---

# Virtual Pins (Blynk)

| Pin | Function |
|---|---|
| V0 | Weight display |
| V1 | Control trigger |
| V2 | GPIO control |
| V4 | Motor control |
| V5 | Additional control |
| V6 | Angle slider |

---

# Serial Communication Protocol

Communication between Raspberry Pi and Arduino uses UART.

### Format:
```
COMMAND:VALUE
```

### Example:
```
ANGLE:45
```

### Supported Commands:
- ANGLE:<value> → sets bridge angle

---

# GPIO Mapping (Raspberry Pi)

| GPIO | Function |
|---|---|
| 17 | Warning LED |
| 22 | Control output |
| 24 | Override system |
| 25 | Auxiliary output |
| 27 | Manual control |

---

# Operating Modes

## 1. Automatic Mode
- Bridge operates based on sensor input and logic
- Limit switches prevent overtravel
- Weight sensor triggers safety conditions

## 2. Manual Override Mode
- Direct control using physical buttons
- Bypasses automatic logic
- Used for testing and emergency control

---

# Safety Features

- Limit switch protection (top & bottom)
- Motor stop on invalid state
- Override emergency control
- Weight threshold warning system

---

# Installation

See full setup instructions in:

- `docs/installation.md`
- `docs/gpio_mapping.md`
- `docs/serial_protocol.md`

---

# Example Usage

1. Start Raspberry Pi script:
```bash
python3 raspberry_pi/main.py
```

2. Open Blynk app and connect

3. Use slider to control bridge angle

4. Monitor weight and system state in real time

---

# Future Improvements

- PID motor control for smoother movement
- Web dashboard (instead of mobile-only control)
- Camera integration for ship detection
- MQTT cloud integration
- Full automatic docking system

---

# Author

**Thomas Vanrobaeys**

Electronics & IoT Engineering Project

---

# License

This project is licensed under the MIT License.
