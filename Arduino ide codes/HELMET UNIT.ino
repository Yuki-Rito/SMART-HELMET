#include<SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN A1
#define DHTTYPE DHT22
#define gas A0
#define IR 2
SoftwareSerial serial1(11, 12); //node mcu
SoftwareSerial serial2(9, 10); //rfid
DHT dht(DHTPIN, DHTTYPE);
int a, b, c;
void rfid();
int count = 0;
char input[12];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial1.begin(9600);
  serial2.begin(9600);
  dht.begin();
  pinMode(gas, INPUT);
  pinMode(IR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = analogRead(gas);
  c = digitalRead(IR);
  float tempC = dht.readTemperature();
  b = tempC;

  serial1.print("G");
  serial1.print(a);
  serial1.print("T");
  serial1.print(b);
  serial1.print("I");
  serial1.print(c);
  serial1.println("Z");
  if (a > 450)
  {
    Serial.println('A');
    c = a;
  }
  if (b >= 45) {
    Serial.println('T');
    c = b;
  }
  if (c == 0) {
    Serial.println('H');
  }
  if (c == 1) {
    Serial.println('N');
  }

  rfid();

  if ((input[0] == '5') && (input[1] == '2') && (input[2] == '0') && (input[3] == '0') && (input[4] == '1') && (input[5] == '4') && (input[6] == 'F') && (input[7] == 'E') && (input[8] == 'F') && (input[9] == '0') && (input[10] == '4') && (input[11] == '8') )
  {
    Serial.println('R');

  }
  input[0] = '\0';

  delay(1000);
}
void rfid() {
  while (serial2.available() > 0)
  {
    input[count] = serial2.read();
    count++;
  }

  if (count >= 12)
  {
    count = 0;
  }

}