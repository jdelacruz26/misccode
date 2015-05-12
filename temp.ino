const int sensorPin = A0;
const float baselineTemp = 20.0;

void setup(){
Serial.begin(9600); //Open a serial port
}

void loop() {
int sensorVal=analogRead(sensorPin);
Serial.print("Sensor value: ");
Serial.print(sensorVal);
// Convert the ADC reading to voltage
float voltage = (sensorVal/1024.0)*5.0;
Serial.print(", Volts: ");
Serial.print(voltage);
Serial.print(", degrees C: ");

// Convert the voltage to temperature in degrees
float temperature = (voltage - 0.5)*100;
Serial.println(temperature);
delay(8000);
}