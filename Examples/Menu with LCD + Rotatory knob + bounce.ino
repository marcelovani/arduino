#include "U8glib.h"
#include <Bounce2.h>

Bounce bounce = Bounce();

// U8GLIB_NHD27OLED_BW(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE) 

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI
// U8GLIB_SSD1306_128X64 u8g();

#define ENCODER_CLK 6
#define ENCODER_DT  7
#define ENCODER_BTN 8

enum GameModes {
  MENU = 0,
  PLAYING = 1,
  TESTING = 2,
} GameState;

// use:
// typedef enum {
//   START,
//   RUNNING,
//   GAMEOVER
// } State;

enum Menus {
  START = 0,
  TEST = 1,
} MenuState;

int menuOption = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);

  bounce.attach(ENCODER_BTN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  bounce.interval(25); // Use a debounce interval of 25 milliseconds

  u8g.setFont(u8g_font_gdb12);
  u8g.setColorIndex(1);
}

boolean buttonPressed() {
  return bounce.fell();
}

int lastClk = HIGH;
void displayMenu() {
  u8g.firstPage();
  do {
    // Check rotary knob.
    int newClk = digitalRead(ENCODER_CLK);
    if (newClk != lastClk) {
      // There was a change on the CLK pin
      lastClk = newClk;
      int dtValue = digitalRead(ENCODER_DT);
      if (newClk == LOW && dtValue == HIGH) {           
        if (menuOption < 1) {
          menuOption++;
        }
      }
      if (newClk == LOW && dtValue == LOW) {
        if (menuOption > 0) {
          menuOption--;
        }
      }
      MenuState = menuOption;
    }

    switch (MenuState) {
        case START:
          u8g.drawStr(10, 25, "> Start Game");
          u8g.drawStr(10, 45, "   Test Targets");
          if (buttonPressed()) {
            GameState = PLAYING;
          }
        break;

        case TEST:
          u8g.drawStr(10, 25, "   Start Game");
          u8g.drawStr(10, 45, "> Test Targets");
          if (buttonPressed()) {
            GameState = TESTING;
          }
          break;
      }    
  } while ( u8g.nextPage() );
}

void displayTest() {
  u8g.firstPage();
  do {
    u8g.drawStr(10, 15, "TEST MODE");
    if (buttonPressed()) {
      GameState = MENU;
    }
  } while ( u8g.nextPage() );
}

void displayScores() {
  u8g.firstPage();
  do {
    u8g.drawStr(10, 15, "Player 1: 10");
    u8g.drawStr(10, 35, "Player 2: 1");
    u8g.drawStr(10, 55, "Player 3: 0");
    if (buttonPressed()) {
      GameState = MENU;
    }
  } while ( u8g.nextPage() );
}

void loop() {
  bounce.update();

  switch (GameState) {
    case MENU:
      displayMenu();
      break;

    case PLAYING:
      displayScores();
      break;

    case TESTING:
      displayTest();
      break;
  }
}
