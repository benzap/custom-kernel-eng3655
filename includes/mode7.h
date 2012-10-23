#ifndef __MODE7_H__
#define __MODE7_H__

#include "size_t.h"
#include "stdint.h"

#define VID_MEMORY 0xB8000
#define COLS 80
#define LINES 25

extern void GotoXY(uint32_t, uint32_t);
extern void SetColor(size_t);
extern void OutPort(uint16_t, uint32_t);
extern size_t strlen(uint8_t *);
extern void DisplayChar(uint8_t);
extern void DisplayString(uint8_t*);
extern void DisplayInteger(uint32_t);
extern void ScrollUp();
extern void MoveCursor();
extern void ClearScreen(uint8_t);
extern size_t GetColor();
extern uint32_t GetWidth();
extern uint32_t GetHeight();
extern uint32_t GetXPos();
extern uint32_t GetYPos();

#endif
