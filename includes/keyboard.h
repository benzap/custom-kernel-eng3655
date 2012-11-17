#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdint.h>
#include <registers.h>

void initKeyboardHandler();

void keyboardHandler(struct isrregs*);

#endif //END KEYBOARD_H
