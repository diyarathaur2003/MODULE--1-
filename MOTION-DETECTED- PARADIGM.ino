// C++ code

int motion = 0;// Intializing the variable "motion" to store status of motion
void setup()
{
  pinMode(2, INPUT); 
  Serial.begin(9600); //Initializing the serial communication at a baud rate of 9600
}

void loop()
{
    motion = digitalRead(2); //Read the digital input from pin 2 (motion sensor)
  if(motion == 1)
  {
    Serial.println("Motion Detected"); // Print the line if motion is detected
  }
  else 
  {
    Serial.println("Motion is not Detected"); // Print the line if the motion is not detected
  }
  delay(1000); //  given the delay of 1 second 
}

