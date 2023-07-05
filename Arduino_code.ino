#define sensorPower 7
#define sensorPin A3
int soilMoistureValue0 = 0;
int soilMoistureValue1 = 0;
int soilMoistureValue2 = 0;
int percentage0=0;
int percentage1=0;
int percentage2=0;

// Value for storing water level
int val = 0;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);

   // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  
  Serial.begin(9600);
  
}
void loop() {
soilMoistureValue0 = analogRead(A0);
soilMoistureValue1 = analogRead(A1);
soilMoistureValue2 = analogRead(A2);
delay(1000);
Serial.print("Moisture level of field 0: ");
Serial.println(percentage0);
Serial.print("Moisture level of field 1: ");
Serial.println(percentage1);
Serial.print("Moisture level of field 2: ");
Serial.println(percentage2);
percentage0 = map(soilMoistureValue0, 490, 1023, 100, 0);
percentage1 = map(soilMoistureValue1, 490, 1023, 100, 0);
percentage2 = map(soilMoistureValue2, 490, 1023, 100, 0);

 //get the reading from the function below and print it
  int WaterLevel = readSensor();
  
  Serial.print("Water level: ");
  Serial.println(WaterLevel);
  delay(1000);

if((percentage0 < 90 || percentage1 < 90 || percentage2 < 90)&& WaterLevel > 200)  
{
  if(percentage0 < 90)
  {
   Serial.println(" Field 0");
   digitalWrite(2,LOW);
   digitalWrite(3,HIGH);
   digitalWrite(4,HIGH);
   delay(2000);
   Serial.println(" Field 0 PUMP ON");
   digitalWrite(5,LOW);
  }
  if(percentage0 > 100 && percentage1 < 90)
  {
   Serial.println(" Field 1");
   digitalWrite(3,LOW);
   delay(1000);
   digitalWrite(2,HIGH);
   digitalWrite(4,HIGH);
   delay(2000);
   Serial.println(" Field 1 PUMP ON");
   digitalWrite(5,LOW);
  }
  if(percentage0 > 100 && percentage1 > 100 && percentage2 < 90 )
  {
   Serial.println(" Field 2");
   digitalWrite(4,LOW);
   delay(1000);
   digitalWrite(2,HIGH);
   digitalWrite(3,HIGH);
   delay(2000);
   Serial.println(" Field 2 PUMP ON");
   digitalWrite(5,LOW);
  }
}

if((percentage0 > 100 && percentage1 > 100 && percentage2 >100) || WaterLevel < 200)
{
  Serial.println("pump off");
  digitalWrite(5,HIGH);
  delay(5000);
}
}
//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}
