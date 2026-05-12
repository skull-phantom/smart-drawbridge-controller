# Wiring Documentation

# Smart Drawbridge Controller

This document describes the hardware wiring used in the smart drawbridge project.

---

# System Overview

The project consists of:

- Raspberry Pi 4 Model B
- Arduino
- H-Bridge motor driver
- Load cell sensor with Qwiic Scale
- Blynk mobile application
- Limit switches
- Manual override buttons

The Raspberry Pi handles:

- Blynk communication
- Weight sensor processing
- UART serial communication
- Data visualization

The Arduino handles:

- Motor control
- Safety logic
- Limit switches
- Override mode

---

# Raspberry Pi GPIO Connections

| GPIO Pin | Function |
|---|---|
| GPIO 17 | Warning LED output |
| GPIO 22 | Pulse output |
| GPIO 24 | Override control |
| GPIO 25 | Extra control output |
| GPIO 27 | Manual control output |

---

# UART Serial Communication

UART communication is used between the Raspberry Pi and Arduino.

| Raspberry Pi | Arduino |
|---|---|
| TX (GPIO14) | RX |
| RX (GPIO15) | TX |
| GND | GND |

Serial settings:

- Baudrate: 9600
- Protocol: UART Serial

---

# Arduino Pin Connections

| Arduino Pin | Function |
|---|---|
| 2 | Upper limit switch |
| 3 | Lower limit switch |
| 4 | Main control button |
| 5 | Override enable switch |
| 8 | Motor direction 1 |
| 9 | Motor direction 2 |
| 11 | Override stop button |
| 12 | Override up button |
| 13 | Override down button |

---

# Motor Driver

An H-Bridge motor driver is used to control the DC motor direction.

| Arduino Pin | H-Bridge |
|---|---|
| 8 | IN1 |
| 9 | IN2 |

Motor states:

| IN1 | IN2 | Action |
|---|---|---|
| HIGH | LOW | Bridge up |
| LOW | HIGH | Bridge down |
| LOW | LOW | Stop motor |

---

# Limit Switches

Two limit switches are used for bridge safety.

| Switch | Purpose |
|---|---|
| Upper limit switch | Detects maximum bridge height |
| Lower limit switch | Detects fully lowered bridge |

The switches use INPUT_PULLUP mode.

---

# Load Cell and Qwiic Scale

The load cell is connected through the SparkFun Qwiic Scale module.

The Raspberry Pi reads weight measurements using Python.

Functions:

- Ship weight detection
- Threshold monitoring
- Real-time graph plotting

---

# Blynk Virtual Pins

| Virtual Pin | Function |
|---|---|
| V0 | Weight display |
| V1 | Pulse trigger |
| V2 | GPIO 27 control |
| V4 | GPIO 24 control |
| V5 | GPIO 25 control |
| V6 | Angle slider |

---

# Angle Control System

The Blynk slider on V6 sends angle values to the Raspberry Pi.

The Raspberry Pi forwards the angle using UART serial communication.

Message format:

ANGLE:<value>

Example:

ANGLE:45

The Arduino receives the angle value and can later use it for automatic bridge positioning.

---

# Safety Features

- Limit switch protection
- Manual override mode
- Emergency stop button
- Weight threshold warning LED

---

# Notes

- Raspberry Pi and Arduino must share GND.
- UART must be enabled on the Raspberry Pi.
- Use external motor power supply when required.
- Do not power motors directly from GPIO pins.