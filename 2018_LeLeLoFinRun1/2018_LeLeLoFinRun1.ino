#define ENCODER_OPTIMIZE_INTERRUPTS   // muss vor dem Aufruf von "Encoder.h" stehen
//#include <Encoder.h>                  // Auslesen Encoder an Motoren
#include <Wire.h>                     // I2C Library für mehrere Sensoren notwendig
#include <Adafruit_TCS34725.h>        // Farbsensor
//#include <TimeLib.h>                  // für real Time Clock notwendig
#include <Adafruit_MLX90614_Bus1.h>   // für Temperatursensoren mit Anpassung an I2C Bus 1
#include <SparkFunSX1509Teensy35.h>   // Include SX1509 library Patched auf Tensy mit 3 I2C und extra Funktion für Blinken aus
//#include <SparkFunSX1509_2.h>         // Include SX1509 library Patched auf I2C2 => Ersatz durch <SparkFunSX1509Teensy35.h>
#include <Adafruit_VL53L0X_2.h>       // Include VL53L0x library Patched auf I2C2
#include <Servo.h>                    // Dropper
#include <LiquidCrystal_I2C.h>        // Displayansteuerung
#include <Adafruit_Sensor.h>          // Orientationsensor BNO055
#include <Adafruit_BNO055.h>          // Orientationsensor BNO055
#include <utility/imumaths.h>         // Orientationsensor BNO055
//#include <SparkFunSX1509.h>           // SX1509 Portexpander an i2c (Original Library) Ersatz durch <SparkFunSX1509Teensy35.h>
//#include <SdFat.h>                    // Zum Lesen und Schreiben auf SD-Card notwendig

#include "hardware_def.h"             // im selben Verzeichnis suchen
#include "variables_def.h"            // im selben Verzeichnis suchen



void setup() {

  pdebug.begin(38400);            // Geschwindigkeit auf Bluetooth, Serial ist bei Tennsy immer full speed
  
  // Init Display
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  lcd.begin();                              // initialize the lcd 
  for ( int i = 0; i < charBitmapSize; i++ )
    {
      lcd.createChar ( i, (uint8_t *)charBitmap[i] );
    }
  lcd.setCursor(0,0);                       // go home
  lcd.print("Hello,");  
  lcd.setCursor ( 0, 1 );                   // go to the next line
  lcd.print ("I'm LeLeLo");    

  
  // interne LED zur Kontrolle
  pinMode(PIN_LED_internal, OUTPUT);    


  // Sparkfun Motorshield
  for (int i=0; i<2; i++){
    pinMode(inCWpin[i], OUTPUT);
    digitalWrite(inCWpin[i], LOW);            // Initialize braked
    pinMode(inCCWpin[i], OUTPUT);
    digitalWrite(inCCWpin[i], LOW);           // Initialize braked
    pinMode(speedpin[i], OUTPUT);
    analogWriteFrequency(speedpin[i], pwmFrequency); // PWM Frequenz für Motor erhöhen
    analogWrite(speedpin[i], 0);              // Speed auf 0 setzen
    pinMode(loadpin[i], INPUT);
    pinMode(healthpin[i], INPUT_PULLUP);    
  }

  // Encoder
  pinMode(PIN_Enc_RA, INPUT_PULLUP);
  pinMode(PIN_Enc_RB, INPUT_PULLUP);
  pinMode(PIN_Enc_LA, INPUT_PULLUP);
  pinMode(PIN_Enc_LB, INPUT_PULLUP);

  // Batteriesensor
  pinMode(PIN_Bat_level, INPUT);    
  

  //Farbsensor
  lcd.clear();
  lcd.setCursor(0,0);                       // go home
  lcd.print("Init Color");
  lcd.setCursor(0,1);
  lcd.print("sensor");  
 
  pinMode(PIN_Color_LED, OUTPUT);
  digitalWrite(PIN_Color_LED,LOW);
  pinMode(PIN_Color_Int, INPUT_PULLUP);
  if (colorFloor.begin()){
    if (debugMode) {pdebug.println("Farbsensor gefunden");}
  }
  lcd.setCursor ( 12, 1 );                   // go to the next line
  lcd.print ("done");    
  delay(250);
  
  // Front Taster
  pinMode(PIN_Front_R, INPUT_PULLUP);
  pinMode(PIN_Front_L, INPUT_PULLUP);

  // set the Time library to use Teensy 3.0's RTC to keep time
//  setSyncProvider(getTeensy3Time);  

  // Temperatur Sensoren
  // Reset der Temp Sensoren auf I2C ==> SCL1 für > 1024 ms auf Low setzen 
  //  
  lcd.clear();
  lcd.setCursor(0,0);                       // go home
  lcd.print("Init Tempsensors");
  lcd.setCursor(0,1);
  lcd.print("(2 sec)");  

  pinMode(PIN_temp_SCL, OUTPUT);
  digitalWrite(PIN_temp_SCL,HIGH);
  delay(600);
  digitalWrite(PIN_temp_SCL,LOW);
  delay(1100);
  digitalWrite(PIN_temp_SCL, HIGH);
  delay(100);
  for (int i=0; i<2; i++){
    tempSensor[i].begin();  
  }
  lcd.setCursor ( 12, 1 );                   // go to the next line
  lcd.print ("done");
  delay(250);    
  
  // Entferunungsensoren incl. SX1509 für Ansteuerung. 
  lcd.clear();
  lcd.setCursor(0,0);                       // go home
  lcd.print("Init Distsensors");
  lcd.setCursor(0,1);
  lcd.print("(2 sec)");  

  boolean retvalDistSelect = DistSelect.begin(Addr_SX1509_dist, i2cBus_SX1509_dist);
  DistSelect.clock(INTERNAL_CLOCK_2MHZ, 4);                 // internene Clock verwenden
  for(int i=0; i<8; i++){
    DistSelect.pinMode(i, OUTPUT);
    DistSelect.digitalWrite(i,LOW); 
    DistSelect.pinMode(i+8, INPUT_PULLUP);
    // DistSelect.enableInterrupt(i+8, FALLING);
  }
  pinMode(PIN_DistSelectInt, INPUT_PULLUP);
  distSensorInit();
  lcd.setCursor ( 12, 1 );                   // go to the next line
  lcd.print ("done");
  delay(250);    

  // Servo Dropper
  DR_servo.attach(PIN_DR_servo, 650, 2500);  // attaches the servo on pin 20 
  DR_servo.write(DR_neutral);                // tell servo to go to position in variable 'pos' 

  // Orientationsensor BNO055
  lcd.clear();
  lcd.setCursor(0,0);                       // go home
  lcd.print("Init Orientation");
  lcd.setCursor(0,1);
  lcd.print("sensor (1 sec)");  

  boolean retvalOri = oriSensor.begin();
  delay(1000);
  oriSensor.setExtCrystalUse(true);
  lcd.setCursor ( 12, 1 );                   // go to the next line
  lcd.print ("done");
  delay(250);    
  

  // Tastatur, Batterie-, Victim-Anzeige incl. SX1509 für Ansteuerung
  keypadControl.begin(Addr_SX1509_keypad, i2cBus_SX1509_keypad);
  keypadControl.clock(INTERNAL_CLOCK_2MHZ, 4);
  keypadControl.keypad(KEY_ROWS, KEY_COLS, keypad_sleepTime, keypad_scanTime, keypad_debounceTime);
  keypadControl.pinMode(PIN_SX1509_HandControl, OUTPUT); // Set LED pin to OUTPUT
  if(handMode){
    keypadControl.digitalWrite(PIN_SX1509_HandControl, HIGH);
  }
  else {
    keypadControl.digitalWrite(PIN_SX1509_HandControl, LOW);
  }
  keypadControl.pinMode(PIN_SX1509_VictimRight, OUTPUT); // Set LED pin to OUTPUT
  keypadControl.digitalWrite(PIN_SX1509_VictimRight, LOW);  
  keypadControl.pinMode(PIN_SX1509_VictimLeft, OUTPUT); // Set LED pin to OUTPUT
  keypadControl.digitalWrite(PIN_SX1509_VictimLeft, LOW);  
  for (int i=0; i<4; i++){
    keypadControl.pinMode(SX1509_Batt[i], OUTPUT); // Set LED pin to OUTPUT
    keypadControl.digitalWrite(SX1509_Batt[i], LOW);
  }
  set_Batterie_Level();                                       // Batterie abfragen und korrekt anzeigen
  myLcdPrint("Losfahren? Mitte", 0, 0, true);
  leaveWhile = false;
  pdebug.println(leaveWhile);
  while(leaveWhile == false) {
    keyData = keypadControl.readKeypad();
    if (keyData != 0) {
      byte row = keypadControl.getRow(keyData);
      byte col = keypadControl.getCol(keyData);
      char key = keyMap[row][col];
     if(key=='2') {
        startOrientZ = getOrientZ();
        digitalWrite(PIN_Color_LED,HIGH);
        leaveWhile = true;
     } else if(key=='8') {
        startOrientZ =getOrientZ();
        digitalWrite(PIN_Color_LED,HIGH);
        setupColorSensor();
        leaveWhile = true;
      }
    }
  }
  
//  lcd.clear();
//  lcd.setCursor(0,0);                       // go home
//  lcd.print("Init done");  
//  lcd.setCursor ( 0, 1 );                   // go to the next line
//  lcd.print ("do something");
}

void loop() {
  // Interne LED als Heartbeat blinken lassen
  if (workingLED > HBintervalTime){
    workingLED = 0;
    HBstate = !HBstate;
    digitalWrite(PIN_LED_internal, HBstate);
  }

  // Batterielevel auslesen und Anzeige neu setzen
  set_Batterie_Level();

  /*pdebug.println("Sensor 0: ");
  pdebug.println(getDstSensor(0));
  pdebug.println("Sensor 1: ");
  pdebug.println(getDstSensor(1));
  pdebug.println("Sensor 2: ");
  pdebug.println(getDstSensor(2));
  pdebug.println("Sensor 3: ");
  pdebug.println(getDstSensor(3));
  pdebug.println("Sensor 4: ");
  pdebug.println(getDstSensor(4));
  pdebug.println("Sensor 5: ");
  pdebug.println(getDstSensor(5));
  pdebug.println("Sensor 6: ");
  pdebug.println(getDstSensor(6));
  pdebug.println("Sensor 7: ");
  pdebug.println(getDstSensor(7));*/
  
  //Fahrlogik
  if(setTaster) {              //Lese Fronttaster aus
    if(is_open_left_front()) {     //Prüfe Links
      linksDrehen();
      delayMainWait();
      vorFahren();
      delayMainWait();
    } else if(is_open_right()) {     //Prüfe Rechts
      rechtsDrehen();
      delayMainWait();
      vorFahren();
      delayMainWait();
    } else {
      linksDrehen();
      linksDrehen();
    }
    setTaster = false;
  }
  if(is_RampeUp()) {        //Prüfe Rampe
    driveRampeUp(); 
  } 
  //while(!is_RampeUp()) { 
    else if(is_open_left_front()) {      //Prüfe Links
      pdebug.println("Links");
      linksDrehen();
      delayMainWait();
      vorFahren();
      delayMainWait();
    }
    else if(is_open_front()) {     //Prüfe Vorne
      pdebug.print("Vorne");
      vorFahren();
      delayMainWait();
    }
    else if(is_open_right()) {      //Prüfe Rechts
      pdebug.println("Rechts");
      rechtsDrehen();
      delayMainWait();
      vorFahren();
      delayMainWait();
    }
    else{
      pdebug.println("SackGasse");
      myLcdPrint("Sackgasse", 0, 0, true);
      delay(1000);
      linksDrehen();
    }
/*  myLcdPrint("*", 15, 1, false);
  delay(1000);
  myLcdPrint(" ", 15, 1, false);*/
}
