//INCLUDES
#include <keyboard.h>
#include <IRQ.h>
#include <mode7.h>

void initKeyboardHandler() {
  irq_install_handler(1, keyboardHandler);
}

void keyboardHandler(struct isrregs *r) {
  //displayChar('a');
  return;
}
