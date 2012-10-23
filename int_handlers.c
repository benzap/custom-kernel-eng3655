#include <int_handlers.h>
#include <idt.h>
#include <mode7.h>

void setup_handlers(uint16_t codeSel) {
  uint16_t _flags = I86_IDT_DESC_PRESENT; //present / abscent
  _flags += I86_IDT_DESC_RING0; //priviledge
  _flags += I86_IDT_DESC_INT32; //type interrupt 32-bit
  
  //Divide by Zero Handler IRQ: 0
  i86_install_ir (0, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_DivideByZero);
  
  
}

static void iHand_DivideByZero() {
  ClearScreen(0x18);
  GotoXY(0,1);
  SetColor(0x1e);
  DisplayString((uint8_t*) "*** You divided by zero, brah");
  
  for(;;);
}
