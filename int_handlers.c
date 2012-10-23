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

  i86_install_ir (1, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Debug_SingleStep);

  i86_install_ir (2, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_NonMaskable_Interrupt);

  i86_install_ir (3, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Debug_Breakpoint);

  i86_install_ir (4, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Overflow);

  i86_install_ir (5, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_OutOfBounds);

  i86_install_ir (6, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Undefined_OPcode);

  i86_install_ir (7, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_No_CoProcessor);
  
  i86_install_ir (8, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Double_Fault);

  i86_install_ir (9, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_CoProcessor_Overrun);

  i86_install_ir (10, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Task_State_Segment);

  i86_install_ir (11, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Segment_Not_Present);

  i86_install_ir (12, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Stack_Fault);

  i86_install_ir (13, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_General_Protection_Fault);

  i86_install_ir (14, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Page_Fault);

  i86_install_ir (15, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Unassigned);

  i86_install_ir (16, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Coprocessor_Error);

  i86_install_ir (17, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Alignment_Check);

  i86_install_ir (18, _flags, codeSel, 
		  (I86_IRQ_HANDLER) iHand_Machine_Check);  

  int irq_num = 19;
  for (; irq_num <= 32; irq_num++) {
    i86_install_ir (irq_num, _flags, codeSel, 
		    (I86_IRQ_HANDLER) iHand_Reserved_Intel);  
  }

}

// Divide By Zero IRQ: 0
static void iHand_DivideByZero() {
  INIT_HANDLER(0, "Divide By Zero");
}

// Debugger Single Step IRQ: 1
static void iHand_Debug_SingleStep() {
  INIT_HANDLER(1, "Debugger Single Step");
}

// Non-Maskable IRQ: 2
static void iHand_NonMaskable_Interrupt() {
  INIT_HANDLER(2, "Non-Maskable");
}

// Debugger Breakpoint IRQ: 3
static void iHand_Debug_Breakpoint() {
  INIT_HANDLER(3, "Debugger Breakpoint");
}

// Overflow IRQ: 4
static void iHand_Overflow() {
  INIT_HANDLER(4, "Overflow");
}

// Out of Bounds IRQ: 5
static void iHand_OutOfBounds() {
  INIT_HANDLER(5, "Out of Bounds");
}

// Undefined OPcode IRQ: 6
static void iHand_Undefined_OPcode() {
  INIT_HANDLER(6, "Undefined OP code");
}

// No Co-Processor IRQ: 7
static void iHand_No_CoProcessor() {
  INIT_HANDLER(7, "No Co-Processor");
}

// Double Fault IRQ: 8
static void iHand_Double_Fault() {
  INIT_HANDLER(8, "Double Fault, all the way");
}

// Co-Processor Segment Overrun IRQ: 9
static void iHand_CoProcessor_Overrun() {
  INIT_HANDLER(9, "Co-Processor Segment Overrun");
}

// Invalid Task State Segment IRQ: 10
static void iHand_Task_State_Segment() {
  INIT_HANDLER(10, "Invalid Task State Segment");
}

// Segment not present IRQ: 11
static void iHand_Segment_Not_Present() {
  INIT_HANDLER(11, "Segment Not Present");
}

// Stack Fault IRQ: 12
static void iHand_Stack_Fault() {
  INIT_HANDLER(12, "Stack Fault");
}

// General Protection Fault IRQ: 13
static void iHand_General_Protection_Fault() {
  INIT_HANDLER(13, "General Protection Fault");
}

// Page Fault IRQ: 14
static void iHand_Page_Fault() {
  INIT_HANDLER(14, "Page Fault");
}

// Unassigned IRQ: 15
static void iHand_Unassigned() {
  INIT_HANDLER(15, "Unassigned Interrupt");
}

// Coprocessor Error IRQ: 16
static void iHand_Coprocessor_Error() {
  INIT_HANDLER(16, "Co-Processor Error");
}

// Alignment Check IRQ: 17
static void iHand_Alignment_Check() {
  INIT_HANDLER(17, "Alignment Check");
}

// Machine Check IRQ: 18
static void iHand_Machine_Check() {
  INIT_HANDLER(18, "Machine Check");
}

// Intel 19-31 Reserved IRQ: 19-31
static void iHand_Reserved_Intel() {
  INIT_HANDLER(19-31, "Reserved Intel");
}
