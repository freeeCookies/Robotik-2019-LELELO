void printColorData() {
   
  colorFloor.getRawData(&r, &g, &b, &c);
  pdebug.print("R: "); pdebug.print(r, DEC); pdebug.print(" ");
  pdebug.print("G: "); pdebug.print(g, DEC); pdebug.print(" ");
  pdebug.print("B: "); pdebug.print(b, DEC); pdebug.print(" ");
  pdebug.print("C: "); pdebug.print(c, DEC); pdebug.println(" ");
}

void setupColorSensor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Init Colorsensor");
  lcd.setCursor(0, 1);
  lcd.print("Weiss");
  delay(5000);
      pdebug.println("Weiss");
      colorFloor.getRawData(&r, &g, &b, &c);
      startcWhite = c, DEC;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Messung fertig!");
      lcd.setCursor(0, 1);
      lcd.print("Wert: ");
      lcd.setCursor(5, 1);
      lcd.print(startcWhite);
      delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Init Colorsensor");
  lcd.setCursor(0, 1);
  lcd.print("Schwarz");
  delay(5000);
      pdebug.println("schwarz");
      colorFloor.getRawData(&r, &g, &b, &c);
      startcBlack = c, DEC;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Messung fertig!");
      lcd.setCursor(0, 1);
      lcd.print("Wert: ");
      lcd.setCursor(5, 1);
      lcd.print(startcBlack);
      delay(2000);
      pdebug.println("Silber");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Init Colorsensor");
  lcd.setCursor(0, 1);
  lcd.print("Silber");
  delay(5000);
      colorFloor.getRawData(&r, &g, &b, &c);
      startcSilver = c, DEC;
      pdebug.println("Berechnung fertig");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Messung fertig!");
      lcd.setCursor(0, 1);
      lcd.print("Wert: ");
      lcd.setCursor(5, 1);
      lcd.print(startcSilver);
      delay(2000);
  tolColor = (startcWhite + startcSilver)/2;
  borderBlack = (startcSilver + startcBlack)/2;
  pdebug.print("Toleranzwert für Farberkennung: ");
  pdebug.println(tolColor);
  pdebug.print("Borderblack: ");
  pdebug.println(borderBlack);
}

int getFieldColor() {   //0 = weiss, 1 = silber, 2 = schwarz
   colorFloor.getRawData(&r, &g, &b, &c);
   tempC = c, DEC;
   pdebug.print("Clearwert: "); pdebug.println(tempC);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print(tempC);
   if(tempC < borderBlack) {
    blackField();
    delay(mainWait);
    return 2;
   }
   else if(tempC > tolColor) {
    return 0;
   }
   else{
    return 1;
   }
}
