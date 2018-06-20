#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const float p1 = 4.428;   //Converte para mm 
const float p2 = 16.17;
const float p3 = 15.35;
const float p4 = 7.229;
const float p5 = 11.59;


int a;
int d;
int y;
float b;
float w;

int button = 7;
int cont = 1;

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


/* Solo umido - 0 a 400
 * Solo Moderado - 400 - 800
 * Solo seco - 800 - 1024
 * 
 * 
 * 
 * calculo para transformar a quantidade de agua no recipiente em litros.  
 */


 
void setup() {
  
  Serial.begin(9600);
  myservo.attach(8,800,2500); // motor Servo
  lcd.begin(16, 2);
  lcd.createChar(1, full);
  lcd.createChar(2, half);
  pinMode(7, INPUT);  // Nível da agua
  pinMode(A1, INPUT); //Sensor de umidade

}

void loop() {
 
  a = analogRead(A0);//nivel de agua
  d = analogRead(A1);//umidade do solo
  y = digitalRead(button);
 
 if (y == HIGH){
    delay(200);
    cont++;
    if ( cont > 3){
      cont = 1;
    }
    status_planta(cont);
    Serial.println(cont);
    delay(50);
  } else {
    status_planta(cont);
    delay(50);
  }
  
  
  


}

int nivel_agua(int agua){
  /*for (int i = 4; i<11; i++){
    lcd.setCursor(i, 1);
    lcd.write((byte)1);
    delay(50);
    lcd.setCursor((i+1),1);
    lcd.write((byte)2);
    delay(50);
  */
    b = (agua - 641.1) / 83.3;
    w = (p1 * pow(b,4) + p2 * pow(b,3) + p3 * pow(b,2) + p4 * b + p5); // Pode ser transformado em cm ou m 

    if (agua <= 480){ 
   /* lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Nivel de agua:");
      lcd.setCursor(1, 1);
      lcd.print("Vazio");
      Serial.println("Nivel de água: 0mm - Vazio!"); 
      myservo.write(180);
      delay(50);*/
      return 1;
  }

    else if (agua > 710){ 
      /*lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Nivel de agua:");
      Serial.println("Nivel de água: Cheio");
      lcd.setCursor(1, 1);
      lcd.print("Cheio"); 
      myservo.write(0);
      delay(50);*/
      return 2;
  }
  
    else { 
      /*Serial.print("ADC: ");
      Serial.println(agua);
      Serial.print("Nivel de água: ");
      Serial.print(w);
      Serial.println(" mm");*/
      return 3;
  }


  
}


  int umidade_solo(int solo ){

    if (solo > 0 && solo < 400){
        Serial.println("Solo umido");
        return 1;
    
    } else if (solo > 400 && solo < 800){
        Serial.println("Solo moderado");
        return 2;
    } else {
        Serial.println("Solo Seco");
        return 3;
    }
    
}


  int temperatura(){
  
}

void status_planta(int lcd_value){
  int p;

 switch (lcd_value){

    case 1: // Nivel de agua
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Nivel de agua:");
      p = nivel_agua(a);
      if (p == 1){
        lcd.setCursor(1, 1);
        lcd.print("Vazio"); 
      } else if(p == 2){
        lcd.setCursor(1, 1);
        lcd.print("Cheio"); 
      } else {
        lcd.setCursor(1, 1);
        lcd.print(w);
     
      }
      break;
      
    case 2: // Umidade
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Umidade solo:");
      p = umidade_solo(d);
      if (p == 1){
        lcd.setCursor(1, 1);
        lcd.print("Umido "+String(conversorpor100(d))); 
      } else if(p == 2){
        lcd.setCursor(1, 1);
        lcd.print("Moderado "+String(conversorpor100(d)); 
      } else {
        lcd.setCursor(1, 1);
        lcd.print("Seco "+String(conversorpor100(d)); 
      }
      break;
      
    case 3: // Luminosidade
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Luminosidade:");
      break;
 }
}

int conversorpor100(int valor){
  int p100umidade=0
  p100umidade=map(valor,1023,350,0,100);
  if (p100umidade>100)
    p100umidade=100;
  return p100umidade
}


