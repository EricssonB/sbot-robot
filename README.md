# SBot - Interactive Robot Companion

<p align="center">
  <img src="docs/images/sbot-logo.png" alt="SBot Logo" width="200"/>
</p>

<p align="center">
  <strong>An expressive, interactive robot built on the Otto DIY platform</strong>
</p>

<p align="center">
  <a href="#features">Features</a> •
  <a href="#hardware">Hardware</a> •
  <a href="#installation">Installation</a> •
  <a href="#usage">Usage</a> •
  <a href="#commands">Commands</a> •
  <a href="#architecture">Architecture</a>
</p>

---

## Overview

SBot is an enhanced Otto DIY robot with extended capabilities including voice recognition, expressive LED lighting, and multiple behavioral states. Designed to be an interactive companion robot with personality and expressiveness inspired by robots like Vector and Eilik.

## Features

- 🎤 **Voice Recognition** - Control SBot with voice commands using DFRobot DF2301Q
- 💡 **NeoPixel LED Arms** - Expressive RGB lighting with smooth animations
- 🤖 **Behavioral States** - Multiple emotional states (Dope, Chill, Alert)
- 🦿 **Otto DIY Walking** - Full walking, dancing, and gesture capabilities
- 🎵 **Sound Effects** - RTTTL melody playback and Otto sound library
- 📱 **Serial Control** - Control via USB serial for debugging and manual control
- 🔧 **Modular Architecture** - Clean, professional codebase with separated concerns

## Hardware

### Components

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino Uno/Mega | 1 | Main microcontroller |
| Otto DIY Kit | 1 | Base robot (4x SG90 servos) |
| SG90 Servo | 2 | Arm servos |
| NeoPixel Strip | 2 | 7 LEDs each, for arm lighting |
| DFRobot DF2301Q | 1 | Voice recognition module |
| Piezo Buzzer | 1 | Sound output |
| HC-06 Bluetooth | 1 | (Optional) Bluetooth control |

### Pin Configuration

#### Digital Pins
| Pin | Component | Function |
|-----|-----------|----------|
| D2 | Left Leg Servo | Otto walking |
| D3 | Right Leg Servo | Otto walking |
| D4 | Left Foot Servo | Otto walking |
| D5 | Right Foot Servo | Otto walking |
| D6 | Left Arm Servo | Arm movement |
| D7 | Right Arm Servo | Arm movement |
| D8 | Ultrasonic Echo | Distance sensing |
| D9 | NeoPixel 1 | Left arm LEDs |
| D10 | NeoPixel 2 | Right arm LEDs |
| D11 | Ultrasonic Trigger | Distance sensing |
| D12 | Digital Microphone | Sound detection |
| D13 | Buzzer | Sound output |

#### Analog Pins
| Pin | Component | Function |
|-----|-----------|----------|
| A0 | IR Receiver | Infrared remote |
| A1 | DHT Sensor | Temperature/Humidity |
| A2 | LDR | Light sensing |
| A3 | Touch Sensor | Touch input |
| A4 | I2C SDA | Voice module + OLED |
| A5 | I2C SCL | Voice module + OLED |
| A6 | PIR Sensor | Motion detection |
| A7 | Analog Mic | Sound intensity |

## Installation

### Prerequisites

- [PlatformIO](https://platformio.org/) (VS Code extension recommended)
- USB cable for Arduino programming

### Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/sbot-robot.git
   cd sbot-robot
   ```

2. **Install PlatformIO extension** (if using VS Code)
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO"
   - Install the extension

3. **Build the project**
   ```bash
   pio run
   ```

4. **Upload to Arduino**
   ```bash
   pio run --target upload
   ```

5. **Open Serial Monitor**
   ```bash
   pio device monitor
   ```

### Dependencies

All dependencies are automatically managed by PlatformIO:

- Adafruit NeoPixel
- Servo
- DFRobot_DF2301Q
- Otto DIY Library (included in lib/)

## Usage

### Serial Commands

Connect via serial monitor at **115200 baud** and use these commands:

| Command | Shortcut | Description |
|---------|----------|-------------|
| `dope` | `d` | Trigger excited celebration state |
| `chill` | `c` | Trigger calm relaxation state |
| `alert` | `a` | Trigger alert attention state |
| `wave` | `w` | Wave arm gesture |
| `home` | `h` | Return to home position |
| `walk` | - | Walk forward 4 steps |
| `dance` | - | Perform dance routine |
| `rainbow` | - | Rainbow LED animation |
| `status` | - | Show system status |
| `help` | `?` | Show command list |

### Voice Commands

After waking the voice module:

| Command ID | Trigger Phrase | Action |
|------------|----------------|--------|
| 5 | (Custom phrase) | Dope State |
| 6 | (Custom phrase) | Chill State |

## Architecture

```
sbot-robot/
├── platformio.ini        # PlatformIO configuration
├── include/
│   ├── config.h          # Pin definitions & constants
│   ├── colors.h          # RGB color definitions
│   ├── melodies.h        # RTTTL melodies
│   ├── led_controller.h  # LED controller interface
│   ├── servo_controller.h # Arm servo interface
│   ├── voice_controller.h # Voice recognition interface
│   └── states.h          # State machine interface
├── src/
│   ├── main.cpp          # Entry point & main loop
│   ├── led_controller.cpp
│   ├── servo_controller.cpp
│   ├── voice_controller.cpp
│   └── states.cpp
├── lib/
│   └── Otto/             # Otto DIY library
├── docs/
│   └── images/           # Documentation images
└── README.md
```

### Design Principles

- **Separation of Concerns** - Each module handles one responsibility
- **Hardware Abstraction** - Controllers abstract hardware details
- **State Machine** - Clean behavioral state management
- **Configurable** - Feature flags for enabling/disabling features
- **Debug Support** - Conditional debug output

## Behavioral States

### IDLE
Default state, waiting for input. LEDs dim white.

### DOPE (Excited)
Celebration state with:
- Magenta → Red → Orange → Yellow LED sequence
- Arms raised with celebration gesture
- Happy sounds and dance moves

### CHILL (Calm)
Relaxation state with:
- Dim magenta breathing LEDs
- Arms in relaxed position
- Soft, calming sounds

### ALERT
Attention state with:
- Flashing orange LEDs
- Arms raised
- Alert sound pattern

## Future Development

- [ ] Bluetooth remote control app
- [ ] OLED display faces/emotions
- [ ] Expanded voice command vocabulary
- [ ] Autonomous behavior modes
- [ ] Web interface control
- [ ] Advanced AI personality responses

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Otto DIY](https://www.ottodiy.com/) - Base robot platform
- [Adafruit](https://www.adafruit.com/) - NeoPixel library
- [DFRobot](https://www.dfrobot.com/) - Voice recognition module

---

<p align="center">
  Made with ❤️ by Eric B
</p>
