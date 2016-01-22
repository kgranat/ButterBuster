/**********************************************
 * Butter Buster
 *  Robot Riot January 2016 Entry
 *  
 *  Kyle Granat
 *  Wade Filewich
 *  
 *
 *  Motor Pins
 *  AIN1 - 2
 *  AIN2 - 4
 *  APWM - 3
 *  BIN1 - 7
 *  BIN2 - 8
 *  BPWM - 5
 *  VM  - Battery
 *  VCC - 5v
 *  GND - Ground
 *  A01 - Left Motor +
 *  A02 - Left Motor -
 *  B01 - Right Motor +
 *  B02 - Right Motor -
 *  STBY - Analog 0 (14)
 *  
 *  
 *  Left Arm - 9
 *  Right Arm  - 10 
 *  Roll Servo - 11
 *  Tilt Servo - 12
 *  
 *  Led1 - 13 (Blink)
 *  LEd2 - 6 (PWM)
 *  NeoPixel - Analog 1 (15)
 *  
 *  FTDI Connector to XBEe
 *
 *****************/

#include <SoftwareSerial.h>
#include <Servo.h>
#include <Commander.h>

Servo leftWheel, rightWheel;
Servo rollServo, tiltServo;
Servo leftArm, rightArm;

Commander command = Commander();  //start commander object

SoftwareSerial mp3(2, 3);//software serial 


const int LEFT_ARM_PIN = 9;
const int RIGHT_ARM_PIN = 10;
const int TILT_PIN = 11;
const int ROLL_PIN = 12;

const int LED2_PIN = 6;
const int LED1_PIN = 13;
const int STBY_PIN = 14;
const int NEOPIXEL_PIN = 15;

const int TREAD_PINS[2][3] = {{4,7,3}, {8,12,5}}; 

//indexes
const int LEFT_MOTOR = 0;
const int RIGHT_MOTOR = 1;
const int DIR_1_PIN = 0; 
const int DIR_2_PIN = 1; 
const int PWM_PIN = 2; 


const int CCW = -1;
const int CW = 1;
const int STOP = 0;

void setup()
{
//   mp3.begin(9600);
//   Serial.begin(9600);
//   copy();
//   SetPlayMode(0x03);
//   SetVolume(0x10);
//   PauseOnOffCurrentMusic();
//   SetMusicPlay(0,1);
//   next();


  
  pinMode(TREAD_PINS[LEFT_MOTOR][DIR_1_PIN],OUTPUT);
  pinMode(TREAD_PINS[LEFT_MOTOR][DIR_2_PIN],OUTPUT);
  pinMode(TREAD_PINS[RIGHT_MOTOR][DIR_1_PIN],OUTPUT);
  pinMode(TREAD_PINS[RIGHT_MOTOR][DIR_2_PIN],OUTPUT);

  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);
  
  leftArm.attach(LEFT_ARM_PIN);
  rightArm.attach(RIGHT_ARM_PIN);
  rollServo.attach(TILT_PIN);
  tiltServo.attach(ROLL_PIN);

  leftArm.writeMicroseconds(1500);
  rightArm.writeMicroseconds(1500);
  rollServo.writeMicroseconds(1500);
  tiltServo.writeMicroseconds(1500);

  setTreadDirection(LEFT_MOTOR, CW);
  setTreadDirection(RIGHT_MOTOR, CW);
  setTreadSpeed(LEFT_MOTOR, 128);
  setTreadSpeed(RIGHT_MOTOR, 128);
  
}

void loop()
{
  
}




void setTreadDirection(int motor, int motor_direction)
{
  if(motor_direction = CCW)
  {
    digitalWrite(TREAD_PINS[motor][DIR_1_PIN], HIGH);
    digitalWrite(TREAD_PINS[motor][DIR_2_PIN], LOW);
  }
  else if(motor_direction = CW )
  {
    digitalWrite(TREAD_PINS[motor][DIR_1_PIN], LOW);
    digitalWrite(TREAD_PINS[motor][DIR_2_PIN], HIGH);
  }
  else
  {
    digitalWrite(TREAD_PINS[motor][DIR_1_PIN], LOW);
    digitalWrite(TREAD_PINS[motor][DIR_2_PIN], LOW); 
  }

}

void setTreadSpeed(int motor, int motorSpeed)
{
  analogWrite(TREAD_PINS[motor][PWM_PIN], motorSpeed);
}







//                                                 /$$                                /$$$$$$                                      /$$           /$$                 /$$                                                /$$$$$$                                 /$$     /$$                              
//                                                | $$                               /$$__  $$                                    |__/          | $$                | $$                                               /$$__  $$                               | $$    |__/                              
//    /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$       /$$$$$$/$$$$   /$$$$$$ |__/  \ $$        /$$$$$$$  /$$$$$$   /$$$$$$  /$$  /$$$$$$ | $$        /$$$$$$ | $$  /$$$$$$  /$$   /$$  /$$$$$$   /$$$$$$       | $$  \__//$$   /$$ /$$$$$$$   /$$$$$$$ /$$$$$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$$
//   /$$_____/ /$$__  $$ /$$__  $$ /$$__  $$ /$$__  $$      | $$_  $$_  $$ /$$__  $$   /$$$$$/       /$$_____/ /$$__  $$ /$$__  $$| $$ |____  $$| $$       /$$__  $$| $$ |____  $$| $$  | $$ /$$__  $$ /$$__  $$      | $$$$   | $$  | $$| $$__  $$ /$$_____/|_  $$_/  | $$ /$$__  $$| $$__  $$ /$$_____/
//  |  $$$$$$ | $$$$$$$$| $$$$$$$$| $$$$$$$$| $$  | $$      | $$ \ $$ \ $$| $$  \ $$  |___  $$      |  $$$$$$ | $$$$$$$$| $$  \__/| $$  /$$$$$$$| $$      | $$  \ $$| $$  /$$$$$$$| $$  | $$| $$$$$$$$| $$  \__/      | $$_/   | $$  | $$| $$  \ $$| $$        | $$    | $$| $$  \ $$| $$  \ $$|  $$$$$$ 
//   \____  $$| $$_____/| $$_____/| $$_____/| $$  | $$      | $$ | $$ | $$| $$  | $$ /$$  \ $$       \____  $$| $$_____/| $$      | $$ /$$__  $$| $$      | $$  | $$| $$ /$$__  $$| $$  | $$| $$_____/| $$            | $$     | $$  | $$| $$  | $$| $$        | $$ /$$| $$| $$  | $$| $$  | $$ \____  $$
//   /$$$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$$      | $$ | $$ | $$| $$$$$$$/|  $$$$$$/       /$$$$$$$/|  $$$$$$$| $$      | $$|  $$$$$$$| $$      | $$$$$$$/| $$|  $$$$$$$|  $$$$$$$|  $$$$$$$| $$            | $$     |  $$$$$$/| $$  | $$|  $$$$$$$  |  $$$$/| $$|  $$$$$$/| $$  | $$ /$$$$$$$/
//  |_______/  \_______/ \_______/ \_______/ \_______/      |__/ |__/ |__/| $$____/  \______/       |_______/  \_______/|__/      |__/ \_______/|__/      | $$____/ |__/ \_______/ \____  $$ \_______/|__/            |__/      \______/ |__/  |__/ \_______/   \___/  |__/ \______/ |__/  |__/|_______/ 
//                                                                        | $$                                                                            | $$                     /$$  | $$                                                                                                             
//                                                                        | $$                                                                            | $$                    |  $$$$$$/                                                                                                             
//                                                                        |__/                                                                            |__/                     \______/                                                                                                              
//Set the music index to play, the index is decided by the input sequence
//of the music;
//hbyte: the high byte of the index;
//lbyte: the low byte of the index;
boolean SetMusicPlay(uint8_t hbyte,uint8_t lbyte)
{
    mp3.write(0x7E);
    mp3.write(0x04);
    mp3.write(0xA0);
    mp3.write(hbyte);
    mp3.write(lbyte);
    mp3.write(0x7E);
    delay(10);
    while(mp3.available())
    {
        if (0xA0==mp3.read())
        return true;
        else
        return false;
    }
}
// Pause on/off  the current music
boolean PauseOnOffCurrentMusic(void)
{
    mp3.write(0x7E);
    mp3.write(0x02);
    mp3.write(0xA3);
    mp3.write(0x7E);
    delay(10);
    while(mp3.available())
    {
        if (0xA3==mp3.read())
        return true;
        else
        return false;
    }
}
 
//Set the volume, the range is 0x00 to 0x1F
boolean SetVolume(uint8_t volume)
{
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0xA7);
    mp3.write(volume);
    mp3.write(0x7E);
    delay(10);
    while(mp3.available())
    {
        if (0xA7==mp3.read())
        return true;
        else
        return false;
    }
}
 
boolean SetPlayMode(uint8_t playmode)
{
    if (((playmode==0x00)|(playmode==0x01)|(playmode==0x02)|(playmode==0x03))==false)
    {
        Serial.println("PlayMode Parameter Error! ");
        return false;
    }
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0xA9);
    mp3.write(playmode);
    mp3.write(0x7E);
    delay(10);
    while(mp3.available())
    {
        if (0xA9==mp3.read())
        return true;
        else
        return false;
    }
 }

 void next()
 {
    mp3.write(0x7E);
    mp3.write(0x02);
    mp3.write(0xA5);
    mp3.write(0x7E);
    delay(10);



 
 }

 void copy()
 {
    mp3.write(0x7E);
    mp3.write(0x03);
    mp3.write(0xAA);
    mp3.write(byte(0));
    mp3.write(0x7E);
    delay(10);

    while(mp3.available())
    {
        Serial.println(mp3.read());
    }


 
 }

