/* 
 *  Arduino Pro Mini
 *  ATmega328p 3.3V 8Mhz
 */
#include <Servo.h>
#include "Xylophone-Songs.h";

/* Configuration */
#define pBtn 2
#define pPos 5
#define pHit 6

// Adjust to (re-)align the stick position per key
const signed char sPosData[] = {  
  0     // Dummy / Rest
  ,  7  // First
  , 20  // Second
  , 37  // etc...
  , 51
  , 67
  , 82
  , 95
  ,110
  ,134
  ,136
  ,145
};

/* Globals */
#define tPls 300
byte songs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
byte sCur, sCnt, sRnd, sBuf;
Servo sPos;
Servo sHit;

/* Program */
void hit() {
  delay(tPls);      // Delay to get the stick in position
  sHit.write(49);   // Hit
  delay(50);
  sHit.write(63);   // Release
}

void play(char *song) {   
  sPos.write(135);  // To starting position
  delay(1000);      // Wait a second....
  int i = 1;
  int s = ((byte) song[0])*10;
  while (song[i] != NULL ) {  
    if ((song[i]/10) > 0) {                   // Check for note or rest
      sPos.write(180-sPosData[song[i]/10]);   // Play the note
      hit();
    }
    delay((s/(song[i]%10))-tPls);             // Delay between notes
    i++;
  }  
}

void setup() {
  sCnt = sizeof(songs);
  sCur = sCnt-1;
  sRnd = 0;
  sBuf = 0;
  delay(2000);
  pinMode(pBtn, INPUT_PULLUP);  
  randomSeed(analogRead(0));  
  sPos.attach(pPos);  
  sHit.attach(pHit);
  sPos.write(135);
  sHit.write(63);  
}

void loop() {   
  delay(50);                              // Save some resources
  if (digitalRead(pBtn) == LOW) {    
    if (sCur == sCnt-1) {                 // When at end of the playlist
      for (byte i = 0; i <= sCnt; i++) {  // Randomize playlist
        sRnd = random(0,sCnt-1);
        sBuf = songs[sRnd];
        songs[sRnd] = songs[i];
        songs[i] = sBuf;
      }
      sCur = 0;
    }
    switch (songs[sCur]) {                // Play song in playlist
      case  1: play(song01); break;
      case  2: play(song02); break;
      case  3: play(song03); break;
      case  4: play(song04); break;
      case  5: play(song05); break;
      case  6: play(song06); break;
      case  7: play(song07); break;
      case  8: play(song08); break;
      case  9: play(song09); break;
      case 10: play(song10); break;
      case 11: play(song11); break;
      case 12: play(song12); break;
      case 13: play(song13); break;
      case 14: play(song14); break;
      case 15: play(song15); break;
      case 16: play(song16); break;    
    }
    sCur++;
  }  
}
