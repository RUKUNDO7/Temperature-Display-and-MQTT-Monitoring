# Temperature Display & MQTT Monitoring System

**Trade Code:** SPE — Embedded Systems Software Integration
**Assessment:** Temperature Reading, LCD Display & MQTT Transmission (40 Marks)

---

## System Overview

```text
LM35 Sensor → Arduino Uno → 16×2 LCD + USB Serial → PC Program → Mosquitto MQTT Broker (VPS)
```

This project implements a complete embedded monitoring system that reads temperature data from an LM35 sensor, displays it on a 16×2 LCD, transmits it to a PC via serial communication, and publishes the readings to a Mosquitto MQTT broker hosted on a VPS.

---

## Objectives

### Part 1 – Arduino System

* Read temperature from an LM35 temperature sensor.
* Display candidate name on the first row of a 16×2 LCD.
* Implement horizontal scrolling if the name exceeds 16 characters.
* Display temperature on the second row of the LCD.
* Send temperature values to the PC through USB serial communication.

### Part 2 – PC Monitoring & MQTT

* Read incoming serial data from Arduino.
* Display temperature values in real time.
* Publish temperature values to a Mosquitto MQTT broker running on a VPS.

---

## Hardware Components

| Component               | Quantity |
| ----------------------- | -------- |
| Arduino Uno             | 1        |
| LM35 Temperature Sensor | 1        |
| 16×2 I2C LCD            | 1        |
| USB Cable               | 1        |
| Jumper Wires            | Several  |

---

## Hardware Connections

### LM35 Temperature Sensor

```text
LM35      Arduino Uno
---------------------
VCC   ->  3.3V
OUT   ->  A0
GND   ->  GND
```

### 16×2 I2C LCD

```text
LCD       Arduino Uno
---------------------
VCC   ->  5V
GND   ->  GND
SDA   ->  A4
SCL   ->  A5
```

Note: The LCD module used during testing operated correctly from the Arduino Uno 3.3V output.

---

## System Architecture

```text
┌─────────────┐
│ LM35 Sensor │
└──────┬──────┘
       │ Analog Signal
       ▼
┌────────────────────┐
│    Arduino Uno     │
│                    │
│ ADC Conversion     │
│ Temperature Calc.  │
│ LCD Display        │
│ UART Transmission  │
└──────┬─────────────┘
       │ USB Serial
       ▼
┌────────────────────┐
│    PC Program      │
│                    │
│ Serial Reader      │
│ Real-time Display  │
│ MQTT Publisher     │
└──────┬─────────────┘
       │ MQTT
       ▼
┌────────────────────┐
│ Mosquitto Broker   │
│ VPS Server         │
│ 157.173.101.159    │
└────────────────────┘
```

---

## Firmware Architecture

```text
Application Layer
│
├── Temperature Measurement
├── LCD Display Management
├── Name Scrolling Logic
└── Serial Communication

Driver Layer
│
├── ADC Driver
├── I2C Driver
└── UART Driver

Hardware Layer
│
├── LM35 Sensor
├── LCD Module
└── Arduino Uno
```

---

## Arduino Program Features

### Temperature Measurement

The LM35 outputs:

```text
10 mV per °C
```

Temperature calculation:

```text
Voltage = (ADC Reading × 5.0) / 1023

Temperature (°C) = Voltage × 100
```

### LCD Display

Row 1:

```text
Candidate Name
```

Row 2:

```text
Temp: 24.50°C
```

### Name Scrolling

If the candidate name exceeds 16 characters, the name scrolls horizontally across the first row of the LCD.

Example:

```text
GIHOZO RUKUNDO B
IHOZO RUKUNDO BE
HOZO RUKUNDO BEN
```

### Serial Transmission

Data is transmitted every cycle at:

```text
9600 baud
```

Format:

```text
TEMP:24.50
TEMP:24.60
TEMP:24.70
```

---

## MQTT Configuration

### Broker Information

```text
Broker IP : 157.173.101.159
Broker    : Mosquitto MQTT
Port      : 1883
Topic     : spe/temperature
QoS       : 1
Client ID : spe_temp_monitor
```

### Example MQTT Payload

```text
24.50
```

---

## Communication Details

### Arduino ↔ PC

| Parameter | Value             |
| --------- | ----------------- |
| Interface | USB Serial (UART) |
| Baud Rate | 9600              |
| Data Bits | 8                 |
| Stop Bits | 1                 |
| Parity    | None              |
| Format    | TEMP:<value>      |

Example:

```text
TEMP:24.50
```

### PC ↔ MQTT Broker

| Parameter | Value             |
| --------- | ----------------- |
| Protocol  | MQTT v3.1.1       |
| Port      | 1883              |
| Topic     | spe/temperature   |
| QoS       | 1                 |
| Payload   | Temperature Value |

---

## Communication Names Used

| Communication Method | Purpose                  |
| -------------------- | ------------------------ |
| Analog Input         | LM35 Sensor → Arduino    |
| I2C                  | Arduino ↔ LCD            |
| USB Serial (UART)    | Arduino → PC             |
| TCP/IP               | PC → VPS                 |
| MQTT                 | Publish Temperature Data |

---

## Real-Time Monitoring

The PC application continuously:

1. Reads serial data from Arduino.
2. Displays temperature readings in real time.
3. Publishes the readings to the MQTT broker.

Example output:

```text
Temperature: 24.50 °C
Published to spe/temperature

Temperature: 24.60 °C
Published to spe/temperature
```

---

## MQTT Verification

To verify published data:

```bash
mosquitto_sub -h 157.173.101.159 -t spe/temperature
```

Expected output:

```text
24.50
24.60
24.70
```

---

## Dashboard and Monitoring

The current implementation uses:

```text
PC Client Console Monitoring
```

and MQTT subscribers to observe incoming temperature values.

Future enhancement:

```text
Node-RED Dashboard
http://157.173.101.159:1880/ui
```

This can be added to provide a web-based visualization dashboard.

---

## Candidate Tasks Checklist

| Task                        | Status    |
| --------------------------- | --------- |
| System Architecture Diagram | Completed |
| Arduino Temperature Reading | Completed |
| LCD Temperature Display     | Completed |
| Horizontal Name Scrolling   | Completed |
| Serial Data Transmission    | Completed |
| PC Serial Reader            | Completed |
| MQTT Publishing             | Completed |
| Communication Documentation | Completed |

---

## Conclusion

The developed system successfully acquires temperature data from an LM35 sensor, displays it locally on an LCD, transmits it through serial communication to a PC, and publishes the readings to a Mosquitto MQTT broker hosted on a VPS. The solution demonstrates sensor interfacing, LCD control, serial communication, and MQTT-based IoT data transmission.
