#define LEFT_WIRE A15
#define RIGHT_WIRE A16
#define UP_WIRE A13
#define DOWN_WIRE A14
#define TRIG 5
#define ECHO 16

void setup(){
  Serial.begin(9600);
  pinMode(LEFT_WIRE, OUTPUT);
  pinMode(RIGHT_WIRE, OUTPUT);
  pinMode(UP_WIRE, OUTPUT);
  pinMode(DOWN_WIRE, OUTPUT);
  pinMode(TRIG, OUTPUT); // set up distance sensor pins
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

// read distance sensor, return centimeters
float readDistance() {
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
  float dist = readDistance();
  Serial.println(dist);
  digitalWrite(UP_WIRE, HIGH);
  if (dist < 20){
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
  
}
