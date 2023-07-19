#define BLYNK_TEMPLATE_ID "TMPL3APhgPvq8"
#define BLYNK_TEMPLATE_NAME "SmartHelmet"
#define BLYNK_AUTH_TOKEN "kqBO5JL8hGlV9JpsdJ-rk-oXykdpGtV1"
#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>
#include<SoftwareSerial.h>
SoftwareSerial iot(D0, D1); //Node
char auth[] = BLYNK_AUTH_TOKEN;
short  a_val[5], b_val[5], c_val[5], d_val[5];
short total_a = 0, total_b = 0, total_c = 0, total_d = 0;
short digit[5] = {1, 10, 100, 1000, 10000};
String myString1, myString2, myString3, myString4;
int a = 0;
char ssid[] = "smart";
char pass[] ="smart@123";
BlynkTimer timer;
BLYNK_READ(V0)
{
  Blynk.virtualWrite(V0, total_a);//Alcohol
}
BLYNK_READ(V1)
{
  Blynk.virtualWrite(V1, total_b);//Temp
}
BLYNK_READ(V2)
{
  Blynk.virtualWrite(V2,  total_c); //IR
}
BLYNK_READ(V3)
{
  Blynk.virtualWrite(V3,  myString1); //tempstr
}

void setup()
{
  Serial.begin(9600);
  iot.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
void loop()
{

  short i = 0;
  short serial1 = 1, serial2 = 0, serial3 = 0;
  char serial[100];
  while (Serial.available() > 0)
  {
    serial[i] = Serial.read();
    delayMicroseconds(1050);
    i++;
  }
  if (serial[0] == 'G')
  {
    total_a = 0, total_b = 0, total_c = 0, total_d = 0;
    for (serial2 = 0; serial[serial1] != 'T'; serial1++, serial2++)
    {
      a_val[serial2] = serial[serial1] - '0';
    }
    serial2 = serial2 - 1;
    for (serial3 = 0; serial2 >= 0; serial2--, serial3++)
    {
      total_a = total_a +  a_val[serial2] * digit[serial3];
    }

    serial1 = serial1 + 1;
    for (serial2 = 0; serial[serial1] != 'I'; serial1++, serial2++)
    {
      b_val[serial2] = serial[serial1] - '0';
    }
    serial2 = serial2 - 1;
    for (serial3 = 0; serial2 >= 0; serial2--, serial3++)
    {
      total_b = total_b + b_val[serial2] * digit[serial3];
    }

    serial1 = serial1 + 1;
    for (serial2 = 0; serial[serial1] != 'Z'; serial1++, serial2++)
    {
      c_val[serial2] = serial[serial1] - '0';
    }
    serial2 = serial2 - 1;
    for (serial3 = 0; serial2 >= 0; serial2--, serial3++)
    {
      total_c = total_c + c_val[serial2] * digit[serial3];
    }
    if(total_b >=45){
      myString1 = "Temperature Increase";
      }
     else{
      myString1 = " ";
      }  
    
  }

  Serial.println( total_a);
  Serial.println( total_b);
  Serial.println( total_c);
  Serial.println( myString1);
  Blynk.virtualWrite(V0, total_a);
  Blynk.virtualWrite(V1, total_b);
  Blynk.virtualWrite(V2, total_c);
  Blynk.virtualWrite(V3,myString1);
  Blynk.run();
  timer.run();

}