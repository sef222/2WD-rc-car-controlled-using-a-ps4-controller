# ESP8266 PS4 RC Car

A 2WD RC car controlled by a **PlayStation 4 DualShock 4 controller** using an **ESP8266** and a **Python bridge** over Wi-Fi.

---

## Features

-  PS4 DualShock 4 control
-  ESP8266 Access Point
-  Low-latency WebSocket communication
-  Analog throttle
-  Analog steering
-  Analog brake with reverse
-  Smooth acceleration & deceleration
-  Automatic failsafe if connection is lost

---

# Hardware

## Microcontroller
- ESP8266 NodeMCU

## Motor Driver
- L293N

## Controller
- Sony DualShock 4 (PS4)

---

# Pinout

| L293N | ESP8266 |
|-------|---------|
| IN1 | D1 (GPIO5) |
| IN2 | D2 (GPIO4) |
| IN3 | D5 (GPIO14) |
| IN4 | D6 (GPIO12) |
| ENA | D7 (GPIO13) |
| ENB | D8 (GPIO15) |
| GND | GND |
| 5V | VIN / 5V |

---

# Wiring

### Left Motor
- OUT1
- OUT2

### Right Motor
- OUT3
- OUT4

### Power
- Battery → L293N
- ESP8266 → USB or regulated 5V

---

# Software

## Arduino Libraries

Install:

- WebSocketsServer (Markus Sattler)
- ArduinoJson

---

## Python

Install:

```bash
pip install pygame-ce websocket-client
```

Run:

```bash
python PS4_RC_Bridge_v2.py
```

---

# Wi-Fi

The ESP8266 creates its own network.

SSID

```
ESP8266-RC
```

Password

```
12345678
```

Connect your computer to this network before running the Python bridge.

---

# Controls

| PS4 Control | Function |
|-------------|----------|
| Left Stick X | Steering |
| R2 | Forward |
| L2 | Brake / Reverse |

---

# Folder Structure

```
ESP8266-PS4-RC/
│
├── ESP8266_PS4_RC_Firmware.ino
├── PS4_RC_Bridge_v2.py
├── README.md
└── LICENSE
```

---


# License

MIT License

Feel free to modify, improve, and share the project.
