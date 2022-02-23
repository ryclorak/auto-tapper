# servo control with joystick
# plus automatic mode

#include<Servo.h>

#define joyX A0
#define joyY A1
#define SWPIN 2

Servo srv;
int sw, pos, xValue, yValue, mode;

void setup()
{
  srv.attach(3);
  Serial.begin(9600);
  pinMode(SWPIN,INPUT_PULLUP);
}

void loop()
{
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  sw = digitalRead(SWPIN);

//  Serial.print(xValue);
//  Serial.print("\t");
//  Serial.print(yValue);
//  Serial.print("\n");
  Serial.print("\nsw= ");
  Serial.print(sw);
  Serial.print("  mode:");
  Serial.print(mode);
  
  if (sw==0)
  {
    delay(250);
    mode++;
    delay(250);
  }
  
  if (mode==0) //manual control
  {
    if (xValue > 550) //pretty much a magic number from observation, will change with case design
    {
      Serial.print(" xValue>550\n");
      srv.write(pos+=5);
      Serial.print(pos);
    }
    else if (xValue < 500)
    {
      Serial.print(" xValue<500\n");
      srv.write(pos-=5);
      Serial.print(pos);
    }
  }
  else if (mode==1) //automated motion
  {
    for (pos=0; pos<=100; pos++) { srv.write(pos); }
    delay(6000);
    for (pos=100; pos>=0; pos--) { srv.write(pos); }
    delay(6000);
  }
  
  if (pos>=180) { pos=180; }
  if (pos<=0) { pos=0; }
  if (mode>1) { mode=0; }
  
//  for(pos=0;pos<=180;pos++)
//  {
//    Myservo.write(pos);
//    delay(15);
//  }
//  delay(1000);
  
//  for(pos=180;pos>=0;pos--)
//  {
//  Myservo.write(pos);
//  delay(15);
//  }
//  delay(1000);

}
