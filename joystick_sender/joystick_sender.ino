#define X 32
#define Y 35
#define BUTTON 14
#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>
//24:DC:C3:45:A0:3C

uint8_t broadcastAddress1[] = {0x24, 0xDC, 0xC3, 0x45, 0xA0, 0x3C};

typedef struct joystick_input {
  int x;
  int y;
  bool control;
} joystick_input;

joystick_input test;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  analogReadResolution(12);
  pinMode(BUTTON, INPUT_PULLUP);
  
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  //attachInterrupt(digitalPinToInterrupt(BUTTON), buttonInterrupt, FALLING);
}
volatile unsigned long last_interrupt_time = 0;

//void buttonInterrupt() {
//  unsigned long interrupt_time = millis();
//  // If interrupts come faster than 50ms, assume it's a bounce and ignore
//  if (interrupt_time - last_interrupt_time > 50) {
//    test.control = !test.control; // Toggle the button state
//    esp_err_t result = esp_now_send(0, (uint8_t *)&test, sizeof(joystick_input));
////    if (result == ESP_OK) {
////      Serial.println("Sent with success");
////    } else {
////      Serial.println("Error sending the data");
////    }
//  }
//  last_interrupt_time = interrupt_time;
//}

int zeroFilter(int val){
  if(val < 50 && val > -50  ){
    return 0;
  }
  if(val > 1800){
    return 1800;
  }
  if(val < -1800){
    return -1800;
  }
  return val;
}

bool safety;
void loop() {
  int xVal = 0;
  int yVal = 0;
  for(int i = 0; i < 15; i++){
    xVal += zeroFilter(analogRead(X)-1984)/15;
    yVal += zeroFilter((analogRead(Y)-1984)*-1)/15;
  }
  test.x = xVal;
  test.y = yVal;

  safety = digitalRead(BUTTON);
  if (safety == 0){
    test.control = !test.control;
  }


//  int buttonState =  analogRead(BUTTON);
//
//  if(buttonState == LOW){
//    //delay(50);
//    if(analogRead(BUTTON) == LOW){
//      safety = !safety;
//      test.button = safety;
//      //delay(50);
//    }
//  }
  Serial.println(test.control);

  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(joystick_input));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
