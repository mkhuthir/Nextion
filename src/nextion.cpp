
/*  
 *   Nextion Display Example to set text component
 *   Muthanna Alwahash 2021
 *   
 */

#include "nextion.h"

//-------------------------------------------------------------------------------------------------------------
// Class Constructor: Check if Hardware or Software Serial to be used.
//-------------------------------------------------------------------------------------------------------------
#if defined(USE_SOFTWARE_SERIAL)
    Nextion::Nextion(SoftwareSerial &next, uint32_t baud): nextion(&next){
        nextion->begin(baud);
        nextion->flush();
    }
#else
    Nextion::Nextion(HardwareSerial &next, uint32_t baud): nextion(&next){
        nextion->begin(baud);
        nextion->flush();
    }
#endif

//-------------------------------------------------------------------------------------------------------------
// Acknowledge Command
//-------------------------------------------------------------------------------------------------------------
boolean Nextion::ackCommand(void)
{
  uint8_t bytes[4] = {0};
  nextion->setTimeout(20);
  
  if (sizeof(bytes) != nextion->readBytes((char *)bytes, sizeof(bytes))){
    return false;
  }

  if((bytes[1]==0xFF)&&(bytes[2]==0xFF)&&(bytes[3]==0xFF)){
      switch (bytes[0]) {
          case 0x00:
            return false; 
            break;

          case 0x01:
            return true; 
            break;

          default: 
            return false;
            break;
      }
  }

  return false;
}


//-------------------------------------------------------------------------------------------------------------
// Send Command
//-------------------------------------------------------------------------------------------------------------
void Nextion::sendCommand(const char* cmd){
  while (nextion->available()){
	    nextion->read();
  }
  nextion->print(cmd);
  nextion->write(0xFF);
  nextion->write(0xFF);
  nextion->write(0xFF);
}

//-------------------------------------------------------------------------------------------------------------
// Initite Class
//-------------------------------------------------------------------------------------------------------------
boolean Nextion::init(const char* pageId){
  
  sendCommand("");
  ackCommand();

  String page = "page " + String(pageId);
  sendCommand(page.c_str());
  delay(50);
  return ackCommand();
}

//-------------------------------------------------------------------------------------------------------------
// Set Component Text
//-------------------------------------------------------------------------------------------------------------
boolean Nextion::setComponentText(String component, String txt){
  String componentText = component + ".txt=\"" + txt + "\"";
  sendCommand(componentText.c_str());
  return ackCommand();
}

//-------------------------------------------------------------------------------------------------------------
// Set Component Value
//-------------------------------------------------------------------------------------------------------------
boolean Nextion::setComponentValue(String component, int value)
{
    String compValue = component +".val=" + value;
    sendCommand(compValue.c_str());
    return ackCommand();
}
