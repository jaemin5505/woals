#include <Servo.h>
#include <DHT.h>

#define DHTPIN 7    // DHT 센서 핀
#define DHTTYPE DHT11 

int gndPin = A0;
int vccPin = A1;
int xPin = A2;
int yPin = A3;
int swPin = A4;
int servoPin = 10;
int buzzerPin = 9;
int DHTPin = 7;
int triggerPin = 5;
int echoPin = 6; 
int ledPin = 2;  // LED 핀 추가

int hzData[8] = {330, 330, 330, 330, 330, 330, 330};

Servo myServo;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(gndPin,OUTPUT);
  pinMode(vccPin,OUTPUT);
  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);
  pinMode(swPin,INPUT_PULLUP);  // 스위치 입력 핀
  pinMode(buzzerPin, OUTPUT);
  pinMode(DHTPIN, INPUT_PULLUP);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);  // LED 핀을 출력으로 설정

  myServo.attach(servoPin);

  digitalWrite(gndPin, LOW);
  digitalWrite(vccPin, HIGH);

  dht.begin();
  delay(2000);
}

float getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

void loop() {
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);

  int x = map(analogRead(xPin), 0, 1023, -100, 100);
  int y = map(analogRead(yPin), 0, 1023, -100, 100);

  //부저
  if(yRaw > 512){
   for(int i = 0; i < 8; i++) {
    tone(buzzerPin, hzData[i]);
    delay(200);
    }
    noTone(buzzerPin);
  }

  //온습도
  if (xRaw > 513) {
    float temp = dht.readTemperature();  // 온도 읽기
    float hum = dht.readHumidity();      // 습도 읽기

    if (!isnan(temp) && !isnan(hum)) {
      Serial.print("온도: ");
      Serial.print(temp);
      Serial.print("°C\t습도: ");
      Serial.print(hum);
      Serial.println("%");
    } else {
      Serial.println("미감지!");
    }
    delay(500);
  }

  //초음파 센서
  if (yRaw < 500) {
    float distance = getDistance();
    Serial.print("거리: ");
    Serial.print(distance);
    Serial.println("cm");

    if (distance < 30.0 && distance > 0) {
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
    }
    delay(500);
  }

  //서브모터
  int servoAngle = map(xRaw, 0, 1023, -5, 180);
  if(xRaw < 512){
    myServo.write(servoAngle);
  }
  else if(xRaw > 510 && xRaw < 514) {
    myServo.write(90); // 모터를 중앙 위치(90도)로 돌리기
    delay(300);
    myServo.write(0);
  }
  else {
    myServo.write(90);
  }

  // LED 제어
  if (!digitalRead(swPin)) {  // 스위치가 눌리면
    digitalWrite(ledPin, HIGH);  // LED 켬
  } else {
    digitalWrite(ledPin, LOW);  // LED 끔
  }

  delay(500);
}
