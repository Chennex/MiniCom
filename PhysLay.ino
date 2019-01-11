//Handles the physical layer of antenna interfacing.
int txPin;
int rxPin;
int bitCounter;

//Header length is in bytes.
const int headerLength = 3;

static volatile uint8_t rxDone = 0;

//Time that receiver will wait before considering packet lost.
int rxWaitMax = 10;
boolean txEnabled = false;
boolean rxEnabled = false;

//Six bit symbols with padding.
static uint8_t symbols[] = {0xd,  0xe,  0x13, 0x15, 0x16, 0x19, 0x1a, 0x1c, 0x23, 0x25, 0x26, 0x29, 0x2a, 0x2c, 0x32, 0x34};

void commSetup(){
  pinMode(txPin, OUTPUT);
  pinMode(rxPin, INPUT); 
}

void txStart(){
  txEnabled = true;
  
}

void txStop(){
  txEnabled = false;
}

void rxStart(){
  rxEnabled = true;
}

void rxStop(){
  rxEnabled = false;
}

byte rxWait(unsigned int milliseconds){
  unsigned long start = millis();

    while (!rxDone && ((millis() - start) < milliseconds))
  ;
    return rxDone;
}

//adds CRC, modulates and transmits a given packet. Performance might be able to be improved by integrating CRC into the modulation step.
void transmit(byte buff[], int len){
  byte index;
  byte i;
  buff[2] = crc8(buff,len);

  //encode message into symbols.
  for(i = 0; i <= len; i++){
    buff[i] = symbols[buff[i] >> 4];
    buff[i] = symbols[buff[i] & 0xf];  //Flipping bits like it's going out of fashion.
  }
  txStart();
  return true;
  
}

