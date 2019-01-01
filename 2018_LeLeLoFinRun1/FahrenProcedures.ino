void rechtsDrehen()
{
  int sen2 = getDstSensor(2);
  pdebug.print("Sensor 2: ");
  if (sen2 < wallCorrectionLeft)
  {
    vorFahren();
  }
  myLcdPrint("Rechts Drehen", 0, 0, true);
  pdebug.println("rechtsDrehen()");
  curX = getOrientX(); //euler.x();
  //pdebug.println(curX);
  //pdebug.print("CurX: ");
  //pdebug.println(curX);
  finX = curX + 90;
  if (finX >= 360)
  {
    finX -= 360;
  }
  //Toleranzbereich berechnen
  if (finX < tol)
  {
    tolX1 = finX + 360 - tol;
    tolX2 = finX + tol;
    dMode = 1;
  }
  else if (finX < 360 - tol)
  {
    tolX1 = finX - tol;
    tolX2 = finX + tol;
    dMode = 2;
  }
  else if (finX < 360)
  {
    tolX1 = finX - tol;
    tolX2 = finX - 360 + tol;
    dMode = 3;
  }

  switch (dMode)
  {
  case 1:
    pdebug.print("Case: 1");
    while (getOrientX() < tolX1 && getOrientX() > tolX2 && leaveWhile == false)
    {
      if (readTemp() == false)
      {
        motorGo(0, CCW, turnSpeed0);
        motorGo(1, CW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        leaveWhile = true;
        while (readTemp() == true)
        {
          motorGo(0, CCW, turnSpeed0);
          motorGo(1, CW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    motorOff(0);
    motorOff(1);
    leaveWhile = false;
    pdebug.println("Rechtsdrehen break!");
    break;

  case 2:
    pdebug.println("Case: 2");
    pdebug.println(getOrientX());
    while (getOrientX() > 90 && leaveWhile == false)
    {
      if (readTemp() == false)
      {
        motorGo(0, CCW, turnSpeed0);
        motorGo(1, CW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        leaveWhile = true;
        while (readTemp() == true)
        {
          motorGo(0, CCW, turnSpeed0);
          motorGo(1, CW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    //pdebug.print("Debugpunkt 1");
    motorOff(0);
    motorOff(1);
    leaveWhile = false;
    while (getOrientX() < tolX1 && leaveWhile == false)
    {
      if (readTemp() == false)
      {
        motorGo(0, CCW, turnSpeed0);
        motorGo(1, CW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        leaveWhile = true;
        while (readTemp() == true)
        {
          motorGo(0, CCW, turnSpeed0);
          motorGo(1, CW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    //pdebug.print("Debugpunkt 2");
    motorOff(0);
    motorOff(1);
    leaveWhile = false;
    break;

  case 3:
    pdebug.print("Case: 3 ");
    while (getOrientX() < tolX1)
    {
      motorGo(0, CCW, turnSpeed0);
      motorGo(1, CW, turnSpeed);
    }
    motorOff(0);
    motorOff(1);
    break;
  }
}

void linksDrehen()
{
  int sen2 = getDstSensor(2);
  pdebug.print("Sensor 2: ");
  pdebug.println(sen2);
  if (sen2 < wallCorrectionLeft)
  {
    vorFahren();
  }
  myLcdPrint("Links Drehen", 0, 0, true);
  pdebug.println("linksDrehen()");
  curX = getOrientX(); //euler.x();
  //pdebug.println(curX);
  pdebug.print("CurX: ");
  pdebug.println(curX);
  finX = curX - 90;
  if (finX < 0)
  {
    finX = finX + 360;
  }
  //Toleranzbereich berechnen
  if (finX <= tol)
  {
    tolX1 = finX + 360 - tol;
    tolX2 = finX + tol;
    dMode = 1;
  }
  else if (finX > tol && finX < 360 - tol)
  {
    tolX1 = finX - tol;
    tolX2 = finX + tol;
    dMode = 2;
  }
  else if (finX <= 360 - tol)
  {
    tolX1 = finX - tol;
    tolX2 = finX - 360 + tol;
    dMode = 3;
  }
  pdebug.print("Tol 1: ");
  pdebug.println(tolX1);
  pdebug.print("Tol 2: ");
  pdebug.println(tolX2);

  switch (dMode)
  {
  case 1:
    pdebug.println("Case: 1");
    pdebug.print("X: ");
    pdebug.println(getOrientX());
    while (getOrientX() < tolX1 && getOrientX() > tolX2)
    {
      pdebug.println(getOrientX());
      if (readTemp() == false)
      {
        motorGo(0, CW, turnSpeed0);
        motorGo(1, CCW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        while (readTemp() == true)
        {
          motorGo(0, CW, turnSpeed0);
          motorGo(1, CCW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    motorOff(0);
    motorOff(1);
    break;

  case 2:
    pdebug.println("Case: 2");
    //pdebug.println(getOrientX());
    while (getOrientX() < 90)
    {
      pdebug.println(getOrientX());
      if (readTemp() == false)
      {
        motorGo(0, CW, turnSpeed0);
        motorGo(1, CCW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        while (readTemp() == true)
        {
          pdebug.println(getOrientX());
          motorGo(0, CW, turnSpeed0);
          motorGo(1, CCW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    //pdebug.print("Debugpunkt 1");
    motorOff(0);
    motorOff(1);
    while (getOrientX() > tolX2)
    {
      pdebug.println(getOrientX());
      if (readTemp() == false)
      {
        motorGo(0, CW, turnSpeed0);
        motorGo(1, CCW, turnSpeed);
        lcd.setCursor(0, 1);
        lcd.print(measure[2].RangeMilliMeter);
      }
      else
      {
        setVictim();
        while (readTemp() == true)
        {
          motorGo(0, CW, turnSpeed0);
          motorGo(1, CCW, turnSpeed);
          lcd.setCursor(0, 1);
          lcd.print(measure[2].RangeMilliMeter);
        }
        clearVictim();
      }
    }
    //pdebug.print("Debugpunkt 2");
    motorOff(0);
    motorOff(1);
    break;

  case 3:
    pdebug.print("Case: 3 ");
    while (getOrientX() < tolX2)
    {
      motorGo(0, CCW, turnSpeed0);
      motorGo(1, CW, turnSpeed);
    }
    motorOff(0);
    motorOff(1);
    break;
  }
}

void vorFahren()
{
  motorGo(0, CCW, breakSpeed0);
  motorGo(1, CCW, breakSpeed);
  delay(100);
  motorOff(0);
  motorOff(1);
  pdebug.println("vorFahren()");
  int Sen2 = getDstSensor(2);
  int Sen5 = getDstSensor(5);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(Sen2);
  lcd.setCursor(8, 1);
  lcd.print(Sen5);
  pdebug.print("Sen2: ");
  pdebug.println(Sen2);
  if (Sen2 < 650)
  {
    dMode = 1;
  }
  else if (Sen5 < 350)
  {
    dMode = 2;
  }
  else
  {
    dMode = 3;
  }
  pdebug.print("Current dMode: ");
  pdebug.println(dMode);

  switch (dMode)
  {
  case 1:
    pdebug.println("Case 1");
    motorGo(0, CCW, breakSpeed0);
    motorGo(1, CCW, breakSpeed);
    delay(100);
    motorOff(0);
    motorOff(1);
    lcd.setCursor(0, 0);
    lcd.print("Case 1");
    //pdebug.print("Ich fahre und hier fahre ich los: ");
    dstBefore = getDstSensor(2);
    pdebug.println(dstBefore);
    Sen2 = dstBefore;
    while (dstBefore - Sen2 < stopThreshold && Sen2 > wallBreak && getFieldColor() != 2 && !is_RampeUp() && doMoveStraight())
    {
      if (readTemp() == false)
      {
        //pdebug.print("Fahren?");
        spurHalteFunktion();
        lcd.setCursor(0, 1);
        lcd.print(Sen2);
      }
      else
      {
        setVictim();
        while (readTemp() == true)
        {
          //pdebug.print("Fahren?");
          spurHalteFunktion();
          lcd.setCursor(0, 1);
          lcd.print(Sen2);
        }
        clearVictim();
      }
      Sen2 = getDstSensor(2);
    }
    //pdebug.print("Ich will nicht mehr und hier steh ich: ");
    //pdebug.println(getDstSensor(2));
    motorGo(0, CCW, breakSpeed0);
    motorGo(1, CCW, breakSpeed);
    delay(100);
    motorOff(0);
    motorOff(1);
    //pdebug.println("Finish");
    //pdebug.print("DstSensor 2: ");
    //pdebug.println(getDstSensor(2));
    pdebug.println("Case 1 break!");
    break;

  case 2:
    lcd.setCursor(0, 0);
    lcd.print("Case 2");
    //pdebug.print("Ich fahre und hier fahre ich los: ");
    dstBefore = getDstSensor(5);
    //pdebug.println(dstBefore);
    Sen5 = dstBefore;
    Sen2 = getDstSensor(2);
    while (Sen5 - dstBefore < stopThreshold && Sen2 > wallBreak && getFieldColor() != 2 && !is_RampeUp() && doMoveStraight())
    {
      if (readTemp() == false)
      {
        //pdebug.print("Fahren?");
        spurHalteFunktion();
        lcd.setCursor(0, 1);
        lcd.print(Sen2);
      }
      else
      {
        setVictim();
        while (readTemp() == true)
        {
          //pdebug.print("Fahren?");
          spurHalteFunktion();
          lcd.setCursor(0, 1);
          lcd.print(Sen2);
        }
        clearVictim();
      }
      Sen5 = getDstSensor(5);
      Sen2 = getDstSensor(2);
    }
    //pdebug.print("Ich will nicht mehr und hier steh ich: ");
    //pdebug.println(getDstSensor(5));
    motorGo(0, CCW, breakSpeed0);
    motorGo(1, CCW, breakSpeed);
    delay(100);
    motorOff(0);
    motorOff(1);
    //pdebug.println("Finish");
    //pdebug.print("DstSensor 5: ");
    //pdebug.println(getDstSensor(5));
    pdebug.println("Case 2 break!");
    break;

  case 3:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Case 3");
    encBefore = encMotRcount;
    pdebug.print("encBefore : ");
    pdebug.println(encBefore);
    while (doMoveStraight() && getDstSensor(6) > wallBreak && getFieldColor() != 2 && !is_RampeUp())
    {
      motorGo(1, CW, speedGrade);
      motorGo(0, CW, speedGrade0);
      speedCorrection(0);
      spurHalteFunktion();
    }
    motorGo(0, CCW, 15 * 1.4);
    motorGo(1, CCW, 15);
    delay(100);
    motorOff(0);
    motorOff(1);
    break;
  }
}

void spurHalteFunktion()
{
  //pdebug.println("spurHalteFunktion()");
  int sens3 = getDstSensor(3);
  myLcdPrint(sens3, 1, 6, true);
  pdebug.print("Sensor 3: ");
  pdebug.println(sens3);
  if (sens3 < CheckSensWall)
  {
    if (sens3 < WallOffsetSmall)
    {
      myLcdPrint("Case 1", 0, 0, false);
      myLcdPrint(sens3, 1, 6, false);
      motorGo(0, CW, speedBerechnung(0, false));
      motorGo(1, CW, speedBerechnung(1, true));
      //pdebug.print("Fahren!");
    }
    else if (sens3 > WallOffsetBig)
    {
      myLcdPrint("Case 2", 0, 0, false);
      myLcdPrint(sens3, 1, 6, false);
      motorGo(0, CW, speedBerechnung(0, true));
      motorGo(1, CW, speedBerechnung(1, false));
      //pdebug.print("Fahren!");
    }
    else
    {
      myLcdPrint("Geradeaus", 0, 0, false);
      motorGo(0, CW, stdSpeed0);
      motorGo(1, CW, stdSpeed);
      //pdebug.print("Fahren!");
    }
  }
  else
  {
    int sens7 = getDstSensor(7);
    pdebug.print("Sensor 7: ");
    pdebug.println(sens7);
    if (sens7 < CheckSensWall)
    {
      if (sens7 < WallOffsetSmall)
      {
        myLcdPrint("Case 3", 0, 0, false);
        myLcdPrint(sens7, 1, 6, false);
        motorGo(0, CW, speedBerechnung(0, true));
        motorGo(1, CW, speedBerechnung(1, false));
        //pdebug.print("Fahren!");
      }
      else if (sens7 > WallOffsetBig)
      {
        myLcdPrint("Case 4", 0, 0, false);
        myLcdPrint(sens7, 1, 6, false);
        motorGo(0, CW, speedBerechnung(0, false));
        motorGo(1, CW, speedBerechnung(1, true));
        //pdebug.print("Fahren!");
      }
      else
      {
        myLcdPrint("Geradeaus", 0, 0, false);
        motorGo(0, CW, stdSpeed0);
        motorGo(1, CW, stdSpeed);
        //pdebug.print("Fahren!");
      }
    }
    else
    {
      myLcdPrint("Geradeaus", 0, 0, false);
      motorGo(0, CW, stdSpeed0);
      motorGo(1, CW, stdSpeed);
    }
  }
}

int speedBerechnung(int side, boolean calc)
{
  pdebug.println("speedBerechnung()");
  int tempSpeed;
  if (calc == true)
  {
    if (side == 0)
    {
      tempSpeed = stdSpeed0 * ausrichtenSpeed;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
    else if (side == 1)
    {
      tempSpeed = stdSpeed * ausrichtenSpeed;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
  }
  else
  {
    if (side == 0)
    {
      tempSpeed = stdSpeed0 * ausrichtenSpeedSlow;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
    else if (side == 1)
    {
      tempSpeed = stdSpeed * ausrichtenSpeedSlow;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
  }
}

int speedBerechnungRampe(int side, boolean calc)
{
  pdebug.println("speedBerechnung()");
  int tempSpeed;
  if (calc == true)
  {
    if (side == 0)
    {
      tempSpeed = rampeSpeed0 * ausrichtenSpeedRampe;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
    else if (side == 1)
    {
      tempSpeed = rampeSpeed * ausrichtenSpeedRampe;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
  }
  else
  {
    if (side == 0)
    {
      tempSpeed = rampeSpeed0 * ausrichtenSpeedSlowRampe;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
    else if (side == 1)
    {
      tempSpeed = rampeSpeed * ausrichtenSpeedSlowRampe;
      if (tempSpeed < 255)
      {
        return tempSpeed;
      }
      else
      {
        return 255;
      }
    }
  }
}

void blackField()
{
  pdebug.println("blackField()");
  myLcdPrint("Black Tile", 0, 0, true);
  motorGo(0, CCW, stdSpeed0);
  motorGo(1, CCW, stdSpeed);
  delay(blackTime);
  motorGo(0, CW, breakSpeed0);
  motorGo(1, CW, breakSpeed);
  delay(100);
  motorOff(0);
  motorOff(1);
  linksDrehen();
  delay(mainWait);
  if (is_open_front())
  {
    vorFahren();
    delay(mainWait);
  }
  else
  {
    linksDrehen();
    delay(mainWait);
    if (is_open_front())
    {
      vorFahren();
      delay(mainWait);
    }
    else
    {
      linksDrehen();
      delay(mainWait);
      vorFahren();
      delay(mainWait);
    }
  }
}

void driveRampeUp()
{
  while (is_RampeUp())
  {
    int sens3 = getDstSensor(3);
    myLcdPrint(sens3, 0, 1, true);
    if (sens3 < CheckSensWall)
    {
      if (sens3 < WallOffsetSmall)
      {
        myLcdPrint("Case 1", 0, 0, false);
        myLcdPrint(sens3, 1, 6, false);
        motorGo(0, CW, speedBerechnungRampe(0, false));
        motorGo(1, CW, speedBerechnungRampe(1, true));
        //pdebug.print("Fahren!");
      }
      else if (sens3 > WallOffsetBig)
      {
        myLcdPrint("Case 2", 0, 0, false);
        myLcdPrint(sens3, 1, 6, false);
        motorGo(0, CW, speedBerechnungRampe(0, true));
        motorGo(1, CW, speedBerechnungRampe(1, false));
        //pdebug.print("Fahren!");
      }
      else
      {
        myLcdPrint("Geradeaus", 0, 0, false);
        motorGo(0, CW, rampeSpeed0);
        motorGo(1, CW, rampeSpeed);
        //pdebug.print("Fahren!");
      }
    }
    else
    {
      int sens7 = getDstSensor(7);
      if (sens7 < CheckSensWall)
      {
        if (sens7 < WallOffsetSmall)
        {
          myLcdPrint("Case 3", 0, 0, false);
          myLcdPrint(sens7, 1, 6, false);
          motorGo(0, CW, speedBerechnungRampe(0, true));
          motorGo(1, CW, speedBerechnungRampe(1, false));
          //pdebug.print("Fahren!");
        }
        else if (sens7 > WallOffsetBig)
        {
          myLcdPrint("Case 4", 0, 0, false);
          myLcdPrint(sens7, 1, 6, false);
          motorGo(0, CW, speedBerechnungRampe(0, false));
          motorGo(1, CW, speedBerechnungRampe(1, true));
          //pdebug.print("Fahren!");
        }
        else
        {
          myLcdPrint("Geradeaus", 0, 0, false);
          motorGo(0, CW, rampeSpeed0);
          motorGo(1, CW, rampeSpeed);
          //pdebug.print("Fahren!");
        }
      }
      else
      {
        myLcdPrint("Geradeaus", 0, 0, false);
        motorGo(0, CW, rampeSpeed0);
        motorGo(1, CW, rampeSpeed);
      }
    }
  }
}

//Basically normales Delay, dass abbricht bei Rampe
void delayMainWait()
{
  mainWaitTime = 0;
  while (mainWaitTime < mainWait && !is_RampeUp())
  {
  }
}

void speedCorrection(int dir)
{ //0 = Geradeaus
  if (timeSpeedCalc == 0)
  {
    //pdebug.println("New Data");
    oldL = encMotLcount;
    oldR = encMotRcount;
    /*pdebug.print("oldL");
    pdebug.println(oldL);
    pdebug.print("oldR");
    pdebug.println(oldR);*/
    timeSpeedCalc = millis() + 250;
  }
  if (dir == 0)
  {
    //pdebug.println("Jup");
    if (timeSpeedCalc <= millis())
    {
      newL = encMotLcount;
      newR = encMotRcount;
      deltaL = newL - oldL;
      deltaR = newR - oldR;
      /*      pdebug.print("newL");
      pdebug.println(newL);
      pdebug.print("newR");
      pdebug.println(newR);*/
      if (doMoveStraight())
      {
        if (deltaL - deltaR > offsetSpeedCalc)
        {
          if (speedGrade0 > basicChange + changeValue)
          {
            retL = false;
          }
          if (speedGrade < basicChange - changeValue)
          {
            retL = true;
          }
          if (retL)
          {
            speedGrade0 = speedGrade0 + changeEnc;
            pdebug.println("c1");
          }
          else
          {
            speedGrade = speedGrade - changeEnc;
            pdebug.println("c2");
          }
          pdebug.println("Correction left");
        }
        if (deltaR - deltaL > offsetSpeedCalc)
        {
          if (speedGrade > basicChange + changeValue)
          {
            retR = false;
          }
          if (speedGrade0 < basicChange - changeValue)
          {
            retR = true;
          }
          if (retR)
          {
            speedGrade = speedGrade + changeEnc;
            pdebug.println("c3");
          }
          else
          {
            speedGrade0 = speedGrade0 - changeEnc;
            pdebug.println("c4");
          }
          pdebug.println("Correction right");
        }
      }
      timeSpeedCalc = 0;
    }
  }
}

boolean doMoveStraight()
{
  deltaAll = (deltaL + deltaR) / 2;
  /*pdebug.print("Millis: ");
  pdebug.println(millis());*/
  /*pdebug.print("deltaL:");
  pdebug.println(deltaL);
  pdebug.print("deltaR: ");
  pdebug.println(deltaR);
  pdebug.print("speedL:");
  pdebug.println(speedGrade);
  pdebug.print("speedR:");
  pdebug.println(speedGrade0);*/
  /*pdebug.print("delta:");
  pdebug.println(deltaAll);*/
  if (deltaAll > encDoMove)
  {
    //pdebug.println("do Move!");
    return true;
  }
  //pdebug.println("do NOT Move!");
  return false;
}

void gradeAusTest()
{
  //pdebug.println("gradeAusTest");
  //int _time = millis() + 2000;
  //while(_time > millis()) {
  motorGo(1, CW, speedGrade);
  motorGo(0, CW, speedGrade0);
  speedCorrection(0);
}
