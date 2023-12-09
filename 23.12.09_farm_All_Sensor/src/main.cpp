#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>


DHT dht(8, DHT11);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd 연결핀 
Servo servo1;
Servo servo2;

int cdsPin = A0;    // CDS 조도 센서의 아날로그 핀
int soilMoisturePin1 = A1;  // 토양 수분 센서1의 아날로그 핀
int soilMoisturePin2 = A2;  // 토양 수분 센서2의 아날로그 핀
int soilMoisturePin3 = A3;  // 토양 수분 센서3의 아날로그 핀
int ledPin = 13;    // LED의 디지털 핀


byte customSmile1[] = { 0b00000, 0b01100, 0b10010, 0b00000, 0b01111, 0b01000, 0b00100, 0b00011 };
byte customSmile2[] = { 0b00000, 0b00110, 0b01001, 0b00000, 0b11110, 0b00010, 0b00100, 0b11000 };
byte customSad1[] = { 0b00000,0b00100,0b01110,0b00100,0b00000,0b00011,0b00100,0b01000 };
byte customSad2[] = { 0b00000,0b00100,0b01110,0b00100,0b00000,0b11000,0b00100,0b00010 };
byte customAngry1[] = { 0b11100,0b00110,0b01111,0b00100,0b00000,0b00011,0b00100,0b01000 };
byte customAngry2[] = { 0b00111,0b01100,0b11110,0b00100,0b00000,0b11000,0b00100,0b00010 };

void displayMoistureEmoji(int moistureValue) {

  lcd.setCursor(7, 1);
  if (moistureValue >= 801) { //물이적음
    lcd.write(6);
    lcd.write(7);
  } else if (moistureValue >= 450) { //적당함
    lcd.write(2);
    lcd.write(3);
  } else { //수분과다
    lcd.write(4);
    lcd.write(5);
  }
}

//*/
void Motormove(int cdsValue){
  if (cdsValue >= 600) { //밝은  
    Serial.print(cdsValue); 
    servo1.write(90);
    servo2.write(0); //보드근처 완료
    digitalWrite(ledPin, HIGH);
  }
  //*/
  if (cdsValue <= 300) { //어둡 
    servo1.write(0);
    servo2.write(80); //보드근처 완료 //근데 반복을안함
    digitalWrite(ledPin, LOW); 
  }
//*/
}


void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);    // LCD 크기 설정
  pinMode(ledPin, OUTPUT);
  servo1.attach(9); //9번핀이 먼 서보
  servo2.attach(10); //10번 핀이 가까운 서보

  //웃는 표정(23) 우는표정(45) 화난표정(67)
  lcd.createChar(2, customSmile1);
  lcd.createChar(3, customSmile2);
  lcd.createChar(4, customSad1);
  lcd.createChar(5, customSad2);
  lcd.createChar(6, customAngry1);
  lcd.createChar(7, customAngry2);
  
}
void loop() {
  
  int cdsValue = analogRead(cdsPin);
  Motormove(cdsValue);
  digitalWrite(ledPin, HIGH);
  // 토양 수분 값 읽기
  int soilMoisture1 = analogRead(soilMoisturePin1);
  int soilMoisture2 = analogRead(soilMoisturePin2);
  int soilMoisture3 = analogRead(soilMoisturePin3);

  float temperature = dht.readTemperature();
  float Humidity = dht.readHumidity();
  Serial.print(abs(temperature));
  Serial.print(Humidity);
  // 첫 3초간 온도 및 습도 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(Humidity);
  lcd.print("%");
  

  delay(3000); // 3초간 첫 번째 화면 표시

  // 두 번째 화면에 토양 센서 1에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 1: ");
  lcd.print(soilMoisture1);

  displayMoistureEmoji(soilMoisture1);

  delay(3000); // 3초간 두 번째 화면 표시

  // 세 번째 화면에 토양 센서 2에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 2: ");
  lcd.print(soilMoisture2);

  displayMoistureEmoji(soilMoisture2); 

  delay(3000); // 3초간 세 번째 화면 표시

  // 네 번째 화면에 토양 센서 3에 대한 수분량과 이모지 표시
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture 3: ");
  lcd.print(soilMoisture3);

  displayMoistureEmoji(soilMoisture3);

  delay(3000); // 3초간 네 번째 화면 표시
}