//INCLUDES
#include <keyboard.h>
#include <IRQ.h>
#include <mode7.h>
#include <port.h>

//scancode global variable init
uint8_t KeyboardList[128] = {};

//functions
void initKeyboardHandler() {
  irq_install_handler(1, keyboardHandler);
  KeyboardList[0x00] = (uint8_t) 0; //NULL
  KeyboardList[0x01] = (uint8_t) 0; //ESC
  KeyboardList[0x02] = (uint8_t) '1';
  KeyboardList[0x03] = (uint8_t) '2';
  KeyboardList[0x04] = (uint8_t) '3';
  KeyboardList[0x05] = (uint8_t) '4';
  KeyboardList[0x06] = (uint8_t) '5';
  KeyboardList[0x07] = (uint8_t) '6';
  KeyboardList[0x08] = (uint8_t) '7';
  KeyboardList[0x09] = (uint8_t) '8';
  KeyboardList[0x0A] = (uint8_t) '9';
  KeyboardList[0x0B] = (uint8_t) '0';
  KeyboardList[0x0C] = (uint8_t) '-';
  KeyboardList[0x0D] = (uint8_t) '=';
  KeyboardList[0x0E] = (uint8_t) '\b';
  KeyboardList[0x0F] = (uint8_t) '\t';

  KeyboardList[0x10] = (uint8_t) 'q';
  KeyboardList[0x11] = (uint8_t) 'w';
  KeyboardList[0x12] = (uint8_t) 'e';
  KeyboardList[0x13] = (uint8_t) 'r';
  KeyboardList[0x14] = (uint8_t) 't';
  KeyboardList[0x15] = (uint8_t) 'y';
  KeyboardList[0x16] = (uint8_t) 'u';
  KeyboardList[0x17] = (uint8_t) 'i';
  KeyboardList[0x18] = (uint8_t) 'o';
  KeyboardList[0x19] = (uint8_t) 'p';
  KeyboardList[0x1A] = (uint8_t) '[';
  KeyboardList[0x1B] = (uint8_t) ']';
  KeyboardList[0x1C] = (uint8_t) '\n';
  KeyboardList[0x1D] = (uint8_t) 0; //LCTRL
  KeyboardList[0x1E] = (uint8_t) 'a';
  KeyboardList[0x1F] = (uint8_t) 's';

  KeyboardList[0x20] = (uint8_t) 'd';
  KeyboardList[0x21] = (uint8_t) 'f';
  KeyboardList[0x22] = (uint8_t) 'g';
  KeyboardList[0x23] = (uint8_t) 'h';
  KeyboardList[0x24] = (uint8_t) 'j';
  KeyboardList[0x25] = (uint8_t) 'k';
  KeyboardList[0x26] = (uint8_t) 'l';
  KeyboardList[0x27] = (uint8_t) ';';
  KeyboardList[0x28] = (uint8_t) '\'';
  KeyboardList[0x29] = (uint8_t) '`';
  KeyboardList[0x2A] = (uint8_t) 0; //LSHFT
  KeyboardList[0x2B] = (uint8_t) '\\';
  KeyboardList[0x2C] = (uint8_t) 'z';
  KeyboardList[0x2D] = (uint8_t) 'x';
  KeyboardList[0x2E] = (uint8_t) 'c';
  KeyboardList[0x2F] = (uint8_t) 'v';

  KeyboardList[0x30] = (uint8_t) 'b';
  KeyboardList[0x31] = (uint8_t) 'n';
  KeyboardList[0x32] = (uint8_t) 'm';
  KeyboardList[0x33] = (uint8_t) ',';
  KeyboardList[0x34] = (uint8_t) '.';
  KeyboardList[0x35] = (uint8_t) '/';
  KeyboardList[0x36] = (uint8_t) 0; //RSHFT
  KeyboardList[0x37] = (uint8_t) '*';
  KeyboardList[0x38] = (uint8_t) 0; //LALT
  KeyboardList[0x39] = (uint8_t) ' ';
  KeyboardList[0x3A] = (uint8_t) 0; //CAPSLOCK
  KeyboardList[0x3B] = (uint8_t) 0; //F1
  KeyboardList[0x3C] = (uint8_t) 0; //F2
  KeyboardList[0x3D] = (uint8_t) 0; //F3
  KeyboardList[0x3E] = (uint8_t) 0; //F4
  KeyboardList[0x3F] = (uint8_t) 0; //F5

  KeyboardList[0x40] = (uint8_t) 0; //F6
  KeyboardList[0x41] = (uint8_t) 0; //F7
  KeyboardList[0x42] = (uint8_t) 0; //F8
  KeyboardList[0x43] = (uint8_t) 0; //F9
  KeyboardList[0x44] = (uint8_t) 0; //F10
  KeyboardList[0x45] = (uint8_t) 0; //NUMLOCK
  KeyboardList[0x46] = (uint8_t) 0; //SCROLL LOCK
  KeyboardList[0x47] = (uint8_t) 0; //KPAD7
  KeyboardList[0x48] = (uint8_t) 0; //KPAD8
  KeyboardList[0x49] = (uint8_t) 0; //KPAD9
  KeyboardList[0x4A] = (uint8_t) 0; //KPAD-
  KeyboardList[0x4B] = (uint8_t) 0; //KPAD4
  KeyboardList[0x4C] = (uint8_t) 0; //KPAD5
  KeyboardList[0x4D] = (uint8_t) 0; //KPAD6
  KeyboardList[0x4E] = (uint8_t) 0; //KPAD+
  KeyboardList[0x4F] = (uint8_t) 0; //KPAD1

  KeyboardList[0x50] = (uint8_t) 0; //KPAD2
  KeyboardList[0x51] = (uint8_t) 0; //KPAD3
  KeyboardList[0x52] = (uint8_t) 0; //KPAD0
  KeyboardList[0x53] = (uint8_t) 0; //KPAD.
  KeyboardList[0x54] = (uint8_t) 0; //NULL
  KeyboardList[0x55] = (uint8_t) 0; //FUNC
  KeyboardList[0x56] = (uint8_t) 0; //blank
  KeyboardList[0x57] = (uint8_t) 0; //F11
  KeyboardList[0x58] = (uint8_t) 0; //F12
  KeyboardList[0x59] = (uint8_t) 0; 
  KeyboardList[0x5A] = (uint8_t) 0;
  KeyboardList[0x5B] = (uint8_t) 0;
  KeyboardList[0x5C] = (uint8_t) 0;
  KeyboardList[0x5D] = (uint8_t) 0;
  KeyboardList[0x5E] = (uint8_t) 0;
  KeyboardList[0x5F] = (uint8_t) 0;
}

void keyboardHandler(struct isrregs *r) {
  //first setup our static variables
  static Escapes escapes = {0,0};
  //receive byte from keyboard
  KeyScanCode scancode = getKeyboardOutput();
  if (!scancode.released) {
    DisplayChar(KeyboardList[scancode.keycode]);
  }
  return;
}

KeyScanCode getKeyboardOutput() {
  //grab the output from the keyboard controller
  uint8_t keyboardOutput = inportb((uint16_t)0x60);
  
  //convert it into the KeyScanCode structure
  KeyScanCode scancode;
  scancode.released = (0b10000000 & keyboardOutput) ? 1 : 0;
  keyboardOutput << 1;
  keyboardOutput >> 1;
  scancode.keycode = keyboardOutput;

  //return the KeyScanCode structure
  return scancode;
}
