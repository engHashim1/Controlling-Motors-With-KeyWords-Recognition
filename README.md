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

License

This project is open-source and available for modification and distribution.
