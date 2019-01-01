void motorOff(int motor) {
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inCWpin[i], LOW);
    digitalWrite(inCCWpin[i], LOW);
  }
  analogWrite(speedpin[motor], 0);
}


/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 255, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm) {
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inCWpin[motor], HIGH);
      else
        digitalWrite(inCWpin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inCCWpin[motor], HIGH);
      else
        digitalWrite(inCCWpin[motor], LOW);

      analogWrite(speedpin[motor], pwm);
    }
  }
}


void ReadMotStatus(){
  for (int i = 0; i<2; i++) {
    motStatus[i].motLoad = analogRead(loadpin[i]);
    motStatus[i].motHealth = digitalRead(healthpin[i]);
  }
  if (debugMode){
    for (int i=0; i<2; i++){
      pdebug.print(i);
      pdebug.print(":\tLoad\t");
      pdebug.print(motStatus[i].motLoad);
      pdebug.print("\tHealth:\t");
      pdebug.print(motStatus[i].motHealth);
      pdebug.print("\t");
    }
    pdebug.println("");
  }
}

