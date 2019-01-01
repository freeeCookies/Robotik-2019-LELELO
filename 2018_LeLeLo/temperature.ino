boolean VictimEndR = false;
boolean VictimEndL = false;

boolean readTemp() {

boolean isVictim = false;

  for (int i=0; i<2; i++){
    tempVictims[i].tempAmbient = tempSensor[i].readAmbientTempC();
    tempVictims[i].tempObject = tempSensor[i].readObjectTempC();
    if (tempVictims[i].tempObject - tempVictims[i].tempAmbient > temp_diff_Victim) {
      tempVictims[i].VictimFound = true;
    }
    else {
        tempVictims[i].VictimFound = false;
    }
    isVictim = isVictim or tempVictims[i].VictimFound;
  }    
  return isVictim;
}

void DebugPrintTempValues(){
  for (int i=0; i<2; i++){
    pdebug.print("Sensor ");
    pdebug.print(i);
    pdebug.print(" :\tAmbient = "); 
    pdebug.print(tempVictims[i].tempAmbient); 
    pdebug.print("*C\tObject = "); 
    pdebug.print(tempVictims[i].tempObject); 
    pdebug.print("*C\tVictim:\t");
    pdebug.print(tempVictims[i].VictimFound);
    pdebug.println("\t");
  }
  pdebug.println("");
}

void setVictim() {
  
 if (tempVictims[temp_L].VictimFound && VictimEndL == false) {
    //keypadControl.blink(PIN_SX1509_VictimLeft, 250, 750);
    keypadControl.digitalWrite(PIN_SX1509_VictimLeft, HIGH);
    motorOff(mot_L);
    motorOff(mot_R);
    DR_servo.write(DR_Right);
    delay(DR_ServoWait); 
    DR_servo.write(DR_neutral);
    delay(DR_ServoWait);
    VictimEndL = true;
  }
  else {
    if (tempVictims[temp_L].VictimFound){}
    else {
      //keypadControl.blink(PIN_SX1509_VictimLeft, 1, 0);
      keypadControl.digitalWrite(PIN_SX1509_VictimLeft, LOW);
      DR_servo.write(DR_neutral);
      VictimEndL = false;
    }
  }
  if (tempVictims[temp_R].VictimFound && VictimEndR == false) {
    //keypadControl.blink(PIN_SX1509_VictimRight, 250, 750);
    keypadControl.digitalWrite(PIN_SX1509_VictimRight, HIGH);
    motorOff(mot_L);
    motorOff(mot_R);
    DR_servo.write(DR_Left);
    delay(DR_ServoWait); 
    DR_servo.write(DR_neutral);
    delay(DR_ServoWait);
    VictimEndR = true;
  }
  else {
    if (tempVictims[temp_R].VictimFound){}
    else {
      //keypadControl.blink(PIN_SX1509_VictimRight, 1, 0);
      keypadControl.digitalWrite(PIN_SX1509_VictimRight, LOW);
      DR_servo.write(DR_neutral);
      VictimEndR = false;
    }  
  }
}


void clearVictim() {
  //keypadControl.blink(PIN_SX1509_VictimLeft, 1, 0);
  keypadControl.digitalWrite(PIN_SX1509_VictimLeft, LOW);
  //keypadControl.blink(PIN_SX1509_VictimRight, 1, 0);
  keypadControl.digitalWrite(PIN_SX1509_VictimRight, LOW);
  DR_servo.write(DR_neutral);
}  
