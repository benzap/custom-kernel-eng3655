#ifndef IRQ_H
#define IRQ_H

//Includes

#include <stdint.h>

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

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();



#endif //IRQ_H
