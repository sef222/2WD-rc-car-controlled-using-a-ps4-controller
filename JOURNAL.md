---

# Improving the Controls

![Current Build](images/next_control.jpg)

The touchscreen joystick was replaced with an eight-direction control pad. Although this was easier to use, it still didn't provide the precision I wanted.

After experimenting with the browser controls, I decided to move to a real controller.

**Total time spent: 1.5 hours**

---

# PS4 Controller Integration

![Current Bridge](images/current_controlpc.jpg)

Instead of connecting the controller directly to the ESP8266, I wrote a Python bridge application.

The bridge:

* Detects the PS4 controller.
* Reads the analog sticks and triggers.
* Sends steering and throttle data over WebSockets.
* Automatically reconnects if the ESP8266 disconnects.

The ESP8266 firmware receives the commands and controls the motors.

Current controls:

| Control      | Function                   |
| ------------ | -------------------------- |
| Left Stick X | Analog steering            |
| R2           | Analog forward throttle    |
| L2           | Analog braking and reverse |

**Total time spent: 1.5 hours**

---

# Firmware Improvements

![Current Control](images/current_control.jpg)

Several improvements were made while testing:

* Smooth acceleration
* Smooth deceleration
* Analog steering
* Analog throttle
* Analog braking
* Differential motor mixing
* Communication fail-safe

There were also several debugging sessions involving Wi-Fi connectivity, firmware uploads, and WebSocket communication.

**Total time spent: 2.5 hours**

---

# Current Status

![Current Build](images/current_build.jpg)

The car is functional as a software development platform. The focus is now shifting toward improving the mechanical design.

Planned upgrades include:

* Steering servo
* Better motor driver (TB6612FNG or DRV8833)
* Battery voltage monitoring
* Telemetry
* ESP32 version
* Formula One chassis
* Brushless motor support

---
