#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const float p1 = 4.428;
const float p2 = 16.17;
const float p3 = 15.35;
const float p4 = 7.229;
const float p5 = 11.59;

int a;
float b;
float w;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte full[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

byte half[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};





 
void setup() {
  
  Serial.begin(9600);
  myservo.attach(8);
  lcd.begin(16, 2);
  lcd.createChar(1, full);
  lcd.createChar(2, half);

}

void loop() {
 
 a = analogRead(A0);

 b = (a - 641.1) / 83.3;

 w = (p1 * pow(b,4) + p2 * pow(b,3) + p3 * pow(b,2) + p4 * b + p5); 


  if (a <= 480){ 
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Nivel de agua:");
    lcd.setCursor(1, 1);
    lcd.print("Vazio");
    Serial.println("Nivel de água: 0mm - Vazio!"); 
    myservo.write(180);
    delay(50);
  
  }
  
  else if (a > 710){ 
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Nivel de agua:");
    Serial.println("Nivel de água: Cheio"); 
    nivel_agua();
    myservo.write(20);
    delay(50);
  }
  
  else { 
    Serial.print("ADC: ");
    Serial.println(a);
    Serial.print("Nivel de água: ");
    Serial.print(w);
    Serial.println(" mm");
  }
  delay(1000);


}

void nivel_agua(){
  for (int i = 4; i<11; i++){
    lcd.setCursor(i, 1);
    lcd.write((byte)1);
    delay(50);
    lcd.setCursor((i+1),1);
    lcd.write((byte)2);
    delay(50);
  
  }
}





