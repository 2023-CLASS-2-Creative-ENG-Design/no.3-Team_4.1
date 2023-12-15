#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

#define DHTPIN 8    // DHT11 센서의 데이터 핀
#define DHTTYPE DHT11   // DHT11 센서 사용

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd 연결핀 
Servo servo1;
Servo servo2;

int cdsPin = A0;    // CDS 조도 센서의 아날로그 핀
int soilMoisturePin1 = A1;  // 토양 수분 센서1의 아날로그 핀
int soilMoisturePin2 = A2;  // 토양 수분 센서2의 아날로그 핀
int soilMoisturePin3 = A3;  // 토양 수분 센서3의 아날로그 핀

/* //서보모터 테스터
void setup() {
  servo1.attach(9);  // 더 먼거 9번 핀
  servo2.attach(10);  // 더 가까운거 10번 핀

  pinMode(13, OUTPUT); //LED 13번 핀 
}

void loop() {
  servo1.write(0);
  //servo2.write(0); //보드근처 완료
  analogWrite(13, 255);
  delay(2000); // 1초간 기다림
   
  servo1.write(90);
  servo2.write(10); //보드근처 완료 //근데 반복을안함
  analogWrite(13, 0);
  delay(2000); // 1초간 기다림
  
  
}
//*/

//* LED 테스터 //작동안함
const int ledPin = 13; // 13핀에 연결된 LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  
  analogWrite(ledPin, LOW);
  delay(1000);
}
//*/

/* LCD동작예제 //작동안함
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  // 첫 번째 줄에 메시지 출력
  lcd.print("Hello, LCD!");
  delay(2000);
  lcd.clear();
}

void loop() {
  
}
//*/