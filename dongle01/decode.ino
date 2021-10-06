uint16_t press_release(uint8_t bb){
  bool released = (bb >= 0b10000000);
  if(released) bb -= 0b10000000;
  if(!released){                            //PRESS
    Serial.print("p(");Serial.print(bb, DEC);Serial.print(")  ");
    last_press[bb] = millis();
    press_action(pick_kc(top_l(), bb));
  }else{                                    //RELEASE
    uint16_t span = uint16_t(millis() - last_press[bb]);
    Serial.print("span:");Serial.println(span);    
    Serial.print("r(");Serial.print(bb, DEC);Serial.print(")  ");
    last_press[bb] = millis();
    release_action(pick_kc(top_l(), bb), span);
    release_LT(bb, span);
  }
  //Serial.println();
  return 0;
}

void press_action(uint16_t code){
  if(code <= 0xFF){
    mypress(true, code);   
  }else if(HAS_MOD(code)){                         /////////
    Serial.print(" p mod  ");
    mypress(true, mod_to_modcode(code));     
  }else if(HAS_LT(code)){                         /////////
    int8_t L = ((code)&0x0F00 )>> 8;
    Serial.print(" p LT_");Serial.println(L, DEC);
    layer16[L] = true;
  }
}
void release_action(uint16_t code, uint16_t span){
  if(code <= 0xFF){
    mypress(false, code); 
  }else if(HAS_MOD(code)){                         /////////
    Serial.print(" r  mod  ");
    mypress(false, mod_to_modcode(code));   
    if(span < 200){                         /////////
      mypress(true, PICK_CODE(code));       //TAP
      mypress(false, PICK_CODE(code));       //TAP
    } 
  }
}
void release_LT(uint8_t bb, uint16_t span){
  uint16_t code = pick_kc(0,bb);
  if(HAS_LT(code)){
    int8_t L = ((code)&0x0F00 )>> 8;
    Serial.print(" r LT_");Serial.println(L, DEC);
    layer16[L] = false;
    if(span < 200){
      mypress(true, PICK_CODE(code));       //TAP
      mypress(false, PICK_CODE(code));       //TAP
    }
  }
}

int16_t mod_to_modcode(int16_t mod){
  mod = (mod &0x0F00);
  switch(mod){
    case QK_LCTL: return k_CTL; break;
    case QK_LSFT: return k_SFT; break;
    case QK_LALT: return k_ALT; break;
    case QK_LGUI: return k_GUI; break;
  }
}
