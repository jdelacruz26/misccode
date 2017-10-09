/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2017, IGMR-RWTH Aachen University
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of SRI International nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
/**
  * \author Jorge De La Cruz
  * \email delacruz@igmr.rwth-aachen.de
  * \version 0.1
  * \date September 29, 2017
  */

/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define MOTOR_ID 1

/*********************** Control table defines ************************/
#define TORQUE_ENABLE 64
#define INPUT_VOLTAGE 144
#define PRESENT_POS 132
#define PRESENT_CURRENT 126
#define GOAL_POSITION 116
#define OPERATING_MODE 11
#define GOAL_CURRENT 102
#define PROFILE_VELOCITY 112
#define PRESENT_TEMPERATURE 146
#define MAXIMUM_POSITION 48
#define HOMING_OFFSET 20
#define MOVING_STATUS 122
/************** 485 EXP switch, LED definces for 485 EXP device ********/
#define BUTTON1 16
#define BUTTON2 17
#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 20
#define USER_BUTTON 23

Dynamixel Dxl(DXL_BUS_SERIAL3);


/*********************** constants definition ******************************/
float read_goal_current;
float read_goal_position;
float read_current_position;
float current_current;
int current_position;
int torque_status;
int ref_pos;
float input_voltage;
int operating_mode;
float present_temperature;
int red_led_state;
int green_led_state;


/*********************** initializing values ********************************/
float closed_position_rev = 7 ;//number of revolutions
float open_position_rev = 0; //initial position, 0 rev.
float closed_current_A = 0.15; //target current in A. Max value = 0.50
float open_current_A = 0.18; //target current in A. Max value = 0.50
float profile_velocity_rps = 0.7; //revolution per second (RPS). Max value = 1.45
int pos_threshold = 57; //~5°
int open_status = 0;
int closed_status = 0;
int open_out_of_range = 0;
int closed_out_of_range = 0;

/********************* transformation ***************************************/
int closed_position = round(closed_position_rev*4095);
int open_position = round(open_position_rev*4095);
int closed_current = round(closed_current_A*1000/1.34);
int open_current = round(open_current_A*1000/1.34);
int profile_velocity = round(profile_velocity_rps*60/0.229);

void setup() {
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps
  Dxl.begin(1);
  delay(1000); // we wait for one second in order to give time the controller.
  //ref_pos = Dxl.readDword(MOTOR_ID, PRESENT_POS);
  Dxl.writeDword(MOTOR_ID, PROFILE_VELOCITY, profile_velocity);
  Dxl.writeDword(MOTOR_ID, MAXIMUM_POSITION, 4095);
  Dxl.writeDword(MOTOR_ID, HOMING_OFFSET, 0);
  Dxl.writeByte(MOTOR_ID, OPERATING_MODE, 5);//Operating mode is set to current-based Position Control mode up.
  //Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);//Torque must be enable in order to drive the motor.

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(USER_BUTTON, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  delay(1000);
}

//Dxl.writeDword(MOTOR_ID, GOAL_POSITION, goal_position);
void loop(){
  current_position = Dxl.readDword(MOTOR_ID, PRESENT_POS);
  torque_status = Dxl.readByte(MOTOR_ID, TORQUE_ENABLE);

  if(digitalRead(BUTTON2)== LOW && digitalRead(BUTTON1)== HIGH){
    torque_status = Dxl.readByte(MOTOR_ID, TORQUE_ENABLE);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    if(torque_status == 0){
      digitalWrite(BLUE_LED, LOW);
      Dxl.writeDword(MOTOR_ID, PROFILE_VELOCITY, profile_velocity);
      Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);
    }
    Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);
    Dxl.writeWord(MOTOR_ID, GOAL_CURRENT, open_current);
    Dxl.writeDword(MOTOR_ID, GOAL_POSITION, open_position);
    delay(500);
    getSensor(0);
    while(Dxl.readByte(MOTOR_ID, MOVING_STATUS)==1){
      delay(1000);
      getSensor(3);
    }
    Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,0);
    open_status = 1;
    closed_status = 0;
    open_out_of_range = 0;
    closed_out_of_range = 0;
    digitalWrite(BLUE_LED, HIGH);
    //ref_pos = Dxl.readDword(MOTOR_ID, PRESENT_POS);
    //delay(14000);
  }
  if(digitalRead(BUTTON2) == HIGH && digitalRead(BUTTON1)== LOW){
    torque_status = Dxl.readByte(MOTOR_ID, TORQUE_ENABLE);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    if(torque_status == 0){
      digitalWrite(BLUE_LED, LOW);
      Dxl.writeDword(MOTOR_ID, PROFILE_VELOCITY, profile_velocity);
      Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);
    }
    Dxl.writeWord(MOTOR_ID, GOAL_CURRENT, closed_current);
    Dxl.writeDword(MOTOR_ID, GOAL_POSITION, closed_position);
    delay(500);
    getSensor(1);
    while(Dxl.readByte(MOTOR_ID, MOVING_STATUS)==1){
      delay(1000);
      getSensor(3);
    }
    ref_pos = Dxl.readDword(MOTOR_ID, PRESENT_POS);
    Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,0);
    open_status = 0;
    closed_status = 1;
    open_out_of_range = 0;
    closed_out_of_range = 0;
    digitalWrite(BLUE_LED, HIGH);
    //delay(14000);
  }

  if(digitalRead(BUTTON1)== HIGH && digitalRead(BUTTON2)== HIGH){
    torque_status = Dxl.readByte(MOTOR_ID,TORQUE_ENABLE);
    delay(1000);
    if(torque_status == 1){
      ref_pos = Dxl.readDword(MOTOR_ID, PRESENT_POS);
      Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,0);
      digitalWrite(BLUE_LED, HIGH);
      delay(1000);
    }

    if(torque_status == 0){
      Dxl.writeDword(MOTOR_ID, PROFILE_VELOCITY, profile_velocity);
      //Dxl.writeDword(MOTOR_ID, HOMING_OFFSET, ref_pos);
      Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);
      digitalWrite(BLUE_LED, LOW);
      delay(1000);
    }
    torque_status = Dxl.readByte(MOTOR_ID, TORQUE_ENABLE);
    //SerialUSB.println(Dxl.readDword(MOTOR_ID, PRESENT_POS));
  }
  delay(1000);
  if(torque_status == 0 && digitalRead(BLUE_LED)==0){
    digitalWrite(BLUE_LED, HIGH);
  }
  if(torque_status == 1 && digitalRead(BLUE_LED)==1){
    digitalWrite(BLUE_LED, LOW);
  }
  if(current_position > (open_position+pos_threshold) && open_status==1 || open_out_of_range == 1){
    green_led_state = digitalRead(GREEN_LED);
    if(green_led_state == HIGH){
      digitalWrite(GREEN_LED, LOW);
    }
    else{
      digitalWrite(GREEN_LED, HIGH);
    }
    open_out_of_range = 1;
    closed_out_of_range = 0;
  }
  if(((closed_position-pos_threshold)> current_position || current_position > (closed_position+pos_threshold)) && closed_status ==1 || closed_out_of_range == 1){
    red_led_state = digitalRead(RED_LED);
    if(red_led_state == HIGH){
      digitalWrite(RED_LED, LOW);
    }
    else{
      digitalWrite(RED_LED, HIGH);
    }
    open_out_of_range = 0;
    closed_out_of_range = 1;
  }
  
  getSensor(3);
}

int getSensor(int a){
  read_current_position = Dxl.readDword(MOTOR_ID, PRESENT_POS)/4095.0; // Read present position
  torque_status = Dxl.readByte(MOTOR_ID, TORQUE_ENABLE);
  input_voltage = Dxl.readWord(MOTOR_ID, INPUT_VOLTAGE)/10.0;
  operating_mode = Dxl.readWord(MOTOR_ID, OPERATING_MODE);
  current_current = Dxl.readWord(MOTOR_ID, PRESENT_CURRENT)*1.34;
  read_goal_current = Dxl.readWord(MOTOR_ID, GOAL_CURRENT)*1.34;
  read_goal_position = Dxl.readWord(MOTOR_ID, GOAL_POSITION)/4095.0;
  present_temperature = Dxl.readByte(MOTOR_ID,PRESENT_TEMPERATURE);


  delay(1000);
  if(a==1){
    SerialUSB.print("================================");
    SerialUSB.print("Closed state data");
    SerialUSB.println("================================");

  }
  if(a==0){
    SerialUSB.print("================================");
    SerialUSB.print("Open state data");
    SerialUSB.println("================================");
  }
  SerialUSB.println("----------------");
  SerialUSB.print("Goal Position[rev]: ");
  SerialUSB.println(read_goal_position);
  SerialUSB.print("Present Position[rev]: ");
  SerialUSB.println(read_current_position);
  SerialUSB.print("Goal Current[mA]: ");
  SerialUSB.println(read_goal_current);
  SerialUSB.print("Current Current[mA]: ");
  SerialUSB.println(current_current);
  SerialUSB.print("Torque enable status: ");
  SerialUSB.println(torque_status);
  SerialUSB.print("Input Voltage[V]: ");
  SerialUSB.println(input_voltage);
  SerialUSB.print("Temperature[C]: ");
  SerialUSB.println(present_temperature);
  //SerialUSB.print("Operating Mode: ");
  //SerialUSB.println(operating_mode);

  return 0;
}
