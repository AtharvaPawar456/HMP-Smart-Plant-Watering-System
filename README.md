# Smart Plant Watering System

This project is designed to monitor the soil moisture level and automatically control a water pump (via a relay) and a buzzer based on soil moisture levels. The system also sends the soil moisture and relay state data to ThingSpeak for monitoring.

## Components Used
- ESP8266 (NodeMCU)
- Relay Module
- Buzzer
- Soil Moisture Sensor
- Wi-Fi Router

## Features
1. **Soil Moisture Monitoring**: Reads the soil moisture value using an analog pin.
2. **Automatic Water Pump Control**: Based on the moisture threshold, the system turns on/off the water pump using a relay.
3. **Buzzer Alerts**: The buzzer gives audio feedback when the pump is turned on or off.
4. **ThingSpeak Integration**: The system sends real-time soil moisture and pump status data to ThingSpeak.
5. **Wi-Fi Connectivity**: The system connects to Wi-Fi for sending data.

## Pin Configuration
- **Relay Pin**: Pin 5
- **Buzzer Pin**: Pin D2
- **Soil Moisture Sensor Pin**: Analog Pin A0

## Setup Instructions
1. **Hardware Connections**:
    - Connect the soil moisture sensor to the analog pin (A0).
    - Connect the relay module to pin 5 of the ESP8266.
    - Connect the buzzer to pin D2 of the ESP8266.
    - Power the ESP8266 using a 5V supply or via USB.

2. **Software Configuration**:
    - Install the Arduino IDE if you haven't already.
    - Add the ESP8266 board support to Arduino IDE by going to **File > Preferences** and adding the following URL to the "Additional Boards Manager URLs":
      ```
      http://arduino.esp8266.com/stable/package_esp8266com_index.json
      ```
    - Select **NodeMCU 1.0 (ESP-12E Module)** from the board manager.
    - Install the following libraries if not already available:
      - ESP8266WiFi
      - ESP8266HTTPClient

3. **Code Upload**:
    - Open the Arduino IDE and paste the provided code.
    - Enter your Wi-Fi credentials where specified.
    - Upload the code to your ESP8266 using a USB cable.

4. **ThingSpeak Setup**:
    - Create a ThingSpeak account at [https://thingspeak.com](https://thingspeak.com).
    - Create a new channel and note down your **API key**.
    - Update the API key in the code to match your ThingSpeak channel.

## How It Works
1. The ESP8266 connects to your Wi-Fi network on startup.
2. It continuously reads the soil moisture level from the sensor.
3. If the moisture level is below the threshold (default is 40), the water pump (via the relay) and buzzer will be turned on. 
4. The system sends the moisture level and pump status to ThingSpeak for remote monitoring.
5. After turning on the pump for 15 seconds, the pump is turned off automatically, and the system waits for the next cycle.

## Customization
- You can adjust the moisture threshold by changing the `soilThreshold` value in the code.
- The ThingSpeak API key can be changed in the `apiKey` variable.
- The Wi-Fi credentials should be updated with your network's SSID and password in the respective variables.

## Troubleshooting
- **Wi-Fi Connection Issues**: Ensure the SSID and password are correct. Try restarting the ESP8266 and check the serial monitor for Wi-Fi connection status.
- **ThingSpeak Data Not Updating**: Double-check that the correct API key is being used and that the ESP8266 is connected to the internet.

## License
This project is open-source and available for modification under the MIT License.

## Author
[AtharvaPawar456](https://github.com/AtharvaPawar456)
