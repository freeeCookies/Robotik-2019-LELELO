void displaySensorDetails(void)
{
  sensor_t sensor;
  oriSensor.getSensor(&sensor);
  pdebug.println("------------------------------------");
  pdebug.print  ("Sensor:       "); pdebug.println(sensor.name);
  pdebug.print  ("Driver Ver:   "); pdebug.println(sensor.version);
  pdebug.print  ("Unique ID:    "); pdebug.println(sensor.sensor_id);
  pdebug.print  ("Max Value:    "); pdebug.print(sensor.max_value); pdebug.println(" xxx");
  pdebug.print  ("Min Value:    "); pdebug.print(sensor.min_value); pdebug.println(" xxx");
  pdebug.print  ("Resolution:   "); pdebug.print(sensor.resolution); pdebug.println(" xxx");
  pdebug.println("------------------------------------");
  pdebug.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
*/
/**************************************************************************/
void displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  oriSensor.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  pdebug.println("");
  pdebug.print("System Status: 0x");
  pdebug.println(system_status, HEX);
  pdebug.print("Self Test:     0x");
  pdebug.println(self_test_results, HEX);
  pdebug.print("System Error:  0x");
  pdebug.println(system_error, HEX);
  pdebug.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  oriSensor.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  //pdebug.print("\t");
  if (!system)
  {
    pdebug.print("! ");
  }

  /* Display the individual values */
  pdebug.print("Sys:");
  pdebug.print(system, DEC);
  pdebug.print(" G:");
  pdebug.print(gyro, DEC);
  pdebug.print(" A:");
  pdebug.print(accel, DEC);
  pdebug.print(" M:");
  pdebug.print(mag, DEC);
  pdebug.println("");
}

void ReadOrientData(){
    // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = oriSensor.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
  pdebug.print("X: ");
  pdebug.print(euler.x());
  pdebug.print(" Y: ");
  pdebug.print(euler.y());
  pdebug.print(" Z: ");
  pdebug.print(euler.z());
  pdebug.print("\t\t");


  /*
  // Quaternion data
  imu::Quaternion quat = oriSensor.getQuat();
  pdebug.print("qW: ");
  pdebug.print(quat.w(), 4);
  pdebug.print(" qX: ");
  pdebug.print(quat.y(), 4);
  pdebug.print(" qY: ");
  pdebug.print(quat.x(), 4);
  pdebug.print(" qZ: ");
  pdebug.print(quat.z(), 4);
  pdebug.print("\t\t");
  */

  /* Display calibration status for each sensor. */
  uint8_t system, gyro, accel, mag = 0;
  oriSensor.getCalibration(&system, &gyro, &accel, &mag);
  pdebug.print("CALIBRATION: Sys=");
  pdebug.print(system, DEC);
  pdebug.print(" Gyro=");
  pdebug.print(gyro, DEC);
  pdebug.print(" Accel=");
  pdebug.print(accel, DEC);
  pdebug.print(" Mag=");
  pdebug.println(mag, DEC);

  delay(BNO055_SAMPLERATE_DELAY_MS);
}

int getOrientX() {
  imu::Vector<3> euler = oriSensor.getVector(Adafruit_BNO055::VECTOR_EULER);
  int returnVal = euler.x();
  return returnVal;
}

