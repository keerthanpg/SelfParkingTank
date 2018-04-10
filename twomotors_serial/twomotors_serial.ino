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
  String Xcord;
  String Ycord;
  int flag=1;
  
  String readString;
  
  while (Serial.available()){
    //delay(30);
    flag=0;
    if (Serial.available() >0){
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }
  } 
  
  
  for(int i=0;i<3;i++){
    Xcord+=readString[i];
  }
  for(int i=3;i<6;i++){
    Ycord+=readString[i];
  }   
  
  vel1=Xcord.toInt();
  vel2=Ycord.toInt(); 
  
  if (flag){
    vel1=255;
    vel2=255;
  }
  
  vel1=vel1-255;
  vel2=vel2-255;
  //Serial.print("Arduino received: ");
  Serial.print(vel1);
  Serial.print(vel2);
  Serial.print("\0");
  
  
  vel2control(vel2); 
  vel2control(vel2);
  SPD1calculation();
  SPD2calculation();    
  //Serial.flush();
  Serial.flush();
  
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

