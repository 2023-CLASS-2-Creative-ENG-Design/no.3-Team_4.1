#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

#define DHTPIN 8    // DHT11 센서의 데이터 핀
#define DHTTYPE DHT11   // DHT11 센서 사용

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd 연결핀 

int cdsPin = A0;    // CDS 조도 센서의 아날로그 핀
int soilMoisturePin1 = A1;  // 토양 수분 센서1의 아날로그 핀
int soilMoisturePin2 = A2;  // 토양 수분 센서2의 아날로그 핀
int soilMoisturePin3 = A3;  // 토양 수분 센서3의 아날로그 핀
int ledPin = 13;    // LED의 디지털 핀

int servoPin1 = 10;   // 첫 번째 서보 모터의 디지털 핀
int servoPin2 = 11;   // 두 번째 서보 모터의 디지털 핀

Servo servo1;
Servo servo2;

void displayEmoji(int emojiLevel) {
  const char* emojiString = ""; // 이모지 문자열 초기화
  
  switch (emojiLevel) {
    case 0:
      emojiString = ":("; // 토양 수분이 적을 때의 이모지
      break;
    case 1:
      emojiString = ":|"; // 중간 토양 수분일 때의 이모지
      break;
    case 2:
      emojiString = ":)"; // 토양 수분이 많을 때의 이모지
      break;
  }

  lcd.setCursor(0, 1);
  lcd.print(emojiString);  // 이모티콘 출력
  delay(3000);  // 고정된 시간으로 변경 (예: 3초)
}



void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);    // LCD 크기 설정
  lcd.backlight();   // LCD 배경 조명 활성화

  pinMode(ledPin, OUTPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  int cdsValue = analogRead(cdsPin);
  int brightness = map(cdsValue, 0, 1023, 255, 0); // 낮을수록 밝게

  // 토양 수분 값 읽기
  int soilMoisture1 = analogRead(soilMoisturePin1);
  int soilMoisture2 = analogRead(soilMoisturePin2);
  int soilMoisture3 = analogRead(soilMoisturePin3);

  // 토양 수분 값을 0에서 1023까지의 범위로 매핑
  int emojiLevel1 = map(soilMoisture1, 0, 1023, 0, 2);
  int emojiLevel2 = map(soilMoisture2, 0, 1023, 0, 2);
  int emojiLevel3 = map(soilMoisture3, 0, 1023, 0, 2);

  // 첫 번째 화면에 온도 및 습도 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(3000); // 3초간 첫 번째 화면 표시

  // 두 번째 화면에 토양 센서 1에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 1: ");
  lcd.print(soilMoisture1);
  lcd.setCursor(0, 1);
  displayEmoji(emojiLevel1);

  delay(3000); // 3초간 두 번째 화면 표시

  // 세 번째 화면에 토양 센서 2에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 2: ");
  lcd.print(soilMoisture2);
  lcd.setCursor(0, 1);
  displayEmoji(emojiLevel2); 

  delay(3000); // 3초간 세 번째 화면 표시

  // 네 번째 화면에 토양 센서 3에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 3: ");
  lcd.print(soilMoisture3);
  lcd.setCursor(0, 1);
  displayEmoji(emojiLevel3);

  delay(3000); // 3초간 네 번째 화면 표시
}