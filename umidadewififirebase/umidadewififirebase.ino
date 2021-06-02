y gi#include <FirebaseESP32.h>
#include<Wifi.h>
#include "DHT.h"
#include<LiquidCrystal.h>
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(22,23,5,18,19,21);
FirebaseData firebaseData;
void setup() {
  Serial.begin(9600);
  Serial.print("A ligar a: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
Serial.println("");
  Serial.println("Ligado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  lcd.begin(16,2);

  lcd.print("Temp:  Umidade:");

}
void loop() {
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Umidade: "); Serial.print(h); Serial.println(" %");
  Serial.print("Temperatura: "); Serial.print(t); Serial.println("°C");
  lcd.setCursor(0,1);
  Firebase.setFloat(firebaseData, "/Teste/Temperatura", t);
  Firebase.setFloat(firebaseData, "/Teste/Umidade", h);

  if (isnan(h) || isnan(t)) {
    lcd.print("ERROR");
    return;
  }

  lcd.print(t);
  lcd.setCursor(7,1);
  lcd.print(h);  
  
  delay(2000);
}
