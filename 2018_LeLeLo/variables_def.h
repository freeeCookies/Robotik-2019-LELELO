int startEncR;
int encBefore;
int temp1 = 0;
int temp2 = 0;
// Variablen zum direkten Zugriff auf i2C Busse
byte error, address;
int nDevices;

boolean debugMode = true;
boolean handMode = false;
boolean something=true;

// internen LED
#define HBintervalTime 1000
elapsedMillis workingLED;       // Autoincrement Variable 
boolean       HBstate = true;   // interne LED Status

// Sparkfun Motorshield
#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define mot_L 0
#define mot_R 1
#define pwmFrequency 18000
int inCWpin[2]   = {PIN_mot_R_InA, PIN_mot_L_InA};
int inCCWpin[2]  = {PIN_mot_R_InB, PIN_mot_L_InB}; 
int speedpin[2]  = {PIN_mot_R_PWM, PIN_mot_L_PWM};
int loadpin[2]   = {PIN_mot_R_load, PIN_mot_L_load};
int healthpin[2] = {PIN_mot_R_health,PIN_mot_L_health};
elapsedMillis MotorTestDauer;             // Testvariable um die Bewegung auf bestimte Zeit am Anfang des Scetch zu begrnzen
typedef struct
 {
     // uint8_t Motor;    MotorNummer kommt über Platz in array
     uint8_t driveDir;
     uint8_t driveSpeed;
 }  motorSetting;
motorSetting motorSettings[2];            // zur globalen Speicherung swe Motor Speed Werte
typedef struct
 {
     int motLoad;
     int motHealth;
 }  motorStatus;
motorStatus motStatus[2];

int stdSpeed = 80;
int stdSpeed0 = stdSpeed*1.2; //1.4

 //Vars für Fahren bis Dst
int wallBreak = 100;
int dstBefore;
int stopThreshold = 280;
int breakSpeed = 15;
int breakSpeed0 = breakSpeed*1.4;
int stopEnc = 65000;
  

//Encoder
int speedGrade = stdSpeed;
int speedGrade0 = stdSpeed0;
long oldL, oldR;
long newL, newR;
int timeSpeedCalc;
long deltaL, deltaR;
int offsetSpeedCalc = 150;
boolean retL, retR;
int deltaAll;
int encDoMove = 7000;
int basicChange = stdSpeed; //middle from encUP encDown
int changeValue = 20;
int changeEnc = 2;


// Encoder
Encoder encMotR(PIN_Enc_RA, PIN_Enc_RB);
Encoder encMotL(PIN_Enc_LA, PIN_Enc_LB);
long encMotRcount = 0;
long encMotLcount = 0;

// Batteriesensor
#define BatLevelRAWmin 775    // entspricht 9,9V 775old 889new
#define BatLevelRAWmax 950    // entspricht 12,6V
#define BatReadInterval 5000  // Intervall in ms
int BatLevelRAW = 0;
int BatLevelPercent = 0;
elapsedMillis BatInterval;

// ColorSensor
Adafruit_TCS34725 colorFloor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t colorClear, colorRed, colorGreen, colorBlue;

// Front Sensor
boolean FrontPressedR = false;
boolean FrontPressedL = false;
boolean FrontPressed  = false;

// Temperatursensoren
#define temp_L 0
#define temp_R 1
#define temp_diff_Victim 3
Adafruit_MLX90614 tempSensor[2] = {Adafruit_MLX90614(Addr_Temp_L),Adafruit_MLX90614(Addr_Temp_R)};
typedef struct
 {
     float tempAmbient;
     float tempObject;
     boolean VictimFound;
 }  tempVictim;
tempVictim tempVictims[2];            // zur globalen Speicherung der Tempwerte


// Entferunungsensoren incl. SX1509 für Ansteuerung. 
SX1509 DistSelect;                              // Create an SX1509 object at i2c 2 to be used throughout
Adafruit_VL53L0X_2 DistSensor[8];
VL53L0X_RangingMeasurementData_t measure[8];
enum posDistSensor {backLeftSide, backLeftBack, frontLeftFront, frontLeftSide, backRightSide, backRightBack, frontRightFront, frontRightSide};
 
 //Array für das Einlesen einzelner Sensoren
  int s[8];

  //Offset Variable
  int ID1;
  int ID2;


// Servo Dropper
int DR_neutral = 88;    // variable to store the servo position 
int DR_Sweep = 80;
int DR_Left = 10;
int DR_Right = 170;
int DR_ServoWait = 1000;
Servo DR_servo;         // create servo object to control a servo 

// Display
LiquidCrystal_I2C lcd(Addr_LCD, 16, 2);
// Creat a set of new characters
const uint8_t charBitmap[][8] = {
   { 16, 16, 8, 4, 4, 2, 1, 0 },
   { 1, 1, 2, 4, 4, 8, 16, 16 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },
   { 0x0, 0x0, 0x0, 0x0, 0x0, 0, 0, 0 },   
};

// Orientationsensor BNO055
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 oriSensor = Adafruit_BNO055(Addr_BNO055);

// Tastatur, Batterie-, Victim-Anzeige incl. SX1509 für Ansteuerung
SX1509 keypadControl;
#define KEY_ROWS 3                          // Number of rows in the keypad matrix
#define KEY_COLS 3                          // Number of columns in the keypad matrix
unsigned int keyData = 0;
unsigned int keypad_sleepTime = 256;
byte keypad_scanTime = 2;                   // Scan time per row, in ms
byte keypad_debounceTime = 1;               // Debounce time
char keyMap[KEY_ROWS][KEY_COLS] = {         // keyMap maps row/column combinations to characters:
{ '1', '2', '3'},
{ '4', '5', '6'},
{ '7', '8', '9'},
};
// const byte SX1509_Handsteuerung = PIN_SX1509_HandControl; 
// const byte SX1509_VictimRechts = PIN_SX1509_VictimRight; 
// const byte SX1509_VictimLinks = PIN_SX1509_VictimLeft; 
const byte SX1509_Batt[4] = {PIN_SX1509_Bat025, PIN_SX1509_Bat050, PIN_SX1509_Bat075, PIN_SX1509_Bat100}; 

// Handsteuerung
#define HC_sliderCenter 512
#define HC_centerDead  30  
#define HC_correctionFactor 2
int HCstatus = 0;                                         // Umschaltung Hanssteuerung an/aus
int HCinSpeedPin[2] = {PIN_motC_L_input, PIN_motC_R_input};

//Drehen
int curX;
int finX;
int tolX1;
int tolX2;
int dMode;
int tempX;
int tol = 2;

//Orientdata
int ortX;
int ortY;
int ortZ;
