# Serial Communication Protocol

# Overview

The Raspberry Pi communicates with the Arduino using UART serial communication.

---

# Baud Rate

- 9600 baud

---

# Message Format

All messages are sent as plain text strings ending with a newline:

```text
COMMAND:VALUE
```

---

# Supported Commands

## 1. Angle Control

Used to control bridge position.

```text
ANGLE:<value>
```

Example:

```text
ANGLE:45
```

Meaning: set bridge to 45 degrees.

---

## 2. Future Commands (optional expansion)

You can extend the protocol with:

- START
- STOP
- OVERRIDE:1
- OVERRIDE:0

Example:

```text
OVERRIDE:1
```

---

# Arduino Parsing Logic

The Arduino reads serial input line by line and:

1. Waits for newline `\n`
2. Checks command type
3. Extracts value using string parsing

Example logic:

```cpp
if (input.startsWith("ANGLE:")) {
    int angle = input.substring(6).toInt();
}
```

---

# Important Notes

- Always end messages with `\n`
- Keep format consistent
- Avoid sending raw numbers without command prefix