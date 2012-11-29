#include "mode7.h"
#include "hal.h"
#include "mem.h"

int KernelMain () {

  //Initialize HAL
  hal_initialize();

  ClearScreen(0x10);
  SetColor(0b01110000);	
  GotoXY(30,5);
  DisplayString((uint8_t*)" <ENGI 3655 Kernel> ");
  SetColor(0b00011111);
  
  __asm__ ( "sti" );
  DisplayString((uint8_t*)"\n\n");
  DisplayString((uint8_t*)"         A fatal exception has not occured at memory location 0x1337.\n");
  DisplayString((uint8_t*)"         The current application will not be terminated.\n");
  DisplayString((uint8_t*)"\n         *  The current application will not be terminated\n");
  DisplayString((uint8_t*)"         *  Press CTRL+ALT+DEL to do nothing, please don't bother. Also,");
  DisplayString((uint8_t*)"                    there are no unsaved changes, so don't worry about it.\n");
  DisplayString((uint8_t*)"\n                          Press any key to do nothing\n");
  
    
  GotoXY(0, GetHeight()-1);
  DisplayString(">>");

  //Start of test Divide by Zero
  
  SetColor(0x12);
  DisplayString("Start of Divisions");
  DisplayInteger(6/0.);
  DisplayString("\n");
  DisplayInteger(5/1.);
  DisplayString("\n");
  DisplayInteger(6/3);
  DisplayString("\n");
  DisplayInteger(6/0);
  DisplayString("\n");
  DisplayInteger(20/0);
  DisplayString("\n");
  DisplayInteger(7/0);
  DisplayString("\n");
  DisplayInteger(12/4);
  DisplayString("\n");
  DisplayString("End of Divisions");
  //End of test Divide by Zero



  while(1);

  hal_shutdown();

  return 0;
}
