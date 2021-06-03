#ifndef PS4_H_
#define PS4_H_

#include <Arduino.h>

namespace ps4 {

// data storage structure to store incomming PS4 values
// This is an expanded structure to make it easier to access the data
struct PS4_data {
  uint8_t  l_joystick_x;
  uint8_t  l_joystick_y;
  uint8_t  r_joystick_x;
  uint8_t  r_joystick_y;
  uint8_t  accel_x;
  uint8_t  accel_y; 
  uint8_t  l2; 
  uint8_t  r2;   
  
  uint8_t  button_left;
  uint8_t  button_down;
  uint8_t  button_right;
  uint8_t  button_up;  
  uint8_t  button_square;
  uint8_t  button_x;
  uint8_t  button_circle;
  uint8_t  button_triangle;   
  
  uint8_t  button_l1;
  uint8_t  button_r1;
  uint8_t  button_l2;
  uint8_t  button_r2;  
  uint8_t  button_share;  
  uint8_t  button_options;
  uint8_t  button_l3;
  uint8_t  button_r3;
  
  uint8_t  button_ps;  
  uint8_t  button_tpad;    
   
  uint8_t  tpad_x;  
  uint8_t  tpad_y;    
  uint8_t  battery;
};

void init(uint8_t i2c_address = 41);
void fetchData();
void printData(Stream* stream);

} // namespace ps4

#endif // PS4_H_
