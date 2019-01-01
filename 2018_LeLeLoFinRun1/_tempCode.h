
  //Handmode
    if(handMode) {
    if (HCstatus){
      getMotorSpeedAll();
      motorGo(mot_L, motorSettings[mot_L].driveDir, motorSettings[mot_L].driveSpeed);
      motorGo(mot_R, motorSettings[mot_R].driveDir, motorSettings[mot_R].driveSpeed);
    } 
   else {              // solange keine Routine fährt alles anhalten
     motorOff(mot_L);
     motorOff(mot_R);
   }
    ReadMotStatus();
  }
  else {
    //Get Sensor Values
    for(int i=0; i<8; i++) {
      s[i]= getDstSensor(i);
      while(s[i]== 3000) {
         s[i]= getDstSensor(i);
      }
    }
  }

    //25.2.18 An Wand lang fahren
    //Driving
  pdebug.println(millis());
  if(getDstSensor(ID2)-getDstSensor(ID1)>15) {
    motorGo(0,CW,stdSpeed0*0.3);
    motorGo(1,CW,stdSpeed*3);
    pdebug.println("Correcting RIGHT");
  }
  else if(getDstSensor(ID1)-getDstSensor(ID2)>15) {
    motorGo(0,CW,stdSpeed0*3);
    motorGo(1,CW,stdSpeed*0.3);
    pdebug.println("Correcting LEFT");
  }
  else {
    motorGo(0,CW,stdSpeed0);
    motorGo(1,CW,stdSpeed);
  }

  
    
    // Encoder auslesen
    encMotRcount = encMotR.read();
    encMotLcount = encMotL.read();
    pdebug.print("Enc Rechts:\t");
    pdebug.print(encMotRcount);
    pdebug.print("\tEnc Links:\t");
    pdebug.println(encMotLcount);

    // Farbsensor auslesen
    digitalWrite(PIN_Color_LED,HIGH);      // turn on LED
    delay(60);                             // takes 50ms to read, später Interupt auswerten 
    colorFloor.getRawData(&colorRed, &colorGreen, &colorBlue, &colorClear);
    digitalWrite(PIN_Color_LED,LOW);      // turn off LED
    pdebug.print("Farbsensor Clear:\t");
    pdebug.print(colorClear);
    pdebug.print("\tRot:\t");
    pdebug.print(colorRed);
    pdebug.print("\tGruen:\t");
    pdebug.print(colorGreen);
    pdebug.print("\tBlau:\t");
    pdebug.println(colorBlue);
    // Front Taster
    FrontPressedR = !digitalRead(PIN_Front_R);
    FrontPressedL = !digitalRead(PIN_Front_L);
    pdebug.print("Fronttaster Links:\t");
    pdebug.print(FrontPressedL);
    pdebug.print("\tRechts:\t");
    pdebug.println(FrontPressedR);

    // Entfernung auslesen
    readDistance();
    // Orientation auslesen
    ReadOrientData();
    //Keypad auslesen
    printKeyPadData();
    // Eingabe Hanssteuerung auslesen
    getMotorSpeedAll();
    DebugPrintMotorValues();


    // Leerzeiten bei Ausgabe
    pdebug.println();
    pdebug.println();
    pdebug.println();
    
  }


    //Get Offset
//    while(something==true) {
//      pdebug.print(s[0]);
      //if(s[0]<300) {
        //offRight = s[0];
        //pdebug.print("Offset: ");
        //pdebug.println(offRight);
      //}
//      something = false;
//    }
//  }

  // Motor ansteuern

  /*
  //Detect Walls
  while(something) {
    if(getDstSensor(4)<250||getDstSensor(7)<250) {
      ID1 = 7;
      ID2 = 4;
    }
    else if(getDstSensor(0)<250||getDstSensor(3)) {
      ID1 = 3;
      ID2 = 0;
    }
    something = false;
  }*/

  
  
  /*
  pdebug.print("Left:");
  pdebug.println(is_open_left());
  pdebug.print("Front:");
  pdebug.println(is_open_front());
  pdebug.print("Right:");
  pdebug.println(is_open_right());
  pdebug.println("***********************");
  delay(500);*/
  // Temperatur auslesen und Victim behandeln
  //vorFahren();
  //boolean tempResult = readTemp();
  //setVictim();
//  if (debugMode) {
//    pdebug.println("");
//    pdebug.print("Measuring at: ");
//    pdebug.println(millis());
//    DebugPrintTempValues();
//    pdebug.println("");
//    //delay(2000);
//  }  

