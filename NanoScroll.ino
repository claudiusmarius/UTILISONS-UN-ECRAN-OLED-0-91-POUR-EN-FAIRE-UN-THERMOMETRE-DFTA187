  //nano seeeduino esp32
   // Petit programme utilisant 3 MCU associés à un mini écran Oled 0.91
  // C'est en fait un afficheur de message scrollé
  // Ma chaîne Youtube : https://www.youtube.com/c/ClaudeDufourmont
  // Mon GitHub : https://github.com/claudiusmarius
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Afin de m'encourager à continuer à PARTAGER tous mes projets, vous pouvez si vous le souhaitez LIKER, COMMENTER, PARTAGER cette vidéo et même vous ABONNER à ma chaîne
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Le lien de la vidéo concernant ce code est ci-dessous, il vous permettra de remonter jusque min GitHub
  //
  // Compatibilité multi-cartes avec affichage OLED I2C
  // Arduino NANO
  // Seeeduino XIAO
  // ESP32 DEV module

  // ✳️ Précautions de câblage
  // Penser à brancher le VCC de l'écran sur la sortie 3.3V du MCU
  // Arduino Nano :   SDA A4 à brancher sur SDA écran
  //                  SCL A5 à brancher sur SDK écran
  // Seeeduino XIAO : SDA D4 à brancher sur SDA écran
  //                  SCL D5 à brancher sur SDK écran
  // ESP32 DEV KIT :  SDA GPIO21 à brancher sur SDA écran
  //                  SCL GPIO22 à brancher sur SDK écran 
  // Ce code est compatible intégralement avec les 3 MCU, prendre garde à la connection à réaliser ci dessus

  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 32

  #define OLED_RESET     -1
  #define SCREEN_ADDRESS 0x3C
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  String youtubeURL = "https://www.youtube.com/c/ClaudeDufourmont";
  int16_t scrollX;

  void setup() 
  {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
  for (;;);
  }

  // ⏱ Affichage CLAUDIUS + GitHub pendant 5 secondes
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("CLAUDIUS");

  display.setTextSize(1);
  display.setCursor(0, 17);
  display.print("https://github.com/claudiusmarius");
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
  delay(100);

  // 🧹 Efface les 2 premières lignes (0–15)
  display.fillRect(0, 0, SCREEN_WIDTH, 24, SSD1306_BLACK);
  display.display();

  scrollX = SCREEN_WIDTH;
  }

  void loop() 
  {
  display.fillRect(0, 24, SCREEN_WIDTH, 8, SSD1306_BLACK); // Efface proprement la ligne du scroll

  // 🎬 Texte défilant sur ligne 4 (y = 24–31)
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(scrollX, 24);
  display.print(youtubeURL);
  
  display.display();

  scrollX--;

  int16_t textWidth = youtubeURL.length() * 6;
  if (scrollX < -textWidth) {
  scrollX = SCREEN_WIDTH;
  delay(1000);  // pause entre deux scrolls
  }

  delay(30);
  }







