#include "EmotionsDisplay.h"
#include "eye.h"
#include <Adafruit_SH1106.h>
extern  Adafruit_SH1106 display;  // Declare the display object as extern

int xp = 16;
int mood = 1;
int xd = 0;
int espera = 0;
int step = 0;
extern int eye_flag;

unsigned char readkey(byte emotions, byte left, byte right, byte hold) {
  unsigned char ret = 0;
  if (emotions != 0) ret = 1;  // emotions
  if (left != 0) ret += 2; // left
  if (right != 0) ret += 4; // right
  if (hold != 0) ret += 8; // hold
  return ret;
}


void emotionsDisplay(byte emotions, byte left, byte right, byte hold) {
  int n;
  static int xd = 0;
  static int espera = 0;
  static int step = 0;
  int x1, x2;
  int y = random(8, 11);
  
  if (espera > 0) {
    espera--;
    delay(1);
  } else {
    x1 = xd + (xp > 16 ? (16 + 2 * (xp - 16)) : xp);
    x2 = 64 + xd + (xp < 16 ? (-16 + (xp * 2)) : xp);
    
    switch (step) {
      case 0:
        display.clearDisplay(); // Clear the display buffer
        if (xp < 6) { 
          display.drawBitmap(x1, y, peyes[mood][2][0], 32, 32, WHITE);
          display.drawBitmap(x2, y, peyes[mood][1][1], 32, 32, WHITE);
        } else if (xp < 26) {
          display.drawBitmap(x1, y, peyes[mood][0][0], 32, 32, WHITE);
          display.drawBitmap(x2, y, peyes[mood][0][1], 32, 32, WHITE); 
        } else {
          display.drawBitmap(x1, y, peyes[mood][1][0], 32, 32, WHITE); 
          display.drawBitmap(x2, y, peyes[mood][2][1], 32, 32, WHITE);
        }
        display.display();
        espera = random(250, 1000);
        n = random(0, 7);
        if (n == 6) {
          step = 1;
        } else {
          step = 2;
        }
        break;

      case 1:
        display.clearDisplay(); // Clear the display buffer
        eye_flag = 1;
        display.drawBitmap(x1, y, eye0, 32, 32, WHITE);
        display.drawBitmap(x2, y, eye0, 32, 32, WHITE);
        display.display();
        espera = 100;
        step = 0;
        break;

      case 2:
        n = random(0, 10);
        if (n < 5) xd--;
        if (n > 5) xd++;
        if (xd < -4) xd = -3;
        if (xd > 4) xd = 3; 
        espera = 0;
        step = 0;
        break;
    }
  }

  // Read the current key state
  n = readkey(emotions, left, right, hold);

  // Update xp and mood based on input
  if (n == 2) xp = (xp <= 0 ? 0 : xp - 1); 
  if (n == 4) xp = (xp >= 32 ? 32 : xp + 1);
  
  // Update mood only if emotions are different
  if (n == 1) {
    if (emotions == 6) {
      mood = 0; // Set mood to a default when emotions is 6
    } else {
      mood = (mood >= 8 ? 0 : emotions);
    }
    delay(1000);
  }

  // Reset waiting time and step if there's any input
  if (n != 0) { 
    espera = 0;
    step = 0; 
  }
}

// void emotionsDisplay(byte emotions,byte left,byte right,byte hold){
//     int n;
//   static int xd=0;
//   static int espera=0;
//   static int step=0;
//   int x1,x2;
//   int y=random(8, 11);
//   if (espera>0) {
//     espera--;
//     delay(1);
//   } else {
//     x1=   xd+ (xp>16? (16+2*(xp-16)):xp);
//     x2=64+xd+ (xp<16? (-16+(xp*2))  :xp);
//     switch (step){
//       case 0:
//        display.clearDisplay(); // Clear the display buffer
//        if (xp<6) { 
//                display.drawBitmap(x1, y, peyes[mood][2][0], 32, 32, WHITE);
//                display.drawBitmap(x2, y, peyes[mood][1][1], 32, 32, WHITE);
//        } else if (xp<26) {
//                display.drawBitmap(x1, y, peyes[mood][0][0], 32, 32, WHITE);
//                display.drawBitmap(x2, y, peyes[mood][0][1], 32, 32, WHITE); 
//        } else {
//                display.drawBitmap(x1, y, peyes[mood][1][0], 32, 32, WHITE); 
//                display.drawBitmap(x2, y, peyes[mood][2][1], 32, 32, WHITE);
//        }
//        display.display();
//        espera=random(250, 1000);
//        n=random(0,7);
//        if (n==6) {
//           step=1;
//        } else {
//           step=2;
//        }
//        break;
//       case 1:
//        display.clearDisplay(); // Clear the display buffer
//       eye_flag=1;
//        display.drawBitmap(x1, y, eye0, 32, 32, WHITE);
//        display.drawBitmap(x2, y, eye0, 32, 32, WHITE);
//       eye_flag=1;
//        display.display();
//        espera=100;
//        step=0;
//        break;
//       case 2:
//        n=random(0,10);
//        if (n<5) xd--;
//        if (n>5) xd++;
//        if (xd<-4) xd=-3;
//        if (xd>4) xd=3; 
//        espera=0;
//        step=0;
//        break;
//     }
//   }
// //n=0;
// n=readkey( emotions,  left,  right,  hold);
// if (n==2) xp=(xp<=0?0:xp-1); 
// if (n==4) xp=(xp>=32?32:xp+1);
// if (n==1) {
//   mood=(mood>=8?0:emotions);
//  // do {} while (readkey( emotions,  left,  right,  hold)!=0);
//  delay(1000);
//   }
// if (n!=0) { 
//   espera=0; step=0; 
// }
// }