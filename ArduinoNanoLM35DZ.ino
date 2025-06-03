  // Petit programme utilisant un MCU Arduino Nano associé à un LM35DZ et un mini écran Oled 0.91
  // C'est en fait un afficheur de température ambiante.
  // Ma chaîne Youtube : https://www.youtube.com/c/ClaudeDufourmont
  // Mon GitHub : https://github.com/claudiusmarius
  // Le lien de la vidéo concernant ce code est ci-dessous, il vous permettra de remonter jusque min GitHub
  // https://youtu.be/aan2i_1ifOk
  // Précautions de câblage :
  // SEEEDUINO XIAO :       SDA A4  à brancher sur SDA écran
  //                        SCL A5  à brancher sur SCK écran 
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Afin de m'encourager à continuer à PARTAGER tous mes projets, vous pouvez si vous le souhaitez LIKER, COMMENTER, PARTAGER cette vidéo et même vous ABONNER à ma chaîne
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                                      ENORME MERCI A TOUTES ET A TOUS
  // ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
  
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 32
  #define OLED_RESET     -1

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  #define LM35_PIN A1           // Broche analogique pour le LM35
  float correction = -1.0;      // Ajustement si besoin
  float temperatureFiltree = 0.0;
  const float alpha = 0.2;      // Coefficient de lissage EMA

  void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
  Serial.println(F("Échec de l'initialisation OLED"));
  while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 15);
  display.println("CLAUDIUSMARIUS");
  display.display();
  delay(2000);

  // Première lecture brute
  int analogValue = analogRead(LM35_PIN);
  float voltage = analogValue * (5.0 / 1023.0);  // Pour Arduino Nano (10 bits, Vref 5V)
  temperatureFiltree = voltage * 100.0 + correction;
  }

  void loop() 
  {
  int analogValue = analogRead(LM35_PIN);
  float voltage = analogValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0 + correction;

  // Filtrage EMA
  temperatureFiltree = alpha * temperature + (1 - alpha) * temperatureFiltree;

  Serial.print("Temp. EMA : ");
  Serial.print(temperatureFiltree, 1);
  Serial.println(" °C");

  afficherTemperature(temperatureFiltree);
  delay(1000);
  }

  void afficherTemperature(float temp) 
  {
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(20, 5);
  display.print(temp, 1);
  display.display();
  }
