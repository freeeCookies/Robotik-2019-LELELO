void rechtsDrehen() {
  curX = getOrientX();//euler.x();
  pdebug.println(curX);
  pdebug.print("CurX: ");
  pdebug.println(curX);
  finX = curX + 90;
  if(finX >= 360) {
    finX -= 360;
  }
  //Toleranzbereich berechnen
  if(finX < tol) {
    tolX1 = finX + 360 - tol;
    tolX2 = finX + tol;
    dMode = 1;
  }
  else if(finX < 360 - tol) {
    tolX1 = finX - tol;
    tolX2 = finX + tol;
    dMode = 2;
  }
  else if(finX < 360) {
    tolX1 = finX - tol;
    tolX2 = finX - 360 + tol;
    dMode = 3;
  }

  switch(dMode) {
    case 1:
      pdebug.print("Case: 1");
      while(getOrientX()<tolX1&&getOrientX()>tolX2) {
        motorGo(0,CCW,stdSpeed0);
        motorGo(1,CW,stdSpeed);
      }
      motorOff(0);
      motorOff(1);
      break;

    case 2:
      pdebug.println("Case: 2");
      pdebug.println(getOrientX());
      while(getOrientX()>90) {
        pdebug.println("Case 2.1");
        motorGo(0,CCW,stdSpeed0);
        motorGo(1,CW,stdSpeed);
      }
      pdebug.print("Debugpunkt 1");
      motorOff(0);
      motorOff(1);
      while(getOrientX()<tolX1) {
        pdebug.println("Case 2.2");
        motorGo(0,CCW,stdSpeed0);
        motorGo(1,CW,stdSpeed);
      }
      pdebug.print("Debugpunkt 2");
      motorOff(0);
      motorOff(1);
      break;


    case 3:
      pdebug.print("Case: 3 ");
      while(getOrientX()<tolX1) {
        //motorGo(0,CCW,stdSpeed0);
        //motorGo(1,CW,stdSpeed);
      }
      motorOff(0);
      motorOff(1);
      break;
  }
}

void linksDrehen() {
  curX = getOrientX();//euler.x();
  pdebug.println(curX);
  pdebug.print("CurX: ");
  pdebug.println(curX);
  finX = curX - 90;
  if(finX < 0) {
    finX += 360;
  }
  //Toleranzbereich berechnen
  if(finX < tol) {
    tolX1 = finX + 360 - tol;
    tolX2 = finX + tol;
    dMode = 1;
  }
  else if(finX > tol && finX < 360-tol) {
    tolX1 = finX - tol;
    tolX2 = finX + tol;
    dMode = 2;
  }
  else if(finX < 360 - tol) {
    tolX1 = finX - tol;
    tolX2 = finX - 360 + tol;
    dMode = 3;
  }

  switch(dMode) {
    case 1:
      pdebug.print("Case: 1");
      while(getOrientX()<tolX1&&getOrientX()>tolX2) {
        motorGo(0,CW,stdSpeed0);
        motorGo(1,CCW,stdSpeed);
      }
      motorOff(0);
      motorOff(1);
      break;

    case 2:
      pdebug.println("Case: 2");
      pdebug.println(getOrientX());
      while(getOrientX()<90) {
        pdebug.println("Case 2.1");
        motorGo(0,CW,stdSpeed0);
        motorGo(1,CCW,stdSpeed);
      }
      pdebug.print("Debugpunkt 1");
      motorOff(0);
      motorOff(1);
      while(getOrientX()>tolX2) {
        pdebug.println("Case 2.2");
        motorGo(0,CW,stdSpeed0);
        motorGo(1,CCW,stdSpeed);
      }
      pdebug.print("Debugpunkt 2");
      motorOff(0);
      motorOff(1);
      break;


    case 3:
      pdebug.print("Case: 3 ");
      while(getOrientX()<tolX2) {
        //motorGo(0,CCW,stdSpeed0);
        //motorGo(1,CW,stdSpeed);
      }
      motorOff(0);
      motorOff(1);
      break;
  }
}

void gradeFahren() {
  int Sen2 = getDstSensor(2);
  pdebug.print("Sen2 :");
  pdebug.println(Sen2);
  int Sen5 = getDstSensor(5);
  pdebug.print("Sen5 :");
  pdebug.println(Sen5);
  if(Sen2 < 650) {
    dMode = 1;  
  }
  else if(Sen5 < 350) {
    dMode = 2;
  }
  else{
    dMode = 3;
  }
  pdebug.println(dMode);
  
   switch(dMode) {
     case 1:
       dstBefore = getDstSensor(2);
       while(dstBefore-getDstSensor(2)<stopThreshold && getDstSensor(6)>wallBreak) {
         motorGo(1,CW,speedGrade);
         motorGo(0,CW,speedGrade0);
         speedCorrection(0); 
       }
       motorGo(0,CCW,15*1.4);
       motorGo(1,CCW,15);
       delay(100);
       motorOff(0);
       motorOff(1);
       break;
       
     case 2:
       dstBefore = getDstSensor(5);
       while(getDstSensor(5)-dstBefore<stopThreshold && getDstSensor(6)>wallBreak){
         motorGo(1,CW,speedGrade);
         motorGo(0,CW,speedGrade0);
         speedCorrection(0); 
       }
       motorGo(0,CCW,15*1.4);
       motorGo(1,CCW,15);
       delay(100);
       motorOff(0);
       motorOff(1);
       break;

       case 3:
       encBefore = encMotRcount;
       pdebug.print("encBefore : ");
       pdebug.println(encBefore);
       while(encMotRcount - encBefore<stopEnc && getDstSensor(6)>wallBreak) {
         motorGo(1,CW,speedGrade);
         motorGo(0,CW,speedGrade0);
         speedCorrection(0); 
       }
       motorGo(0,CCW,15*1.4);
       motorGo(1,CCW,15);
       delay(100);
       motorOff(0);
       motorOff(1);
       break;
       
   }
} 

void vorFahren() {
  int Sen2 = getDstSensor(2);
  int Sen5 = getDstSensor(5);
  lcd.clear();
  lcd.setCursor(0,1);                      
  lcd.print(Sen2);
  lcd.setCursor(8,1);
  lcd.print(Sen5);
  if(Sen2 < 650) {
    dMode = 1;
  } else if(Sen5 < 350) {
    dMode = 2;
  } else{
    dMode = 3;
  }

  switch(dMode) {
    case 1:
      lcd.setCursor(0,0);                      
      lcd.print("Case 1");
      pdebug.print("Ich fahre und hier fahre ich los: ");
      dstBefore = getDstSensor(2);
      pdebug.println(dstBefore);
      while(dstBefore-getDstSensor(2)<stopThreshold && getDstSensor(6)>wallBreak){
        motorGo(0,CW,stdSpeed0);
        motorGo(1,CW,stdSpeed);
        lcd.setCursor(0,1);
        lcd.print(measure[2].RangeMilliMeter); 
      }
      pdebug.print("Ich will nicht mehr und hier steh ich: ");
      pdebug.println(getDstSensor(2));
      motorGo(0,CCW,15*1.4);
      motorGo(1,CCW,15);
      delay(100);
      motorOff(0);
      motorOff(1);
      delay(1000);
      delay(5000);
      pdebug.println("Finish");
      pdebug.print("Sehr Spastischer Wert: ");
      pdebug.println(getDstSensor(2));
      break;

    case 2:
      lcd.setCursor(0,0);                      
      lcd.print("Case 2");
      pdebug.print("Ich fahre und hier fahre ich los: ");
      dstBefore = getDstSensor(5);
      pdebug.println(dstBefore);
      while(getDstSensor(5)-dstBefore<stopThreshold){
        motorGo(0,CW,stdSpeed0);
        motorGo(1,CW,stdSpeed);
        lcd.setCursor(8,1);
        lcd.print(measure[5].RangeMilliMeter); 
      }
      pdebug.print("Ich will nicht mehr und hier steh ich: ");
      pdebug.println(getDstSensor(5));
      motorGo(0,CCW,15*1.4);
      motorGo(1,CCW,15);
      delay(100);
      motorOff(0);
      motorOff(1);
      delay(1000);
      delay(5000);
      pdebug.println("Finish");
      pdebug.print("Sehr Spastischer Wert: ");
      pdebug.println(getDstSensor(5));
      break;

    case 3:
      lcd.setCursor(0,0);                      
      lcd.print("Case 3"); 
      break;
  }  
}


void speedCorrection(int dir) {  //0 = Geradeaus
  if(timeSpeedCalc == 0) { 
    //pdebug.println("New Data");
    oldL = encMotLcount;
    oldR = encMotRcount;
    /*pdebug.print("oldL");
    pdebug.println(oldL);
    pdebug.print("oldR");
    pdebug.println(oldR);*/
    timeSpeedCalc = millis() + 250;
  }
  if(dir == 0) {
    //pdebug.println("Jup");    
    if(timeSpeedCalc <= millis()) {
      newL = encMotLcount;
      newR = encMotRcount;
      deltaL = newL - oldL;
      deltaR = newR - oldR;
/*      pdebug.print("newL");
      pdebug.println(newL);
      pdebug.print("newR");
      pdebug.println(newR);*/
      if(doMoveStraight()) {
        if(deltaL - deltaR > offsetSpeedCalc) {
          if(speedGrade0 > basicChange + changeValue) {
            retL = false;
          }
          if(speedGrade < basicChange - changeValue) {           
            retL = true;            
          }
          if(retL) {            
            speedGrade0 = speedGrade0 +changeEnc;
            pdebug.println("c1");
          } else{
            speedGrade = speedGrade -changeEnc;  
            pdebug.println("c2"); 
          }
          pdebug.println("Correction left");       
        }
        if(deltaR - deltaL > offsetSpeedCalc) {         
          if(speedGrade > basicChange + changeValue) {
            retR = false;
          }
          if(speedGrade0 < basicChange - changeValue) {
            retR = true;                     
          }
          if(retR) {             
            speedGrade = speedGrade +changeEnc;
            pdebug.println("c3");
          } else{
            speedGrade0 = speedGrade0 -changeEnc;   
            pdebug.println("c4");
          }
          pdebug.println("Correction right");       
        }     
      }
      timeSpeedCalc = 0;   
    } 
  }
}



boolean doMoveStraight() {
  deltaAll = (deltaL + deltaR) /2;
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
  if(deltaAll > encDoMove) {
    //pdebug.println("do Move!");
    return true; 
  }
  //pdebug.println("do NOT Move!");
  return false;
}

void gradeAusTest() {
  //pdebug.println("gradeAusTest");
  //int _time = millis() + 2000;
  //while(_time > millis()) {
  motorGo(1,CW,speedGrade);
  motorGo(0,CW,speedGrade0);
  speedCorrection(0); 
}
