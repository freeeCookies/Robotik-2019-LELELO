// Ziel Debugausgabe Serial
//#define pdebug Serial
#define pdebug Serial


// internen LED
#define PIN_LED_internal        13    // Digital OUTPUT

// Sparkfun Motorshield
#define PIN_mot_R_load          22    // analog Input
#define PIN_mot_L_load          23    // analog Input
#define PIN_mot_R_InB           25    // Digital OUTPUT
#define PIN_mot_R_InA           26    // Digital OUTPUT
#define PIN_mot_L_InB           27    // Digital OUTPUT
#define PIN_mot_L_InA           28    // Digital OUTPUT
#define PIN_mot_R_PWM           29    // PWM (FTM2)
#define PIN_mot_L_PWM           30    // PWM (FTM2)
#define PIN_mot_R_health        31    // Digital INPUT_PULLUP
#define PIN_mot_L_health        32    // Digital INPUT_PULLUP

// Encoder Inputs
#define PIN_Enc_RA              14
#define PIN_Enc_RB              15
#define PIN_Enc_LA              16  
#define PIN_Enc_LB              17

// Batteriesensor
#define PIN_Bat_level           39    // analog Input (9V = 2.21V, 9.9V = 2.43V, 11.1V = 2.72V, 12.6V = 3.05V, 13.47V = 3.3V)

//Farbsensor
#define PIN_Color_LED           11
#define PIN_Color_Int           12

// Fronttaster
#define PIN_Front_R             33
#define PIN_Front_L             34
#define PIN_Front               33   // HW Oder sSchaltung der beiden Pins ist möglich, 33 und 34 sind dann kurzgeschlossen

// Temperatursensoren
#define Addr_Temp_L             0x5B  
#define Addr_Temp_R             0x5C
#define PIN_temp_SCL            37
#define PIN_temp_SDA            38

// Enterferunungsensoren incl. SX1509 für Ansteuerung
#define Addr_SX1509_dist        0x3F
#define i2cBus_SX1509_dist      2
#define PIN_DistSelectInt       2   
#define Addr_VL53L0X_default    0x29
#define Addr_VL53L0X_start      0x30

// Servo Dropper
#define PIN_DR_servo            35

// Display
#define Addr_LCD                0x27

// Orientationsensor BNO055
#define Addr_BNO055             0x28
#define PIN_Orient_Int          5

// Tastatur, Batterie-, Victim-Anzeige incl. SX1509 für Ansteuerung
#define Addr_SX1509_keypad      0x3E
#define i2cBus_SX1509_keypad    0
#define PIN_SX1509_Int_T        6
#define PIN_SX1509_HandControl  4
#define PIN_SX1509_VictimRight  3
#define PIN_SX1509_VictimLeft   15
#define PIN_SX1509_Bat025       11
#define PIN_SX1509_Bat050       12
#define PIN_SX1509_Bat075       13
#define PIN_SX1509_Bat100       14

// Handsteuerung
#define PIN_motC_R_input        21        // gelb
#define PIN_motC_L_input        20        // weiß
