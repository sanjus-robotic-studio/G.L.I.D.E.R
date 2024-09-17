//Receiver signal pins
double ch1_pin = 3;  // Left/Right control (ch1)
double ch2_pin = 5;  // Forward/Backward control (ch2)

// Motor driver pins
int R_EN_right = 2; 
int L_EN_right = 4;
int R_PWM_right = 6; // PWM pin for right motor
int L_PWM_right = 9; // PWM pin for right motor
int R_EN_left = 7; 
int L_EN_left = 8;
int R_PWM_left = 10; // PWM pin for left motor
int L_PWM_left = 11; // PWM pin for left motor

// Threshold values based on transmitter
int Ch2_start_Fwd = 1540;  // Forward motion start value
int Ch2_End_Fwd = 1885;    // Max forward value
int Ch2_start_Bac = 1500;  // Backward motion start value
int Ch2_End_Bac = 1220;     // Max backward value

int Ch1_Left_start = 1460;        // Left turn start value
int Ch1_Right_start = 1495;   
int Ch1_Left_end = 1105;        // Left turn start value
int Ch1_Right_end = 1895;    // Right turn start value
   // Neutral value for turning

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);  // Ch1 (Left/Right)
  pinMode(5, INPUT);  // Ch2 (Forward/Backward)
  pinMode(2, OUTPUT); // Right motor enable
  pinMode(4, OUTPUT); // Left motor enable
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT);
}

void loop() {
  // Read PWM signals from receiver
  double ch1 = pulseIn(3, HIGH); // Left/Right control (turning)
  double ch2 = pulseIn(5, HIGH); // Forward/Backward control (speed)


  Serial.print("ch1: ");
  Serial.println(ch1);

  // Speed mapping for forward/backward motion based on ch2 (Forward/Backward)
  int spdFwd = map(ch2, Ch2_start_Fwd, Ch2_End_Fwd, 0, 255);   
  int spdBac = map(ch2, Ch2_start_Bac, Ch2_End_Bac, 0, 255);    

  // Speed mapping for turning based on ch1 (Left/Right)
  int spdTurn_Right = map(ch1,  Ch1_Right_start,Ch1_Right_end, 0, 255);  // Higher value for turning right
  int spdTurn_Left = map(ch1, Ch1_Left_start, Ch1_Left_end, 0, 255);    // Higher value for turning left

  // Enable motor drivers
  digitalWrite(R_EN_right, HIGH);
  digitalWrite(L_EN_right, HIGH);
  digitalWrite(R_EN_left, HIGH);
  digitalWrite(L_EN_left, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  // If both ch1 and ch2 are neutral, stop motors
  if (ch1 == 0 && ch2 == 0) {
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, 0);
  }
  // Forward motion
  else if (ch2 > Ch2_start_Fwd) { 
    // Adjust speed based on turning input
    analogWrite(R_PWM_right, spdFwd);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, spdFwd);
    analogWrite(L_PWM_left, 0);
  }
  // Backward motion
  else if (ch2 < Ch2_start_Bac) {
    // Adjust speed based on turning input
    Serial.print("back");
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, spdBac);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, spdBac);
  }
  // Turning Right
  else if (ch1 > Ch1_Right_start) { 
    Serial.print("right");
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, spdTurn_Right);
    analogWrite(R_PWM_left, spdTurn_Right);
    analogWrite(L_PWM_left, 0);
  }
  // Turning Left
  else if (ch1 < Ch1_Left_start) {
    Serial.print("left");
    analogWrite(R_PWM_right, spdTurn_Left);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, spdTurn_Left);
  }
  else {
    analogWrite(R_PWM_right, 0);
    analogWrite(L_PWM_right, 0);
    analogWrite(R_PWM_left, 0);
    analogWrite(L_PWM_left, 0);
  }
}
