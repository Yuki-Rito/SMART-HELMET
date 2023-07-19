#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
#include <TinyGPS++.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
SoftwareSerial serial1(2, 3); //gsm
SoftwareSerial serial2(5, 6); //gps
TinyGPSPlus gps;
void gpsloc();
void sendsms1();
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
#define M 4
#define A A0
char a;
void setup() {
  pinMode(M, OUTPUT);
  pinMode(A, INPUT);
  Serial.begin(9600);
  serial1.begin(9600);
  serial2.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  int b = analogRead(b);
  lcd.setCursor(0, 0);
  lcd.print("Bike:");
  lcd.setCursor(6, 0);
  lcd.print(b);
  if (Serial.available() > 0)
  {
    a = Serial.read();
    Serial.println(a);

  }
  if (a == 'N')
  {

    lcd.setCursor(0, 1);
    lcd.print("Wear Helmet");
  }
  if (a == 'H')
  {

    lcd.setCursor(0, 1);
    lcd.print("Start Bike");

  }
  if (a == 'R')
  {
    int z = 0;
    while (z == 0) {
      if (Serial.available() > 0)
      {

        a = Serial.read();
      }
      if (a == 'H')
      {
        digitalWrite(M, 1);
        lcd.clear();

        lcd.setCursor(0, 1);
        lcd.print("Bike is running");

      }
      if (a == 'N')
      {
        digitalWrite(M, 0);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Wear Helmet");
      }
      if (a == 'A')
      {
        digitalWrite(M, 0);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Alcohol Detect");
      }
      if (a == 'T')
      {

        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Temperature");
      }

    }
  }
  if (b <= 310) {
    gpsloc();
    String msg = "Accident Detection";
    msg += "lat:";
    msg += lat_str;
    msg += "lon:";
    msg += lng_str;
    sendsms1(msg, "+919629802408");

    lcd.setCursor(0, 1);
    lcd.print("Accident");
    digitalWrite(M, 0);
    Serial.println(msg);


  }
  gpsloc();
  Serial.print("lat:");
  Serial.println(lat_str);
  Serial.print("long:");
  Serial.println(lng_str);
}
void sendsms1(String message, String number)
{
  String mnumber = "AT+CMGS=\"" + number + "\"";
  serial1.println("AT+CMGF=1\r");
  delay(1000);
  serial1.println(mnumber);
  delay(1000);
  serial1.println(message);
  delay(1000);
  serial1.println((char)26);
  delay(100);
}
void gpsloc()
{
  while (serial2.available() > 0)//while data is available
    if (gps.encode(serial2.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
      }
      if (gps.date.isValid()) //check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (date < 10)
          date_str = '0';
        date_str += String(date);// values of date,month and year are stored in a string
        date_str += " / ";
      }
    }
}