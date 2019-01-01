void distSensorInit() {  // Adafruit Library
  pdebug.println("Init DistSensoren");
  for (int i = 0; i < 8; i++) {                   //Alle Sensoren zurücksetzen
    DistSelect.digitalWrite(i, LOW);
  }
  delay(10);                                      //warten, damit alle Sensoren sicher zurückgesetzt sind
  for (int i = 0; i < 8; i++) {                   // Alle Sensoren neu initialisieren
    DistSelect.digitalWrite(i, HIGH);
    DistSensor[i].begin(i + Addr_VL53L0X_start);
    pdebug.print("Init DistSensor : ");
    pdebug.print(i);
    pdebug.print(" mit Adresse ");
    pdebug.println(i + Addr_VL53L0X_start);
  }
}

boolean distSensorDefaultCheck() {  //Test auf 0x29 auf I2C2
  boolean retval = false;
  Wire2.beginTransmission(Addr_VL53L0X_default);
  error = Wire2.endTransmission();
  if (error == 0) {
    pdebug.println ("einen Sensor auf Default Adresse erkannt, alle Sensoren neu Initialisieren");
    //distSensorInit();
    retval = true;
  }
  return retval;
}

void readDistance() {       // Adafruit Library
  for (int i = 0; i < 8; i++) {
    DistSensor[i].rangingTest(&measure[i], false); // pass in 'true' to get debug data printout!
    if (measure[i].RangeStatus != 4) {  // phase failures have incorrect data
        DistValue[i] = measure[i].RangeMilliMeter;
        pdebug.print("Sensor ");
        pdebug.print(i);
        pdebug.print(":     ");
        pdebug.print(millis());
        pdebug.print(" : ");
      if(DistValue[i]>650) {
        pdebug.print("600+");
      }
      else {
        pdebug.print(DistValue[i]);
      }
      pdebug.println("");
      //pdebug.print(" , ");
   } else {
      DistValue[i]= 4000;     //32767;            //Maximalwert für Int+- Werte
      pdebug.print("Sensor ");
      pdebug.print(i);
      pdebug.print(":     ");
      pdebug.print(millis());
      pdebug.print(" : ");
      pdebug.print("Out of Range or Failure");
      pdebug.println("");
    }
  }
  pdebug.print("Ende Messung: ");
  pdebug.print(millis());
  pdebug.println("");
}

int getDstSensor(int ID) {
  if(ID == 2 && getTaster()) {  //Verhindern von Falschmessungen. Falls Taster gedrückt: Hindernis
    pdebug.println("Taster! Return 1");
    return 1;
  }
  DistSensor[ID].rangingTest(&measure[ID], false);
  if (measure[ID].RangeStatus != 4) {  // phase failures have incorrect data
    int value = measure[ID].RangeMilliMeter;
    pdebug.print("org W: ");
    pdebug.println(value);

    if (value < correctDistSens[ID]) {  //Messung nach unendlich, Annahme Rückgbewert ist 0
      value = 5100;
    }

    value = value-correctDistSens[ID] -3;
    if(value < 1) {
      value=1;
    }
    pdebug.print("Sensor ");
    pdebug.print(ID);
    pdebug.print(" : ");
    pdebug.println(value);
    if(value>650) {
      pdebug.println("Overflow");
      return 4000;
    }
    else {
      return value;
    }
  }
  else { 
    return 3000;
  }
}

boolean is_open_left_front() {
  int sen3 = getDstSensor(3);
  pdebug.print("Messung links");
  pdebug.println(sen3);
  if(sen3 < 300) {
    return false;
  } else{
    pdebug.println("left open true");
    return true;
  }
}

boolean is_open_left_back() {
  if(getDstSensor(0) < 300) {
    return false;
  } else{
    pdebug.println("left open true");
    return true;
  }
}

boolean is_open_front() {
  if(getDstSensor(2) < 300) {
    pdebug.println("front closed");
    return false;
  } else{
    pdebug.println("front open true");
    return true;
  }
}

boolean is_open_right() {
  if(getDstSensor(7) < 300) {
    return false;
  } else{
    pdebug.println("right open true");
    return true;
  }
}

void measureAll() {
  
  while(getKeyPad() == 0) {
    readDistance();
    printDistSensors();
    delay(1000);
  }
}


void printDistSensors() {

  String iText[10];
  String iValueText;
  
  iText[0] = "           ^            ";
  iText[1] = "     ";
  iValueText = "    " + DistValue[frontLeftFront];
  iText[1] += iValueText.substring(iValueText.length()-4);
  iText[1] += " | ";
  iValueText = "    " + DistValue[frontRightFront];
  iText[1] += iValueText.substring(iValueText.length()-4);
  iText[1] += "    ";
  iText[2] = "     +------------+     ";
  iValueText = "    " + DistValue[frontLeftSide];
  iText[3] = "";
  iText[3] += iValueText.substring(iValueText.length()-4); 
  iText[3] += "<|            |>";
  iValueText = "    " + DistValue[frontRightSide];
  iText[3] += iValueText.substring(iValueText.length()-4); 
  iText[4] = "     |            |     ";
  iText[5] = "     |            |     ";
  iText[6] = "";
  iValueText = "    " + DistValue[backLeftSide];
  iText[6] += iValueText.substring(iValueText.length()-4); 
  iText[6] += "<|            |>";
  iValueText = "    " + DistValue[backRightSide];
  iText[6] += iValueText.substring(iValueText.length()-4); 
  iText[7] = "     +------------+     ";
  iValueText = "     " + 
  iText[8] += iValueText.substring(iValueText.length()-4);
  iText[8] += "   ";
  iValueText = "     " + DistValue[backRightBack];
  iText[8] += iValueText.substring(iValueText.length()-4);
  iText[8] += "    ";
  iText[9] = "           H            ";

  for (int i=0; i<10; i++) {
    pdebug.println(iText[i]);
  }
}

boolean getTaster() {
  if(digitalRead(PIN_Front_R) == 0 || digitalRead(PIN_Front_R) == 0) {
    setTaster = true;
    return true;
  } else {
    return false;
  }
}

