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
#include <Adafruit_NeoPixel.h>


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

const int TREAD_PINS[2][3] = {{2,4,3}, {7,8,5}}; 

//indexes
const int LEFT_MOTOR = 0;
const int RIGHT_MOTOR = 1;
const int DIR_1_PIN = 0; 
const int DIR_2_PIN = 1; 
const int PWM_PIN = 2; 


const int CCW = -1;
const int CW = 1;
const int STOP = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


int leftServoVal = 1500;
int rightServoVal = 1500;
int rollServoVal = 1500;
int tiltServoVal = 1500;

int leftTreadDir;
int rightTreadDir;
int leftTreadSpeed;
int rightTreadSpeed;

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

Serial.begin(38400); 
  leftArm.attach(LEFT_ARM_PIN);
  rightArm.attach(RIGHT_ARM_PIN);
  rollServo.attach(TILT_PIN);
  tiltServo.attach(ROLL_PIN);
  
  pinMode(TREAD_PINS[LEFT_MOTOR][DIR_1_PIN],OUTPUT);
  pinMode(TREAD_PINS[LEFT_MOTOR][DIR_2_PIN],OUTPUT);
  pinMode(TREAD_PINS[RIGHT_MOTOR][DIR_1_PIN],OUTPUT);
  pinMode(TREAD_PINS[RIGHT_MOTOR][DIR_2_PIN],OUTPUT);

  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);
  digitalWrite(STBY_PIN, HIGH);
  digitalWrite(LED1_PIN, HIGH);

  leftArm.writeMicroseconds(leftServoVal);
  rightArm.writeMicroseconds(rightServoVal);
  rollServo.writeMicroseconds(rollServoVal);
  tiltServo.writeMicroseconds(tiltServoVal);

  setTreadDirection(LEFT_MOTOR, CW);
  setTreadDirection(RIGHT_MOTOR, CW);
  setTreadSpeed(LEFT_MOTOR, 0);
  setTreadSpeed(RIGHT_MOTOR, 0);

  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
    strip.setPixelColor(0, strip.Color(255, 255, 255));   //set all pixels to off
  strip.show(); // Initialize all pixels to 'off'



  
//  leftArm.attach(LEFT_ARM_PIN);
//  rightArm.attach(RIGHT_ARM_PIN);
//  rollServo.attach(TILT_PIN);
//  tiltServo.attach(ROLL_PIN);
//
//  leftArm.writeMicroseconds(1500);
//  rightArm.writeMicroseconds(1500);
//  rollServo.writeMicroseconds(1500);
//  tiltServo.writeMicroseconds(1500);
//  delay(1000);
//  
//  leftArm.writeMicroseconds(600);
//  rightArm.writeMicroseconds(2400);
//  rollServo.writeMicroseconds(1700);
//  tiltServo.writeMicroseconds(1300);
//  delay(2000);
//  
//  leftArm.writeMicroseconds(2400);
//  rightArm.writeMicroseconds(600);
//  rollServo.writeMicroseconds(1300);
//  tiltServo.writeMicroseconds(1700);
//  delay(1000);
//  leftArm.writeMicroseconds(1500);
//  rightArm.writeMicroseconds(1500);
//  rollServo.writeMicroseconds(1500);
//  tiltServo.writeMicroseconds(1500);

}

int servoSpeed = 50;
int servoMin = 600;
int servoMax = 2400;
void loop()
{


   if(command.ReadMsgs() > 0)
   {
      if((command.walkV) > 15   )
      {
        int tempLeftSpeed = map(command.walkV, 0, 128, 0, 255);
        int tempRightSpeed = map(command.walkV, 0, 128, 0, 255);

        
           if((command.walkH) > 30   )
          {
            tempLeftSpeed = 0;
            tempRightSpeed = 200;
            
        tempRightSpeed = max(0, tempRightSpeed);
        tempRightSpeed = min(255, tempRightSpeed);  
        tempLeftSpeed = max(0, tempLeftSpeed);
        tempLeftSpeed = min(255, tempLeftSpeed); 
        

        
        setTreadDirection(LEFT_MOTOR, CCW);
        setTreadSpeed(LEFT_MOTOR, tempLeftSpeed);
        setTreadDirection(RIGHT_MOTOR, CCW);
        setTreadSpeed(RIGHT_MOTOR, tempRightSpeed );

        
          }

          else if((command.walkH) < -30   )
          {
            tempRightSpeed = 0;
            tempLeftSpeed = 200;

            
        tempRightSpeed = max(0, tempRightSpeed);
        tempRightSpeed = min(255, tempRightSpeed);  
        tempLeftSpeed = max(0, tempLeftSpeed);
        tempLeftSpeed = min(255, tempLeftSpeed); 
        

        

        

          }

          else
          {

            
         tempLeftSpeed = map(command.walkV, 0, 128, 0, 255);
         tempRightSpeed = map(command.walkV, 0, 128, 0, 255);
        
            
   
          }

          
              
        setTreadDirection(LEFT_MOTOR, CCW);
        setTreadSpeed(LEFT_MOTOR, tempLeftSpeed);
        setTreadDirection(RIGHT_MOTOR, CCW);
        setTreadSpeed(RIGHT_MOTOR, tempRightSpeed );
  

        
      }
      else if((command.walkV < -15))
      {   
        int tempLeftSpeed = map(command.walkV, 0, -128, 0, 255);
        int tempRightSpeed = map(command.walkV, 0, -128, 0, 255);

        
           if((command.walkH) > 30   )
          {
            tempLeftSpeed = 0;
            tempRightSpeed = 255;
          }

          else if((command.walkH) < -30   )
          {
            tempRightSpeed = 0;
            tempLeftSpeed = 255;

          }

          
        tempRightSpeed = max(0, tempRightSpeed);
        tempRightSpeed = min(255, tempRightSpeed);  
        tempLeftSpeed = max(0, tempLeftSpeed);
        tempLeftSpeed = min(255, tempLeftSpeed); 
        

        
        setTreadDirection(LEFT_MOTOR, CW);
        setTreadSpeed(LEFT_MOTOR, tempLeftSpeed);
        setTreadDirection(RIGHT_MOTOR, CW);
        setTreadSpeed(RIGHT_MOTOR, tempRightSpeed );
        
      }
      else
      {
        if(command.walkH > 90)
        {
        
          setTreadDirection(LEFT_MOTOR, CW);
          setTreadSpeed(LEFT_MOTOR, 255);
          setTreadDirection(RIGHT_MOTOR, CCW);
          setTreadSpeed(RIGHT_MOTOR, 255 );
        }
        else if(command.walkH < -90)
        {
        
          setTreadDirection(LEFT_MOTOR, CCW);
          setTreadSpeed(LEFT_MOTOR, 255);
          setTreadDirection(RIGHT_MOTOR, CW);
          setTreadSpeed(RIGHT_MOTOR, 255 );
        }
        else
        {
        setTreadDirection(RIGHT_MOTOR, STOP);
        setTreadDirection(LEFT_MOTOR, STOP);
        }
      
      }


      

      if((command.lookV) > 25 || (command.lookV < -25) )
      {
        tiltServoVal = tiltServoVal +(map(command.lookV, -128, 128, servoSpeed, -servoSpeed));

        tiltServoVal = max(servoMin, tiltServoVal);
        tiltServoVal = min(servoMax, tiltServoVal); 
        tiltServo.writeMicroseconds(tiltServoVal);
      }




      if((command.lookH) > 20 || (command.lookH< -25) )
      {
        rollServoVal = rollServoVal -(map(command.lookH, -128, 128, -servoSpeed, servoSpeed));

        rollServoVal = max(servoMin, rollServoVal);
        rollServoVal = min(servoMax, rollServoVal); 
        rollServo.writeMicroseconds(rollServoVal);
      }

     if(command.buttons&BUT_LT)
     { 
      leftServoVal = leftServoVal - servoSpeed;
      leftServoVal = max(servoMin, leftServoVal);
      leftServoVal = min(servoMax, leftServoVal); 
      leftArm.writeMicroseconds(leftServoVal); 

     }


     if(command.buttons&BUT_RT)
     { 
      rightServoVal = rightServoVal + servoSpeed;
      rightServoVal = max(servoMin, rightServoVal);
      rightServoVal = min(servoMax, rightServoVal); 
      rightArm.writeMicroseconds(rightServoVal);

     }

     if(command.buttons&BUT_L6)
     { 
      leftServoVal = leftServoVal + servoSpeed;
      leftServoVal = max(servoMin, leftServoVal);
      leftServoVal = min(servoMax, leftServoVal);
      leftArm.writeMicroseconds(leftServoVal); 

     }


     if(command.buttons&BUT_R1)
     { 
      rightServoVal = rightServoVal - servoSpeed;
      rightServoVal = max(servoMin, rightServoVal);
      rightServoVal = min(servoMax, rightServoVal); 
      rightArm.writeMicroseconds(rightServoVal);

     }



    
   }

   
}




void setTreadDirection(int motor, int motor_direction)
{
  if(motor_direction == CCW)
  {
    digitalWrite(TREAD_PINS[motor][DIR_1_PIN], HIGH);
    digitalWrite(TREAD_PINS[motor][DIR_2_PIN], LOW);
  }
  else if(motor_direction == CW )
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

