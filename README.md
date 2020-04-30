# nodemcu-sensor
A simple arduino sketch that sends temperature, pressure, humidity and light level via mqtt

# WIP WIP WIP WIP WIP WIP WIP

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

# Setup
- Connect the ESP to the PC
- Use nodemcu-flasher to flash the firmware from the firmware folder
  - Tab config: Select firmware offset 0x00000
  - Tab advanced: Baudrate 9600, Flash size 4MByte, Flash speed: 40Mhz, SPI Mode: DIO
  
- After flashing start the Arduino IDE
- Go to File > Preferences
- Copy below URL into the Additional Board Manager URLs text box situated on the bottom of the window
`http://arduino.esp8266.com/stable/package_esp8266com_index.json`

- Go to Tools > Board > Boards Manager
- Search for esp8266 and install

- Make sure the correct board is selected:
  - Arduino IDE > Tools > Board > NodeMCU 0.9 (ESP-12 Module) 
- Make sure the correct COM port is selected:
  - Tools -> Port -> COM
- Make sure upload speed is set to 115200  

- Paste the code from this repo

- Edit the config

- Press upload

- After uploading you should see some messages printed to the serial monitor.
  - You can open the serial monitor from the tools menu.

- When confirmed working correctly, off you go.

