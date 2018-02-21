volatile double count = 0; //set the counts of the encoder
volatile double angle = 0;//set the angles
volatile double prev_angle = 0;
volatile double curr_spd = 0;
boolean A,B;
double PWM = 6;
const int InA1 = 4;//
const int InB1 = 10;//
int encodPinA1=2;                       // encoder A pin
int encodPinB1=11;                      // encoder B pin

double setpoint = -100;//1 setting it to move through 100 degrees
double tar_spd = 0.3;
double Kp = 5;// you can set these constants however you like depending on trial & error
double Ki = 0;
double Kd = 5;
char mode='S';                                                              
int vel=-125; 

float last_error = 0;
float error = 0;
float changeError = 0;
float totalError = 0;
float pidTerm = 0;
float pidTerm_scaled = 0;// if the total gain we get is not in the PWM range we scale it down so that it's not bigger than |255|
int potpin = A0; 



void setup() {
  Serial.begin(9600);
  pinMode(encodPinA1, INPUT);//encoder pins
  pinMode(encodPinB1, INPUT);
  attachInterrupt(0,Achange,CHANGE);
  pinMode(PWM, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);


}

void loop(){
  if (mode == 'P'){
    loop_PID_POS();
  }
  else if (mode == 'S'){
    velcontrol(vel);  
  } 
  Serial.flush();
  
}
void loop_PID_POS(){
  
  PIDcalculation_POS();// find PID value
  
  if (angle > setpoint) {
    digitalWrite(InA1, LOW);// Forward motion
    digitalWrite(InB1, HIGH);
//    delay(50);
  }
    
  else {
    digitalWrite(InA1, HIGH);// Forward motion
    digitalWrite(InB1, LOW);
//    delay(5);
  }

  analogWrite(PWM, pidTerm_scaled);

//  Serial.println("WHEEL ANGLE:");
Serial.print(angle);

  delay(100);
}


void loop_PID_SPD(){
  PIDcalculation_SPD();// find PID value
  
  if (tar_spd < 0) {
    digitalWrite(InA1, LOW);// Forward motion
    digitalWrite(InB1, HIGH);
  }
    
  else {
    digitalWrite(InA1, HIGH);// Forward motion
    digitalWrite(InB1, LOW);

  }

  analogWrite(PWM, pidTerm_scaled);

//  Serial.println("speed:");
//  Serial.print(curr_spd);

  delay(100);
}

void PIDcalculation_POS()
{
  angle = (1 * count);//count to angle conversion
  error = setpoint - angle;
  
  changeError = error - last_error; // derivative term
  totalError += error; //accumalate errors to find integral term
  pidTerm = (Kp * error) + (Ki * totalError) + (Kd * changeError);//total gain
  pidTerm = constrain(pidTerm, -255, 255);//constraining to appropriate value
  pidTerm_scaled = abs(pidTerm);//make sure it's a positive value
  last_error = error;
}

void PIDcalculation_SPD()
{
  prev_angle = (1 * count);//count to angle conversion
  delay(50);
  angle = (1 * count);
  curr_spd = (angle - prev_angle)/ 50;
  error = abs(tar_spd) - abs(curr_spd);
  changeError = error - last_error; // derivative term
  totalError += error; //accumalate errors to find integral term
  pidTerm = (Kp * error) + (Ki * totalError) + (Kd * changeError);//total gain
  pidTerm = constrain(pidTerm, -255, 255);//constraining to appropriate value
  pidTerm_scaled = abs(pidTerm);//make sure it's a positive value
  last_error = error;

}
  
void Achange() //these functions are for finding the encoder counts
{
  A = digitalRead(encodPinA1);
  B = digitalRead(encodPinB1);

  if(A==B)
  {
    count++;
  }
  else
  {
    count--;
  
  }
}

void velcontrol(int vel){
  if (vel>-255 && vel<255)
 {
    if (vel>0)
    {
      motorForward(vel);
    }
    else
    {
      motorBackward(-1*vel);
      //Serial.println("printvel");
    }
  }
}
void motorForward(int PWM_val)  {
 analogWrite(PWM, PWM_val);
 digitalWrite(InA1, LOW);
 digitalWrite(InB1, HIGH);
 
}

void motorBackward(int PWM_val)  {
 analogWrite(PWM, PWM_val);
 digitalWrite(InA1, HIGH);
 digitalWrite(InB1, LOW);

}

