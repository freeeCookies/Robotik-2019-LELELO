void printKeyPadData(){
  
  keyData = keypadControl.readKeypad();
  // If keyData is 0, then nothing has been pressed. Otherwise
  // at least two bits in the 16-bit value will be set, each
  // corresponding to either a row or a column.
  if (keyData != 0) // If a key was pressed:
  {
    // Use io.getRow(<readKeypad>) and io.getCol(<readKeypad>)
  // to find the active row and columns:
    byte row = keypadControl.getRow(keyData);
    byte col = keypadControl.getCol(keyData);
  
  // Once you've found out the active row/col, put them in 
  // keyMap to get the character pressed.
    char key = keyMap[row][col];
    pdebug.print("Row: " + String(row));
    pdebug.print("\tCol: " + String(col));
    pdebug.print("\tKeydata: ");
    pdebug.print(keyData);
    pdebug.print("\tKey: ");
    pdebug.print(key);
    pdebug.println("");
  }
  else
  {
    //pdebug.print("keine Taste gedrueckt");
    pdebug.println("");
  }
}

void doStuffWithKeys() { 
  keyData = keypadControl.readKeypad();
  if (keyData != 0) {
    byte row = keypadControl.getRow(keyData);
    byte col = keypadControl.getCol(keyData);
    char key = keyMap[row][col];
    if(key=='1') {
      
    }
    else if(key=='2') {
      //rechtsDrehen();
    }
    else if(key=='3') {
      //rechtsDrehen();
    }
    else if(key=='4') {
      //rechtsDrehen();
    }
    else if(key=='5') {
      //linksDrehen();
    }
    else if(key=='6') {
      //rechtsDrehen();
    }
    else if(key=='7') {
     // measureAll();
    }
    else if(key=='8') {
     // vorFahren();
    }
    else if(key=='9') {
     // printColorData();
    }
  } 
}

int getKeyPad() {
  keyData = keypadControl.readKeypad();
  if (keyData != 0) {
    byte row = keypadControl.getRow(keyData);
    byte col = keypadControl.getCol(keyData);
    char key = keyMap[row][col];
    pdebug.print("Key: ");
    pdebug.println(key);
    return keyData;
  } else {
    return 0;
  }
}

