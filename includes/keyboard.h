#ifndef KEYBOARD_H
#define KEYBOARD_H

//**********
//includes
//**********
#include <stdint.h>
#include <registers.h>

//**********
//typedef
//**********
typedef struct escapes_struct {
  uint8_t E0 : 1;
  uint8_t E1 : 1;
} Escapes;

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

void isReleased(uint8_t);

#endif //END KEYBOARD_H
