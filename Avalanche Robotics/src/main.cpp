#include <Arduino.h>
#include <NewPing.h>
#include <Stepper.h>
#include  <LiquidCrystal_I2C.h>

int Vitesse_moteur = 10;
Stepper _corde(2048, 8, 10, 9, 11);
NewPing _neige(2, 3, 400);
LiquidCrystal_I2C lcd(0x27,16,2);

#define RED 4
#define GREEN 5
#define BLUE 6

void setup() {
  Serial.begin(9600);

  //LCD
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  //pinMode Ultrasonic sensor
  pinMode(2, OUTPUT); //Trigger pin
  pinMode(3, INPUT); //Echo pin

  //pinMode RGB CNT-1
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(13 , OUTPUT);

  //Moteur Stepper
  _corde.setSpeed(Vitesse_moteur);
  //_corde.step(1024);

}

void loop() {
//Serial.println("marche");
float hauteurNeige = _neige.ping_cm();
Serial.println(hauteurNeige);
delay(1000);


  if(hauteurNeige <= 4){
    lcd.clear();
    lcd.print("----heating----");
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
    delay(10000);

    lcd.clear();
    lcd.print("---Shoveling---");
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);

    _corde.setSpeed(Vitesse_moteur);
    _corde.step(20000);
    lcd.clear();
  }


}