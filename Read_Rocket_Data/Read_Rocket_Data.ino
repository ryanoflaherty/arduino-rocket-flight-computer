#include <SPIEEP.h>
#include <SPI.h>

SPIEEP eep(16, 128, 65536); // Microchip 25LC512
#define EEPROM_CSPIN 17  // Chip Select attached to pin 10
#define BUF_SIZE 30 // How much memory to read from at a time
#define MAX_ADDR  0xFFE1  // Don't let the program read past this address
uint32_t addr = 0x0010; // First EEPROM address

void setup() {
  delay(1000);
  
  Serial.begin(9600);
  eep.begin_spi(EEPROM_CSPIN);
  Serial.println("Begin reading...");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  if (addr >  MAX_ADDR){
    digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
    while(1);
  }
  
  byte buf[BUF_SIZE];
  int i;
  
  if (!eep.readn(addr, buf, BUF_SIZE)) {
    Serial.println("Error reading 500 bytes from address=0x1F0E");
  } else {
    for (i=0; i < BUF_SIZE; i++) {
      Serial.write(buf[i]);
    }
    addr += uint32_t(BUF_SIZE);
    Serial.println("");
    /*
    Serial.print(" @ 0x");
    Serial.print(addr, HEX);
    Serial.println("");
    */
  }
}
