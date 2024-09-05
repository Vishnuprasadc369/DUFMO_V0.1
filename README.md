# DUFMO - The ESP32-Based Cute Robot with Camera Integration

DUFMO is an open-source robot project built around the ESP32 microcontroller, now enhanced with an **ESP32-CAM** module for real-time video streaming and image capture. Designed for hobbyists and makers, this robot integrates simple yet powerful hardware to offer interactive features like movement control, obstacle detection, touch-based feedback, and now, vision capabilities. DUFMO’s design is compact, customizable, and ideal for learning robotics, sensors, and embedded systems.

![DUFMO Robot](circuit/DUFMo.jpg)

## Key Features
- **ESP32 Microcontroller**: Acts as the robot’s brain, offering built-in Wi-Fi and Bluetooth capabilities for remote control and wireless communication.
- **ESP32-CAM Module**: Provides real-time video streaming and image capture, enabling DUFMO to "see" its surroundings for advanced projects like object tracking and surveillance.
- **OLED Display**: Displays status updates or visual feedback for easy interaction.
- **Motor Control via L293D**: A dual motor setup controlled by an L293D motor driver allows DUFMO to move forward, backward, and turn.
- **Touch Sensor**: Enables user interaction by responding to touch.
- **IR Obstacle Detection**: Detects objects in DUFMO’s path, allowing it to avoid collisions.

## Hardware Components
- **ESP32** microcontroller for robot control
- **ESP32-CAM** module for vision capabilities
- **OLED display** for user feedback
- **L293D motor driver** to control two DC motors
- **Touch sensor** for interaction
- **IR sensor** for obstacle detection

## Project Objectives
- **Learning Platform**: Explore ESP32 programming, motor control, sensor integration, and now vision processing using the ESP32-CAM.
- **Interactive and Visual**: DUFMO responds to touch and can avoid obstacles, while the ESP32-CAM allows for video streaming, making the robot more interactive.
- **Expandability**: With the ESP32-CAM, DUFMO’s functionality is greatly enhanced, opening up possibilities for advanced projects like object recognition, surveillance, and more.

## Getting Started
Follow the instructions in the repository to:

1. Assemble the hardware, including the ESP32 and ESP32-CAM.
2. Flash the ESP32 with the provided code to bring DUFMO to life.
3. Stream video from the ESP32-CAM and control the robot wirelessly.

---

Happy Building!
