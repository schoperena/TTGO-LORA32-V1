//librerias para LoRa
#include <SPI.h>
#include <LoRa.h>

//Librerias para el Display OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "logo.h"

//pines Módulo LoRa
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//Bandas LoRa
//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 915E6

//Pines del Display OLED
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

String LoRaData;

void logo();

void setup() { 
  
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  
  //inicializar el OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // No procede y queda en bucle infinito
  }

  logo();
  delay(2000);
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA RECEIVER ");
  display.display();
  
  //inicializa el monitor serial
  Serial.begin(115200);
  Serial.println("LoRa Receiver Test");
  
  //pines SPI LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup del modulo LoRa
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Falla al inicializar LoRa");
    while (1);
  }
  Serial.println("LoRa Inicializando OK");
  display.setCursor(0,10);
  display.println("LoRa Inicializando OK");
  display.display();  
}

void loop() {

  //intenta capturar un paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    //alerta cuando reciba un paquete
    Serial.print("Paquete recibido ");

    //Lectura del paquete
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    //imprime el RSSI del paquete
    int rssi = LoRa.packetRssi();
    Serial.print("RSSI ");    
    Serial.println(rssi);
    
    // muestra la info en el OLED
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("LORA RECEIVER");
   display.setCursor(0,20);
   display.print("Paquete recibido:");
   display.setCursor(0,30);
   display.print(LoRaData);
   display.setCursor(0,40);
   display.print("RSSI:");
   display.setCursor(30,40);
   display.print(rssi);
   display.display();   
  }
}

void logo(){
  display.clearDisplay();
  display.drawBitmap(0, 0,  logo_sch, 128, 64, WHITE);
  display.display();
}