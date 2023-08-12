const byte START_DELIMITER = '<';
const byte END_DELIMITER = '>';
const int BUFFER_SIZE = 9;
byte data[BUFFER_SIZE] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, incomingByte;

int start = 0, bufferIndex = 0;
boolean isPacketComplete = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
}

// void loop() {
//     if (Serial.available() == 9) {
    
//     data[0] =  Serial.read();
//     data[1] =  Serial.read();
//     data[2] =  Serial.read();
//     data[3] =  Serial.read();
//     data[4] =  Serial.read();
//     data[5] =  Serial.read();
//     data[6] =  Serial.read();
//     data[7] =  Serial.read();
//     data[8] =  Serial.read();

//     for (int i = 0; i < 9; i++) {
//       Serial.print(data[i]);
//       Serial.print(", ");
//     }
//     Serial.println();
//   }
// }
void loop () {
      if (Serial.available() > 0) {
        incomingByte = Serial.read();

        if (incomingByte == START_DELIMITER) {
          bufferIndex = 0;
          incomingByte = Serial.read();
          start = 1;
        }
        if (incomingByte == END_DELIMITER) {
          bufferIndex = 0;
          incomingByte = Serial.read();
          start = 0;
          for (int i = 0; i < BUFFER_SIZE; i++) {
            Serial.print(data[i]);
            Serial.print(", ");
          }
          Serial.println();
          Serial.flush();
        }
        if(start) {
          data[bufferIndex++] = incomingByte;
        }
        else Serial.println();
        if (bufferIndex >= BUFFER_SIZE) bufferIndex = 0;
      }
}