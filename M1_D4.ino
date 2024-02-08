const int sensorPin = A0;  // Declaring the consant variable for analog input
const int motionPin = 4;   // Declaring the constant variable for Interrupt pin 2
int soilM = 0;             // Intializing the variable "soilM"
int motion = 0;            // Intializing the variable "motion"
int motionPin1 = 8;        // Intializing the variable "motionPin1"
int led1 = 11;             // Declaring the led1 for Interrupt Timer

void setup()  // Setup function (will run only one time)
{

  pinMode(motionPin, INPUT);   // Setting up the interrupt pin as Input for PIR Motion Sensor
  pinMode(sensorPin, INPUT);   // Setting up the interrupt pin as Input for soil moisture
  pinMode(motionPin1, INPUT);  // Setting up the interrupt pin as Input for another PIR Motion Sensor
  pinMode(7, OUTPUT);          // setting the digital pin as Output
  Serial.begin(9600);          // Intializing the Serial Communication at a baud rate of 9600
  PCICR |= B00000111;          // PCICR register used for selecting the PORT B
  PCMSK0 |= B00000001;
  PCMSK2 |= B0010000;
  PCMSK1 |= B00000001;
  startTimer();
}

void loop() {  // Loop function which will run repeditely
}
ISR(PCINT0_vect) {
  mointionInterrupt1();
}
ISR(PCINT1_vect) {
  soil();
}
ISR(PCINT2_vect) {
  mointionInterrupt();
}

void soil() {
  soilM = digitalRead(sensorPin);       // Used to read the digital value of Pin 3
  if (soilM == 1) {                     //  if intPin = HIGH, then soilM = 1
    Serial.println("Moisture Rising");  // Print the statment if the moisture of the soil is more than 500
    digitalWrite(9, HIGH);
  } else {
    Serial.println("Moisture Falling");  //Following line will print when the moisture value is below 500
    digitalWrite(9, HIGH);
  }
}

void mointionInterrupt() {
  motion = digitalRead(motionPin);  // used to read the digital value of the motion sensor
  if (motion == 1) {                //  Condition for the motion sensor, if it detects any motion
    Serial.println("Motion Detected");


  } else {
    Serial.println("Motion is not Deteced");
  }
}
void mointionInterrupt1() {
  motion = digitalRead(motionPin1);  // used to read the digital value of the motion sensor
  if (motion == 1) {                 //  Condition for the motion sensor, if it detects any motion
    Serial.println("Motion Detected");
  } else {
    Serial.println("Motion is not Detected");
  }
}
void startTimer() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // frequency = clock_speed / (prescaler * (1 + OCR1A))
  // OCR1A = (clock_speed / (prescaler * frequency)) - 1
  OCR1A = 31249;

  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  // CTC mode
  TCCR1B |= (1 << WGM12);
  interrupts();
}

int led = 0;  // Declaring the led variable for Timer Interrupt
ISR(TIMER1_COMPA_vect) {
  //digitalWrite(led1, digitalRead(led1) ^ 1);
  if (led == 0) {
    digitalWrite(led1, HIGH);
    led = 1;
  } else {
    digitalWrite(led1, LOW);
    led = 0;
  }
}
