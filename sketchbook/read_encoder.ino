 /* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define J_ID 1
/* Control table defines */
#define TORQUE_ENABLE 64
#define INPUT_VOLTAGE 144
#define PRESENT_POS 132
#define GOAL_POSITION 116
#define OPERATING_MODE 11
 
Dynamixel Dxl(DXL_BUS_SERIAL3); 
 
void setup() {
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps  
  Dxl.begin(1);
  delay(1000);
  Dxl.writeByte(1,TORQUE_ENABLE,1);
  //Dxl.maxTorque(J_ID,0.7); // it has maxtorque for weak movement  
//  Dxl.jointMode(J_ID); //jointMode() is to use position mode  
}
int goal_position =4095;
int current_goal_position;
int pos;
int torque_status;
int input_voltage;
int operating_mode;
void loop() {

  // Wait for 20 milliseconds
  delay(2000);
  //Dxl.writeWord(J_ID, 64, 1);
  Dxl.writeDword(J_ID, GOAL_POSITION, goal_position);
  if( goal_position == 4095 )
    goal_position = 0;
  else
    goal_position = 4095;
    
  delay(1500);

  pos = Dxl.readWord(J_ID, PRESENT_POS); // Read present position
  torque_status = Dxl.readWord(J_ID, TORQUE_ENABLE);
  input_voltage = Dxl.readWord(J_ID, INPUT_VOLTAGE);
  operating_mode = Dxl.readWord(J_ID, OPERATING_MODE);
  current_goal_position = Dxl.readWord(J_ID, GOAL_POSITION);

  SerialUSB.print("Present Position: ");
  SerialUSB.println(pos);
  SerialUSB.print("Torque enable status: ");
  SerialUSB.println(torque_status);
  SerialUSB.print("Input Voltage: ");
  SerialUSB.println(input_voltage);
  SerialUSB.print("Operating Mode: ");
  SerialUSB.println(operating_mode); 
  SerialUSB.print("Goal Position: ");
  SerialUSB.println(current_goal_position); 
}
