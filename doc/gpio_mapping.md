# GPIO Mapping

# Raspberry Pi GPIO Overview

This document explains all GPIO connections used in the Smart Drawbridge Controller project.

---

# Raspberry Pi GPIO Pins

| GPIO Pin | Function | Description |
|---|---|---|
| GPIO 17 | Warning LED | Turns on when weight threshold is exceeded |
| GPIO 22 | Output signal | Pulse / control signal |
| GPIO 24 | Override control | Enables manual override mode |
| GPIO 25 | Extra output | Additional control output |
| GPIO 27 | Motor control signal | Manual motor control input |

---

# UART Serial Communication

Used for communication between Raspberry Pi and Arduino.

| Raspberry Pi | Arduino |
|---|---|
| GPIO 14 (TX) | RX |
| GPIO 15 (RX) | TX |
| GND | GND |

---

# Important Notes

- All GPIO pins use 3.3V logic
- Never connect 5V directly to Raspberry Pi GPIO
- Always share common GND between Raspberry Pi and Arduino