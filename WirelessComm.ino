//Arduino wireless access point. Inspired by, but not based on IEEE 802.11 technology. Designed for the purposes of experimenting with CSMA/CA.
//Packet Structure:
//0 target address (256 possible addresses)
//1 source address
//2 is CRC
//3 - 255 is payload.
//ACK and NACK are in payload as lone data in packet.
boolean isReceiving;
byte myAddress = 1;
void setup() {
  Serial.begin(9600);

}

void loop() {


}

void serialEvent() {
  byte buff[255];
  int i = 0;
  while (Serial.available()) {
    isReceiving = true;
    byte in = (byte) Serial.read();
    buff[i] = in;
    i++;

    if (in == '\n') { //23 in ascii table = end of transmission block. Used as packet terminator.
      handlePacket(buff, i);
      i = 0;
    }
  }
  isReceiving = false;
}

//Handles a test case. Returning serial input as string. i is the amount of bytes that are to be considered valid data.
void handlePacket(byte packet[], int i) {
  if (checkValidity(packet, i)) {
    String out;
    char temp;
    for (int x = 0; x <= i; x++) {
      temp = (char) packet[i];
      out += temp;
    }
//    transmit(out);
  }

}

//Handles carrier sense multiple access w/ collission avoidance.
//The basic principle is to not send while receiving (pretty easy since there is no multitasking)
//Second part means that a random amount of time (the SIF) needs to pass before attempting to send.
//Even then, thread safety implemented.
void CSMACA() {
  long sif = random(100);
}

void ack() {
  //transmit(6); //6 = ACK on ascii table.
}

void nack() {
  //transmit(21); //21 = ASCII NACK
}

boolean checkValidity(byte packet[], int i) {
  //if the data in the packet is less than 18, header is incomplete.
  //if Address does not match the device, packet is meant for someone else.
  if (i < 18 || packet[0] == myAddress) {
    return false;
  }
  //Do the CRC.

  return true;

}
void transmit(byte destination, byte payload[]) {
  byte packet[255];
  packet[0] = destination;
  //Count of x and i are offset, thus two variables.
  int x = 0;
  for (int i = 3; i <= sizeof(payload) || i == 252; i++) {
    packet[i] = payload[x];
    x++;
  }
}

