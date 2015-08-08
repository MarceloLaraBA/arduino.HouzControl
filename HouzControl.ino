#include <Arduino.h>
#include <..\libraries\LightOut\LightOut.h>
#include <..\libraries\HouzEnviroment\HouzEnviroment.h>
#include <..\libraries\IRLib\IRLib.h>


//input/output setup
LightOut light(11,13,12); //595 pins
HouzEnviroment houz;

//Fx setup
int i=-1;


void setup()
{
    light.output=123;
    houz.setDaySensorPin(1);
    houz.setDoorSensorPin(2);
}

void loop()
{


    if(i==7) {i=0;}
    else {i++;};
    light.toggle(i);

    Serial.print("step ");
    Serial.print(i);
    Serial.print(": ");



  delay(50);
}
