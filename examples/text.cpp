/*  
 *   Nextion Display Example to set text component
 *   Muthanna Alwahash 2021
 *   
 */

#include <SoftwareSerial.h>
#include <Nextion.h>

SoftwareSerial nextion(11, 10); // Nextion TX to pin 11 and RX to pin 10 of Arduino

Nextion nexDisp(nextion, 9600); 

void setup() {
  Serial.begin(9600);
  nexDisp.init();

}

void loop() {

  nexDisp.setComponentText("rssi", "50");
  delay(50);
  
  nexDisp.setComponentText("freq", "99.90");
  delay(50);
  
}
