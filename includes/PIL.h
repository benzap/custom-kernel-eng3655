#ifndef PIL_H
#define PIL_H
#include <stdint.h>
#include <registers.h>

//sets up the PILHandler within the given code descriptor location
//assumed Kernel Mode 32-bit
void initPILHandler();

//handler used with IRQ0 of the vector table.
void PILHandler(struct isrregs *r);

//draws a clock with the given hours, minutes and seconds in the top
//right corner of the screen
void drawClock(int, int, int);

#endif //PIL_H
