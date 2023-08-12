const byte END_DELIMITER = '>';
const int BUFFER_SIZE = 10;
// This is where all our controller data wil be stored
byte data[BUFFER_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
  while(Serial.available()) Serial.readBytesUntil(END_DELIMITER, data, BUFFER_SIZE);
}

void loop() {
  if (Serial.available() > 0) {

    // Read data until we meet the end delimiter character
    Serial.readBytesUntil(END_DELIMITER, data, BUFFER_SIZE);

    /*
    * data values are in this order:
    * A, B, X, Y, Hat, RightThumbRadius, RightThumbAngle, LeftThumbRadius, LeftThumbAngle, END_DELIMITER
    * Do whatever you want with the data
  */

    // Last value is the end delimiter
    // for (int i = 0; i < BUFFER_SIZE - 1; i++) {
    //   Serial.print(data[i]);
    //   Serial.print(", ");
    // }
    Serial.print(data[6] == 0 ? "Stopped: " : checkDirection(data[6]) ? "Right: " : "Left: ");
    Serial.print(data[5]);
    Serial.print(", ");
    Serial.print(data[8] == 0 ? "Stopped: " : data[8] <= 127 ? "Up: " : "Down: ");
    Serial.print(data[7]);
    Serial.println();
  }
}
// true for right and false for left
boolean checkDirection(byte angle) {
  const int MAX_ANGLE = 255;
  if ( (angle > 0 && angle < MAX_ANGLE/4) || (angle > 3* MAX_ANGLE/4))
    return true;
  return false;
}
