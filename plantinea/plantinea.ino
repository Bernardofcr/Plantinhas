#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const float p1 = 4.428;   //Converte para mm 
const float p2 = 16.17;
const float p3 = 15.35;
const float p4 = 7.229;
const float p5 = 11.59;


int a;
int u;
int b1;
int b2;
float b;
float w;

int luminoso;
int button1 = 7; // Botão do lcd
int button2 = 8; // Botão do Motor servo
int cont = 1;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int conversorpor100(int valor){     // Converte o valor da umidade e coloca em porcentagem
  int p100umidade=0;
  p100umidade=map(valor,1023,350,0,100);
  if (p100umidade>100){
    p100umidade=100;
  }
  return p100umidade;
}
/* Solo umido - 0 a 400
 * Solo Moderado - 400 - 800
 * Solo seco - 800 - 1024
 * 
 * 
 * 
 * calculo para transformar a quantidade de agua no recipiente em litros.  
 */

void status_planta (int lcd_value) // Mostra o status da planta no LCD
{
  int p;
  switch (lcd_value)
  {

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
      p = umidade_solo(u);
      lcd.setCursor(1,1);
      lcd.print(String(conversorpor100(u))+"%");
      break;
      
    case 3: // Luminosidade
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Luminosidade:");
      lcd.setCursor(1,1);
      if( luz(luminoso)== 1)
      {
        lcd.print("baixa");
      }
      else if( luz(luminoso)== 2)
      {
        lcd.print("mediana");
      }
      else if (luz(luminoso)== 3)
      {
        lcd.print("alta");
      }
      else if (luz(luminoso)==4)
      {
        lcd.print("sem condicoes");
      }
      delay(500);
      break;
 }
}

 
void setup() {
  
  Serial.begin(9600);
  myservo.attach(9,800,2500); // motor Servo
  lcd.begin(16, 2);
  lcd.createChar(1, full);
  lcd.createChar(2, half);
  pinMode(7, INPUT);  // Nível da agua
  pinMode(A1, INPUT); //Sensor de umidade

}

void loop() {
 
  a = analogRead(A0);//nivel de agua
  u = analogRead(A1);//umidade do solo
  b1 = digitalRead(button1);
  b2 = digitalRead(button2);
  
  luminoso=analogRead(A2);
 
 if (b1 == HIGH){
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

  teste_door(b2);
  


}

int nivel_agua(int agua){
 
    b = (agua - 641.1) / 83.3;
    w = (p1 * pow(b,4) + p2 * pow(b,3) + p3 * pow(b,2) + p4 * b + p5); // Pode ser transformado em cm ou m 

    if (agua <= 480){ 
      return 1;
  }
    else if (agua > 710){ 
      return 2;
  } 
    else { 
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


  int luz(int x) // Intensidade da luz no ambiente
  {
    if(x < 30)
    {
      //sem luz
      return 1;  
    }
    else if (x >=30 && x <= 120) 
    {
      //luz mediana
      return 2;
    }
    else if(x > 120 && x< 300)
    {
      // luz intensa
      return 3;
    }
    else
    {
      return 4;
    }
    }

  void open_door(){
    int c = 0;
    while (c <= 180){
      myservo.write(c);
      delay(50);
      c ++;
    }
     
  }


  void close_door(){
    int c = 180;
    while (c > 1){
      myservo.write(c);
      delay(50);
      c --;
    }
  }

  void teste_door(int status_button){ // Movimenta o motor para liberação da água
    if (status_button == HIGH){
      int c = 0;
      while (c <= 180){
        myservo.write(c);
        delay(50);
        c ++;
      }
       if (c = 181){
        while (c > 1){
          myservo.write(c);
          delay(50);
          c --;
        }
       }
    }   
  }


