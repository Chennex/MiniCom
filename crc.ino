//CRC functionality. Bit of homebrew, probably not the best regarding uniqueness.

byte crc8(byte data[], int i){
  byte crc = 0xff;
  for(int x = 0; x <= i; x++){
    crc = data[x] xor crc;
  }
  return crc xor 0xff;
}

