#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
//#define BUZZER 2
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myServo.attach(3);
  myServo.write(0);
  pinMode(13, OUTPUT);
  
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void loop() {
  if(!mfrc522.PICC_IsNewCardPresent()){
      return;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
      return;
  }
  Serial.print("UID tag : ");
  String content= "";
  byte letter;
  for(byte i = 0; i < mfrc522.uid.size; i++){
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if(content.substring(1) == "A9 8B 98 1A"){
      Serial.println("Authorized access");
      Serial.println();
      digitalWrite(13 , HIGH);
      delay(500);
      digitalWrite(13 , LOW);
      delay(500);
  }
  else{
      Serial.println("Access denied");
      digitalWrite(13 , HIGH);
      delay(100);
      digitalWrite(13 , LOW);
      delay(100);
  }
}
