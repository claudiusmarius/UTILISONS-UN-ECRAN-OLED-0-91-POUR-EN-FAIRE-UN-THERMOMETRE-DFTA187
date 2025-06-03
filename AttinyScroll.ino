  // Petit programme utilisant un MCU ATtiny85 associé à un mini écran Oled 0.91
  // C'est en fait un afficheur simplifié de texte scrollé
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


  #include <TinyWireM.h>
  #include <Tiny4kOLED.h>

  const char* message = " Hello ATtiny85! ";
  int scrollX = 128; // Position initiale, hors de l'écran à droite

  void setup() 
  {
  TinyWireM.begin();
  oled.begin();
  oled.clear();
  oled.setFont(FONT6X8);
  oled.on();
  }

  void loop() {
  // Efface proprement toute la ligne (ligne 4 = y = 24 px)
  oled.setCursor(0, 24);
  for (int i = 0; i < 128 / 6; i++) { // 6 pixels par caractère
  oled.print(' ');
  }

  // Affiche le message à la position actuelle
  oled.setCursor(scrollX, 24);
  oled.print(message);

  oled.switchRenderFrame();  // Met à jour l'affichage

  scrollX--;
  if (scrollX < -((int)strlen(message) * 6)) 
  {
  scrollX = 128;
  }

  delay(30); // Vitesse du scroll
  }
