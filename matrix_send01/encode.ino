// col 20 x row 6

byte encode(bool p_r,int row, int col, bool lft,bool inv){
  byte res = 0b00000000;
  if(!lft){
    col += 10;
  }
  if(inv){
    col = 19 - col;
  }
  res += (row*20) + col;
  
  if(p_r){
    res += 0b00000000;
  }else{
    res += 0b10000000;
  }
  
  return res;
}
