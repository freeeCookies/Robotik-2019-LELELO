
//Einlesen Analogwerte für Handsteuerung des Roboters
motorSetting getSpeed(uint8_t iMotor)
{
int iInputPWM = 0;
int iSpeed = 0; // Interne Zwischenvariable, da bei Verwendung anderer Faktoren nach der Berechnung der Wertebreich für Byte überschritten werden kann 

motorSetting iMotorSetting;

  if (iMotor < 2)
    iInputPWM = analogRead(HCinSpeedPin[iMotor]);

    if (iInputPWM < HC_sliderCenter)
      {
        iMotorSetting.driveDir = CCW;
        iSpeed = (HC_sliderCenter - iInputPWM - 1)/HC_correctionFactor;
      }
    else
      {
        iMotorSetting.driveDir = CW;
        iSpeed = (iInputPWM - HC_sliderCenter)/HC_correctionFactor;
      }

//Abfrage auf Verletzung Maxilamwerte
    if (iSpeed < HC_centerDead)
      {
        iSpeed = 0;
      }
    else if (iSpeed > 255)
      {
        iSpeed = 255;
      }

        iMotorSetting.driveSpeed = iSpeed;


    return iMotorSetting;
}


//Abfrage aller Eingänge
void getMotorSpeedAll()
{
  motorSettings[mot_L] = getSpeed(mot_L);
  motorSettings[mot_R] = getSpeed(mot_R);
}

// Ausgabe der altuellen Werte zur Motorsteuerung
void DebugPrintMotorValues()
{
  for (int i=0; i<2; i++)
    {
      pdebug.print("Motor ");
      pdebug.print(i);
      pdebug.print(" Direction:    ");
      pdebug.print(motorSettings[i].driveDir);
      pdebug.print("     Speed:    ");
      pdebug.print(motorSettings[i].driveSpeed);
      pdebug.print("\t\t");
    }
    pdebug.println("");
}

