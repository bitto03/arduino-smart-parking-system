# Arduino Smart Parking System with Environment Monitoring

This project is a smart parking system built using Arduino that not only manages parking slot availability using IR sensors and a servo gate, but also monitors the surrounding temperature and humidity using a DHT11 sensor. The system provides real-time updates via a 16x2 I2C LCD display.

## Features

- Detects vehicle entry and exit using IR sensors.
- Controls a servo motor to open/close the parking gate.
- Keeps track of available parking slots.
- Displays "Parking Full" when no slots are available.
- Displays real-time temperature and humidity data using DHT11 sensor.
- LCD alternates between slot availability and environmental data every 5 seconds.

## Hardware Components

- Arduino Uno (or compatible board)
- IR Sensors (2 units)
- Servo Motor
- I2C 16x2 LCD Display
- DHT11 Temperature and Humidity Sensor
- Jumper wires and Breadboard
- USB Cable for programming

## Pin Configuration

- IR1 Sensor: Digital Pin 2
- IR2 Sensor: Digital Pin 3
- Servo Motor: Digital Pin 4
- DHT11 Sensor: Digital Pin 5
- LCD: I2C (default address 0x27)

## How It Works

1. **Car Entry**:
   - When IR1 is triggered and slots are available, the gate opens and the slot count decreases.
   - If the parking is full, a message is shown and the gate remains closed.

2. **Car Exit**:
   - When IR2 is triggered, the gate opens and the slot count increases.

3. **Display Behavior**:
   - The LCD alternates every 5 seconds between:
     - Welcome message and available slots
     - Temperature and humidity data

## Libraries Used

- `Wire.h`
- `LiquidCrystal_I2C.h`
- `Servo.h`
- `DHT.h`

Make sure all required libraries are installed in your Arduino IDE.

## Getting Started

1. Connect all hardware components as described above.
2. Upload the code to your Arduino board using the Arduino IDE.
3. Open the Serial Monitor (optional) to observe any debug information.
4. Observe the LCD displaying the slot count and environment data in cycles.

## Developer
Developed and maintained by BHB Enterprise (Basirul Hasin ).
