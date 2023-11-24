#include <DHT.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define DHTPIN 1 // DHT11 센서의 데이터 핀
#define DHTTYPE DHT11 // DHT11 센서 사용

DHT dht(DHTPIN, DHTTYPE);

// RS, EN, D4, D5, D6, D7 순서로 연결
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int cdsPin = A0; // CDS 조도 센서의 아날로그 핀
int ledPin = 13; // LED의 디지털 핀
int servoPin = 10; // 서보 모터의 디지털 핀

Servo servo;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // 1602 LCD의 크기에 맞게 설정

  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  int cdsValue = analogRead(cdsPin);
  int brightness = map(cdsValue, 0, 1023, 255, 0); // 낮을수록 밝게
  int tem =(int)temperature;
  int hum =(int)humidity;
  int index =1.8*tem -0.55*(1-hum /100)*(1.8*tem -26) +32;
  // LCD에 온습도 출력
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEM : ");
  lcd.print((int)temperature); 
  lcd.print("`C, "); 
  lcd.print((int)humidity); 
  lcd.print("H");
  lcd.setCursor(0,1);
  lcd.print("DI : ");
  lcd.print(index);

  // LED 밝기 설정
  analogWrite(ledPin, brightness);

  // 서보 모터 각도 설정
  int servoAngle = map(brightness, 0, 255, 0, 180);
  servo.write(servoAngle);

  // 시리얼 모니터에 데이터 출력
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("C  Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Brightness: ");
  Serial.print(brightness);
  Serial.print("  Servo Angle: ");
  Serial.println(servoAngle);

  delay(2000); // 2초마다 측정
}
