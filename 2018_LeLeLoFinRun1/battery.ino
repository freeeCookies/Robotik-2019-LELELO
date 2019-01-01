int calcBatLevelPercent(int iBatLevel) {
  int iResult = 0;
  if (iBatLevel < BatLevelRAWmin) {iBatLevel = BatLevelRAWmin;};
  if (iBatLevel > BatLevelRAWmax) {iBatLevel = BatLevelRAWmax;};
  iResult = map(iBatLevel, BatLevelRAWmin, BatLevelRAWmax, 0, 100);
  return iResult;
}

void set_Batterie_Level() {
  /*
   * Eingabe 0%-100%
   * 4 LED verfügbar
   * 100% 4 LED an
   *  85% 3 LED an 4te LED blinkt
   *  75% 3 LED an
   *  60% 2 LED an 3te LED blinkt
   *  50% 2 LED an
   *  35% 1 LED an 2te LED blinkt
   *  25% 1 LED an
   *  
   *  15% 1 LED blinkt langsam
   *  10% 1 LED blinkt schnell
   *   5% 1 LED blinkt extrem schnell
   */

  if (BatInterval > BatReadInterval){
    BatInterval = 0;

    BatLevelRAW = analogRead(PIN_Bat_level);
    BatLevelPercent = calcBatLevelPercent(BatLevelRAW);

    if (BatLevelPercent > 95) {
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat075, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat100, HIGH);
    }
    else if (BatLevelPercent > 85){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat075, HIGH);
      keypadControl.blink(PIN_SX1509_Bat100, 1000, 1000);
    }
    else if (BatLevelPercent > 75){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat075, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent > 60){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, HIGH);
      keypadControl.blink(PIN_SX1509_Bat075, 1000, 1000);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent > 50){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent > 30){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blink(PIN_SX1509_Bat050, 1000, 1000);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent >= 25){
      keypadControl.blinkOff(PIN_SX1509_Bat025, HIGH);
      keypadControl.blinkOff(PIN_SX1509_Bat050, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent < 25 && BatLevelPercent >= 10){
      keypadControl.blink(PIN_SX1509_Bat025, 1000, 1000);
      keypadControl.blinkOff(PIN_SX1509_Bat050, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else if (BatLevelPercent < 10 && BatLevelPercent > 5){
      keypadControl.blink(PIN_SX1509_Bat025, 500, 500);
      keypadControl.blinkOff(PIN_SX1509_Bat050, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }  
    else if (BatLevelPercent <= 5){
      keypadControl.blink(PIN_SX1509_Bat025, 100, 100);
      keypadControl.blinkOff(PIN_SX1509_Bat050, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat075, LOW);
      keypadControl.blinkOff(PIN_SX1509_Bat100, LOW);
    }
    else {
      keypadControl.blink(PIN_SX1509_Bat025, 500, 500);
      keypadControl.blink(PIN_SX1509_Bat050, 500, 500);
      keypadControl.blink(PIN_SX1509_Bat075, 500, 500);
      keypadControl.blink(PIN_SX1509_Bat100, 500, 500);
    }
    if (debugMode){
      pdebug.print("Bat-Level RAW:\t");
      pdebug.print(BatLevelRAW);
      pdebug.print("\tBat-Level %:\t");
      pdebug.println(BatLevelPercent);    
    }
  }
}

