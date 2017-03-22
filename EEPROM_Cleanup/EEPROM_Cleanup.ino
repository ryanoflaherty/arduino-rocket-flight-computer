/* Copyright (C) 2017 by Ryan O'Flaherty
 * Distributed under the terms of the GNU Lesser General Public License
 * A copy of this license may be obtained at:
 * http://www.gnu.org/copyleft/lesser.html
 */

#include <SPIEEP.h>
#include <SPI.h>

SPIEEP eep(16, 128, 65536); // Microchip 25LC512
#define EEPROM_CSPIN 17  // Chip Select attached to pin 10

void setup() {
  delay(1000);
  Serial.begin(9600);
  eep.begin_spi(EEPROM_CSPIN);
  Serial.println("Begin Cleanup...");
}

void loop() {
  delay(1000);
  Serial.println("Erasing chip...");
  if(eep.chip_erase()){
    Serial.println("Success");
  } else {
    Serial.println("Error - something went wrong.");
  }
  while(1);
}
