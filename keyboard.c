//INCLUDES
#include <keyboard.h>
#include <IRQ.h>
#include <mode7.h>
#include <port.h>
#include <scancode.h>

//scancode global variable init
uint8_t KeyboardList[1024] = {};
uint8_t Keyboard_bPressed[1024] = {};
//functions
void initKeyboardHandler() {
  //add handler to list of IRQs
  irq_install_handler(1, keyboardHandler);

  //initialize keyboard listing with keymappings and keypresses
  //zero it first
  for (int i = 0; i < 1024; i++) {
    KeyboardList[i] = 0;
    Keyboard_bPressed[i] = 0;
  }

  //keymappings with no escapes
  KEY_INDEX(0x00, ESCAPE_NONE) = (uint8_t) 0; //NULL
  KEY_INDEX(0x01, ESCAPE_NONE) = (uint8_t) 0; //ESC
  KEY_INDEX(0x02, ESCAPE_NONE) = (uint8_t) '1';
  KEY_INDEX(0x03, ESCAPE_NONE) = (uint8_t) '2';
  KEY_INDEX(0x04, ESCAPE_NONE) = (uint8_t) '3';
  KEY_INDEX(0x05, ESCAPE_NONE) = (uint8_t) '4';
  KEY_INDEX(0x06, ESCAPE_NONE) = (uint8_t) '5';
  KEY_INDEX(0x07, ESCAPE_NONE) = (uint8_t) '6';
  KEY_INDEX(0x08, ESCAPE_NONE) = (uint8_t) '7';
  KEY_INDEX(0x09, ESCAPE_NONE) = (uint8_t) '8';
  KEY_INDEX(0x0A, ESCAPE_NONE) = (uint8_t) '9';
  KEY_INDEX(0x0B, ESCAPE_NONE) = (uint8_t) '0';
  KEY_INDEX(0x0C, ESCAPE_NONE) = (uint8_t) '-';
  KEY_INDEX(0x0D, ESCAPE_NONE) = (uint8_t) '=';
  KEY_INDEX(0x0E, ESCAPE_NONE) = (uint8_t) '\b';
  KEY_INDEX(0x0F, ESCAPE_NONE) = (uint8_t) '\t';

  KEY_INDEX(0x10, ESCAPE_NONE) = (uint8_t) 'q';
  KEY_INDEX(0x11, ESCAPE_NONE) = (uint8_t) 'w';
  KEY_INDEX(0x12, ESCAPE_NONE) = (uint8_t) 'e';
  KEY_INDEX(0x13, ESCAPE_NONE) = (uint8_t) 'r';
  KEY_INDEX(0x14, ESCAPE_NONE) = (uint8_t) 't';
  KEY_INDEX(0x15, ESCAPE_NONE) = (uint8_t) 'y';
  KEY_INDEX(0x16, ESCAPE_NONE) = (uint8_t) 'u';
  KEY_INDEX(0x17, ESCAPE_NONE) = (uint8_t) 'i';
  KEY_INDEX(0x18, ESCAPE_NONE) = (uint8_t) 'o';
  KEY_INDEX(0x19, ESCAPE_NONE) = (uint8_t) 'p';
  KEY_INDEX(0x1A, ESCAPE_NONE) = (uint8_t) '[';
  KEY_INDEX(0x1B, ESCAPE_NONE) = (uint8_t) ']';
  KEY_INDEX(0x1C, ESCAPE_NONE) = (uint8_t) '\n';
  KEY_INDEX(0x1D, ESCAPE_NONE) = (uint8_t) 0; //LCTRL
  KEY_INDEX(0x1E, ESCAPE_NONE) = (uint8_t) 'a';
  KEY_INDEX(0x1F, ESCAPE_NONE) = (uint8_t) 's';

  KEY_INDEX(0x20, ESCAPE_NONE) = (uint8_t) 'd';
  KEY_INDEX(0x21, ESCAPE_NONE) = (uint8_t) 'f';
  KEY_INDEX(0x22, ESCAPE_NONE) = (uint8_t) 'g';
  KEY_INDEX(0x23, ESCAPE_NONE) = (uint8_t) 'h';
  KEY_INDEX(0x24, ESCAPE_NONE) = (uint8_t) 'j';
  KEY_INDEX(0x25, ESCAPE_NONE) = (uint8_t) 'k';
  KEY_INDEX(0x26, ESCAPE_NONE) = (uint8_t) 'l';
  KEY_INDEX(0x27, ESCAPE_NONE) = (uint8_t) ';';
  KEY_INDEX(0x28, ESCAPE_NONE) = (uint8_t) '\'';
  KEY_INDEX(0x29, ESCAPE_NONE) = (uint8_t) '`';
  KEY_INDEX(0x2A, ESCAPE_NONE) = (uint8_t) 0; //LSHFT
  KEY_INDEX(0x2B, ESCAPE_NONE) = (uint8_t) '\\';
  KEY_INDEX(0x2C, ESCAPE_NONE) = (uint8_t) 'z';
  KEY_INDEX(0x2D, ESCAPE_NONE) = (uint8_t) 'x';
  KEY_INDEX(0x2E, ESCAPE_NONE) = (uint8_t) 'c';
  KEY_INDEX(0x2F, ESCAPE_NONE) = (uint8_t) 'v';

  KEY_INDEX(0x30, ESCAPE_NONE) = (uint8_t) 'b';
  KEY_INDEX(0x31, ESCAPE_NONE) = (uint8_t) 'n';
  KEY_INDEX(0x32, ESCAPE_NONE) = (uint8_t) 'm';
  KEY_INDEX(0x33, ESCAPE_NONE) = (uint8_t) ',';
  KEY_INDEX(0x34, ESCAPE_NONE) = (uint8_t) '.';
  KEY_INDEX(0x35, ESCAPE_NONE) = (uint8_t) '/';
  KEY_INDEX(0x36, ESCAPE_NONE) = (uint8_t) 0; //RSHFT
  KEY_INDEX(0x37, ESCAPE_NONE) = (uint8_t) '*';
  KEY_INDEX(0x38, ESCAPE_NONE) = (uint8_t) 0; //LALT
  KEY_INDEX(0x39, ESCAPE_NONE) = (uint8_t) ' ';
  KEY_INDEX(0x3A, ESCAPE_NONE) = (uint8_t) 0; //CAPSLOCK
  KEY_INDEX(0x3B, ESCAPE_NONE) = (uint8_t) 0; //F1
  KEY_INDEX(0x3C, ESCAPE_NONE) = (uint8_t) 0; //F2
  KEY_INDEX(0x3D, ESCAPE_NONE) = (uint8_t) 0; //F3
  KEY_INDEX(0x3E, ESCAPE_NONE) = (uint8_t) 0; //F4
  KEY_INDEX(0x3F, ESCAPE_NONE) = (uint8_t) 0; //F5

  KEY_INDEX(0x40, ESCAPE_NONE) = (uint8_t) 0; //F6
  KEY_INDEX(0x41, ESCAPE_NONE) = (uint8_t) 0; //F7
  KEY_INDEX(0x42, ESCAPE_NONE) = (uint8_t) 0; //F8
  KEY_INDEX(0x43, ESCAPE_NONE) = (uint8_t) 0; //F9
  KEY_INDEX(0x44, ESCAPE_NONE) = (uint8_t) 0; //F10
  KEY_INDEX(0x45, ESCAPE_NONE) = (uint8_t) 0; //NUMLOCK
  KEY_INDEX(0x46, ESCAPE_NONE) = (uint8_t) 0; //SCROLL LOCK
  KEY_INDEX(0x47, ESCAPE_NONE) = (uint8_t) '7'; //KPAD7
  KEY_INDEX(0x48, ESCAPE_NONE) = (uint8_t) '8'; //KPAD8
  KEY_INDEX(0x49, ESCAPE_NONE) = (uint8_t) '9'; //KPAD9
  KEY_INDEX(0x4A, ESCAPE_NONE) = (uint8_t) '-'; //KPAD-
  KEY_INDEX(0x4B, ESCAPE_NONE) = (uint8_t) '4'; //KPAD4
  KEY_INDEX(0x4C, ESCAPE_NONE) = (uint8_t) '5'; //KPAD5
  KEY_INDEX(0x4D, ESCAPE_NONE) = (uint8_t) '6'; //KPAD6
  KEY_INDEX(0x4E, ESCAPE_NONE) = (uint8_t) '+'; //KPAD+
  KEY_INDEX(0x4F, ESCAPE_NONE) = (uint8_t) '1'; //KPAD1

  KEY_INDEX(0x50, ESCAPE_NONE) = (uint8_t) '2'; //KPAD2
  KEY_INDEX(0x51, ESCAPE_NONE) = (uint8_t) '3'; //KPAD3
  KEY_INDEX(0x52, ESCAPE_NONE) = (uint8_t) '0'; //KPAD0
  KEY_INDEX(0x53, ESCAPE_NONE) = (uint8_t) '.'; //KPAD.
  KEY_INDEX(0x54, ESCAPE_NONE) = (uint8_t) 0; //NULL
  KEY_INDEX(0x55, ESCAPE_NONE) = (uint8_t) 0; //FUNC
  KEY_INDEX(0x56, ESCAPE_NONE) = (uint8_t) 0; //blank
  KEY_INDEX(0x57, ESCAPE_NONE) = (uint8_t) 0; //F11
  KEY_INDEX(0x58, ESCAPE_NONE) = (uint8_t) 0; //F12
  KEY_INDEX(0x59, ESCAPE_NONE) = (uint8_t) 0; 
  KEY_INDEX(0x5A, ESCAPE_NONE) = (uint8_t) 0;
  KEY_INDEX(0x5B, ESCAPE_NONE) = (uint8_t) 0;
  KEY_INDEX(0x5C, ESCAPE_NONE) = (uint8_t) 0;
  KEY_INDEX(0x5D, ESCAPE_NONE) = (uint8_t) 0;
  KEY_INDEX(0x5E, ESCAPE_NONE) = (uint8_t) 0;
  KEY_INDEX(0x5F, ESCAPE_NONE) = (uint8_t) 0;

  //escaped with shift
  KEY_INDEX(0x00, ESCAPE_SHIFT) = (uint8_t) 0; //NULL
  KEY_INDEX(0x01, ESCAPE_SHIFT) = (uint8_t) 0; //ESC
  KEY_INDEX(0x02, ESCAPE_SHIFT) = (uint8_t) '!';
  KEY_INDEX(0x03, ESCAPE_SHIFT) = (uint8_t) '@';
  KEY_INDEX(0x04, ESCAPE_SHIFT) = (uint8_t) '#';
  KEY_INDEX(0x05, ESCAPE_SHIFT) = (uint8_t) '$';
  KEY_INDEX(0x06, ESCAPE_SHIFT) = (uint8_t) '%';
  KEY_INDEX(0x07, ESCAPE_SHIFT) = (uint8_t) '^';
  KEY_INDEX(0x08, ESCAPE_SHIFT) = (uint8_t) '&';
  KEY_INDEX(0x09, ESCAPE_SHIFT) = (uint8_t) '*';
  KEY_INDEX(0x0A, ESCAPE_SHIFT) = (uint8_t) '(';
  KEY_INDEX(0x0B, ESCAPE_SHIFT) = (uint8_t) ')';
  KEY_INDEX(0x0C, ESCAPE_SHIFT) = (uint8_t) '_';
  KEY_INDEX(0x0D, ESCAPE_SHIFT) = (uint8_t) '+';
  KEY_INDEX(0x0E, ESCAPE_SHIFT) = (uint8_t) '\b';
  KEY_INDEX(0x0F, ESCAPE_SHIFT) = (uint8_t) '\t';

  KEY_INDEX(0x10, ESCAPE_SHIFT) = (uint8_t) 'Q';
  KEY_INDEX(0x11, ESCAPE_SHIFT) = (uint8_t) 'W';
  KEY_INDEX(0x12, ESCAPE_SHIFT) = (uint8_t) 'E';
  KEY_INDEX(0x13, ESCAPE_SHIFT) = (uint8_t) 'R';
  KEY_INDEX(0x14, ESCAPE_SHIFT) = (uint8_t) 'T';
  KEY_INDEX(0x15, ESCAPE_SHIFT) = (uint8_t) 'Y';
  KEY_INDEX(0x16, ESCAPE_SHIFT) = (uint8_t) 'U';
  KEY_INDEX(0x17, ESCAPE_SHIFT) = (uint8_t) 'I';
  KEY_INDEX(0x18, ESCAPE_SHIFT) = (uint8_t) 'O';
  KEY_INDEX(0x19, ESCAPE_SHIFT) = (uint8_t) 'P';
  KEY_INDEX(0x1A, ESCAPE_SHIFT) = (uint8_t) '{';
  KEY_INDEX(0x1B, ESCAPE_SHIFT) = (uint8_t) '}';
  KEY_INDEX(0x1C, ESCAPE_SHIFT) = (uint8_t) '\n';
  KEY_INDEX(0x1D, ESCAPE_SHIFT) = (uint8_t) 0; //LCTRL
  KEY_INDEX(0x1E, ESCAPE_SHIFT) = (uint8_t) 'A';
  KEY_INDEX(0x1F, ESCAPE_SHIFT) = (uint8_t) 'S';

  KEY_INDEX(0x20, ESCAPE_SHIFT) = (uint8_t) 'D';
  KEY_INDEX(0x21, ESCAPE_SHIFT) = (uint8_t) 'F';
  KEY_INDEX(0x22, ESCAPE_SHIFT) = (uint8_t) 'G';
  KEY_INDEX(0x23, ESCAPE_SHIFT) = (uint8_t) 'H';
  KEY_INDEX(0x24, ESCAPE_SHIFT) = (uint8_t) 'J';
  KEY_INDEX(0x25, ESCAPE_SHIFT) = (uint8_t) 'K';
  KEY_INDEX(0x26, ESCAPE_SHIFT) = (uint8_t) 'L';
  KEY_INDEX(0x27, ESCAPE_SHIFT) = (uint8_t) ':';
  KEY_INDEX(0x28, ESCAPE_SHIFT) = (uint8_t) '"';
  KEY_INDEX(0x29, ESCAPE_SHIFT) = (uint8_t) '~';
  KEY_INDEX(0x2A, ESCAPE_SHIFT) = (uint8_t) 0; //LSHFT
  KEY_INDEX(0x2B, ESCAPE_SHIFT) = (uint8_t) '|';
  KEY_INDEX(0x2C, ESCAPE_SHIFT) = (uint8_t) 'Z';
  KEY_INDEX(0x2D, ESCAPE_SHIFT) = (uint8_t) 'X';
  KEY_INDEX(0x2E, ESCAPE_SHIFT) = (uint8_t) 'C';
  KEY_INDEX(0x2F, ESCAPE_SHIFT) = (uint8_t) 'V';

  KEY_INDEX(0x30, ESCAPE_SHIFT) = (uint8_t) 'B';
  KEY_INDEX(0x31, ESCAPE_SHIFT) = (uint8_t) 'N';
  KEY_INDEX(0x32, ESCAPE_SHIFT) = (uint8_t) 'M';
  KEY_INDEX(0x33, ESCAPE_SHIFT) = (uint8_t) '<';
  KEY_INDEX(0x34, ESCAPE_SHIFT) = (uint8_t) '>';
  KEY_INDEX(0x35, ESCAPE_SHIFT) = (uint8_t) '?';
  KEY_INDEX(0x36, ESCAPE_SHIFT) = (uint8_t) 0; //RSHFT
  KEY_INDEX(0x37, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x38, ESCAPE_SHIFT) = (uint8_t) 0; //LALT
  KEY_INDEX(0x39, ESCAPE_SHIFT) = (uint8_t) ' ';
  KEY_INDEX(0x3A, ESCAPE_SHIFT) = (uint8_t) 0; //CAPSLOCK
  KEY_INDEX(0x3B, ESCAPE_SHIFT) = (uint8_t) 0; //F1
  KEY_INDEX(0x3C, ESCAPE_SHIFT) = (uint8_t) 0; //F2
  KEY_INDEX(0x3D, ESCAPE_SHIFT) = (uint8_t) 0; //F3
  KEY_INDEX(0x3E, ESCAPE_SHIFT) = (uint8_t) 0; //F4
  KEY_INDEX(0x3F, ESCAPE_SHIFT) = (uint8_t) 0; //F5

  KEY_INDEX(0x40, ESCAPE_SHIFT) = (uint8_t) 0; //F6
  KEY_INDEX(0x41, ESCAPE_SHIFT) = (uint8_t) 0; //F7
  KEY_INDEX(0x42, ESCAPE_SHIFT) = (uint8_t) 0; //F8
  KEY_INDEX(0x43, ESCAPE_SHIFT) = (uint8_t) 0; //F9
  KEY_INDEX(0x44, ESCAPE_SHIFT) = (uint8_t) 0; //F10
  KEY_INDEX(0x45, ESCAPE_SHIFT) = (uint8_t) 0; //NUMLOCK
  KEY_INDEX(0x46, ESCAPE_SHIFT) = (uint8_t) 0; //SCROLL LOCK
  KEY_INDEX(0x47, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD7
  KEY_INDEX(0x48, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD8
  KEY_INDEX(0x49, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD9
  KEY_INDEX(0x4A, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD-
  KEY_INDEX(0x4B, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD4
  KEY_INDEX(0x4C, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD5
  KEY_INDEX(0x4D, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD6
  KEY_INDEX(0x4E, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD+
  KEY_INDEX(0x4F, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD1

  KEY_INDEX(0x50, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD2
  KEY_INDEX(0x51, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD3
  KEY_INDEX(0x52, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD0
  KEY_INDEX(0x53, ESCAPE_SHIFT) = (uint8_t) 0; //KPAD.
  KEY_INDEX(0x54, ESCAPE_SHIFT) = (uint8_t) 0; //NULL
  KEY_INDEX(0x55, ESCAPE_SHIFT) = (uint8_t) 0; //FUNC
  KEY_INDEX(0x56, ESCAPE_SHIFT) = (uint8_t) 0; //blank
  KEY_INDEX(0x57, ESCAPE_SHIFT) = (uint8_t) 0; //F11
  KEY_INDEX(0x58, ESCAPE_SHIFT) = (uint8_t) 0; //F12
  KEY_INDEX(0x59, ESCAPE_SHIFT) = (uint8_t) 0; 
  KEY_INDEX(0x5A, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x5B, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x5C, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x5D, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x5E, ESCAPE_SHIFT) = (uint8_t) 0;
  KEY_INDEX(0x5F, ESCAPE_SHIFT) = (uint8_t) 0;
  
  //escaped with caps lock
  KEY_INDEX(0x00, ESCAPE_CAPS) = (uint8_t) 0; //NULL
  KEY_INDEX(0x01, ESCAPE_CAPS) = (uint8_t) 0; //ESC
  KEY_INDEX(0x02, ESCAPE_CAPS) = (uint8_t) '1';
  KEY_INDEX(0x03, ESCAPE_CAPS) = (uint8_t) '2';
  KEY_INDEX(0x04, ESCAPE_CAPS) = (uint8_t) '3';
  KEY_INDEX(0x05, ESCAPE_CAPS) = (uint8_t) '4';
  KEY_INDEX(0x06, ESCAPE_CAPS) = (uint8_t) '5';
  KEY_INDEX(0x07, ESCAPE_CAPS) = (uint8_t) '6';
  KEY_INDEX(0x08, ESCAPE_CAPS) = (uint8_t) '7';
  KEY_INDEX(0x09, ESCAPE_CAPS) = (uint8_t) '8';
  KEY_INDEX(0x0A, ESCAPE_CAPS) = (uint8_t) '9';
  KEY_INDEX(0x0B, ESCAPE_CAPS) = (uint8_t) '0';
  KEY_INDEX(0x0C, ESCAPE_CAPS) = (uint8_t) '-';
  KEY_INDEX(0x0D, ESCAPE_CAPS) = (uint8_t) '=';
  KEY_INDEX(0x0E, ESCAPE_CAPS) = (uint8_t) '\b';
  KEY_INDEX(0x0F, ESCAPE_CAPS) = (uint8_t) '\t';

  KEY_INDEX(0x10, ESCAPE_CAPS) = (uint8_t) 'Q';
  KEY_INDEX(0x11, ESCAPE_CAPS) = (uint8_t) 'W';
  KEY_INDEX(0x12, ESCAPE_CAPS) = (uint8_t) 'E';
  KEY_INDEX(0x13, ESCAPE_CAPS) = (uint8_t) 'R';
  KEY_INDEX(0x14, ESCAPE_CAPS) = (uint8_t) 'T';
  KEY_INDEX(0x15, ESCAPE_CAPS) = (uint8_t) 'Y';
  KEY_INDEX(0x16, ESCAPE_CAPS) = (uint8_t) 'U';
  KEY_INDEX(0x17, ESCAPE_CAPS) = (uint8_t) 'I';
  KEY_INDEX(0x18, ESCAPE_CAPS) = (uint8_t) 'O';
  KEY_INDEX(0x19, ESCAPE_CAPS) = (uint8_t) 'P';
  KEY_INDEX(0x1A, ESCAPE_CAPS) = (uint8_t) '[';
  KEY_INDEX(0x1B, ESCAPE_CAPS) = (uint8_t) ']';
  KEY_INDEX(0x1C, ESCAPE_CAPS) = (uint8_t) '\n';
  KEY_INDEX(0x1D, ESCAPE_CAPS) = (uint8_t) 0; //LCTRL
  KEY_INDEX(0x1E, ESCAPE_CAPS) = (uint8_t) 'A';
  KEY_INDEX(0x1F, ESCAPE_CAPS) = (uint8_t) 'S';

  KEY_INDEX(0x20, ESCAPE_CAPS) = (uint8_t) 'D';
  KEY_INDEX(0x21, ESCAPE_CAPS) = (uint8_t) 'F';
  KEY_INDEX(0x22, ESCAPE_CAPS) = (uint8_t) 'G';
  KEY_INDEX(0x23, ESCAPE_CAPS) = (uint8_t) 'H';
  KEY_INDEX(0x24, ESCAPE_CAPS) = (uint8_t) 'J';
  KEY_INDEX(0x25, ESCAPE_CAPS) = (uint8_t) 'K';
  KEY_INDEX(0x26, ESCAPE_CAPS) = (uint8_t) 'L';
  KEY_INDEX(0x27, ESCAPE_CAPS) = (uint8_t) ';';
  KEY_INDEX(0x28, ESCAPE_CAPS) = (uint8_t) '\'';
  KEY_INDEX(0x29, ESCAPE_CAPS) = (uint8_t) '`';
  KEY_INDEX(0x2A, ESCAPE_CAPS) = (uint8_t) 0; //LSHFT
  KEY_INDEX(0x2B, ESCAPE_CAPS) = (uint8_t) '\\';
  KEY_INDEX(0x2C, ESCAPE_CAPS) = (uint8_t) 'Z';
  KEY_INDEX(0x2D, ESCAPE_CAPS) = (uint8_t) 'X';
  KEY_INDEX(0x2E, ESCAPE_CAPS) = (uint8_t) 'C';
  KEY_INDEX(0x2F, ESCAPE_CAPS) = (uint8_t) 'V';

  KEY_INDEX(0x30, ESCAPE_CAPS) = (uint8_t) 'B';
  KEY_INDEX(0x31, ESCAPE_CAPS) = (uint8_t) 'N';
  KEY_INDEX(0x32, ESCAPE_CAPS) = (uint8_t) 'M';
  KEY_INDEX(0x33, ESCAPE_CAPS) = (uint8_t) ',';
  KEY_INDEX(0x34, ESCAPE_CAPS) = (uint8_t) '.';
  KEY_INDEX(0x35, ESCAPE_CAPS) = (uint8_t) '/';
  KEY_INDEX(0x36, ESCAPE_CAPS) = (uint8_t) 0; //RSHFT
  KEY_INDEX(0x37, ESCAPE_CAPS) = (uint8_t) '*';
  KEY_INDEX(0x38, ESCAPE_CAPS) = (uint8_t) 0; //LALT
  KEY_INDEX(0x39, ESCAPE_CAPS) = (uint8_t) ' ';
  KEY_INDEX(0x3A, ESCAPE_CAPS) = (uint8_t) 0; //CAPSLOCK
  KEY_INDEX(0x3B, ESCAPE_CAPS) = (uint8_t) 0; //F1
  KEY_INDEX(0x3C, ESCAPE_CAPS) = (uint8_t) 0; //F2
  KEY_INDEX(0x3D, ESCAPE_CAPS) = (uint8_t) 0; //F3
  KEY_INDEX(0x3E, ESCAPE_CAPS) = (uint8_t) 0; //F4
  KEY_INDEX(0x3F, ESCAPE_CAPS) = (uint8_t) 0; //F5

  KEY_INDEX(0x40, ESCAPE_CAPS) = (uint8_t) 0; //F6
  KEY_INDEX(0x41, ESCAPE_CAPS) = (uint8_t) 0; //F7
  KEY_INDEX(0x42, ESCAPE_CAPS) = (uint8_t) 0; //F8
  KEY_INDEX(0x43, ESCAPE_CAPS) = (uint8_t) 0; //F9
  KEY_INDEX(0x44, ESCAPE_CAPS) = (uint8_t) 0; //F10
  KEY_INDEX(0x45, ESCAPE_CAPS) = (uint8_t) 0; //NUMLOCK
  KEY_INDEX(0x46, ESCAPE_CAPS) = (uint8_t) 0; //SCROLL LOCK
  KEY_INDEX(0x47, ESCAPE_CAPS) = (uint8_t) '7'; //KPAD7
  KEY_INDEX(0x48, ESCAPE_CAPS) = (uint8_t) '8'; //KPAD8
  KEY_INDEX(0x49, ESCAPE_CAPS) = (uint8_t) '9'; //KPAD9
  KEY_INDEX(0x4A, ESCAPE_CAPS) = (uint8_t) '-'; //KPAD-
  KEY_INDEX(0x4B, ESCAPE_CAPS) = (uint8_t) '4'; //KPAD4
  KEY_INDEX(0x4C, ESCAPE_CAPS) = (uint8_t) '5'; //KPAD5
  KEY_INDEX(0x4D, ESCAPE_CAPS) = (uint8_t) '6'; //KPAD6
  KEY_INDEX(0x4E, ESCAPE_CAPS) = (uint8_t) '+'; //KPAD+
  KEY_INDEX(0x4F, ESCAPE_CAPS) = (uint8_t) '1'; //KPAD1

  KEY_INDEX(0x50, ESCAPE_CAPS) = (uint8_t) '2'; //KPAD2
  KEY_INDEX(0x51, ESCAPE_CAPS) = (uint8_t) '3'; //KPAD3
  KEY_INDEX(0x52, ESCAPE_CAPS) = (uint8_t) '0'; //KPAD0
  KEY_INDEX(0x53, ESCAPE_CAPS) = (uint8_t) '.'; //KPAD.
  KEY_INDEX(0x54, ESCAPE_CAPS) = (uint8_t) 0; //NULL
  KEY_INDEX(0x55, ESCAPE_CAPS) = (uint8_t) 0; //FUNC
  KEY_INDEX(0x56, ESCAPE_CAPS) = (uint8_t) 0; //blank
  KEY_INDEX(0x57, ESCAPE_CAPS) = (uint8_t) 0; //F11
  KEY_INDEX(0x58, ESCAPE_CAPS) = (uint8_t) 0; //F12
  KEY_INDEX(0x59, ESCAPE_CAPS) = (uint8_t) 0; 
  KEY_INDEX(0x5A, ESCAPE_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5B, ESCAPE_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5C, ESCAPE_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5D, ESCAPE_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5E, ESCAPE_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5F, ESCAPE_CAPS) = (uint8_t) 0;

  //escaped with shift and caps lock
  KEY_INDEX(0x00, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //NULL
  KEY_INDEX(0x01, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //ESC
  KEY_INDEX(0x02, ESCAPE_SHIFT_CAPS) = (uint8_t) '!';
  KEY_INDEX(0x03, ESCAPE_SHIFT_CAPS) = (uint8_t) '@';
  KEY_INDEX(0x04, ESCAPE_SHIFT_CAPS) = (uint8_t) '#';
  KEY_INDEX(0x05, ESCAPE_SHIFT_CAPS) = (uint8_t) '$';
  KEY_INDEX(0x06, ESCAPE_SHIFT_CAPS) = (uint8_t) '%';
  KEY_INDEX(0x07, ESCAPE_SHIFT_CAPS) = (uint8_t) '^';
  KEY_INDEX(0x08, ESCAPE_SHIFT_CAPS) = (uint8_t) '&';
  KEY_INDEX(0x09, ESCAPE_SHIFT_CAPS) = (uint8_t) '*';
  KEY_INDEX(0x0A, ESCAPE_SHIFT_CAPS) = (uint8_t) '(';
  KEY_INDEX(0x0B, ESCAPE_SHIFT_CAPS) = (uint8_t) ')';
  KEY_INDEX(0x0C, ESCAPE_SHIFT_CAPS) = (uint8_t) '_';
  KEY_INDEX(0x0D, ESCAPE_SHIFT_CAPS) = (uint8_t) '+';
  KEY_INDEX(0x0E, ESCAPE_SHIFT_CAPS) = (uint8_t) '\b';
  KEY_INDEX(0x0F, ESCAPE_SHIFT_CAPS) = (uint8_t) '\t';

  KEY_INDEX(0x10, ESCAPE_SHIFT_CAPS) = (uint8_t) 'q';
  KEY_INDEX(0x11, ESCAPE_SHIFT_CAPS) = (uint8_t) 'w';
  KEY_INDEX(0x12, ESCAPE_SHIFT_CAPS) = (uint8_t) 'e';
  KEY_INDEX(0x13, ESCAPE_SHIFT_CAPS) = (uint8_t) 'r';
  KEY_INDEX(0x14, ESCAPE_SHIFT_CAPS) = (uint8_t) 't';
  KEY_INDEX(0x15, ESCAPE_SHIFT_CAPS) = (uint8_t) 'y';
  KEY_INDEX(0x16, ESCAPE_SHIFT_CAPS) = (uint8_t) 'u';
  KEY_INDEX(0x17, ESCAPE_SHIFT_CAPS) = (uint8_t) 'i';
  KEY_INDEX(0x18, ESCAPE_SHIFT_CAPS) = (uint8_t) 'o';
  KEY_INDEX(0x19, ESCAPE_SHIFT_CAPS) = (uint8_t) 'p';
  KEY_INDEX(0x1A, ESCAPE_SHIFT_CAPS) = (uint8_t) '{';
  KEY_INDEX(0x1B, ESCAPE_SHIFT_CAPS) = (uint8_t) '}';
  KEY_INDEX(0x1C, ESCAPE_SHIFT_CAPS) = (uint8_t) '\n';
  KEY_INDEX(0x1D, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //LCTRL
  KEY_INDEX(0x1E, ESCAPE_SHIFT_CAPS) = (uint8_t) 'a';
  KEY_INDEX(0x1F, ESCAPE_SHIFT_CAPS) = (uint8_t) 's';

  KEY_INDEX(0x20, ESCAPE_SHIFT_CAPS) = (uint8_t) 'd';
  KEY_INDEX(0x21, ESCAPE_SHIFT_CAPS) = (uint8_t) 'f';
  KEY_INDEX(0x22, ESCAPE_SHIFT_CAPS) = (uint8_t) 'g';
  KEY_INDEX(0x23, ESCAPE_SHIFT_CAPS) = (uint8_t) 'h';
  KEY_INDEX(0x24, ESCAPE_SHIFT_CAPS) = (uint8_t) 'j';
  KEY_INDEX(0x25, ESCAPE_SHIFT_CAPS) = (uint8_t) 'k';
  KEY_INDEX(0x26, ESCAPE_SHIFT_CAPS) = (uint8_t) 'l';
  KEY_INDEX(0x27, ESCAPE_SHIFT_CAPS) = (uint8_t) ':';
  KEY_INDEX(0x28, ESCAPE_SHIFT_CAPS) = (uint8_t) '"';
  KEY_INDEX(0x29, ESCAPE_SHIFT_CAPS) = (uint8_t) '~';
  KEY_INDEX(0x2A, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //LSHFT
  KEY_INDEX(0x2B, ESCAPE_SHIFT_CAPS) = (uint8_t) '|';
  KEY_INDEX(0x2C, ESCAPE_SHIFT_CAPS) = (uint8_t) 'z';
  KEY_INDEX(0x2D, ESCAPE_SHIFT_CAPS) = (uint8_t) 'x';
  KEY_INDEX(0x2E, ESCAPE_SHIFT_CAPS) = (uint8_t) 'c';
  KEY_INDEX(0x2F, ESCAPE_SHIFT_CAPS) = (uint8_t) 'v';

  KEY_INDEX(0x30, ESCAPE_SHIFT_CAPS) = (uint8_t) 'b';
  KEY_INDEX(0x31, ESCAPE_SHIFT_CAPS) = (uint8_t) 'n';
  KEY_INDEX(0x32, ESCAPE_SHIFT_CAPS) = (uint8_t) 'm';
  KEY_INDEX(0x33, ESCAPE_SHIFT_CAPS) = (uint8_t) '<';
  KEY_INDEX(0x34, ESCAPE_SHIFT_CAPS) = (uint8_t) '>';
  KEY_INDEX(0x35, ESCAPE_SHIFT_CAPS) = (uint8_t) '?';
  KEY_INDEX(0x36, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //RSHFT
  KEY_INDEX(0x37, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x38, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //LALT
  KEY_INDEX(0x39, ESCAPE_SHIFT_CAPS) = (uint8_t) ' ';
  KEY_INDEX(0x3A, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //CAPSLOCK
  KEY_INDEX(0x3B, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F1
  KEY_INDEX(0x3C, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F2
  KEY_INDEX(0x3D, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F3
  KEY_INDEX(0x3E, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F4
  KEY_INDEX(0x3F, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F5

  KEY_INDEX(0x40, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F6
  KEY_INDEX(0x41, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F7
  KEY_INDEX(0x42, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F8
  KEY_INDEX(0x43, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F9
  KEY_INDEX(0x44, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F10
  KEY_INDEX(0x45, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //NUMLOCK
  KEY_INDEX(0x46, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //SCROLL LOCK
  KEY_INDEX(0x47, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD7
  KEY_INDEX(0x48, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD8
  KEY_INDEX(0x49, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD9
  KEY_INDEX(0x4A, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD-
  KEY_INDEX(0x4B, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD4
  KEY_INDEX(0x4C, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD5
  KEY_INDEX(0x4D, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD6
  KEY_INDEX(0x4E, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD+
  KEY_INDEX(0x4F, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD1

  KEY_INDEX(0x50, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD2
  KEY_INDEX(0x51, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD3
  KEY_INDEX(0x52, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD0
  KEY_INDEX(0x53, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //KPAD.
  KEY_INDEX(0x54, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //NULL
  KEY_INDEX(0x55, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //FUNC
  KEY_INDEX(0x56, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //blank
  KEY_INDEX(0x57, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F11
  KEY_INDEX(0x58, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; //F12
  KEY_INDEX(0x59, ESCAPE_SHIFT_CAPS) = (uint8_t) 0; 
  KEY_INDEX(0x5A, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5B, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5C, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5D, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5E, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;
  KEY_INDEX(0x5F, ESCAPE_SHIFT_CAPS) = (uint8_t) 0;

  KEY_INDEX(0x35, ESCAPE_E0) = (uint8_t) '//';
  KEY_INDEX(0x48, ESCAPE_E0) = (uint8_t) '^';
  KEY_INDEX(0x4B, ESCAPE_E0) = (uint8_t) '<';
  KEY_INDEX(0x4D, ESCAPE_E0) = (uint8_t) '>';
  KEY_INDEX(0x50, ESCAPE_E0) = (uint8_t) 'V';
}

void keyboardHandler(struct isrregs *r) {
  //first setup our static variables
  static Escapes escapes = {
    0, //E0
    0, //E1
    0, //LSHIFT
    0, //RSHIFT
    0, //LCTRL
    0, //RCTRL
    0, //LALT
    0, //RALT
  };

  static keyLEDs leds = {
    0, //scroll
    0, //caps
    0, //num
  };

  //receive byte from keyboard
  KeyScanCode scancode = getKeyboardOutput();

  //first determine if the key being pressed is an escape
  static uint8_t escapeCode = ESCAPE_NONE;

  if (!scancode.released) {
    switch (scancode.keycode) {

    case KEY_CAPSLOCK:
      if (leds.caps) {
	leds.caps = 0;
      }
      else {
	leds.caps = 1;
      }
      updateKeyboardLEDs(leds);
      return;

    case KEY_LSHIFT:
      escapes.LSHIFT = 1;
      return;

    case KEY_RSHIFT:
      escapes.RSHIFT = 1;
      return;

    case KEY_LCTRL:
      escapes.LCTRL = 1;
      return;

    case KEY_LALT:
      escapes.LALT = 1;
      return;
    }
    

    escapeCode = ESCAPE_NONE;
    //determine what escape code we should be registering
    if (escapes.LSHIFT || escapes.RSHIFT) {
      escapeCode = ESCAPE_SHIFT;
      if (leds.caps) {
	escapeCode = ESCAPE_SHIFT_CAPS;
      }
    }
    else {
      if (leds.caps) {
	escapeCode = ESCAPE_CAPS;
      }
    }

    //override all other codes if we get E0 or E1
    if (escapes.E0) {
      escapeCode = ESCAPE_E0;
    }
    if (escapes.E1) escapeCode = ESCAPE_E1;

    //if the value isn't an escape, register that we pressed down the given key
    KEYPRESS_INDEX(scancode.keycode, escapeCode) = 1;

    //check to see if an ascii value can be displayed
    if (KEY_INDEX(scancode.keycode, escapeCode)) {
      DisplayChar(KEY_INDEX(scancode.keycode, escapeCode));
    }
    else {
      DisplayInteger(scancode.keycode);
      DisplayChar(':');
      DisplayInteger(KEY_INDEX(scancode.keycode, escapeCode));
      DisplayChar(':');
      DisplayInteger(escapeCode);
      DisplayChar(' ');
    }
  }
  else {
    switch (scancode.keycode) {

    case KEY_ESCAPE0:
    case KEY_ESCAPE0_OLD:
      escapes.E0 = !escapes.E0;
      return;

    case KEY_ESCAPE1:
    case KEY_ESCAPE1_OLD:
      escapes.E1 = !escapes.E1;
      return;

    case KEY_CAPSLOCK:
      return;

    case KEY_LSHIFT:
      escapes.LSHIFT = 0;
      return;

    case KEY_RSHIFT:
      escapes.RSHIFT = 0;
      return;

    case KEY_LCTRL:
      escapes.LCTRL = 0;
      return;

    case KEY_LALT:
      escapes.LALT = 0;
      return;
    }
    
    KEYPRESS_INDEX(scancode.keycode, escapeCode) = 0;
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

void updateKeyboardLEDs(keyLEDs leds) {

}
