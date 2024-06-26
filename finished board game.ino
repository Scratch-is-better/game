#include <Servo.h>
Servo MyServo;

#include <time.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>;

LiquidCrystal_I2C lcd1(0x27, 16, 2);

int shock = 10;
int btn = 4;
int way = 0; // way that the servo will turn depending on whose turn it is
bool rip = false; //boolean for letting the servos move

void setup() {
  // put your setup code here, to run once:

  srand(time(NULL));
  pinMode(btn, INPUT);
  pinMode(shock, INPUT);
  MyServo.attach(8);
  Serial.begin(9600);
  lcd1.begin();
  lcd1.backlight();
  delay(1000);
  lcd1.setCursor(0, 0);
  lcd1.print("Welcome to:");
  lcd1.setCursor(0, 1);
  delay(800);
  lcd1.print("Gamble For Four");
  delay(2000);
  lcd1.clear();
  MyServo.write(90);
  
}


void servo()
{
  MyServo.write(way);
  delay (1000);
  MyServo.write(90);
  delay (1000);
}


void end() 
{
  rip = false;
  MyServo.write(90);
  lcd1.clear();
}


void loop() { //main code here

  lcd1.print("Pull the lever");
  lcd1.setCursor(0, 1);
  lcd1.print("to play!        ");
  int random = rand() % 100; //THE rng
  Serial.println(way);



  // 90 mid, 0 right, 180 left

  //btn pressed stuff ------------------------------------------------------V

  if (digitalRead(btn) == HIGH)
  {
    lcd1.clear();
    Serial.println(random);

    for (int t = 0; t < 1400; t++) //loading screen
    {
      int load = rand() % 100;
      lcd1.print(load);
      random % load;
    }

    lcd1.clear();
    lcd1.setCursor(7, 0);
    lcd1.print(random);
    rip = true;
  }
  //servo moving stuff ---------------------------------------------------------------------V
  while (rip == true)
  {
    if (random <= 20)
    {
      delay(2000);
      
      if (digitalRead(shock) == HIGH)
      {
        MyServo.write(way);
        servo();
      }
      end();
     
    }

    else if ((random >= 21) && (random <= 65))
    {
      for (int t = 0; t < 1; t++)
      {
        servo();
      }
     
      end();
    }

    else if ((random >= 66) && (random <= 80))
    {

      for (int t = 0; t < 2; t++)
      {
        servo();
      }
    
      end();
    }

    else if ((random >= 81) && (random <= 98))
    {
      for (int t = 0; t < 3; t++)
      {

        servo();
      }
     
      end();
    }

    else if (random == 99) {

      for (int t = 0; t < 4; t++)
      {
        servo();
      }
      
      end();
    }

    else
    {
      end();
    }

    //turn changer -----V
    if (way == 0) {
      way = 180;
    }
    else if (way == 180) {
      way = 0;
    }
  }
}
