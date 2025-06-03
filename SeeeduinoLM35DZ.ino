  // Petit programme utilisant un MCU SEEEDUINO associé à un LM35DZ et un mini écran Oled 0.91
  // C'est en fait un afficheur de température ambiante.
  // Ma chaîne Youtube : https://www.youtube.com/c/ClaudeDufourmont
  // Mon GitHub : https://github.com/claudiusmarius
  // Le lien de la vidéo concernant ce code est ci-dessous, il vous permettra de remonter jusque min GitHub
  // https://youtu.be/aan2i_1ifOk
  // Précautions de câblage :
  // SEEEDUINO XIAO :       SDA D4  à brancher sur SDA écran
  //                        SCL D5  à brancher sur SCK écran 
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

  #define LM35_PIN A1
  float correction = -1.0;
  float temperatureFiltree = 0.0;
  const float alpha = 0.2;

  void setup() {
  Serial.begin(9600);
  analogReadResolution(12); // Pour ESP32 ou Seeeduino XIAO (0-4095)

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
  Serial.println(F("Échec OLED"));
  while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 15);
  display.println("CLAUDIUSMARIUS");
  display.display();
  delay(2000);

  // Lecture initiale
  int analogValue = analogRead(LM35_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  temperatureFiltree = voltage * 100.0 + correction;
  }

  void loop() 
  {
  int analogValue = analogRead(LM35_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float temperature = voltage * 100.0 + correction;

  // Filtrage EMA
  temperatureFiltree = alpha * temperature + (1 - alpha) * temperatureFiltree;

  Serial.print("Temp. EMA : ");
  Serial.print(temperatureFiltree, 1);  // 1 chiffre après la virgule
  Serial.println(" °C");

  afficherTemperature(temperatureFiltree);
  delay(1000);
  }

  void afficherTemperature(float temp) 
  {
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(20, 5);
  display.print(temp, 1);  // 1 décimale exacte (ex: 26.0, 26.3...)
  display.display();
  }
