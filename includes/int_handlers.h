#ifndef INT_HANDLERS_H
#define INT_HANDLERS_H

// INCLUDES

#include <stdint.h>
#include <registers.h>

// MACROS

#define INT_COUNT 32

#define INIT_HANDLER(__IRQ_, __STRING)					\
  ClearScreen(0x48);							\
  GotoXY(0,1);								\
  SetColor(0x4e);							\
  DisplayString((uint8_t*) "IRQ: " #__IRQ_ "\n");				\
  DisplayString((uint8_t*) __STRING);				\
  for(;;);


// FUNCTIONS

void int_handler(struct isrregs *r);

void int_install_handler(uint32_t _int, 
			 void (*handler)(struct isrregs *r));

extern void int0();

void setup_handlers(uint16_t codeSel);

// Divide By Zero IRQ: 0
static void iHand_DivideByZero(struct isrregs *r);

// Debugger Single Step IRQ: 1
static void iHand_Debug_SingleStep();

// Non-Maskable IRQ: 2
static void iHand_NonMaskable_Interrupt();

// Debugger Breakpoint IRQ: 3
static void iHand_Debug_Breakpoint();

// Overflow IRQ: 4
static void iHand_Overflow();

// Out of Bounds IRQ: 5
static void iHand_OutOfBounds();

// Undefined OPcode IRQ: 6
static void iHand_Undefined_OPcode();

// No Co-Processor IRQ: 7
static void iHand_No_CoProcessor();

// Double Fault IRQ: 8
static void iHand_Double_Fault();

// Co-Processor Segment Overrun IRQ: 9
static void iHand_CoProcessor_Overrun();

// Invalid Task State Segment IRQ: 10
static void iHand_Task_State_Segment();

// Segment not present IRQ: 11
static void iHand_Segment_Not_Present();

// Stack Fault IRQ: 12
static void iHand_Stack_Fault();

// General Protection Fault IRQ: 13
static void iHand_General_Protection_Fault();

// Page Fault IRQ: 14
static void iHand_Page_Fault();

// Unassigned IRQ: 15
static void iHand_Unassigned();

// Coprocessor Error IRQ: 16
static void iHand_Coprocessor_Error();

// Alignment Check IRQ: 17
static void iHand_Alignment_Check();

// Machine Check IRQ: 18
static void iHand_Machine_Check();

// Intel 19-31 Reserved IRQ: 19-31
static void iHand_Reserved_Intel();

#endif //INT_HANDLERS_H
