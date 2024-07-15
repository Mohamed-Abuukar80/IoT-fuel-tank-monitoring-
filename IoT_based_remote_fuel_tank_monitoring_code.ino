#define BLYNK_PRINT Serial
  
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
  #include <LiquidCrystal.h>
  #include <WiFiManager.h>
  
const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
  
char auth[] = "V4S_gL9SFN3V3ow5j3u60iAk-vciaWfd";
//char ip[] = "43.252.237.67";
//uint16_t port = 8080;

//char ssid[] = "enter virus";
//char pass[] = "Hormuud@5";

#define trig D4   // Trig pin
#define echo D3
int depth =20;

\\D5

BlynkTimer timer;

void SR04()
{
   digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
 // Serial.println(cm);
  long level= depth-cm;
  if (level<0)
  level=0;
  level = map(level,0,depth-3,100,0);
    if(level < 0) 
  {
  // int leve = 0;
    Serial.print("sonic: ");
   Serial.print(0);
   Serial.print("cm");
  Serial.print("\n");
  delay(1000); 

  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.print(0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("place object");
  delay(1000);
  lcd.clear();

 Blynk.virtualWrite(V7, 0);
    }
else if (level >= 100)
{

    Serial.print("sonic: ");
   Serial.print(0);
   Serial.print("cm");
  Serial.print("\n");
  delay(1000); 

  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.print(0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("More than I can");
  delay(1000);
  lcd.clear();

 Blynk.virtualWrite(V7, 0); 
  }
    
 else {
  Serial.print("sonic: ");
  Serial.print(level);
  Serial.print("cm");
  Serial.print("\n");
  delay(1000); 

  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.print(level);
  lcd.print("cm");
 // lcd.setCursor(0,1);
 // lcd.print("place object");
  delay(1000);
  lcd.clear();

 Blynk.virtualWrite(V7, level);
  }

}
void setup() {
  Serial.begin(9600);

      WiFiManager wm;
     bool res;
 res = wm.autoConnect("distance measurement"); // password protected ap
    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        Blynk.config(auth); 
    }

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Distance Mobile");
  lcd.setCursor(5,1);
  lcd.print("Measurement");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Made by:");
  lcd.setCursor(0,1);
  lcd.print("Uniso Students");
  delay(1000);
  lcd.clear();

  timer.setInterval(1000L, SR04);//每隔1000毫秒执行一次SR04函数
}

void loop()
{
  Blynk.run();
  timer.run(); 
}