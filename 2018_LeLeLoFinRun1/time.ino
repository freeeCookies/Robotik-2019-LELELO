/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * Source TimeTennsy3
 * 
 */

/*
 * 
void setup()  {


  pdebug.begin(115200);
  while (!pdebug);  // Wait for Arduino Serial Monitor to open
  delay(100);
  if (timeStatus()!= timeSet) {
    pdebug.println("Unable to sync with the RTC");
  } else {
    pdebug.println("RTC has set the system time");
  }
}

void loop() {
  if (pdebug.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay() {
  // digital clock display of the time
  pdebug.print(hour());
  printDigits(minute());
  printDigits(second());
  pdebug.print(" ");
  pdebug.print(day());
  pdebug.print(" ");
  pdebug.print(month());
  pdebug.print(" ");
  pdebug.print(year()); 
  pdebug.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}
*/
/*  code to process time sync messages from the serial port   */
/*#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(pdebug.find(TIME_HEADER)) {
     pctime = pdebug.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  pdebug.print(":");
  if(digits < 10)
    pdebug.print('0');
  pdebug.print(digits);
}
*/
