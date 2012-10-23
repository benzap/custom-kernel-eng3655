#include "mode7.h"

static uint32_t _xPos = 0;
static uint32_t _yPos = 0;
static size_t _color = 0;

void SetColor(size_t c) { _color = c; }
size_t GetColor() { return _color; }
uint32_t GetWidth() { return COLS; }
uint32_t GetHeight() { return LINES; }
uint32_t GetXPos() { return _xPos; }
uint32_t GetYPos() { return _yPos; } 

// Move write position to (_xPos, _yPos)
void GotoXY(uint32_t x, uint32_t y)
{
	_xPos = x;
	_yPos = y;
}


// Helper function to move screen cursor to (_xPos, _yPos)
void OutPort(uint16_t port, uint32_t data)
{
    __asm__ __volatile__ ("out %1, %0" : : "dN" (port), "a" (data));
}

// Returns the length of string
size_t strlen(uint8_t *string)
{
	size_t length = 0;

	while(string[length++] != '\0');
	
	return length;
}


// Put character c on screen at (_xPos, _yPos) with attributes _color
void DisplayChar(uint8_t c)
{
	// Return on NULL
	if (c == '\0')
	{ return; }

	// Handle new line
	if (c == '\n')
	{
		_yPos++;
		_xPos=0;
		
		if (_yPos >= LINES)
		{
			ScrollUp();
		}

		MoveCursor();
		return;
	}
	
	// Handle out of X bound
	if (_xPos >= COLS)
	{
		_yPos++;
		_xPos=0;

		if (_yPos >= LINES)
		{
			ScrollUp();
		}
	}

	// Write character to memory (incl. attributes)
	uint8_t* p = (uint8_t*) VID_MEMORY + _yPos * COLS * 2 + (_xPos++)*2;
	*p++ = c;
	*p = _color;
	MoveCursor();
}


// Move buffer up one line
void ScrollUp()
{
	uint8_t* to_memory = (uint8_t*) VID_MEMORY;
	uint8_t* from_memory = to_memory + 2*COLS;

	// Copy row i+1 to row i for all rows
	do
	{
		*to_memory++ = *from_memory++;
	} while(from_memory >= (uint8_t*) VID_MEMORY &&
		to_memory >= (uint8_t*) VID_MEMORY &&
		from_memory < (uint8_t*) VID_MEMORY + 2*COLS*LINES &&
		to_memory < from_memory);

	// Clear last row
	do	
	{
		*to_memory++ = (uint8_t) ' ';
		*to_memory++ = (uint8_t) 0;
	} while(to_memory >= (uint8_t*) VID_MEMORY &&
		to_memory < (uint8_t*) VID_MEMORY + 2*COLS*LINES);

	if (_yPos > 0)
	{
		_yPos--;
	}
}

// Move the CRT cursor to (_xPos, _yPos)
void MoveCursor()
{
	uint32_t cPos = _yPos * COLS + _xPos;

	OutPort(0x3D4, 14);
	OutPort(0x3D5, cPos >> 8);
	OutPort(0x3D4, 15);
	OutPort(0x3D5, cPos);
}

// Write a string to the screen starting at (_xPos, _yPos)
void DisplayString(uint8_t *string)
{
	if (!string)
	{ return; }

	for (uint32_t i = 0; i < strlen(string); i++)
	{ DisplayChar(string[i]); }
}

// Prints integer value to the screen starting at (_xPos, _yPos) with attribute _color
//   Recursive version that does not require a buffer be allocated.
//   (A uint32_t won't have that many digits, right?)
void DisplayInteger(uint32_t n)
{
	uint32_t nt = n/10;

	if (nt == 0)
	{
		DisplayChar('0' + n%10);
		return;
	}
	else
	{
		DisplayInteger(nt);
		DisplayChar('0' + n%10);
	}
}

// Fill screen with attribute c
void ClearScreen(uint8_t c)
{
	uint8_t* video_memory = (uint8_t*) VID_MEMORY;

	// Fill video memory with spaces
	do {
		*video_memory++ = (uint8_t) ' ';
		*video_memory++ = c;
	} while (video_memory >= (uint8_t*) VID_MEMORY &&
		 video_memory < (uint8_t*) VID_MEMORY + 2*LINES*COLS);
}
