//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9,10);  // CE, CSN
//address through which two modules communicate.
const byte address[6] = "00001";


//////////////////////////////////////
#define left_keybord true //set false if right
#define invert_col false //set true to invert columns

const int colNum = 10;
const int rowNum = 4;
const int colPin[colNum] = { 19,18,17,16,15, 4,3,2,1,0 };
const int rowPin[rowNum] = { 8,7,6,5};
bool currentState[rowNum][colNum];
bool beforeState[rowNum][colNum];
int i,j;


void setup()
{
  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  //Set module as transmitter
  radio.stopListening();

  ///////////////////////////////////
  for( i = 0; i < rowNum; i++){pinMode(rowPin[i],OUTPUT);}
  for( i = 0; i < colNum; i++){pinMode(colPin[i],INPUT_PULLUP);}
  for( i = 0; i < rowNum; i++){
    for( j = 0; j < colNum; j++){
      currentState[i][j] = HIGH;
      beforeState[i][j] = HIGH;
    }
    digitalWrite(rowPin[i], HIGH);
  }
}


void loop()
{
  //Send message to receiver
  //const char text[] = "Hello World";
  //radio.write(&text, sizeof(text));
  /*for(byte i = 96; i<107; i++){
    //buint8_t b = 'm';
    radio.write(&i, sizeof(i));
    delay(1);
  }*/
  
  for( i = 0; i < rowNum; i++){
    digitalWrite( rowPin[i], LOW );
    for( j = 0; j < colNum; j++){
      currentState[i][j] = digitalRead(colPin[j]);
      if ( currentState[i][j] != beforeState[i][j] ){
        /*Serial.print("key(");
        Serial.print(i);
        Serial.print(",");
        Serial.print(j);
        Serial.println(")");*/

        bool press_release = currentState[i][j];
        byte code = encode(
          !press_release, i, j,
          left_keybord,invert_col);
        //Serial.print("code: ");
        //Serial.println(code);
        ////////////Serial.write('b');
        //Serial.write(code);
        radio.write(&code, sizeof(code));
        
      beforeState[i][j] = currentState[i][j];
      //delay(20);
      }
    }
    digitalWrite( rowPin[i], HIGH );
  }
}
