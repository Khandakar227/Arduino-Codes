#define leftSideForward 5
#define leftSideBackward 4
#define rightSideForward 8
#define rightSideBackward 7

#define enA 10
#define enB 11

const byte END_DELIMITER = '>';
const int BUFFER_SIZE = 10;
int speed = 0;
// This is where all our controller data wil be stored
byte data[BUFFER_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

unsigned long timer0 = 2000;  //Stores the time (in millis since execution started)
unsigned long timer1 = 0;     //Stores the time when the last sensor reading was sent to the phone
unsigned long timer2 = 0;     //Stores the time when the last command was received from the phone


void setup() {
  Serial.begin(9600);
  // Motor pins
  pinMode(leftSideForward, OUTPUT);
  pinMode(leftSideBackward, OUTPUT);
  pinMode(rightSideForward, OUTPUT);
  pinMode(rightSideBackward, OUTPUT);
  //Motor speed control pins
  pinMode(enA, OUTPUT);
  pinMode(enA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    timer2 = millis();  //Store the time when last command was received
    Serial.readBytesUntil(END_DELIMITER, data, BUFFER_SIZE);
    
  /*
    * data values are in this order:
    * A, B, X, Y, Hat, RightThumbRadius, RightThumbAngle, LeftThumbRadius, LeftThumbAngle, END_DELIMITER
  */

   if (data[8] != 0 && data[8] <= 127) {
     if (data[6] != 0 && checkDirection(data[6])) forwardRight();
     else if (data[6] != 0 && !checkDirection(data[6])) forwardLeft();
     else forward();
   }
   else if (data[8] > 127) {
     if (data[6] != 0 && checkDirection(data[6])) backwardRight();
     else if (data[6] != 0 && !checkDirection(data[6])) backwardLeft();
     else backward();
   }
   else if (data[6] != 0 && checkDirection(data[6])) hardRight();
   else if (data[6] != 0 && !checkDirection(data[6])) hardLeft();
   else stop();
  
   if (data[5] != 0) speed = data[5];
   else speed = data[7];
   
   analogWrite(enA, speed);
   analogWrite(enB, speed);
  } else {
    timer0 = millis();  //Get the current time (millis since execution started)
    if ((timer0 - timer2) > 500) {  //Check if it has been 400ms since we received last command
      //More tan 400ms have passed since last command received, car is out of range. Therefore
      //Stop the car and turn lights off
      stop();
    }
  }
}
// true for right and false for left
boolean checkDirection(byte angle) {
  const int MAX_ANGLE = 255;
  if ( (angle > 0 && angle < MAX_ANGLE/4) || (angle > 3* MAX_ANGLE/4))
    return true;
  
  return false;
}

void forwardLeft() {
  digitalWrite(rightSideForward, HIGH);
  digitalWrite(rightSideBackward, LOW);
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(leftSideForward, LOW);
}
void forwardRight() {
  digitalWrite(leftSideForward, HIGH);
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, LOW);
}
void backwardLeft() {
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, HIGH);
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(leftSideForward, LOW);
}
void backwardRight() {
  digitalWrite(leftSideForward, LOW);
  digitalWrite(leftSideBackward, HIGH);
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, LOW);
}
void forward() {
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(leftSideForward, HIGH);
  digitalWrite(rightSideForward, HIGH);
  digitalWrite(rightSideBackward, LOW);
}
void backward() {
  digitalWrite(leftSideBackward, HIGH);
  digitalWrite(leftSideForward, LOW);
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, HIGH);
}
void hardLeft() {
  digitalWrite(rightSideForward, HIGH);
  digitalWrite(rightSideBackward, LOW);
  digitalWrite(leftSideBackward, HIGH);
  digitalWrite(leftSideForward, LOW);
}
void hardRight() {
  digitalWrite(leftSideForward, HIGH);
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, HIGH);
}
void stop() {
  digitalWrite(leftSideForward, LOW);
  digitalWrite(leftSideBackward, LOW);
  digitalWrite(rightSideForward, LOW);
  digitalWrite(rightSideBackward, LOW);
}