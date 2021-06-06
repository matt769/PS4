#include "ps4.h"

#include <Arduino.h>
#include <Wire.h>

namespace ps4 {

PS4::PS4(TwoWire* wire_in, const uint8_t i2c_address_in)
  : new_data_received(false), wire(wire_in), i2c_address(i2c_address_in)
  {
  wire->begin(); // should be no harm in calling again if already done
}

void PS4::parseBuffer() {  
   input.l_joystick_x = buffer[0];
   input.l_joystick_y = buffer[1];
   input.r_joystick_x = buffer[2];
   input.r_joystick_y = buffer[3];
   input.accel_x      = buffer[4];
   input.accel_y      = buffer[5]; 
   input.l2           = buffer[6]; 
   input.r2           = buffer[7]; 

    // 8 values for horizontal, vertical and diagonal directions
   const uint8_t dpad = buffer[8] & 0x0F;
   if((dpad==5) || (dpad==6) || (dpad==7)) input.button_left = true;  else input.button_left = false;
   if((dpad==3) || (dpad==4) || (dpad==5)) input.button_down = true;  else input.button_down = false;
   if((dpad==1) || (dpad==2) || (dpad==3)) input.button_right = true; else input.button_right = false;
   if((dpad==0) || (dpad==1) || (dpad==7)) input.button_up = true;    else input.button_up = false;

   const uint8_t shapes = buffer[8] & 0xF0;
   input.button_square  = (shapes & 0b00010000);
   input.button_x       = (shapes & 0b00100000);
   input.button_circle  = (shapes & 0b01000000);
   input.button_triangle= (shapes & 0b10000000);
  

   const uint8_t more_buttons = buffer[9];
   input.button_l1     = (more_buttons & 0b00000001);
   input.button_r1     = (more_buttons & 0b00000010);
   input.button_l2     = (more_buttons & 0b00000100);
   input.button_r2     = (more_buttons & 0b00001000);
   input.button_share  = (more_buttons & 0b00010000);
   input.button_options= (more_buttons & 0b00100000);
   input.button_l3     = (more_buttons & 0b01000000);
   input.button_r3     = (more_buttons & 0b10000000);

   input.button_ps    = (buffer[10] & 0b00000001);
   input.button_tpad   = (buffer[10] & 0b00000010);
                
   input.tpad_x        = buffer[11]; 
   input.tpad_y        = buffer[12];      
   input.battery       = buffer[13];    
   
   new_data_received = true; 
}

void PS4::fetchData() {
  wire->beginTransmission(i2c_address);
  wire->write(0);                        // Start receiving data from register 0
  wire->endTransmission();
   
  wire->requestFrom(i2c_address, request_num_bytes);
  if(wire->available() == request_num_bytes) {
    uint8_t idx = 0;
    while (wire->available()) {
      buffer[idx++] = wire->read();     
    }
  } else {
    Serial.print("Unexpected buffer size: "); Serial.println(Wire.available()); // DEBUG remove later
    return;
  }
  
  parseBuffer();
}

void printData(Stream* stream, const PS4_data& input) {
  stream->print(input.l_joystick_x); stream->print('\t');
  stream->print(input.l_joystick_y); stream->print('\t');
  stream->print(input.r_joystick_x); stream->print('\t');
  stream->print(input.r_joystick_y); stream->print('\t');
  stream->print(input.accel_x); stream->print('\t');
  stream->print(input.accel_y); stream->print('\t');
  stream->print(input.l2); stream->print('\t');
  stream->print(input.r2); stream->print('\t');
  stream->print(input.button_left); stream->print('\t');
  stream->print(input.button_down); stream->print('\t');
  stream->print(input.button_right); stream->print('\t');
  stream->print(input.button_up  ); stream->print('\t');
  stream->print(input.button_square); stream->print('\t');
  stream->print(input.button_x); stream->print('\t');
  stream->print(input.button_circle); stream->print('\t');
  stream->print(input.button_triangle); stream->print('\t');
  stream->print(input.button_l1); stream->print('\t');
  stream->print(input.button_r1); stream->print('\t');
  stream->print(input.button_l2); stream->print('\t');
  stream->print(input.button_r2  ); stream->print('\t');
  stream->print(input.button_share  ); stream->print('\t');
  stream->print(input.button_options); stream->print('\t');
  stream->print(input.button_l3); stream->print('\t');
  stream->print(input.button_r3); stream->print('\t');
  stream->print(input.button_ps); stream->print('\t');
  stream->print(input.button_tpad); stream->print('\t');
  stream->print(input.tpad_x); stream->print('\t');
  stream->print(input.tpad_y); stream->print('\t');
  stream->print(input.battery); stream->print('\t');
  stream->println();
}

} // namespace ps4
