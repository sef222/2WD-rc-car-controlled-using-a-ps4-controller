---
title: "ESP8266 PS4 RC Car"
author: "Seif Safina"
description: "A low-cost Wi-Fi controlled 2WD RC car using an ESP8266, L293N motor driver, and a PlayStation 4 controller connected through a Python bridge."
created_at: "2026-07-18"
---

# Project Started

![Current Build](images/current_build.jpg)

I started this project to learn more about robotics, embedded systems, and RC vehicle design while keeping the cost as low as possible. Instead of buying a ready-made RC car, I decided to build one from individual components so I could understand every part of the system.

The long-term goal is to turn this prototype into a modular RC platform that can later become a Formula One style RC car with proportional steering, telemetry, and better electronics.

**Total time spent: 0.5 hour**

---

# Electronics and Wiring

![Current Build](images/current_wiring.jpg)

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

After completing the wiring, I verified every connection and confirmed that the motor driver and ESP8266 were communicating correctly before moving on to firmware development.

**Total time spent: 0.75 hours**

---

# First Firmware

![Current Build](images/old_firmware.jpg)

The initial firmware hosted a Wi-Fi access point so a phone could connect directly to the ESP8266.

Features included:
- Web interface
- Virtual joystick
- Speed control
- Turn compensation
- Adjustable braking

After testing, I discovered that the virtual joystick wasn't ideal for precise driving.

**Total time spent: 1 hour**

---

# Improving the Controls

![Current Build](images/next_control.jpg)

The touchscreen joystick was replaced with an eight-direction control pad. Although this was easier to use, it still didn't provide the precision I wanted.

After experimenting with the browser controls, I decided to move to a real controller.

**Total time spent: 1.5 hours**

---

# PS4 Controller Integration

![Current Build](images/current_control.jpg)

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

**Total time spent: 2.5 hours**

---

# Current Status

![Current Build](images/current_build.jpg)

The car is functional as a software development platform. The focus is now shifting toward improving the mechanical design.

Planned upgrades include:

- Steering servo
- Better motor driver (TB6612FNG or DRV8833)
- Battery voltage monitoring
- Telemetry
- ESP32 version
- Formula One chassis
- Brushless motor support

---
