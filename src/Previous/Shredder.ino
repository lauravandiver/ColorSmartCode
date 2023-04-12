int pwm_value = 0;
const int dir = 4;          // Digital pin for direction of motor
const int pwm = 3;          // Variable for the pwm signal

void setup() {
  Serial.begin(9600);

// Initiallize pin modes for the output to the motor driver
  pinMode(dir,OUTPUT);
  pinMode(pwm,OUTPUT);

}

void loop() {
    // put your setup code here, to run once:
  static unsigned long runTime = 0;
  static unsigned long currentTime = 0;
  static unsigned long forwardTime = 2000;
  static unsigned long reverseTime = 7000;
  static unsigned long neutralTime = 1000;

  static int max_speed = 175;

  static int direction = 1;
  currentTime = millis();
  if (direction == 1) {
      Serial.println("Forward");

      digitalWrite(dir,HIGH);
      
      if (pwm_value < max_speed) {
        pwm_value = pwm_value +5;
      }
      analogWrite(pwm,pwm_value);

      // Run shredder motor FORWARD at full speed.
      if (currentTime - runTime >= forwardTime) {
        runTime = currentTime;
        direction = -1;
      }                    // Send stop command to the motor.
      

  }else if (direction == -1) {
      Serial.println("Neutral");
      
      if (pwm_value > 0) {
        pwm_value = pwm_value - 5;                // Run at full speed
      }

      analogWrite(pwm,pwm_value);     // Set PWM value

      if (currentTime - runTime >= neutralTime) {
        if (digitalRead(dir) == HIGH) {
          direction = 0;
        }else if (digitalRead(dir) == LOW) {
          direction = 1;
        }
        Serial.println(direction);
        //direction = 1;
        runTime = currentTime;
        //Serial.print('n');
      }
      
    }else if (direction == 0) {
      //Begin reverse direction
      Serial.println("Reverse");

      digitalWrite(dir,LOW);    // Set direction to reverse
      
      if (pwm_value < max_speed) {
        pwm_value = pwm_value +5;
      }
                      // Run at full speed
      analogWrite(pwm,pwm_value);     // Set PWM value

      if (currentTime - runTime >= reverseTime) {
        runTime = currentTime;
        direction = -1;
      }                    // Send stop command to the motor.
      //direction = 1;
    }
  Serial.println(pwm_value);
}


