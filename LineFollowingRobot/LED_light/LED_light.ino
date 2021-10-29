void setup() {// Setup of each pin
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600); //used for intially finding sensor values
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}
//Find the values of each sensor
int outputValueL=0; //A1
int outputValueCL=0; //A2
int outputValueC=0; //A3
int outputValueCR=0; //A4
int outputValueR=0; //A5
//If the sensor value is above the threshold for that particular sensor, the variable below will change to 1
int OoutputValueL=0; //A1
int OoutputValueCL=0; //A2
int OoutputValueC=0; //A3
int OoutputValueCR=0; //A4
int OoutputValueR=0; //A5



void updateSensorValues(){//function to update sensor values and turns the LED's on or off
  int threshold=900;
  //reads sensor values
  outputValueL=analogRead(A1);
  outputValueCL=analogRead(A2);
  outputValueC=analogRead(A3);
  outputValueCR=analogRead(A4);
  outputValueR=analogRead(A5);

//below code tells if the sensor is on or off, and it turns the LED's on or off
  if(outputValueL>threshold){
    OoutputValueL = 1;
    digitalWrite(2,HIGH);    
  }
  if(outputValueL<threshold){
    OoutputValueL = 0;
    digitalWrite(2,LOW);    
  }

   if(outputValueCL>threshold){
    OoutputValueCL = 1;
    digitalWrite(3,HIGH);    
  }
  if(outputValueCL<threshold){
    OoutputValueCL = 0;
    digitalWrite(3,LOW);    
  }

   if(outputValueC>threshold){
    OoutputValueC = 1;
    digitalWrite(4,HIGH);    
  }
  if(outputValueC<threshold){
    OoutputValueC = 0;
    digitalWrite(4,LOW);    
  }

   if(outputValueCR>threshold){
    OoutputValueCR = 1;
    digitalWrite(5,HIGH);    
  }
  if(outputValueCR<threshold){
    OoutputValueCR = 0;
    digitalWrite(5,LOW);    
  }
   if(outputValueR>threshold){
    OoutputValueR = 1;
    digitalWrite(6,HIGH);    
  }
  if(outputValueR<threshold){
    OoutputValueR = 0;
    digitalWrite(6,LOW);    
  }
  
}


int speed = 150;
//functions to turn the motor
void turnRightMotor(){
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  int speedone = speed +20;
  analogWrite(10,speedone);
}

void turnLeftMotor(){
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  analogWrite(11,speed);
}

void turnLeftMotorFast(){
  digitalWrite(13,LOW);
  digitalWrite(12,HIGH);
  int speed2=speed+30;
  analogWrite(11,speed2);
}
void backRightMotor(){
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  int speed3 = speed +20;
  analogWrite(10,speed3);
}


void backLeftMotor(){
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  analogWrite(11,speed);
}
void goStraight(){
  turnLeftMotor();
  turnRightMotor();
}
void stop(){
   digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
}
void loop() {
  updateSensorValues(); 

  //if only center sensor is on or if the middle 3 are activated
  if((OoutputValueC==1&&OoutputValueCL==0&&OoutputValueL==0&&OoutputValueCR==0&&OoutputValueR==0)||(OoutputValueC==1&&OoutputValueCL==1&&OoutputValueCR==1)){  //straight
    goStraight();
  }
  else if(OoutputValueL==1){ //turns it left
    turnRightMotor();
    backLeftMotor();
    delay(100);
  }
    else if(OoutputValueR==1){//turns it right
    turnLeftMotor();
    backRightMotor();
    delay(100);
  }  
  else if(OoutputValueCL==1||(OoutputValueC==1&&OoutputValueCL==1)){ //turn left
    turnRightMotor();
    
}
  else if(OoutputValueCR==1||(OoutputValueC==1&&OoutputValueCR==1)){ //turn right
    turnLeftMotor();
}


  else if(OoutputValueL==0&&OoutputValueCL==0&&OoutputValueC==0&&OoutputValueCR==0&&OoutputValueR==0){//if all off, it will go backwards
  backRightMotor();
  backLeftMotor();
}
  

  delay(1);         
}
