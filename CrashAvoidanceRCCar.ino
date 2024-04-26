#define LEFT_WIRE A15 // White
#define RIGHT_WIRE A13 // Purple
#define UP_WIRE A14 // Brown
#define DOWN_WIRE A16 // Yellow
#define TRIG1 5
#define ECHO1 16
#define TRIG2 A4
#define ECHO2 A5


void setup(){
  Serial.begin(9600);
  pinMode(LEFT_WIRE, OUTPUT);
  pinMode(RIGHT_WIRE, OUTPUT);
  pinMode(UP_WIRE, OUTPUT);
  pinMode(DOWN_WIRE, OUTPUT);
  
  pinMode(TRIG1, OUTPUT); // set up distance1 sensor pins
  pinMode(ECHO1, INPUT);
  digitalWrite(TRIG1, LOW);
  pinMode(TRIG2, OUTPUT); // set up distance2 sensor pins
  pinMode(ECHO2, INPUT);
  digitalWrite(TRIG2, LOW);
}

// read distance sensor, return centimeters
float readDistance(int TRIG, int ECHO) {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long timeout = micros() + 26233L;
  while((digitalRead(ECHO) == LOW) && (micros() < timeout));
  unsigned long start_time = micros();
  timeout= start_time + 26233L;
  while((digitalRead(ECHO) == HIGH) && (micros() < timeout));
  unsigned long lapse = micros() - start_time;
  return lapse * 0.01716f;
}

void loop(){
  float dist1 = readDistance(TRIG1, ECHO1);
  float dist2 = readDistance(TRIG2, ECHO2);
  Serial.println(dist1);
  Serial.println(dist2);
  digitalWrite(UP_WIRE, HIGH);
  if (dist1 < 20 || dist2 < 20){
    digitalWrite(UP_WIRE, LOW);
  }

//  digitalWrite(LEFT_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(LEFT_WIRE, LOW);
//  digitalWrite(RIGHT_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(RIGHT_WIRE, LOW);
//  delay(5000);
//  
//  digitalWrite(DOWN_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(DOWN_WIRE, LOW);
//  delay(2000);
//
//  digitalWrite(UP_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(UP_WIRE, LOW);
//  delay(2000);
  
}
