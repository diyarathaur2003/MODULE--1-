const int sensorPin = A0;  // decalaring the constant variable
const int intPin = 2;      // declaring costant pin for interrupt pin
int soilM = 0;             // variable to store the state of the soil moisture

void setup()  // Setup function
{
  pinMode(intPin, INPUT);                                        // Set the interrupt pin as input
  pinMode(12, OUTPUT);                                           //  Set the digital pin(12) as output
  pinMode(sensorPin, INPUT);                                     // Set the Sensorpin as input
  Serial.begin(9600);                                            // Initializing the Serial communication at a baud rate of 9600
  attachInterrupt(digitalPinToInterrupt(intPin), soil, CHANGE);  // Attaching the Interrupt function to pin
}

void loop()  // Loop function which runs repeteadily
{
  int sensorValue = analogRead(sensorPin);  // Read analog value from the soil moisture sensor
  if (sensorValue > 500)                    // Setting the threshold of the moisture using if else condition
  {
    digitalWrite(12, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(1000);
}

void soil() {
  soilM = digitalRead(intPin);  // It is used to read the state of the interrupt pin
  if (soilM == 1)               //setting the soilM condition for if else statement to generate interrupt
  {
    Serial.println("Moisture Rising");  // Print the message if moisture is rising
  } else {
    Serial.println("Moisture Falling");  // Print the messagw if the moisture is falling below a specific conditioned as mentioned
  }
}