#include "ps4.h"

#include <Arduino.h>
#include <Wire.h>

namespace ps4 {

namespace {
uint8_t kI2cAddress;
bool initialised = false;
constexpr uint8_t request_num_bytes = 14;

uint8_t buffer[request_num_bytes];
bool new_data_received = false;
PS4_data input;

void parse_buffer() {
  if (!initialised) return;
  
   input.l_joystick_x = buffer[0];
   input.l_joystick_y = buffer[1];
   input.r_joystick_x = buffer[2];
   input.r_joystick_y = buffer[3];
   input.accel_x      = buffer[4];
   input.accel_y      = buffer[5]; 
   input.l2           = buffer[6]; 
   input.r2           = buffer[7]; 
             
   if(((buffer[8]&0x0F)==5) || ((buffer[8]&0x0F)==6) || ((buffer[8]&0x0F)==7)) input.button_left=1;  else input.button_left=0;  //W
   if(((buffer[8]&0x0F)==3) || ((buffer[8]&0x0F)==4) || ((buffer[8]&0x0F)==5)) input.button_down=1;  else input.button_down=0; //S
   if(((buffer[8]&0x0F)==1) || ((buffer[8]&0x0F)==2) || ((buffer[8]&0x0F)==3)) input.button_right=1; else input.button_right=0;  //E
   if(((buffer[8]&0x0F)==0) || ((buffer[8]&0x0F)==1) || ((buffer[8]&0x0F)==7)) input.button_up=1;    else input.button_up=0; //N
   input.button_square  =((buffer[8]&0b00010000)>>4); // SQUARE
   input.button_x       =((buffer[8]&0b00100000)>>5); // X
   input.button_circle  =((buffer[8]&0b01000000)>>6); // CIRCLE
   input.button_triangle=((buffer[8]&0b10000000)>>7); // TRIANGLE

   input.button_l1     =((buffer[9]&0b00000001));    // L1
   input.button_r1     =((buffer[9]&0b00000010)>>1); // R1
   input.button_l2     =((buffer[9]&0b00000100)>>2); // L2
   input.button_r2     =((buffer[9]&0b00001000)>>3); // R2
   input.button_share  =((buffer[9]&0b00010000)>>4); // SHARE
   input.button_options=((buffer[9]&0b00100000)>>5); // OPTIONS
   input.button_l3     =((buffer[9]&0b01000000)>>6); // L3
   input.button_r3     =((buffer[9]&0b10000000)>>7); // R3

   input.button_ps    =((buffer[10]&0b00000001));    // PS4
   input.button_tpad   =((buffer[10]&0b00000010)>>1); // TPAD
                
   input.tpad_x        =buffer[11]; 
   input.tpad_y        =buffer[12];      
   input.battery       =buffer[13];    
   
   new_data_received = true; 
}

}

void init(uint8_t i2c_address) {
  kI2cAddress = i2c_address;
  Wire.begin();
  initialised = true;
}

void fetchData() {
  if (!initialised) return;
  Wire.beginTransmission(kI2cAddress);  // transmit to device
  Wire.write(0);                        // Start receiving data from register 0
  Wire.endTransmission();               // end transmission
   
  Wire.requestFrom(kI2cAddress, request_num_bytes);
  if(Wire.available() == request_num_bytes) {
    uint8_t idx = 0;
    while (Wire.available()) {
      buffer[idx++] = Wire.read();     
    }
  } else {
    Serial.print("Unexpected buffer size: "); Serial.println(Wire.available()); // DEBUG remove later
    return;
  }
  
  parse_buffer();                         // Decode PS4 data
}



void printData(Stream* stream) {
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
