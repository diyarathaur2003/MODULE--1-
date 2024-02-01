const int sensorPin = A0;  // Declaring the consant variable for analog input
const int motionPin = 2;   // Declaring the constant variable for Interrupt pin 2
const int intPin = 3;      // Declarint the constant variable for Interrupt pin 3
int soilM = 0;             // Intializing the variable "soilM"
int motion = 0;            // Intializing the variable "motion"
int led1 = 9;              // declaring the variables of led 1 and 2 for respective pins
int led2 = 11;


void setup()  // Setup function( will run only one time)
{
  pinMode(intPin, INPUT);                                                        // Setting up the interrupt pin as Input
  pinMode(motionPin, INPUT);                                                     // Setting up the interrupt pin as Input
  pinMode(sensorPin, INPUT);                                                     // Setting up the Analog Pin as Input
  pinMode(12, OUTPUT);                                                           // setting the digital pin as Output
  Serial.begin(9600);                                                            // Intializing the Serial Communication at a baud rate of 9600
  attachInterrupt(digitalPinToInterrupt(intPin), soil, CHANGE);                  // Generating an Interrupt for Soil Moisture
  attachInterrupt(digitalPinToInterrupt(motionPin), mointionInterrupt, CHANGE);  // Generating an Interrupt for PIR Motion Sensor
}

void loop() {                               // Loop function which will run repeditely
  int sensorValue = analogRead(sensorPin);  // It is used to read the analog value of Soil Moisture Sensor
  if (sensorValue > 500) {                  //Setting the Threshold value
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
}

void soil() {
  soilM = digitalRead(intPin);          // Used to read the digital value of Pin 3
  if (soilM == 1) {                     //  if intPin = HIGH, then soilM = 1
    Serial.println("Moisture Rising");  // Print the statment if the moisture of the soil is more than 500
    digitalWrite(9, HIGH);              // LED 1 will glow, if the above condition is fullfilled
  } else {
    digitalWrite(9, LOW);                // LED 1 light will turn off when the moisture is below 500
    Serial.println("Moisture Falling");  //Following line will print when the moisture value is below 500
  }
}

void mointionInterrupt() {
  motion = digitalRead(motionPin);  // used to read the digital value of the motion sensor
  if (motion == 1) {                //  Condition for the motion sensor, if it detects any motion
    Serial.println("Motion Detected");
    digitalWrite(11, HIGH);  // LED 2 will glow when motion will be detected

  } else {
    Serial.println("Motion is not Detected");
    digitalWrite(11, LOW);  // LED 2 will turn off when the emotion is not detected
  }
}
