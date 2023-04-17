// Structure Serial + Call Line
int callLineOut = 10;
int callLineIn = 9;
//int incomingCall = 0;
int outgoingCall = 0;
//int messageOut[6] = {1, 1, 1, 1, 1, 1};
int messageIn[6] = {0, 0, 0, 0, 0, 0};

int A2Pi[11] = {1, 1, 1, 1, 1, 1, 23, 24, 25, 5, 1};

void setup() {
  Serial.begin(9600);
  pinMode(callLineOut, OUTPUT);
  pinMode(callLineIn, INPUT);
}

void loop() {
  if(callLineIn){                                          // Ri2A
    for (unsigned int i = 0; i < 6; i++) {                 // Read In message from Pi
    ((unsigned char *)messageIn)[i] = (byte)Serial.read();
    }              
  }

  if(outgoingCall){                                        // A2Pi
    digitalWrite(callLineOut, HIGH);                       // Call Pi
    for (unsigned int i = 0; i < sizeof(A2Pi); i++) {      // Send Pi Struct
    Serial.write(((unsigned char *)&A2Pi)[i]);
    }
    digitalWrite(callLineOut, LOW);                       // Stop Call to Pi
  }
  
  if(outgoingCall == 2){
    outgoingCall = 0;
  }
  else{
    outgoingCall += 1;
  }

  delay(5000);
}
