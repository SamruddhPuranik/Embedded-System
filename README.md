# Vehicle Indicator System (Push Button + BLE Control)

This project simulates a car indicator system using an Arduino Uno, two push buttons, two LEDs, and optional BLE control via a mobile phone.

## 📌 Features

- Left/right turn indicator control via push buttons (1-second press detection)
- Hazard light mode via simultaneous button press
- LED blinking at 300ms rate using PWM
- UART logging of all actions (saved in this repo)
- Optional BLE command input support (commands: `L`, `R`, `H`)
- 100ms scheduler used for task execution

## 🔧 Hardware Used

- Arduino Uno
- 2 Push Buttons
- 2 LEDs (Left and Right indicators)
- Jumper Wires
- HC-05 (optional, for BLE control)

## 📁 File Structure

- `indicator_system.ino` – Main Arduino code
- `UART_Log.txt` – UART log file recorded from Serial Monitor
- `BLE_Control_Snippet.txt` – (Optional) BLE integration snippet for extended control
- `README.md` – This file

## 🔌 BLE Control (Optional)

If a BLE module is connected (like HC-05), send the following commands from a mobile app:

- `L` → Activate Left Indicator
- `R` → Activate Right Indicator
- `H` → Toggle Hazard Mode

These commands are processed in real-time alongside the push buttons.

## 🧰 Tools Used

- Arduino IDE
- Serial Monitor (for logging)
- GitHub (for version control and submission)

## 📃 Assignment Notes

This project satisfies the embedded software assignment requirements:

- Push-button control system
- PWM-based blinking for indicators
- UART-based logging
- 100ms periodic scheduler
- Documented BLE extension

