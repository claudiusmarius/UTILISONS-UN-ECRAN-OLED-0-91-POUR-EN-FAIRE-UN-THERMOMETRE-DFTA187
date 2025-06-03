  // Petit programme utilisant un MCU ATtiny85 associé à un LM35DZ et un mini écran Oled 0.91
  // C'est en fait un afficheur de température ambiante avec filtrage EMA
  // Auteur : Claude Dufourmont
  // Ma chaîne Youtube : https://www.youtube.com/c/ClaudeDufourmont
  // Mon GitHub : https://github.com/claudiusmarius
  // Rappel : pour programmer des ATtiny85 vous pouvez utiliser mon programmateur d'ATtiny85 ainsi que ma plaquette de développement.
  // Tous les éléments pour les reproduire à l'identique dans les vidéos ci-après :
  // https://youtu.be/1XOWKyjqMR4
  // https://youtu.be/x3gs_hjUjcw
  // Le lien de la vidéo concernant ce code est ci-dessous, il vous permettra de remonter jusque min GitHub
  // https://youtu.be/aan2i_1ifOk
  // ✳️ Précautions de câblage
  // ATtiny85 :       SDA PB0 (pin5) à brancher sur SDA écran
  //                  SCL BP2 (pin7) à brancher sur SCK écran 
  //                  Penser aussi aux résistances de pull-up sur ces 2 ports (entre le port et le + VCC) 4.7 à 10K sont des bonnes valeurs
  // Nota : l'utilisation de la librairie Tiny4kOLED.h prédermine les pinout SDA et SCL, pas besoin d'affecter les dans le setup
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // Afin de m'encourager à continuer à PARTAGER tous mes projets, vous pouvez si vous le souhaitez LIKER, COMMENTER, PARTAGER cette vidéo et même vous ABONNER à ma chaîne
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //                                          MERCI A TOUTES ET A TOUS ET A BIENTOT SUR D'AUTRES VIDEOS
  // ----------------------------------------------------------------------------------------------------------------------------------------------------------------------

  #include <TinyWireM.h>                        // Bus I2C pour ATtiny
  #include <Tiny4kOLED.h>                       // Pilote spécifique pour écran OLED SSD1306

  const int LM35_PIN = A3;                      // Broche PB3 (physique pin2)
  float temperatureEMA = 0.0;                   // Température filtrée
  const float alpha = 0.1;                      // Coefficient EMA
  const float correction = -1.6;                // Décalage température (à ajuster)
  const float scaleCorrection = 1.05;           // Correction d'échelle (à ajuster)
  float lastDisplayedTemperature = -1000.0;     // Pour forcer l’affichage au démarrage

  void setup() {
  TinyWireM.begin();
  oled.begin();
  oled.clear();
  oled.setFont(FONT8X16);                       // Police large
  oled.on();

  // Affichage initial
  oled.setCursor(2, 9);                         // Centré horizontalement
  oled.print(F("CLAUDIUSMARIUS"));
  delay(2000);                                  // Affichage pendant 2 secondes

  // Lecture initiale
  int raw = analogRead(LM35_PIN);
  float temp = (raw * 500.0) / 1024.0 + correction;
  temperatureEMA = temp;
  lastDisplayedTemperature = temperatureEMA;
  }

  void loop() 
  {
  int raw = analogRead(LM35_PIN);
  float temp = (raw * 500.0) / 1024.0 + correction;
  temp *= scaleCorrection;

  // Application du filtre EMA
  temperatureEMA = alpha * temp + (1 - alpha) * temperatureEMA;

  // Affichage de la température avec 1 décimale
  char buffer[6];
  dtostrf(temperatureEMA, 4, 1, buffer);          // Format 4 caractères, 1 décimale

  // Centrage horizontal
  int largeurTexte = strlen(buffer) * 8;
  int posX = (128 - largeurTexte) / 2;
  int posY = 12;                                  // Ligne approximative pour centrage vertical

  if (abs(temperatureEMA - lastDisplayedTemperature) >= 0.1) 
  {
  oled.clear();
  oled.setCursor(posX, posY);
  oled.println();
  oled.print ("       ");
  oled.print(buffer);
  oled.switchRenderFrame();                       // Appliquer le rendu
  lastDisplayedTemperature = temperatureEMA;
  }

  delay(1000);  // Rafraîchissement toutes les 1s
  }
