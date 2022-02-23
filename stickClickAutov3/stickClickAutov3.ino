// servo control with joystick
// plus automatic mode

#include<Servo.h>

#define joyX A0
#define joyY A1
#define SWPIN 2

Servo srv;
int sw, pos, xValue, yValue, mode, t, period1, period2;
unsigned long time1, time2;

void setup()
{
  srv.attach(3);
  Serial.begin(9600);
  pinMode(SWPIN,INPUT_PULLUP);
  mode=0;
  time1 = time2 = millis();
  period1 = 6000;
  period2 = 5000;
}

void loop()
{
  t = millis();
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  sw = digitalRead(SWPIN);

//  Serial.print(xValue);
//  Serial.print("\t");
//  Serial.print(yValue);
//  Serial.print("\n");
  Serial.print("\nsw= ");
  Serial.print(sw);
  Serial.print("\n  mode:");
  Serial.print(mode);
  
  if (sw==0)
  {
//    t = millis()
    mode++;
//    while(millis() < t+500);  // pause to prevent accidental mode switch
  }
  
  if (mode==0) //manual control
  {
    if (xValue > 550) //pretty much a magic number from observation, will change with case design
    {
//      Serial.print(" xValue>550\n");
      srv.write(pos+=5);
//      Serial.print(pos);
    }
    else if (xValue < 500)
    {
//      Serial.print(" xValue<500\n");
      srv.write(pos-=5);
//      Serial.print(pos);
    }
  }
  else if (mode==1) //automated motion
  {
//    t = millis();
//    for (pos=0; pos<=100; pos++) { srv.write(pos); }
//    while(millis() < t+6000);
//    t = millis();
//    for (pos=100; pos>=0; pos--) { srv.write(pos); }
//    while(millis() < t+6000);

    // this will just overlap, gonna do it all differently, gotta encapsulate, simplify main
    if (millis()-time1 >= period1)
    {
      for (pos=0; pos<=100; pos++) { srv.write(pos); }
      time1 = millis();
    }
    if (millis()-time2 >= period2)
    {
      for (pos=100; pos>=0; pos--) { srv.write(pos); }
      time2 = millis();
    }
  }
  
//  if (pos>=180) { pos=180; }
//  if (pos<=0) { pos=0; }
  if (mode>1) { mode=0; } // allows for more modes
}
