#ifndef mp3_control_h
#define mp3_control_h

#include "FirstInclude.h"
#include "button_control.h"

// implement a notification class,
// its member methods will get called
//
class Mp3Notify {
public:
  static void OnError(uint16_t errorCode) {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(uint16_t track) {
    Serial.print("Track beendet");
    Serial.println(track);
    delay(100);
  }
  static void OnCardOnline(uint16_t code) {
    Serial.println(F("SD Karte online "));
  }
  static void OnCardInserted(uint16_t code) {
    Serial.println(F("SD Karte bereit "));
  }
  static void OnCardRemoved(uint16_t code) {
    Serial.println(F("SD Karte entfernt "));
  }
};

extern uint8_t CURRENT_FOLDER;

#define NumOfNotifications 100
#define Album_selected()  (CURRENT_FOLDER > 0)

extern void MP3_INIT();
extern void START_NEW_TRACK();
extern void SELECT_ALBUM();
extern void PLAY_ALBUM();
#endif

