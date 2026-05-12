# Troubleshooting Guide

# Smart Drawbridge Controller

This document helps solve common issues in the system.

---

# 1. Raspberry Pi does not communicate with Arduino

### Problem:
No data received on Arduino.

### Fix:

- Check UART wiring:
  - TX ↔ RX
  - RX ↔ TX
  - GND shared

- Enable serial port:
```bash
sudo raspi-config
```

- Check device:
```bash
ls /dev/serial0
```

---

# 2. Blynk not connecting

### Problem:
App does not connect to project.

### Fix:

- Check internet connection
- Verify Blynk token
- Make sure correct server is selected
- Restart script

---

# 3. GPIO not working

### Problem:
Pins do not respond.

### Fix:

- Run as root:
```bash
sudo python3 main.py
```

- Or add user to GPIO group:
```bash
sudo usermod -aG gpio $USER
```

Then reboot.

---

# 4. Motor does not move

### Problem:
No motor response.

### Fix:

- Check H-Bridge wiring
- Check external power supply
- Verify enable pins
- Test manually via Arduino override mode

---

# 5. Weight sensor not working

### Problem:
No readings or incorrect values.

### Fix:

- Check Qwiic connections
- Ensure correct I2C wiring
- Verify calibration values
- Make sure load cell is properly tared

---

# 6. Serial data is wrong or unreadable

### Problem:
Garbage or mixed messages.

### Fix:

- Ensure baud rate = 9600 on both sides
- Make sure messages end with `\n`
- Avoid printing debug spam in same serial channel

---

# 7. Arduino stuck or unresponsive

### Problem:
Motor not reacting or loop frozen.

### Fix:

- Reset Arduino
- Check for infinite loops in override mode
- Verify limit switch logic

---

# Safety Tip

Always disconnect motor power when debugging GPIO or serial issues.