volatile double count1 = 0; //set the counts of the encoder
volatile double count2 = 0;
volatile double angle = 0;//set the angles
volatile double prev_angle = 0;
volatile double curr_spd = 0;
boolean c1, c2, last1=LOW, last2=LOW;

const int InA1 = 7;
const int InB1 = 8;
int encodPinA1=3;                       
int encodPinB1=5; 
double PWM1 = 11;

const int InA2 = 10;
const int InB2 = 12;
int encodPinA2=2;                       
int encodPinB2=4;
double PWM2 = 9;

double setpoint = -100;//1 setting it to move through 100 degrees
double tar_spd = 0.3;
double Kp = 5;//you can set these constants however you like depending on trial & error
double Ki = 0;
double Kd = 5;                                              
int vel1=-255;
int vel2=-255; 

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
  pinMode(encodPinA2, INPUT);//encoder pins
  pinMode(encodPinB2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2),change2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),change1,CHANGE);
  //attachInterrupt(0,change1,CHANGE);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
}

void loop(){  

  //Serial.print("here in loop");
  
  for (vel1=-255; vel1<256; vel1++){
    vel2control(vel2);
    delay(500);
    SPD1calculation();
  }
  //vel1control(vel1); 
  //vel2control(vel2);
  //SPD1calculation();
  //SPD2calculation();    
  //Serial.flush();
  
}

void change1() //these functions are for finding the encoder counts
{
  //Serial.print("here1");
  c1 = digitalRead(encodPinA1);
  c2 = digitalRead(encodPinB1);
 /*
  if ((last1 == LOW) && (c1 == HIGH)) {
    if (c2 == LOW) {
      count1--;
    } else {
      count1++;
    }
   Serial.print (count1);
   Serial.print ("/");
  }
  last1 = c1;

  */ 
  

  if(c1==c2)
  {
    count1++;
  }
  else
  {
    count1--;
  
  }
  
  
}

void change2() //these functions are for finding the encoder counts
{
  //Serial.print("here2");
  c1 = digitalRead(encodPinA2);
  c2 = digitalRead(encodPinB2); 
 /*
  if ((last2 == LOW) && (c1 == HIGH)) {
    if (c2 == LOW) {
      count2--;
    } else {
      count2++;
    }
    Serial.print (count2);
    Serial.print ("//");
  }
  last2 = c1;
*/
  if(c1==c2)
  {
    count2++;
  }
  else
  {
    count2--;
  
  }
  
}

void vel1control(int vel){
  
  if (vel>-256 && vel<256)
 {
    if (vel>0)
    {
      motor1Forward(vel);
    }
    else
    {
      motor1Backward(-1*vel);
      //Serial.println("printvel");
    }
  }
}

void vel2control(int vel){
  
  if (vel>-256 && vel<256)
 {
    if (vel>0)
    {
      motor2Forward(vel);
    }
    else
    {
      motor2Backward(-1*vel);
      //Serial.println("printvel");
    }
  }
}


void motor1Forward(int PWM_val)  {
 analogWrite(PWM1, PWM_val);
 digitalWrite(InA1, LOW);
 digitalWrite(InB1, HIGH);
 
}

void motor1Backward(int PWM_val)  {
 analogWrite(PWM1, PWM_val);
 digitalWrite(InA1, HIGH);
 digitalWrite(InB1, LOW);
}

void motor2Forward(int PWM_val)  {
 analogWrite(PWM2, PWM_val);
 digitalWrite(InA2, LOW);
 digitalWrite(InB2, HIGH);
 
}

void motor2Backward(int PWM_val)  {
 analogWrite(PWM2, PWM_val);
 digitalWrite(InA2, HIGH);
 digitalWrite(InB2, LOW);
}

void SPD1calculation()
{
  prev_angle = (1 * count1);//count to angle conversion
  delay(1000);
  angle = (1 * count1);
  curr_spd = (angle - prev_angle)/1000;
  //Serial.println(millis()); 
  
  Serial.print(vel2); 
  Serial.print(',');
  Serial.println(curr_spd, 6);
  
}

void SPD2calculation()
{
  prev_angle = (1 * count2);//count to angle conversion
  delay(1000);
  angle = (1 * count2);
  curr_spd = (angle - prev_angle)/1000;
  Serial.print(vel1); 
  Serial.print(',');
  Serial.println(curr_spd, 6);
}

