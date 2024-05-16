#include <Servo.h>
Servo MyServo;

#include <time.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>;

LiquidCrystal_I2C lcd1(0x27, 16, 2);

int shock = 10;
int btn = 4;
int val;    // numeric variable to store sensor status
bool turn = true; // score changer
int way = 0; // way that the servo will turn depending on whose turn it is

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

void shok()
{
  val = digitalRead(shock); // read and assign the value of digital interface 3 to val

  if (val == HIGH ) // when sensor detects a signal, the LED flashes
  {
    Serial.print("ouch\n");
    delay(1000);
  }
  else
  {
    Serial.print("smooth sailin'\n");
    delay(1000);
  }
}


void rng()
{

  int random = rand() % 99;
  Serial.println(random);
  lcd1.print(random);

}


void servo()
{
  MyServo.write(way);
  delay (1000);
  MyServo.write(90);
  delay (1000);
}

void end() {
  MyServo.write(90);
  lcd1.clear();
}


void loop() { // put your main code here, to run repeatedly:

  lcd1.print("Pull the lever");
  lcd1.setCursor(0, 1);
  lcd1.print("to play!        ");
  int random = rand() % 100;
  Serial.println(way);
  bool rip = false; //boolean for letting the servos move



  // 90 mid, 0 right, 180 left

  //btn pressed stuff ------------------------------------------------------

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
  //servo moving stuff ---------------------------------------------------------------------
  while (rip == true)
  {
    if (random <= 20)
    {

      delay(2000);
      if (digitalRead(shock) == HIGH)
      {
        Serial.println(shock);
        MyServo.write(way);
        servo();
      }


      end();
      rip = false;
    }

    else if ((random >= 21) && (random <= 65))
    {
      for (int t = 0; t < 1; t++)
      {

        servo();
      }
      rip = false;
      end();
    }

    else if ((random >= 66) && (random <= 80))
    {

      for (int t = 0; t < 2; t++)
      {

        servo();
      }
      rip = false;
      end();
    }

    else if ((random >= 81) && (random <= 98))
    {
      for (int t = 0; t < 3; t++)
      {

        servo();
      }
      rip = false;
      end();
    }

    else if (random == 99) {

      for (int t = 0; t < 4; t++)
      {

        servo();
      }
      rip = false;
      end();
    }

    else
    {
      MyServo.write(90);
    }


    if (way == 0) {
      way = 180;
    }
    else if (way == 180) {
      way = 0;
    }
  }
}
