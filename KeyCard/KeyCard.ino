// Imports
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_SSD1306.h>

/*
 * Keycard-Authenticator von Leo Ferrari
 * Diese Schaltung erkennt, ob ein Key zugelassen ist oder nicht.
 */

// definiert die verschiedenen Pins
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 32 
#define LOGO16_GLCD_WIDTH  128 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define BUZZER_PIN 8

// Setup-Methode
void setup(){
  // Serial beginnt auf 9600
  Serial.begin(9600);   
  // der LCD Panel wird initialisiert
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  SPI.begin();
  // NFC Scanner wird initialisiert
  mfrc522.PCD_Init();
  Serial.println("Halten Sie die Karte an den Sensor");
  Serial.println();
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(8, OUTPUT);

  // Clear Display
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  // Please Scan wird auf LCD gedrucked
  display.println("Please     Scan");
  display.display();
}

// Loop-Mehtode
void loop(){
  // Falls keine neue NFC Karte gefunden wird, wird Schleife unterbrochen
  if ( ! mfrc522.PICC_IsNewCardPresent()){ 
    return;
  }

  // Falls das lesen der Karte nicht möglich ist, wird Schleife unterbrochen
  if ( ! mfrc522.PICC_ReadCardSerial()){
    return;
  }

  // Drucke UID tag der NFC-Karte
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  // Falls die gescannte Karte, "authorised" ist
  if (content.substring(1) == "04 B3 EF 22 C8 48 80") //change here the UID of the card/cards that you want to give access
  {
    
  Serial.println("Authorized access");
  Serial.println();
  digitalWrite(7, HIGH); // Grüne Lampe anschalten
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Access   Granted");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F); // Text wird auf Display nach rechts gescrolled
  tone(8, 1000, 3000); // Tone wird auf Lautsprecher gespielt
  delay(3000);
  
  display.stopscroll(); // Rechts-Scroll wird aufgehört
  display.println("Please Scan");
  digitalWrite(7, LOW); // Grüne Lampe wird ausgeschaltet
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Please     Scan");
  display.display();

    
  }
 
 else   {
  Serial.println(" Access denied");
  digitalWrite(2, HIGH);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Access   DENIED");
  display.display();
  delay(1);
  
  display.startscrollright(0x00, 0x0F); // Scroll wird angeschaltet

  for(int i = 0; i<3000; i++){
    tone(8, i,1); // Sirene tönt
  }

  for(int i = 0; i<3000; i++){
    tone(8, i,1); // Sirene tönt
  }
  
  for(int i = 0; i<3000; i++){
    tone(8, i,1); // Sirene tönt
  }

 
  for(int i = 0; i<3000; i++){
    tone(8, i, 1); // Sirene tönt
  }
  tone(8, 1,1);
  tone(8,500,1000);

  
  delay(1000);
  display.stopscroll();
  digitalWrite(2, LOW); // Lampen werden abgeschaltet
  display.println("Please Scan");
   
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("Please     Scan");
  display.display();

  }
} 
