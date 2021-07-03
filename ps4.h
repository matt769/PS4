#ifndef PS4_H_
#define PS4_H_

#include <Arduino.h>
#include <Wire.h>

namespace ps4 {

struct PS4_data {
  uint8_t  l_joystick_x; // left (0) to right (255)
  uint8_t  l_joystick_y; // up (0) to down (255)
  uint8_t  r_joystick_x; // left (0) to right (255)
  uint8_t  r_joystick_y; // up (0) to down (255)
  uint8_t  accel_x; // roll right (0) to roll left (255)
  uint8_t  accel_y; // pitch up (0) to pitch down (255)
  uint8_t  l2; // 0-255 value as well as separate on/off indicator (button_l2)
  uint8_t  r2; // 0-255 value as well as separate on/off indicator (button_r2)
  
  bool  button_left;
  bool  button_down;
  bool  button_right;
  bool  button_up;  
  bool  button_square;
  bool  button_x;
  bool  button_circle;
  bool  button_triangle;   
  
  bool  button_l1;
  bool  button_r1;
  bool  button_l2;
  bool  button_r2;  
  bool  button_share;  
  bool  button_options;
  bool  button_l3;
  bool  button_r3;
  
  bool  button_ps;  
  bool  button_tpad;    
   
  uint8_t  tpad_x; // left (0) to right (255)
  uint8_t  tpad_y; // up (0) to down (255)   
  uint8_t  battery;
};

class PS4 {
  public:
    PS4(TwoWire* wire, uint8_t i2c_address = 41);
    void fetchData();
    PS4_data input;
    bool new_data_received;
    static constexpr uint8_t request_num_bytes = 14;
  private:
    TwoWire* wire;
    uint8_t i2c_address;
    uint8_t buffer[request_num_bytes];
    void parseBuffer();
  
};

void printData(Stream* stream, const PS4_data& data);

} // namespace ps4

#endif // PS4_H_
