# Controlling-Motors-With-KeyWords-Recognition
This project aims to controlling motors wirelessly with voice commands

Voice-Controlled Motor System
Project Overview

This project enables voice-controlled movement of a motor system using an ESP32 microcontroller. The system consists of:

    A web interface for voice command input

    A PHP backend to process and store commands

    An ESP32 that retrieves commands and controls motors accordingly

Components

    Web Interface (speech_webapi.html):

        Voice recognition using the Web Speech API

        Arabic/English interface for voice commands

        Real-time command display

    Backend PHP Scripts:

        save_command.php: Stores voice commands in a database

        get_command.php: Retrieves the latest command for the ESP32

    ESP32 Firmware (VoiceRC.ino):

        Connects to WiFi

        Polls the server for new commands

        Controls motors based on received commands

        Includes auto-stop safety feature

Setup Instructions
1. Database Setup

    Create a MySQL database named motor_control

    Create a table named commands with:
    sql

    CREATE TABLE commands (
      id INT AUTO_INCREMENT PRIMARY KEY,
      command VARCHAR(50) NOT NULL,
      timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );

2. Web Server Setup

    Place these files in your web server's root directory:

        speech_webapi.html

        save_command.php

        get_command.php

    Ensure PHP and MySQL are properly configured

3. ESP32 Setup

    Upload the VoiceRC.ino sketch to your ESP32

    Modify these variables in the code:

        ssid: Your WiFi network name

        password: Your WiFi password

        serverUrl: URL to your get_command.php file

    Connect the motors to the specified GPIO pins:

        IN1: GPIO 26

        IN2: GPIO 27

        IN3: GPIO 14

        IN4: GPIO 12

Usage

    Open speech_webapi.html in a Chrome browser

    Click the microphone button and speak commands:

        "forward" - Moves motors forward

        "backward" - Moves motors backward

        "stop" - Stops the motors

    The ESP32 will automatically execute the commands

Safety Features

    Auto-stop after 5 seconds of inactivity

    Motor stop on "stop" command

    Secure command transmission

Supported Commands

    Forward

    Backward

    Stop

Troubleshooting

    Ensure all components are properly connected

    Verify WiFi credentials in the ESP32 code

    Check server URLs and database connections

    Use Chrome for best voice recognition results

Future Enhancements

    Add more movement commands (left, right)

    Implement speed control

    Add authentication for the web interface

    Support for multiple languages


    Adding Brushless (BLDC) Motor Support
Additional Requirements for Brushless Motor:

    Additional Hardware Components:

        Brushless (BLDC) motor with ESC (Electronic Speed Controller)

        Suitable LiPo battery (e.g., 3S 11.1V)

        ESC programmer (optional for fine-tuning settings)

    Circuit Modifications:

        Replace H-Bridge circuit with ESC

        Connect PWM signal from ESP32 to ESC signal input

        Ensure proper power supply (ESC typically handles motor power directly)

        Add capacitor bank if using high-power motors

    Code Modifications (VoiceRC.ino):

cpp

// Add these constants
const int ESC_PWM_PIN = 13; // PWM pin connected to ESC
const int MIN_PULSE = 1000; // Minimum throttle (stop)
const int MAX_PULSE = 2000; // Maximum throttle

// In setup():
ledcSetup(0, 50, 16); // 50Hz PWM, 16-bit resolution
ledcAttachPin(ESC_PWM_PIN, 0);
ledcWrite(0, MIN_PULSE); // Initialize with motor stopped
delay(5000); // ESC arming delay

// Replace motor functions with:
void forward() {
  ledcWrite(0, 1500); // Medium speed forward
  Serial.println("BLDC Moving Forward");
}

void backward() {
  ledcWrite(0, 1300); // Medium speed reverse (if ESC supports)
  Serial.println("BLDC Moving Backward");
}

void stopMotors() {
  ledcWrite(0, MIN_PULSE);
  Serial.println("BLDC Stopped");
}

    ESC Configuration:

        Calibrate ESC throttle range

        Set braking mode if needed

        Configure low-voltage cutoff matching your battery

        Enable/disable reverse rotation as required

    Safety Considerations:

        Always connect battery to ESC last

        Keep hands clear during arming sequence

        Use proper current-rated connectors

        Monitor motor temperature during initial tests

    Web Interface Changes:

        No changes required to HTML/PHP files

        Same voice commands will work ("forward", "backward", "stop")

    Additional Commands (Optional):

cpp

// Add to loop() handling:
else if (payload.equalsIgnoreCase("slow")) {
  ledcWrite(0, 1200); // Slow speed
}
else if (payload.equalsIgnoreCase("fast")) {
  ledcWrite(0, 1800); // Fast speed
}

Note: Some ESCs may require different signal values or calibration procedures. Always consult your specific ESC documentation before implementation.

License

This project is open-source and available for modification and distribution.
