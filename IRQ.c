//includes
#include <IRQ.h>
#include <port.h>

#include <idt.h>
#include <port.h>
#include <mode7.h>

//defines

#define IRQ_PRIMARY_PIC_COMMAND_PORT 0x20
#define IRQ_PRIMARY_PIC_DATA_PORT 0x21

#define IRQ_SECONDARY_PIC_COMMAND_PORT 0xA0
#define IRQ_SECONDARY_PIC_DATA_PORT 0xA1

#define IRQ_ICW1 0x11
#define IRQ_ICW2_PRIMARY_PIC 32
#define IRQ_ICW2_SECONDARY_PIC 40
#define IRQ_ICW3_PRIMARY_PIC 0x04
#define IRQ_ICW3_SECONDARY_PIC 0x02
#define IRQ_ICW4 0x01

#define IRQ_COUNT 16

//macros

#define EOF_PIC_DEINIT(IRQ)					\
  outport(IRQ_PRIMARY_PIC_COMMAND_PORT, 0x20);			\
  if ((IRQ)>7) outport(IRQ_SECONDARY_PIC_COMMAND_PORT, 0x20);



void *irq_routines[IRQ_COUNT];


//functions

void i86_irq_initialize(uint16_t codeSel) {
  for(uint8_t i = 0; i < IRQ_COUNT; i++)
    {
      irq_routines[i] = 0;
    }

  // Remap IRQ 0-15 to interrupts 32-47
  outport(IRQ_PRIMARY_PIC_COMMAND_PORT, IRQ_ICW1);
  outport(IRQ_SECONDARY_PIC_COMMAND_PORT, IRQ_ICW1);

  outport(IRQ_PRIMARY_PIC_DATA_PORT, IRQ_ICW2_PRIMARY_PIC);
  outport(IRQ_SECONDARY_PIC_DATA_PORT, IRQ_ICW2_SECONDARY_PIC);

  outport(IRQ_PRIMARY_PIC_DATA_PORT, IRQ_ICW3_PRIMARY_PIC);
  outport(IRQ_SECONDARY_PIC_DATA_PORT, IRQ_ICW3_SECONDARY_PIC);

  outport(IRQ_PRIMARY_PIC_DATA_PORT, IRQ_ICW4);
  outport(IRQ_SECONDARY_PIC_DATA_PORT, IRQ_ICW4);

  // Zero data port
  outport(IRQ_PRIMARY_PIC_DATA_PORT, 0);
  outport(IRQ_SECONDARY_PIC_DATA_PORT, 0);

  
  uint16_t _flags = I86_IDT_DESC_PRESENT + I86_IDT_DESC_RING0 + I86_IDT_DESC_INT32;
  // Set up IDT for IRQs
  i86_install_ir(32, _flags, codeSel, (I86_IRQ_HANDLER) irq0);
  i86_install_ir(33, _flags, codeSel, (I86_IRQ_HANDLER) irq1);
  i86_install_ir(34, _flags, codeSel, (I86_IRQ_HANDLER) irq2);
  i86_install_ir(35, _flags, codeSel, (I86_IRQ_HANDLER) irq3);
  i86_install_ir(36, _flags, codeSel, (I86_IRQ_HANDLER) irq4);
  i86_install_ir(37, _flags, codeSel, (I86_IRQ_HANDLER) irq5);
  i86_install_ir(38, _flags, codeSel, (I86_IRQ_HANDLER) irq6);
  i86_install_ir(39, _flags, codeSel, (I86_IRQ_HANDLER) irq7);
  i86_install_ir(40, _flags, codeSel, (I86_IRQ_HANDLER) irq8);
  i86_install_ir(41, _flags, codeSel, (I86_IRQ_HANDLER) irq9);
  i86_install_ir(42, _flags, codeSel, (I86_IRQ_HANDLER) irq10);
  i86_install_ir(43, _flags, codeSel, (I86_IRQ_HANDLER) irq11);
  i86_install_ir(44, _flags, codeSel, (I86_IRQ_HANDLER) irq12);
  i86_install_ir(45, _flags, codeSel, (I86_IRQ_HANDLER) irq13);
  i86_install_ir(46, _flags, codeSel, (I86_IRQ_HANDLER) irq14);
  i86_install_ir(47, _flags, codeSel, (I86_IRQ_HANDLER) irq15);

  return 0;
}

//void irq_install_handler(uint32_t irq, 
//			 void (*handler)(struct isrregs *r)) { 
//  irq_routines[irq] = handler; 
//}

void irq_uninstall_handler(uint32_t irq) { 
  irq_routines[irq] = 0; 
}

// IRQ handlers
void irq0() {
  INIT_IRQ_HANDLER(0, "IRQ0");
  EOF_PIC_DEINIT(0)
}

void irq1() {
  INIT_IRQ_HANDLER(1, "IRQ0");
  EOF_PIC_DEINIT(1)
}

void irq2() {
  INIT_IRQ_HANDLER(2, "IRQ0");
  EOF_PIC_DEINIT(2)
}

void irq3() {
  INIT_IRQ_HANDLER(3, "IRQ0");
  EOF_PIC_DEINIT(3)
}

void irq4() {
  INIT_IRQ_HANDLER(4, "IRQ0");
  EOF_PIC_DEINIT(4)
}

void irq5() {
  INIT_IRQ_HANDLER(5, "IRQ0");
  EOF_PIC_DEINIT(5)
}

void irq6() {
  INIT_IRQ_HANDLER(6, "IRQ0");
  EOF_PIC_DEINIT(6)
}

void irq7() {
  INIT_IRQ_HANDLER(7, "IRQ0");
  EOF_PIC_DEINIT(7)
}

void irq8() {
  INIT_IRQ_HANDLER(8, "IRQ0");
  EOF_PIC_DEINIT(8)
}

void irq9() {
  INIT_IRQ_HANDLER(9, "IRQ0");
  EOF_PIC_DEINIT(9)
}

void irq10() {
  INIT_IRQ_HANDLER(10, "IRQ0");
  EOF_PIC_DEINIT(10)
}

void irq11() {
  INIT_IRQ_HANDLER(11, "IRQ0");
  EOF_PIC_DEINIT(11)
}

void irq12() {
  INIT_IRQ_HANDLER(12, "IRQ0");
  EOF_PIC_DEINIT(12)
}

void irq13() {
  INIT_IRQ_HANDLER(13, "IRQ0");
  EOF_PIC_DEINIT(13)
}

void irq14() {
  INIT_IRQ_HANDLER(14, "IRQ0");
  EOF_PIC_DEINIT(14)
}

void irq15() {
  INIT_IRQ_HANDLER(15, "IRQ0");
  EOF_PIC_DEINIT(15)
}
