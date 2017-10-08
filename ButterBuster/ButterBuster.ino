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
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//a0 14
//a1 15
//a216
//a3 17
SoftwareSerial mySoftwareSerial(16, 17); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


Servo leftWheel, rightWheel;
Servo rollServo, tiltServo;
Servo leftArm, rightArm;

Commander command = Commander();  //start commander object



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

int ledState;
int tiltServoSpeed = 50;

int servoSpeed = 100;
int servoMin = 600;
int servoMax = 2400;



int tiltServoMin = 600;
int tiltServoMax = 2300;
//int tiltServoMin = 600;
//int tiltServoMax = 1600;


int rollServoMin = 1200;
int rollServoMax = 1800;


int roboDir = STOP;

int lastCommand;
bool taunt = false; 
bool escape = false; 
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

  mySoftwareSerial.begin(9600);
  
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


  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.


  }

  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3


  
  rainbow(5);


  
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


void loop()
{


   if(command.ReadMsgs() > 0)
   {
      if((command.walkV) > 15   )
      {
        if(roboDir != CW)
        {
          strip.setPixelColor(0, strip.Color(0, 255, 0));   //set all pixels to off
          strip.show(); // Initialize all pixels to 'off'
          roboDir = CW;
        }

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
        
        if(roboDir != CCW)
        {
          strip.setPixelColor(0, strip.Color(0, 0, 255));   //set all pixels to off
          strip.show(); // Initialize all pixels to 'off'
          roboDir = CCW;
        }


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
        
        if(roboDir != CW)
        {
          strip.setPixelColor(0, strip.Color(0, 255, 0));   //set all pixels to off
          strip.show(); // Initialize all pixels to 'off'
          roboDir = CW;
        }

          setTreadDirection(LEFT_MOTOR, CW);
          setTreadSpeed(LEFT_MOTOR, 255);
          setTreadDirection(RIGHT_MOTOR, CCW);
          setTreadSpeed(RIGHT_MOTOR, 255 );
        }
        else if(command.walkH < -90)
        {
            
            if(roboDir != CCW)
            {
              strip.setPixelColor(0, strip.Color(0, 0, 255));   //set all pixels to off
              strip.show(); // Initialize all pixels to 'off'
              roboDir = CCW;
            }

          setTreadDirection(LEFT_MOTOR, CCW);
          setTreadSpeed(LEFT_MOTOR, 255);
          setTreadDirection(RIGHT_MOTOR, CW);
          setTreadSpeed(RIGHT_MOTOR, 255 );
        }
        else
        {
          
        if(roboDir != STOP)
        {
          strip.setPixelColor(0, strip.Color(255, 0, 0));   //set all pixels to off
          strip.show(); // Initialize all pixels to 'off'
          roboDir = STOP;
        }


          setTreadDirection(RIGHT_MOTOR, STOP);
          setTreadDirection(LEFT_MOTOR, STOP);
        }
      
      }


      

      if((command.lookV) > 25 || (command.lookV < -25) )
      {
        tiltServoVal = tiltServoVal +(map(command.lookV, -128, 128, tiltServoSpeed, -tiltServoSpeed));

        tiltServoVal = max(tiltServoMin, tiltServoVal);
        tiltServoVal = min(tiltServoMax, tiltServoVal); 
        tiltServo.writeMicroseconds(tiltServoVal);
      }




      if((command.lookH) > 20 || (command.lookH< -25) )
      {
        rollServoVal = rollServoVal -(map(command.lookH, -128, 128, -servoSpeed, servoSpeed));

        rollServoVal = max(rollServoMin, rollServoVal);
        rollServoVal = min(rollServoMax, rollServoVal); 
        rollServo.writeMicroseconds(rollServoVal);
      }






     if((command.buttons&BUT_LT) && (command.buttons&BUT_L6))
     { 
      
        myDFPlayer.next();  //Play next mp3 every 3 second.
     }


     if((command.buttons&BUT_RT) && (command.buttons&BUT_R1))
     { 
      
        myDFPlayer.previous();  //Play next mp3 every 3 second.
     }


     
     if(command.buttons&BUT_LT)
     { 
      leftServoVal = leftServoVal - servoSpeed;
      leftServoVal = max(servoMin, leftServoVal);
      leftServoVal = min(servoMax, leftServoVal); 
      leftArm.writeMicroseconds(leftServoVal); 
      ledState = !ledState;
      digitalWrite(LED1_PIN, ledState);
      taunt = false;
      escape = false;

     }


     if(command.buttons&BUT_RT)
     { 
      rightServoVal = rightServoVal + servoSpeed;
      rightServoVal = max(servoMin, rightServoVal);
      rightServoVal = min(servoMax, rightServoVal); 
      rightArm.writeMicroseconds(rightServoVal);
      ledState = !ledState;
      digitalWrite(LED1_PIN, ledState);
      taunt = false;
      escape = false;

     }

     if(command.buttons&BUT_L6)
     { 
      leftServoVal = leftServoVal + servoSpeed;
      leftServoVal = max(servoMin, leftServoVal);
      leftServoVal = min(servoMax, leftServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      ledState = !ledState;
      digitalWrite(LED1_PIN, ledState);

     }


     if(command.buttons&BUT_R1)
     { 
      rightServoVal = rightServoVal - servoSpeed;
      rightServoVal = max(servoMin, rightServoVal);
      rightServoVal = min(servoMax, rightServoVal); 
      rightArm.writeMicroseconds(rightServoVal);
      ledState = !ledState;
      digitalWrite(LED1_PIN, ledState);

     }





     

     if(command.buttons&BUT_R2)
     { 
      leftServoVal = servoMax;
      rightServoVal = servoMin;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      

     }
     if(command.buttons&BUT_R3 && (escape == false))
     { 

        rollServoVal = 1500;
        leftServoVal = servoMin;
        rightServoVal = servoMax;
        tiltServoVal = tiltServoMax;
      
      //back and prop up
      tiltServo.writeMicroseconds(tiltServoVal); 
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      rollServo.writeMicroseconds(rollServoVal); 
      delay(500);

        rollServoVal = 1100;
        leftServoVal = servoMax;
      

      //rol side setup arm      
      leftArm.writeMicroseconds(leftServoVal); 
      rollServo.writeMicroseconds(rollServoVal); 
      delay(500);


      for(int i = tiltServoMax; i > 1500; i--)
      {
          tiltServoVal = i;
          tiltServo.writeMicroseconds(tiltServoVal); 
          delay(3);
      }

        
        tiltServoVal = 1500;
        rightServoVal = servoMin;
        
        rightArm.writeMicroseconds(rightServoVal);
        
        rollServoVal = 1500;

         rollServo.writeMicroseconds(rollServoVal); 
        
//      leftServoVal = 1500;
//      rightServoVal = 1500;
//      rightArm.writeMicroseconds(rightServoVal);
//      leftArm.writeMicroseconds(leftServoVal); 


      escape = true;
     }
     if((command.buttons&BUT_L4 ) && (taunt == false))
     { 

      
      tiltServoVal = 1500;
      rollServoVal = 1500;
      tiltServo.writeMicroseconds(tiltServoVal);
      rollServo.writeMicroseconds(rollServoVal); 

      
    
      leftServoVal = 1500;
      rightServoVal = 1500;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      delay(250);     
      leftServoVal = 2000;
      rightServoVal = 2000;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      delay(250);
      leftServoVal = 1000;
      rightServoVal = 1000;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      delay(250);
    
      leftServoVal = 1500;
      rightServoVal = 1500;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 
      delay(250);   

      
      
      rollServoVal = 1700;
      rollServo.writeMicroseconds(rollServoVal); 
      delay(400);   
      rollServoVal = 1300;
      rollServo.writeMicroseconds(rollServoVal); 
      delay(400);   
      rollServoVal = 1500;
      rollServo.writeMicroseconds(rollServoVal); 
      delay(450);   
      
      
      tiltServoVal = 1400;
      tiltServo.writeMicroseconds(tiltServoVal); 
      delay(100);   
      rollServoVal = 1600;
      tiltServo.writeMicroseconds(tiltServoVal); 
      delay(100);   
      tiltServoVal = 1500;
      tiltServo.writeMicroseconds(tiltServoVal); 
      //delay(250);   
      

      taunt = true;
     }
     else 
     {
      //taunt = false;
     }
     if(command.buttons&BUT_L5)
     { 
    
      leftServoVal = servoMin;
      rightServoVal = servoMax;
      rightArm.writeMicroseconds(rightServoVal);
      leftArm.writeMicroseconds(leftServoVal); 


     }


     lastCommand = command.buttons;
    
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





void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}





