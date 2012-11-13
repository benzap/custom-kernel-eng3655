#ifndef IRQ_H
#define IRQ_H

//Includes

#include <stdint.h>
#include <registers.h>

//MACROS

#define INIT_IRQ_HANDLER(__IRQ_)			\
  GotoXY(0,1);						\
  SetColor(0x4e);					\
  DisplayString((uint8_t*) "IRQ: " #__IRQ_ "\n");	\

//Functions

void i86_irq_initialize(uint16_t codeSel);

void irq_install_handler(uint32_t irq, 
			 void(*handler) (struct isrregs *r));

void irq_uninstall_handler(uint32_t irq);

void irq_handler(struct isrregs *r);

//irq handlers

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();



#endif //IRQ_H
