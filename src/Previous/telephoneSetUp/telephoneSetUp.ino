// Seting up Call Line
int callLineOut = 10;
int callLineIn = 9;
//int incomingCall = 0;
int outgoingCall = 0;
int messageOut = 4;
int messageIn = 3;

void setup() {
  Serial.begin(9600);
  pinMode(callLineOut, OUTPUT);
  pinMode(callLineIn, INPUT);
}

void loop() {
  if(callLineIn){
    messageIn = Serial.read() - '0';
    messageOut = messageIn;
    outgoingCall = 1;
  }
  else{
    outgoingCall = 0;
  }

  if(outgoingCall){
    digitalWrite(callLineOut, HIGH);
    for(int i=0; i<4; i++) {
    Serial.write(((uint8_t*)&messageOut)[i]);
    }
    outgoingCall = 0;
  }
  else{
    digitalWrite(callLineIn, LOW);
  }
  
  delay(5000);
}
