void distSensorInit()   // Adafruit Library
{
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
      pdebug.print("Sensor ");
      pdebug.print(i);
      pdebug.print(":     ");
      pdebug.print(millis());
      pdebug.print(" : ");
      int value = measure[i].RangeMilliMeter;
      if(value>600) {
        pdebug.print("600+");
      }
      else {
        pdebug.print(value);
      }
      pdebug.println("");
      //pdebug.print(" , ");
    } else {
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
  DistSensor[ID].rangingTest(&measure[ID], false);
  if (measure[ID].RangeStatus != 4) {  // phase failures have incorrect data
    int value = measure[ID].RangeMilliMeter;
//    pdebug.print("Sensor ");
//    pdebug.print(ID);
//    pdebug.print(" : ");
//    pdebug.println(value);
    if(value>650) {
      pdebug.println("Overflow");
      return 4000;
    }
    else {
      pdebug.println("gemessener Wert");
      return value;
    }
  }
  else { 
    pdebug.println("Phase Failure");
    return 3000;
  }
}

boolean is_open_left() {
  if(getDstSensor(3) < 300) {
    return false;
  } else{
    return true;
  }
}

boolean is_open_front() {
  if(getDstSensor(6) < 300) {
    return false;
  } else{
    return true;
  }
}

boolean is_open_right() {
  if(getDstSensor(7) < 300) {
    return false;
  } else{
    return true;
  }
}

void measureAll() {
  
  while(getKeyPad() == 0) {
    readDistance();
    delay(1000);
  }
}


void printDistSensors() {

  String iText[10];
  String iValueText;
  
  iText[0] = "           ^            ";
  iText[1] = "     ";
  iValueText = "    " + measure[frontLeftFront].RangeMilliMeter;
  iText[1] += iValueText.substring(iValueText.length()-4);
  iText[1] += " | ";
  iValueText = "    " + measure[frontRightFront].RangeMilliMeter;
  iText[1] += iValueText.substring(iValueText.length()-4);
  iText[1] += "    ";
  iText[2] = "     +------------+     ";
  iText[3] = "    <|            |>    ";
  iText[4] = "     |            |     ";
  iText[5] = "     |            |     ";
  iText[6] = "    <|            |>    ";
  iText[7] = "     +------------+     ";
  iText[8] = "                        ";
  iText[9] = "           H            ";

  for (int i=0; i<10; i++) {
    pdebug.println(iText[i]);
  }
}

