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
- 🎬 **Dual Modes** - Voice-activated OR auto-play demo mode
- 💡 **NeoPixel LED Arms** - Expressive RGB lighting with smooth animations
- 🤖 **Behavioral States** - Multiple emotional states (Dope, Chill)
- 🦿 **Otto DIY Walking** - Full walking, dancing, and gesture capabilities
- 🎵 **Sound Effects** - RTTTL melody playback and Otto sound library
- 📱 **Serial Control** - Control via USB serial for debugging and manual control
- 🔧 **Professional Architecture** - Clean, modular PlatformIO project structure

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
   git clone https://github.com/EricssonB/sbot-robot.git
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

## Build Modes

SBot comes with **two firmware versions** that you can choose from:

### 🎤 Voice Mode (`env:voice`) - Default
**Requires: DFRobot DF2301Q voice recognition module**

Waits for voice commands or serial input to trigger states. Perfect for interactive use.

```bash
# Build and upload voice mode
pio run -e voice -t upload
```

### 🎬 Auto-Play Mode (`env:autoplay`)
**No voice module needed**

Plays the full startup sequence automatically when powered on. Great for demos and showcases.

```bash
# Build and upload auto-play mode
pio run -e autoplay -t upload
```

### Switching Modes in VS Code

1. Click the **PlatformIO icon** (alien head) in the sidebar
2. Under **PROJECT TASKS**, expand the environment you want:
   - `voice` → for voice-activated version
   - `autoplay` → for auto-play demo version
3. Click **Upload**

Or use the environment switcher in the bottom status bar.

### Available Build Environments

| Environment | Board | Voice Module | Description |
|-------------|-------|--------------|-------------|
| `voice` | Uno | Required | Voice-activated (default) |
| `autoplay` | Uno | Not needed | Auto-plays on startup |
| `voice_mega` | Mega | Required | Voice mode for Arduino Mega |
| `autoplay_mega` | Mega | Not needed | Auto-play for Arduino Mega |

### Dependencies

All dependencies are automatically managed by PlatformIO:

- Adafruit NeoPixel
- Servo
- DFRobot_DF2301Q
- Otto DIY Library (included in lib/)

## Usage

### Serial Commands (Both Modes)

Connect via serial monitor at **115200 baud** and use these commands:

| Command | Description |
|---------|-------------|
| `dope` | Run excited celebration state |
| `chill` | Run calm relaxation state |
| `startup` or `demo` | Run full startup sequence |
| `home` | Return to home position |
| `help` | Show available commands |

### Voice Commands (Voice Mode Only)

After waking the voice module with your wake word:

| Command ID | Action |
|------------|--------|
| CMDID 5 | Triggers Dope State |
| CMDID 6 | Triggers Chill State |

> **Note:** Voice commands are configured in the DFRobot DF2301Q module. See DFRobot documentation for setting up custom wake words and command phrases.

## Architecture

```
sbot-robot/
├── platformio.ini        # PlatformIO config (defines build modes)
├── include/
│   ├── config.h          # Pin definitions & constants
│   ├── colors.h          # RGB color definitions
│   ├── melodies.h        # RTTTL melodies
│   └── ...               # Other header files
├── src/
│   └── main.cpp          # Main program (supports both modes)
├── lib/
│   ├── Otto/             # Otto DIY library
│   └── PlayRtttl/        # RTTTL melody player
├── docs/
│   ├── pinout.md         # Wiring reference
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
