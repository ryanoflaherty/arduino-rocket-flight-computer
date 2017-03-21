#include <SPIEEP.h>
#include <SPI.h>

SPIEEP eep(16, 128, 65536); // Microchip 25LC512
#define EEPROM_CSPIN 17  // Chip Select attached to pin 10

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  eep.begin_spi(EEPROM_CSPIN);
  Serial.println("Begin Cleanup...");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("Erasing chip...");
  if(eep.chip_erase()){
    Serial.println("Success");
  } else {
    Serial.println("Error - something went wrong.");
  }
  while(1);
}
