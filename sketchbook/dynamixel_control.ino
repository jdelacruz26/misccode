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

/* Control table defines */
#define TORQUE_ENABLE 64
#define INPUT_VOLTAGE 144
#define PRESENT_POS 132
#define PRESENT_CURRENT 126
#define GOAL_POSITION 116
#define OPERATING_MODE 11
#define GOAL_CURRENT 102
#define PROFILE_VELOCITY 112
/* 485 EXP switch, LED definces for 485 EXP device */
#define BUTTON1 16
#define BUTTON2 17
#define RED_LED 18
#define GREEN_LED 19
#define BLUE_LED 20

Dynamixel Dxl(DXL_BUS_SERIAL3); 

 
/*constants definition*/
float read_goal_current;
float read_goal_position;
float current_position;
float current_current;
int torque_status;
float input_voltage;
int operating_mode;
/*initializing values*/
float closed_position_rev = 5 ;//number of revolutions
float open_position_rev = 0; //initial position, 0 rev.
float closed_current_A = 0.05; //target current in A. Max value = 0.50
float open_current_A = 0.01; //target current in A. Max value = 0.50
float profile_velocity_rps = 0.5; //revolution per second (RPS). Max value = 1.45
/*transformation*/
int closed_position = int(closed_position_rev*4095);
int open_position = int(open_position_rev*4095);
int closed_current = int(closed_current_A*1000/1.34);
int open_current = int(open_current_A*1000/1.34);
int profile_velocity = int(profile_velocity_rps*60/0.229);

void setup() {
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps  
  Dxl.begin(1);
  delay(1000); // we wait for one second in order to give time the controller.
  Dxl.writeByte(MOTOR_ID, OPERATING_MODE, 5);//Operating mode is set to current-based Position Control mode up.
  Dxl.writeDword(MOTOR_ID, PROFILE_VELOCITY, profile_velocity);
  Dxl.writeByte(MOTOR_ID,TORQUE_ENABLE,1);//Torque must be enable in order to drive the motor.
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

//Dxl.writeDword(MOTOR_ID, GOAL_POSITION, goal_position);   
void loop(){
  if(digitalRead(BUTTON1)== HIGH){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    Dxl.writeWord(MOTOR_ID, GOAL_CURRENT, closed_current);
    Dxl.writeDword(MOTOR_ID, GOAL_POSITION, 0);
    delay(11000);
    getSensor(1);
  }
  if(digitalRead(BUTTON2) == HIGH){
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Dxl.writeWord(MOTOR_ID, GOAL_CURRENT, open_current);
    Dxl.writeDword(MOTOR_ID, GOAL_POSITION, 20475);
    delay(11000);
    getSensor(0);
  }    
}

int getSensor(int a){
  current_position = Dxl.readDword(MOTOR_ID, PRESENT_POS)/4095; // Read present position
  torque_status = Dxl.readWord(MOTOR_ID, TORQUE_ENABLE);
  input_voltage = Dxl.readWord(MOTOR_ID, INPUT_VOLTAGE)/10.0;
  operating_mode = Dxl.readWord(MOTOR_ID, OPERATING_MODE);
  current_current = Dxl.readWord(MOTOR_ID, PRESENT_CURRENT)*1.34;
  read_goal_current = Dxl.readWord(MOTOR_ID, GOAL_CURRENT)*1.34;
  read_goal_position = Dxl.readWord(MOTOR_ID, GOAL_POSITION)/4095;


  delay(1000);
  SerialUSB.print("================================");
  if(a==1){
    SerialUSB.print("Closed state data");
  }
  if(a==0){
    SerialUSB.print("Open state data");
  }
  SerialUSB.println("================================");
  SerialUSB.print("Goal Position[rev]: ");
  SerialUSB.println(read_goal_position);
  SerialUSB.print("Present Position[rev]: ");
  SerialUSB.println(current_position);
  SerialUSB.print("Goal Current[mA]: ");
  SerialUSB.println(read_goal_current); 
  SerialUSB.print("Current Current[mA]: ");
  SerialUSB.println(current_current); 
  //SerialUSB.print("Torque enable status: ");
  //SerialUSB.println(torque_status);
  SerialUSB.print("Input Voltage[V]: ");
  SerialUSB.println(input_voltage);
  //SerialUSB.print("Operating Mode: ");
  //SerialUSB.println(operating_mode); 

  return 0;
}
