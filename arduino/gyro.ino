#include <Wire.h>
float RateRoll, RatePitch, RateYaw;
float AccX, AccY, AccZ;
float AngleRoll, AnglePitch, AngleYaw;
float LoopTimer;
float negativeZ = 0;
float positiveZ = 0;
float negativeY = 0;
float positiveY = 0;
float thrustConstant = 1;
float X = 1;
float Y = 0;
float Z = 0;
const float radToDeg = 180.0 / PI;
float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
int RateCalibrationNumber;

void gyro_signals(void)
{
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  int16_t AccXLSB = Wire.read() << 8 | Wire.read();
  int16_t AccYLSB = Wire.read() << 8 | Wire.read();
  int16_t AccZLSB = Wire.read() << 8 | Wire.read();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 6);
  int16_t GyroX = Wire.read() << 8 | Wire.read();
  int16_t GyroY = Wire.read() << 8 | Wire.read();
  int16_t GyroZ = Wire.read() << 8 | Wire.read();
  RateRoll = (float)GyroX / 65.5;
  RatePitch = (float)GyroY / 65.5;
  RateYaw = (float)GyroZ / 65.5;
  X = (float)AccXLSB / 4096;
  Y = (float)AccYLSB / 4096;
  Z = (float)AccZLSB / 4096;
  AngleRoll = atan(Y / sqrt(X * X + Z * Z)) * 1 / (3.142 / 180);
  AnglePitch = -atan(X / sqrt(Y * Y + Z * Z)) * 1 / (3.142 / 180);
  AngleYaw = atan2(Y, X) * radToDeg;
}

void motorSpeeds(void)
{
  if (Z > 0)
  {
    positiveZ = thrustConstant * Z;
  }
  if (Z < 0)
  {
    negativeZ = thrustConstant * Z;
  }
  if (Y > 0)
  {
    positiveY = thrustConstant * Y;
  }
  if (Y < 0)
  {
    negativeY = thrustConstant * Y;
  }
}

void setup()
{
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for (RateCalibrationNumber = 0;
       RateCalibrationNumber < 2000;
       RateCalibrationNumber++)
  {
    gyro_signals();
    RateCalibrationRoll += RateRoll;
    RateCalibrationPitch += RatePitch;
    RateCalibrationYaw += RateYaw;
    delay(1);
  }
  RateCalibrationRoll /= 2000;
  RateCalibrationPitch /= 2000;
  RateCalibrationYaw /= 2000;
}
void loop()
{
  gyro_signals();
  motorSpeeds();
  RateRoll -= RateCalibrationRoll;
  RatePitch -= RateCalibrationPitch;
  RateYaw -= RateCalibrationYaw;
  Serial.print("z+: ");
  Serial.print(positiveZ);
  Serial.print(" z-: ");
  Serial.print(negativeZ);
  Serial.print(" y+: ");
  Serial.print(positiveY);
  Serial.print(" y-: ");
  Serial.print(negativeY);
  Serial.print(" Angleroll: ");
  Serial.print(AngleRoll);
  Serial.print(" Anglepitch: ");
  Serial.print(AnglePitch);
  Serial.print(" Angleyaw: ");
  Serial.println(AngleYaw);
  delay(1000);
}