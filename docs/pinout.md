# SBot Pinout Reference

## Overview

SBot uses an Arduino Uno (or Mega) with the following pin assignments.

## Digital Pins

| Pin | Component | Type | Notes |
|-----|-----------|------|-------|
| D0 | Bluetooth TX | Serial | Reserved for HC-06 |
| D1 | Bluetooth RX | Serial | Reserved for HC-06 |
| D2 | Left Leg Servo | PWM | Otto DIY walking |
| D3 | Right Leg Servo | PWM | Otto DIY walking |
| D4 | Left Foot Servo | PWM | Otto DIY walking |
| D5 | Right Foot Servo | PWM | Otto DIY walking |
| D6 | Left Arm Servo | PWM | Arm movement |
| D7 | Right Arm Servo | PWM | Arm movement |
| D8 | Ultrasonic Echo | Digital | HC-SR04 distance |
| D9 | NeoPixel Strip 1 | PWM | Left arm LEDs (7 pixels) |
| D10 | NeoPixel Strip 2 | PWM | Right arm LEDs (7 pixels) |
| D11 | Ultrasonic Trigger | Digital | HC-SR04 distance |
| D12 | Digital Microphone | Digital | Sound detection |
| D13 | Buzzer | Digital | Piezo speaker |

## Analog Pins

| Pin | Component | Type | Notes |
|-----|-----------|------|-------|
| A0 | IR Receiver | Analog | Infrared remote control |
| A1 | DHT Sensor | Digital | Temperature & humidity |
| A2 | Light Sensor | Analog | LDR for ambient light |
| A3 | Touch Sensor | Digital | Capacitive touch input |
| A4 | I2C SDA | I2C | Voice module + OLED |
| A5 | I2C SCL | I2C | Voice module + OLED |
| A6 | Motion Sensor | Analog | PIR motion detection |
| A7 | Analog Microphone | Analog | Sound intensity |

## I2C Devices

| Address | Device | Description |
|---------|--------|-------------|
| 0x64 | DFRobot DF2301Q | Voice recognition |
| 0x3C | SSD1306 OLED | Display (future) |

## Wiring Diagram

```
                    ┌─────────────────────┐
                    │     Arduino Uno     │
                    │                     │
    Left Leg ─────► │ D2              A0 │ ◄───── IR Receiver
   Right Leg ─────► │ D3              A1 │ ◄───── DHT Sensor
   Left Foot ─────► │ D4              A2 │ ◄───── Light Sensor
  Right Foot ─────► │ D5              A3 │ ◄───── Touch Sensor
    Left Arm ─────► │ D6              A4 │ ◄───── I2C SDA
   Right Arm ─────► │ D7              A5 │ ◄───── I2C SCL
  Ultra Echo ─────► │ D8              A6 │ ◄───── PIR Sensor
   NeoPixel1 ─────► │ D9              A7 │ ◄───── Analog Mic
   NeoPixel2 ─────► │ D10                │
 Ultra Trig  ─────► │ D11            GND │ ◄───── Ground
  Digital Mic ────► │ D12            5V  │ ◄───── Power
      Buzzer ─────► │ D13            3.3V│
                    └─────────────────────┘
```

## Power Requirements

- **Arduino**: 5V via USB or 7-12V via barrel jack
- **Servos**: 5V (use external power for multiple servos)
- **NeoPixels**: 5V (external power recommended for full brightness)
- **Voice Module**: 3.3V-5V

## Notes

1. **Servo Power**: When using all 6 servos, use an external 5V power supply
2. **NeoPixels**: Add a 300-500Ω resistor on data line and 1000µF capacitor on power
3. **I2C Pull-ups**: The voice module has internal pull-ups, external may not be needed
4. **Bluetooth**: D0/D1 are used for Serial, disconnect when uploading code
