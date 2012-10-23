#ifndef INT_HANDLERS_H
#define INT_HANDLERS_H

#include <stdint.h>

void setup_handlers(uint16_t codeSel);

static void iHand_DivideByZero();

#endif //INT_HANDLERS_H
