/*
  Ultrasonic Distance Sensor using HC - SR04
 */
 
const int trigPin = 13;
const int echoPin = 12;
const int pulseToDistanceFactor = 57;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Trig is used for sending request to the device
  pinMode(trigPin, OUTPUT);
  // Echo is used for getting the values from the device
  pinMode(echoPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // We are using HC-SR04 which needs a minimum of 10us of
  // HIGH signal on Trig to calculate the distance
  // The first signal is for TRIG and second one is for ECHO
  
  //   5 sec  ___________
  // ________|   10 sec  |__________________
  
  //                              _______
  // ____________________________|
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // After 10us set the trig back to LOW
  digitalWrite(trigPin, LOW);
  
  // After the 10us HIGH on trig pin, we
  // need to wait for a HIGH on echoPin
  // where we would get our desired distance
  // by measuring the length of HIGH pulse
  long highDuration = pulseIn (echoPin, HIGH);
  long distance = highDuration/pulseToDistanceFactor;
  Serial.println(distance);
  
  // Everyone needs some time off before they start
  // the same old boring job the next day
  delay(1000);
}
