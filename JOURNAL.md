from pathlib import Path
from textwrap import dedent

md = dedent("""\
---
title: "ESP8266 PS4 RC Car"
author: "Seif Safina"
description: "A low-cost Wi-Fi controlled 2WD RC car using an ESP8266, L293N motor driver, and a PlayStation 4 controller connected through a Python bridge."
created_at: "2026-07-18"
---

# Project Started

I started this project to learn more about robotics, embedded systems, and RC vehicle design while keeping the cost as low as possible. Instead of buying a ready-made RC car, I decided to build one from individual components so I could understand every part of the system.

The long-term goal is to turn this prototype into a modular RC platform that can later become a Formula One style RC car with proportional steering, telemetry, and better electronics.

![Project Components](images/components.jpg)

**Total time spent: 1 hours**

# Electronics and Wiring

The first hardware milestone was wiring the ESP8266 to the L293N motor driver.

## Pinout

| L293N | ESP8266 |
|-------|---------|
| IN1 | D1 (GPIO5) |
| IN2 | D2 (GPIO4) |
| IN3 | D5 (GPIO14) |
| IN4 | D6 (GPIO12) |
| ENA | D7 (GPIO13) |
| ENB | D8 (GPIO15) |

After wiring the board I verified the motor outputs and prepared the hardware for software development.

![Wiring](images/wiring.jpg)

**Total time spent: 0.75 hours**

# First Firmware

The initial firmware hosted a Wi-Fi access point so a phone could connect directly to the ESP8266.

Features included:
- Web interface
- Virtual joystick
- Speed control
- Turn compensation
- Adjustable braking

After testing, I discovered that the virtual joystick wasn't ideal for precise driving.

![Web Controller](images/web_controller.png)

**Total time spent: 1 hours**

# Improving the Controls

The touchscreen joystick was replaced with an eight-direction control pad. Although this was easier to use, it still didn't provide the precision I wanted.

After experimenting with the browser controls, I decided to move to a real controller.

![Directional Controls](images/dpad.png)

**Total time spent: 1.5 hours**

# PS4 Controller Integration

Instead of connecting the controller directly to the ESP8266, I wrote a Python bridge application.

The bridge:
- Detects the PS4 controller.
- Reads the analog sticks and triggers.
- Sends steering and throttle data over WebSockets.
- Automatically reconnects if the ESP8266 disconnects.

The ESP8266 firmware receives the commands and controls the motors.

Current controls:

| Control | Function |
|---------|----------|
| Left Stick X | Analog steering |
| R2 | Analog forward throttle |
| L2 | Analog braking and reverse |

![Python Bridge](images/python_bridge.png)

**Total time spent: 1.5 hours**

# Firmware Improvements

Several improvements were made while testing:

- Smooth acceleration
- Smooth deceleration
- Analog steering
- Analog throttle
- Analog braking
- Differential motor mixing
- Communication fail-safe

There were also several debugging sessions involving Wi-Fi connectivity, firmware uploads, and WebSocket communication.

![Firmware Development](images/firmware.png)

**Total time spent: 0.5 hours**

# Current Status

The car is functional as a software development platform. The focus is now shifting toward improving the mechanical design.

Planned upgrades include:

- Steering servo
- Better motor driver (TB6612FNG or DRV8833)
- Battery voltage monitoring
- Telemetry
- ESP32 version
- Formula One chassis
- Brushless motor support

![Current Build](images/current_build.jpg)


# Notes

The dates above are intentionally grouped because development happened over multiple sessions and exact dates were not recorded. The journal reflects the chronological order of development rather than specific calendar days.
""")

path="/mnt/data/JOURNAL.md"
Path(path).write_text(md, encoding="utf-8")
print(path)
