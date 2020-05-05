# nodemcu-sensor
A simple arduino sketch that sends temperature, pressure, humidity and light level via mqtt

# Required hardware
- [NodeMcu V3](https://www.aliexpress.com/item/32665100123.html?spm=a2g0s.9042311.0.0.105d4c4dNoFD6G)
- [BME280](https://www.aliexpress.com/item/32849462236.html?spm=a2g0s.9042311.0.0.105d4c4dNoFD6G) (Temperature, Pressure and Humidity sensor)
- [BH1750](https://www.aliexpress.com/item/32421754536.html?spm=a2g0s.9042311.0.0.105d4c4dNoFD6G) (Light sensor)

# Required software
- [nodemcu-flasher](https://github.com/nodemcu/nodemcu-flasher)
- [NodeMCU Firmware](https://github.com/sleemanj/ESP8266_Simple/raw/master/firmware/ai-thinker-0.9.5.2-115200.bin)
- [Arduino IDE](https://www.arduino.cc/en/main/software)


# Required libraries
- [Adafruit BME280 library](https://github.com/adafruit/Adafruit_BME680)
- [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)
- [MQTT Library for Arduino](https://github.com/256dpi/arduino-mqtt)
- [BH1750 library](https://github.com/claws/BH1750)

# Wiring
![Wiring](https://github.com/brantje/nodemcu-sensor/raw/master/wiring.png)

# Setup
- Follow [this](https://www.instructables.com/id/Getting-Started-With-ESP8266LiLon-NodeMCU-V3Flashi/) setup guide.
  
- Import the required libaries
  
- Paste the code from this repo

- Edit the config

- Press upload

- After uploading you should see some messages printed to the serial monitor.
  - You can open the serial monitor from the tools menu.

- When confirmed working correctly, off you go.

