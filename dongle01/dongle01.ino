#include "Keyboard.h"

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
//address through which two modules communicate.
const byte address[6] = "00001";

////////////////////////////////
#include "kc.h"
#include "layout_macro.h"
#include "quantum_keycodes.h"
#define TAPPING_TERM 200;
unsigned long last_press[120];      
bool layer16[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};  

void setup()
{
  //while (!Serial);
    Serial.begin(9600);
  Serial.println("mimi");
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

  Keyboard.begin();
  //delay(2000);//
  //Keyboard.print("hello");//
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(byte(text[0]));
    press_release(byte(text[0]));
  }
}


/////////////////////////
void mypress(bool pressed, uint8_t code){
  if (pressed == 1){
    Serial.print("press; ");
    //bleKeyboard.press(code);
    Keyboard.press(code);
  }else{
    Serial.print("release; ");
    //bleKeyboard.release(code);
    Keyboard.release(code);
  }
  Serial.print(top_l());Serial.print("**"); Serial.println(code, HEX);
}
uint8_t top_l(){
  for(int i=15; i>=0; i--){
    if(layer16[i]) return i;
  }
  return 0;
}
void layer_xin16(uint8_t L){
  for(int i=15; i>=0; i--){
    layer16[i] = false;
  }
  layer16[L] = true;
}
