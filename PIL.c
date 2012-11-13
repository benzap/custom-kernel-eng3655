//INCLUDES
#include <PIL.h>
#include <IRQ.h>
#include <mode7.h>

void initPILHandler() {
  irq_install_handler(0, PILHandler);
}

//
void PILHandler(struct isrregs *r) {
  static uint32_t totalTicks = 0;
  uint32_t time_hours, time_minutes, time_seconds;

  //one tick
  totalTicks++;

  //rough conversion to total seconds
  time_seconds = totalTicks / 18;

  //number of hours
  time_hours = time_seconds / 3600;
  time_seconds %= 3600;

  //number of minutes
  time_minutes = time_seconds / 60;
  time_seconds %= 60;

  //draw the clock
  drawClock(time_hours, time_minutes, time_seconds);
  
  return;
}

void drawClock(int hours, int minutes, int seconds) {
  //move the curser to the top left
  GotoXY(0,0);
  //show hours
  if (hours <= 9) {
    DisplayInteger(0);
  }
  DisplayInteger(hours);
  DisplayChar(':');

  //show minutes
  if (minutes <= 9) {
    DisplayInteger(0);
  }
  DisplayInteger(minutes);
  DisplayChar(':');

  //show seconds
  if (seconds <= 9) {
    DisplayInteger(0);
  }
  DisplayInteger(seconds);
}
