# Installation Guide

# Smart Drawbridge Controller

This guide explains how to install and run the project on a Raspberry Pi.

---

# Requirements

Hardware:

- Raspberry Pi 4 Model B
- Arduino
- H-Bridge motor driver
- Load cell + Qwiic Scale
- DC motor
- Limit switches
- Internet connection

Software:

- Python 3
- Arduino IDE

---

# 1. Clone the Repository

Open a terminal on the Raspberry Pi.

Clone the GitHub repository:

```bash
git clone https://github.com/YOUR_USERNAME/smart-drawbridge-controller.git
```

Go into the project folder:

```bash
cd smart-drawbridge-controller
```

---

# 2. Create a Python Virtual Environment (venv)

Create a virtual environment:

```bash
python3 -m venv venv
```

This creates an isolated Python environment for the project.

---

# 3. Activate the Virtual Environment

Activate the venv:

```bash
source venv/bin/activate
```

If successful, the terminal should show:

```bash
(venv)
```

at the beginning of the line.

---

# 4. Upgrade pip

Upgrade pip before installing libraries:

```bash
pip install --upgrade pip
```

---

# 5. Install Required Libraries

Install all Python dependencies:

```bash
pip install blynklib
pip install matplotlib
pip install numpy
pip install pyserial
pip install RPi.GPIO
```

Install the Blynk Python library:

```bash
pip install git+https://github.com/vshymanskyy/blynk-library-python
```

Install the SparkFun Qwiic libraries:

```bash
pip install sparkfun-qwiic-scale
```

---

# 6. Enable UART on Raspberry Pi

UART serial communication is required between the Raspberry Pi and Arduino.

Open Raspberry Pi configuration:

```bash
sudo raspi-config
```

Go to:

```text
Interface Options
```

Then:

```text
Serial Port
```

Settings:

| Option | Value |
|---|---|
| Login shell over serial | No |
| Enable serial hardware | Yes |

Reboot the Raspberry Pi:

```bash
sudo reboot
```

---

# 7. Verify Serial Port

Check if UART is enabled:

```bash
ls /dev/serial0
```

Expected output:

```bash
/dev/serial0
```

---

# 8. Upload Arduino Code

Open the Arduino IDE.

Upload:

```text
arduino/bridge_controller.ino
```

or

```text
arduino/serial_angle_receiver.ino
```

Select:

- Correct Arduino board
- Correct COM port

Then click Upload.

---

# 9. Configure Blynk

Open the Blynk app.

Create widgets:

| Widget | Virtual Pin |
|---|---|
| Gauge | V0 |
| Button | V1 |
| Button | V2 |
| Button | V4 |
| Button | V5 |
| Slider | V6 |

Copy your Blynk authentication token.

Replace:

```python
BLYNK_AUTH = "YOUR_BLYNK_TOKEN"
```

with your own token.

---

# 10. Run the Project

Activate the virtual environment:

```bash
source venv/bin/activate
```

Run the main program:

```bash
python3 raspberry_pi/main.py
```

or for angle control testing:

```bash
python3 raspberry_pi/angle_control.py
```

---

# 11. Exit the Virtual Environment

To deactivate the venv:

```bash
deactivate
```

---

# Troubleshooting

## Permission Errors

If GPIO access fails:

```bash
sudo usermod -aG gpio $USER
```

Then reboot.

---

## Serial Port Not Found

Check UART settings again using:

```bash
sudo raspi-config
```

---

## Blynk Not Connecting

Check:

- Internet connection
- Correct Blynk token
- Firewall settings

---

# Notes

- Raspberry Pi and Arduino must share GND.
- Do not power motors directly from GPIO pins.
- Use external motor power when required.
- Always activate the virtual environment before running the project.
