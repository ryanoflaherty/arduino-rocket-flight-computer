## Arduino Model Rocket Flight Computer
This is a simple collection of programs written to collect data from a model rocket flight. The inspiration for this project came from [ALTDuino](http://www.altduino.de/index.php?all).

__Note:__ I only included the code the I wrote here. You will need to install the appropriate libraries to get this to work (e.g. Adafruit Sensor Libraries, SPIEEP, etc).

### Software
There are three main programs needed to interact with the arduino:
* [Rocket Runtime](https://github.com/ryanoflaherty/arduino-rocket-flight-computer/tree/master/Rocket_Runtime)
  * Collects data from the various flight sensors
* [Read Rocket Data](https://github.com/ryanoflaherty/arduino-rocket-flight-computer/tree/master/Read_Rocket_Data)
  * Reads data from memory and formats it
* [EEPROM Cleanup](https://github.com/ryanoflaherty/arduino-rocket-flight-computer/tree/master/EEPROM_Cleanup)
  * Resets the EEPROM Chip
  
I wanted to give a special shoutout to a bitbucket user [spirilis](https://bitbucket.org/spirilis/) for writing a totally awesome SPI EEPROM library that I was able to take advantage of. You can find his library [SPIEEP here](https://bitbucket.org/spirilis/spieep).

### Hardware
The hardware for this project was fairly straightforward, and I was able to find them online quite easily. Here are the required components:
* Arduino Micro (ATMega32U4 Chipset)
* Adafruit 10-DOF IMU Breakout - L3GD20H + LSM303 + BMP180
* Microchip 25LC512 EEPROM
* Pololu 5V Step-Up Voltage Regulator U1V10F5
* 150 mAh 3.7V LiPoly Battery

### Sample Data
See [rocket.csv](https://github.com/ryanoflaherty/arduino-rocket-flight-computer/blob/master/rocket.csv) for an example of what the data looks like after being read from the Arduino.
