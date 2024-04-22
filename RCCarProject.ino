#define LEFT_WIRE 15
#define RIGHT_WIRE A14
#define UP_WIRE A15
#define DOWN_WIRE A16

void setup(){
  Serial.begin(9600);
  pinMode(LEFT_WIRE, OUTPUT);
  pinMode(RIGHT_WIRE, OUTPUT);
  pinMode(UP_WIRE, OUTPUT);
  pinMode(DOWN_WIRE, OUTPUT);
}

void loop(){
  digitalWrite(LEFT_WIRE, HIGH);
  delay(1000);
  digitalWrite(LEFT_WIRE, LOW);
  digitalWrite(RIGHT_WIRE, HIGH);
  delay(1000);
  digitalWrite(RIGHT_WIRE, LOW);
  delay(5000);
//  digitalWrite(DOWN_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(DOWN_WIRE, LOW);
//  delay(2000);
  
}
