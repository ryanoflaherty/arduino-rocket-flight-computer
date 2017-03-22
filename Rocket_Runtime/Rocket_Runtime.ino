/* Copyright (C) 2017 by Ryan O'Flaherty
 * Distributed under the terms of the GNU Lesser General Public License
 * A copy of this license may be obtained at:
 * http://www.gnu.org/copyleft/lesser.html
 */

#include <SPIEEP.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <string.h>

/********************************************************
EEPROM Encoding

Formatted for .csv - line ending in "" (^M) denotes end of row
Copy from serial terminal to csv - see example in rocket.csv

Line 1: Column names (setup())
Byte 0-4: "Temp,"
Byte 5-9: "Pres,"
Byte 10-13: "Alt,"
Byte 14-18: "Time,"
Byte 19-29: *Empty*

Line 2-N: Rows of data (loop())
Byte 0-4: Temp (C)
Byte 5-6: ", "
Byte 7-12: Pressure (Pa)
Byte 13-14: ", "
Byte 15-20: Altitude (m)
Byte 21-22: ", "
Byte 23-28: Time (ms)
Byte 29: ","

********************************************************/

/* Initialize SPI Connection to EEPROM */
SPIEEP eep(16, 128, 65536); // Microchip 25LC512
#define EEPROM_CSPIN  17  // Chip Select attached to digital pin 17
#define BUF_SIZE  30  // Length of the buffer
#define MAX_ADDR  0xFFE1  // Don't let the program write past this address
#define MAX_TIME  600000  // Only run for 10 min max

/* Global variables for writing to EEPROM */ 
uint32_t addr = 0x0010;   // First EEPROM address
unsigned long time; // Relative time (after program started)
char blink;

/* Assign a unique ID to the sensors */
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

/* Update this with the correct SLP for accurate altitude measurements */
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

/* Initializes all of the sensors */
void initSensors(){
  if(!bmp.begin())
  {
    // There was a problem detecting the BMP180 ... check your connections
    Serial.println("Ooops, no BMP180 detected ... Check your wiring!");
    while(1);
  }
}

/* Setup Function - Begin Serial Communication (Runs Once) */
void setup() {
  delay(1000);  // This is only so the serial port on the computer can keep up
  
  pinMode(13, OUTPUT);  // Initialize Pin 13 LED as output
  blink = 0;
  Serial.begin(115200);
  eep.begin_spi(EEPROM_CSPIN);  // Enable SPI
  //initSensors(); // Initialize the sensors
  Serial.println("Begin test...");

  /* Write the columns of .csv into Storage */
  char init_buf[BUF_SIZE] = {}; // Byte/Char buffer that is written to EEPROM
  strcat(init_buf, "Temp,Pres,Alt,Time,");
  if (!eep.writen(addr, init_buf, BUF_SIZE)) {
    Serial.println("Error writing  to address=0x0100");
  } else {
    addr += uint32_t(BUF_SIZE); // Increment the address for next write
  }
  
}

/* Main Code (Runs Repeatedly) */
void loop() {
  /* Initialize Runtime Variables */
  time = millis();  // Get the current time since the program started
  //sensors_event_t bmp_event;  // New sensor event for BMP180
  char buf[BUF_SIZE] = {}; // Byte/Char buffer that is written to EEPROM
  char temp_buf[5] = {};  // String for temperature reading
  char pres_buf[6] = {};  // String for pressure reading
  char alt_buf[6] = {};   // String for altitude calculation
  char time_buf[6] = {};  // String for altitude calculation
  
  /* Convert unsigned long to char array */
  String time_s(time, 6);  // String for altitude calculation
  time_s.toCharArray(time_buf, 6);  // Load into char array

  /* Constrain our Program to 10 min or ~17,000 writes (per our encoding) */
  if (time > MAX_TIME || addr >  MAX_ADDR){
    digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
    while(1);
  }

  /* Blink LED so we know we are recording */
  if(blink){
    digitalWrite(13, HIGH); // LED on 
    blink = 0;  // Next time off
  } else {
    digitalWrite(13, LOW);  // LED on
    blink = 1;  // Next time on
  }
  
  /* Calculate the altitude using the barometric pressure sensor */
  
  //bmp.getEvent(&bmp_event);
  //if (bmp_event.pressure)
  //{
    /* Get ambient temperature in C, load into buffer */
    //float temperature;
    //bmp.getTemperature(&temperature);
    //dtostrf(temperature, 5, 2, temp_buf);
    //strncat(buf, temp_buf, 5);
    //strcat(buf, ", ");

    /* Get atmospheric pressure in Pa, load into buffer */
    //float pressure;
    //bmp.getPressure(&pressure);
    //dtostrf(pressure, 6, 0, pres_buf);
    //strncat(buf, pres_buf, 6);
    //strcat(buf, ", ");
    
    /* Convert atmospheric pressure, SLP and temp to altitude, write to buffer */
    //float altitude;
    //altitude = bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, temperature);
    //dtostrf(altitude, 5, 2, alt_buf);
    //strncat(buf, alt_buf, 6);
    //strcat(buf, ", ");
  //}

  /* Add a relative time stamp */
  strncat(buf, time_buf, 6);
  strcat(buf, ",");
  
  Serial.print(buf);
  if (!eep.writen(addr, buf, BUF_SIZE)) {
    Serial.println("Error writing  to address=0x0100");
  } else {
    addr += uint32_t(BUF_SIZE); // Increment the address for next write
    Serial.print(" @ 0x");
    Serial.print(addr, HEX);
    Serial.println("");
  }

  delay(100);
}
