#ifndef KEYBOARD_H
#define KEYBOARD_H

//**********
//includes
//**********
#include <stdint.h>
#include <registers.h>

//MACROS

#define ESCAPE_NONE 0
#define ESCAPE_SHIFT 1
#define ESCAPE_CAPS 2
#define ESCAPE_SHIFT_CAPS 3
#define ESCAPE_NUM 4
#define ESCAPE_E0 5
#define ESCAPE_E1 6

#define KEY_INDEX(index, escape) \
  KeyboardList[escape*128+index]
  
#define KEYPRESS_INDEX(index, escape) \
  Keyboard_bPressed[escape*128+index]

//**********
//typedef
//**********
typedef struct escapes_struct {
  uint8_t E0 : 1;
  uint8_t E1 : 1;
  uint8_t LSHIFT : 1;
  uint8_t RSHIFT : 1;
  uint8_t LCTRL : 1;
  uint8_t RCTRL : 1;
  uint8_t LALT : 1;
  uint8_t RALT : 1;
} Escapes;

typedef struct keyLEDs_struct {
  uint8_t scroll : 1;
  uint8_t caps : 1;
  uint8_t num : 1;
} keyLEDs;

typedef struct keyScanCode_struct {
  uint8_t released : 1;
  uint8_t keycode : 7;
} KeyScanCode;

//**************
//functions
//**************

//initialization and handler
void initKeyboardHandler();

void keyboardHandler(struct isrregs*);


//keyboard functions

//returns the key scancode
KeyScanCode getKeyboardOutput();

void updateKeyboardLEDs(keyLEDs leds);

#endif //END KEYBOARD_H
