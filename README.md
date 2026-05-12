# Smart Drawbridge Controller

A smart drawbridge system using:

- Raspberry Pi 4 Model B
- Arduino
- Blynk mobile app
- H-Bridge motor driver
- Load cell weight sensor

The Raspberry Pi processes sensor data and communicates with the Arduino over serial communication.  
The Arduino controls the bridge motor and safety logic.

---

## Features

- Automatic bridge movement
- Manual override mode
- Blynk smartphone control
- Weight detection using load cell
- Real-time graph plotting
- Safety limit switches

---

## Hardware Used

- Raspberry Pi 4 Model B
- Arduino Uno
- H-Bridge motor driver
- SparkFun Qwiic Scale
- DC Motor
- Limit switches
- Push buttons

---

## Wiring

### Raspberry Pi GPIO

| GPIO |    Function    |
|------|----------------|
|  22  | Pulse output   |
|  27  | Manual control |
|  24  | Override       |
|  25  | Extra control  |
|  17  | Alarm LED      |

### Arduino Pins

| Pin |      Function      |
|-----|--------------------|
|  8  | Motor direction 1  |
|  9  | Motor direction 2  |
|  2  | Upper limit switch |
|  3  | Lower limit switch |
|  4  | Control button     |

---

## Installation

### Raspberry Pi

Install dependencies:

```bash
pip install blynklib
pip install qwiicscale
pip install matplotlib
pip install pyserial
```

Run:

```bash
python3 main.py
```

### Arduino

Upload:

```text
arduino/bridge_controller.ino
```

using the Arduino IDE.

---

## Blynk Controls

| Virtual Pin |   Function   |
|-------------|--------------|
|      V1     | Pulse output |
|      V2     |    GPIO 27   |
|      V4     |    GPIO 24   |
|      V5     |    GPIO 25   |
|      V6     | Angle slider |

---

## Future Improvements

- PID motor control
- Web dashboard
- Camera integration
- Automatic ship detection

---

## Author

Thomas Vanrobaeys
