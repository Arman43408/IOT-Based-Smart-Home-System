#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servo1;

int trigPin = 9;
int echoPin = 8;
int irSensor = 13;
int buzzer = 12;
int val = 0;  
int watersensor = A0; 
int Motor = 2;
long distance;
long duration;
const int sensor=A1;
float tempc;  
float tempf;  
float vout; 

void setup() {
  servo1.attach(7); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  pinMode(sensor,INPUT);
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Motor,OUTPUT);
  digitalWrite(Motor,LOW); 
}

void loop() {
ultra_sonic();
servo1.write(180);
if(distance <=9){
servo1.write(90);
  }
vout=analogRead(sensor);
Serial.print("Analog Value = ");
Serial.print(vout);
Serial.println();
vout=(vout*5000)/1023;
tempc=vout/23; // Storing value in Degree Celsius
tempf=(tempc*1.8)+32; // Converting to Fahrenheit 
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
Serial.print("in Fahrenheit=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();
showTemp(tempf, tempc);
delay(0); 
int value = digitalRead(irSensor);
    Serial.println("");
    Serial.print("Sensor Value = ");
    Serial.print(value);
    
    if(value == 0)
    {
        digitalWrite(buzzer, HIGH);
    }
    else
    {
        digitalWrite(buzzer, LOW);
    }
    delay(0);

    val = analogRead(watersensor);
  if (val<=100)
  {  
    digitalWrite(Motor,HIGH);
  } 
  else if (val>100 && val<=450)
  { 
    digitalWrite(Motor,HIGH); 
  } 
  else if (val>500)
  { 
    digitalWrite(Motor,LOW); 
  }
  delay(0); 
}

void ultra_sonic()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(0);
digitalWrite(trigPin, HIGH);
delayMicroseconds(5);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration*0.034/2;
}

void showTemp(int tempf, int tempc) {

  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40, 0);
  display.println(F("Temp"));
  display.setCursor(0, 20);
  display.print(F("F: "));
  display.println(tempf);
  display.setCursor(0, 40);
  display.print(F("C: "));
  display.println(tempc);

  display.display();    // Show initial text
}
