#include <Bounce2.h>
#include "Display.h"
 
#define LDR 16
#define LED_GREEN 5
#define LED_RED 4
#define LED_BLUE 6
#define LED_YELLOW 7
#define BTN_K1 8
#define BTN_K2 9
#define BUZZER 3
 
const int HALFNOTE = 500;
const int C4 = 261;
const int pizzaTemp = 30;

const int PIN_NTC = 15;
const int NTC_R25 = 10000; // the resistance of the NTC at 25'C is 10k ohm
const int NTC_MATERIAL_CONSTANT = 3950; // value provided by manufacturer
 
bool sysStatus = false;
bool pizzaStatus = false;
 
int cnt = 0;
int index = 0;
 
Bounce K1 = Bounce(BTN_K1, 50);
Bounce K2 = Bounce(BTN_K2, 50);
 
void setup() {
  Serial.begin(9600);
 
Display.clear();
 
  pinMode(LDR, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BTN_K1, INPUT_PULLUP);
  pinMode(BTN_K2, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
 
  digitalWrite(BUZZER, LOW);
}
 
void loop() {
  K1.update();
  K2.update();
  //Serial.println(analogRead(LDR));
  //Gets temperature in celcius
  float celcius = get_temperature();
  int defaultLdrVal = 300; //to be set in the future
 //Check is the system is turned ON
  if (sysStatus == true)
  {
    //Checks if the current light is less than the default value and if the temperature is higher tha normal (like when a pizza passes) it registers as completed
    if (analogRead(LDR) < (defaultLdrVal - 10) && pizzaStatus == false && celcius > pizzaTemp)
    {
      //Sends a message to the C# application that the pizza is completed
      Serial.println("Completed");      
      greenLight();
      cnt++;
      Serial.println(cnt);
      /*tone(BUZZER, C4, HALFNOTE);
        delay(100);
        digitalWrite(BUZZER, LOW);*/
      //TODO Display
      pizzaStatus = true;
 
      if (cnt < 10 ) {
        Display.showDigitAt(0, cnt);
      } else if (cnt < 100) {
        Display.showDigitAt(0, cnt / 10);
        Display.showDigitAt(1, cnt % 10);
      } else if (cnt < 1000) {
        Display.showDigitAt(0, cnt / 100);
        Display.showDigitAt(1, (cnt % 100) / 10);
        Display.showDigitAt(2, (cnt % 100) % 10);
      }
    }
    else if (analogRead(LDR) > (defaultLdrVal - 10) && pizzaStatus == true) {
      pizzaStatus = false;
    }
  }
 //If the left button is pressed the light bridge turns ON
  if (K2.fell())
  {
    //First checks if it is OFF
    if (sysStatus == false)
    {
      sysStatus = true;
      redLight();
      greenLight();
      blueLight();
      yellowLight();
      blueLight();
      greenLight();
      redLight();
 
    }
  }
 //If the right button is pressed the system shuts DOWN
  if (K1.fell())
  {
    yellowLight();
    blueLight();
    greenLight();
    redLight();
    greenLight();
    sysStatus = false;
  }
}
 
void redLight()
{
  digitalWrite(LED_RED, HIGH);
  delay(500);
  digitalWrite(LED_RED, LOW);
}
 
void greenLight()
{
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
}
 
void blueLight()
{
  digitalWrite(LED_BLUE, HIGH);
  delay(500);
  digitalWrite(LED_BLUE, LOW);
}
 
void yellowLight()
{
  digitalWrite(LED_YELLOW, HIGH);
  delay(500);
  digitalWrite(LED_YELLOW, LOW);
}
//This method is from Examples, it transforms the value from the NTC to celcius
float get_temperature()
{
    float temperature,resistance;
    int value;
    value = analogRead(PIN_NTC);
    resistance   = (float)value * NTC_R25/(1024 - value); // Calculate resistance
    /* Calculate the temperature according to the following formula. */
    temperature  = 1/(log(resistance/NTC_R25)/NTC_MATERIAL_CONSTANT+1/298.15)-273.15;
    return temperature;
}
