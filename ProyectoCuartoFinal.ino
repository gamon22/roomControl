                                                                                                                                                           /*
 *      LCD 16x2 Pin Configuration:
 *      
 *      VSS -> GND
 *      VDD -> VCC
 *      V0  -> middle pin from potentiometer
 *      RS  -> digital pin 7
 *      RW  -> GND
 *      E   -> digital pin 6
 *      D4  -> digital pin 5
 *      D5  -> digital pin 4
 *      D6  -> digital pin 3
 *      D7  -> digital pin 2
 *      A   -> digital pin 11
 *      K   -> 1kohm resistor to gnd
 */

 
#include <math.h>
#include <LiquidCrystal.h>
#define RELAYCooler 8   
#define RELAYCalefactor 9
#define RELAYLamp 12
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;




int temp =70, flag, flag2, flag3, flag4,confirmar, temperatura, counter, lCounter;
int select = A3, mic = 10, lDisplay = 11, mic2 = A5, state, value, displayLcd, enableLamp;
int increase = A1, activar, conCooler, conCale, tempRegulate;
double operation;
int decrease = A2;
int screenWidth = 16;
int screenHeight = 2;
String message="", message2="";
int stringStart, stringStop = 0;
int scrollCursor = screenWidth;

 byte arrow[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100
};




void setup() {
  // set up the LCD's number of columns and rows:
  
  lcd.createChar(2, arrow);
  lcd.begin(16, 2);
  
  pinMode(increase,INPUT);
  pinMode(decrease,INPUT);
  pinMode(select,INPUT);
  
  pinMode(RELAYCooler, OUTPUT); 
  pinMode(RELAYCalefactor, OUTPUT); 
  pinMode(RELAYLamp, OUTPUT);
  pinMode(mic, INPUT);
  pinMode(lDisplay, OUTPUT);
  //for test mic's potentometer
  //Serial.begin(9600);
       
}


void enableDisableLamp(){
   //Para Desabilitar microfono
   /*if(counter == 0)
      value = digitalRead(mic);
   if(value == HIGH && counter == 0)
      state=digitalRead(RELAYLamp),
      digitalWrite(RELAYLamp, !state);
     */
      // for test mic's potentiometer
     // value= analogRead(mic2);
      //Serial.println(value);

   if(counter == 1)
      digitalWrite(RELAYLamp, HIGH),
      delay(1000);
   
   if(counter == 2)
      digitalWrite(RELAYLamp, LOW),
      delay(1000);

      
   delay(10);  
}



String confirmarmsg(String message2){
    
    message2="conf si " + String((char)94) + " no " ;
    message2.concat((char)arrow);

    delay(100);
    return(message2);
}


void clearLCD(){
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.clear();
    
}

void Seleccion(){
     
   flag=1;
   if(digitalRead(increase)== HIGH && confirmar==2) {
      temp ++;
      delay(500);
      flag=1;
   }

    if (digitalRead(decrease)== HIGH && confirmar == 2) {
        temp --;
        flag=1;
        delay(500);
    }
    if(confirmar == 2){
       lcd.setCursor(0, 0);
       lcd.clear();
       confirmar=2;
       digitalWrite(RELAYCooler, LOW);
       digitalWrite(RELAYCalefactor, LOW);
       lcd.print("Select Temp");
       lcd.setCursor(3, 1);
       lcd.print(temp);
       delay(500);
    }

    if(digitalRead(select)==HIGH && confirmar==2 ){
       confirmar=3;
      
       message="Confirmar?";
       lcd.print(message);
       digitalWrite(RELAYCooler, LOW);
       digitalWrite(RELAYCalefactor, LOW);
       lcd.setCursor(0,0);
       lcd.clear();
      
       lcd.print(confirmarmsg(message2));
       lcd.setCursor(3,1);
       
       lcd.print(temp);
       enableDisableLamp();
       delay(700);
    }

      
   if(digitalRead(increase) && confirmar ==3){
       
       confirmar=4;
       digitalWrite(RELAYCooler, LOW);
       digitalWrite(RELAYCalefactor, LOW);
       message="confirmado";
       enableDisableLamp();
       clearLCD();
       lcd.print(message);
       enableDisableLamp();
       delay(3000);
      }
      
   if(digitalRead(decrease)==HIGH && confirmar ==3){
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("procesando");
      delay(500);
      confirmar = 2;
      activar=0;
      flag=1;
      enableDisableLamp();
      delay(100);  
     }

      
   if(digitalRead(select)==HIGH ){
      message="ac.var tem.or?";
      lcd.setCursor(0, 0);
      confirmar=1;
      lcd.clear();
      lcd.print(message);
      lcd.setCursor(0, 1);
      lcd.print(confirmarmsg(message2));
      delay(3300);
     }

   if(digitalRead(increase)== HIGH && confirmar==1) {
      confirmar=2;
      flag2=0;
      tempRegulate=HIGH;
      message="temp Reg.da: ON";
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print(message);
      delay(3000);
      clearLCD();
     }

   if(digitalRead(decrease)== HIGH && confirmar == 1) {
      message="temp Reg.da: OFF";
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print(message);
      conCooler=LOW;
      conCale=LOW;
      confirmar=8;
      tempRegulate=LOW;
      delay(3000);
      clearLCD();
    }

    if(confirmar==4 ) {
       message="ac.var Cooler?";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       lcd.setCursor(0, 1);
       lcd.print(confirmarmsg(message2));
       delay(3300);
       confirmar=5;
     }

     if(digitalRead(increase)== HIGH && confirmar==5) {
        clearLCD();
        conCooler=HIGH;
        confirmar=6;
        message="Cooler acti.do";
        lcd.setCursor(0, 0);
        lcd.print(message);
        delay(3000);
        clearLCD();
      }

    if(digitalRead(decrease)== HIGH && confirmar == 5) {
       conCooler=LOW,
       confirmar=6;
       message="Cooler desa.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
    }

    if(confirmar==6 && flag!=0){
       confirmar=7;
       message="ac.var Cale.or?";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       lcd.setCursor(0, 1);
       lcd.print(confirmarmsg(message2));
       delay(3000);
     }

     if(digitalRead(increase)== HIGH && confirmar==7) {
        conCale=HIGH;
        confirmar=0;
        flag=0;
        message="Cale.or acti.do";
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.print(message);
        delay(3000);
        clearLCD();
     }

    if(digitalRead(decrease)== HIGH && confirmar == 7) {
       conCale=LOW,
       confirmar=0;
       flag=0;
       message="Cale.or desa.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
    }

    // manual activation
    if(confirmar == 8) {
       confirmar = 9;
       message="Ac.var Manual?";
       lcd.setCursor(0,0);
       lcd.clear();
       lcd.print(message);  
       lcd.setCursor(0,1);
       lcd.print(confirmarmsg(message2));
       delay(3000);
    }

    if(digitalRead(increase)== HIGH && confirmar==9) {
       clearLCD();
       confirmar=10;
       flag2=1;
       digitalWrite(RELAYCooler, LOW);
       digitalWrite(RELAYCalefactor, LOW);
       message="Procesando";
       lcd.setCursor(0, 0);
       lcd.print(message);
       delay(3000);
       clearLCD();
      }

    if(digitalRead(decrease)== HIGH && confirmar == 9) {
       confirmar=0;
       flag=0;
       message="Manual desa.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
       loop();
    }

    if(confirmar == 10) {
       confirmar = 11;
       message="Ac.var Cooler?";
       lcd.setCursor(0,0);
       lcd.clear();
       lcd.print(message);
       lcd.setCursor(0,1);
       lcd.print(confirmarmsg(message2));
       delay(3000);
     }

    if(digitalRead(increase)== HIGH && confirmar==11) {
       clearLCD();
       conCooler=HIGH;
       confirmar=12;
       message="Cooler Act.do";
       lcd.setCursor(0, 0);
       lcd.print(message);
       delay(3000);
       clearLCD();
      }

    if(digitalRead(decrease)== HIGH && confirmar == 11) {
       conCooler=LOW;
       confirmar=12;
       message="Cooler desa.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
    }

    if(confirmar == 12) {
       confirmar = 13;
       message="Ac.var Ca.tor?";
       lcd.setCursor(0,0);
       lcd.clear();
       lcd.print(message);
       lcd.setCursor(0,1);
       lcd.print(confirmarmsg(message2));
       delay(3000);
    }

    if(digitalRead(increase)== HIGH && confirmar==13) {
       clearLCD();
       conCale=HIGH;
       confirmar=0;
       flag=0;
       message="Ca.tor Act.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
       loop();
      }

    if(digitalRead(decrease)== HIGH && confirmar == 13) {
       conCale=LOW;
       confirmar=0;
       flag=0;
       message="Ca.tor desa.do";
       lcd.setCursor(0, 0);
       lcd.clear();
       lcd.print(message);
       delay(3000);
       clearLCD();
       loop();
      
    }
}

/*
void messagge(){
  
  lcd.setCursor(0, 0);
    message="Creado por:";
    lcd.print(message);
    lcd.setCursor(0, 1);
    message2="Luis A. Gamon";
    lcd.print(message2);
    delay(4000);
    clearLCD();
    message="";
}*/

void loop() {

  
   if(digitalRead(select)==HIGH && activar==0 && displayLcd==HIGH|| flag==1 && displayLcd==HIGH){
      if(confirmar==0){
         clearLCD();
         delay(100);
      }
      Seleccion();
    }

  
     
   if(digitalRead(select)==LOW && flag==0 ){
      Vo = analogRead(ThermistorPin);
      R2 = R1 * (1023.0 / (float)Vo - 1.0);
      logR2 = log(R2);
      T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
      T = T - 273.15;
      T = (T * 9.0)/ 5.0 + 32.0;
      operation = ((int)T) - temp;  

      
   if(flag2==0){
      message="Temp: "+String((int)T)+ (char)223+ "F";
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print(message);
      //temperatura=temp+3;
     }

    //Activar forma manual
   if( flag2>0 && conCooler ==HIGH){
      message="Manual act.do"; 
      lcd.setCursor(0, 0);
      lcd.print(message);
      //message2="QQ";
      //lcd.setCursor(0, 1);
      //lcd.print(message2);
      digitalWrite(RELAYCooler, conCooler);
      digitalWrite(RELAYCalefactor, conCale);
     }
   if( flag2>0 && conCale ==HIGH){
      message="Manual act.do"; 
      lcd.setCursor(0, 0);
      lcd.print(message);
      message2="Ca..dor: ON";
      lcd.setCursor(0, 1);
      lcd.print(message2);
      digitalWrite(RELAYCooler, conCooler);
      digitalWrite(RELAYCalefactor, conCale);
     }


     //Activar Cooler forma regulada
   //if ( ((int)T) > temp && ((int)T) > temperatura && conCooler==HIGH && flag2==0) {
   //if(operation > 3 && 
   //if ( ((int)T) > temp &&  conCooler==HIGH && flag2==0) {
     if ( operation > 0 &&  conCooler==HIGH && flag2==0  || conCooler==HIGH && conCale==LOW && operation > 0 ) {
       digitalWrite(RELAYCooler, HIGH);
       digitalWrite(RELAYCalefactor, LOW);
       lcd.setCursor(0,1);
       message2="Cooler:ON";
       lcd.print(message2);
       }

      //else if( conCale==LOW && conCooler==HIGH && flag3==0){
      else if( conCale==LOW && conCooler==HIGH && operation>-2 && operation<2){
      message2="Procesando";
      lcd.setCursor(0,1);
      lcd.print(message2);
     }

       if( operation < -1 && conCale==LOW && conCooler==HIGH){ 
       digitalWrite(RELAYCooler, LOW); 
       message2="Cooler:OFF";
        lcd.setCursor(0,1);
        lcd.print(message2);
       }
       

      // Activar Calefactor
   //if (((int)T) < temperatura && ((int)T) <temp && conCale==HIGH && flag2==0) {
   //if( operation < -3
   //if (((int)T) <temp && conCale==HIGH && flag2==0) {
   
   if (operation < 0 && conCale==HIGH && flag2==0 ||  conCooler==LOW && conCale==HIGH && operation < 0 ) {
     // if (operation < 0 && conCale==HIGH && flag2==0  ) {
       digitalWrite(RELAYCalefactor, HIGH);
       digitalWrite(RELAYCooler, LOW);
       message2="Ca..dor:ON";
       //message2=operation;
       lcd.setCursor(0,1);
       lcd.print(message2);
       }

      
    
       else if( conCale==HIGH && conCooler==LOW && operation>-1 && operation<2){
      message2="Procesando";
      lcd.setCursor(0,1);
      lcd.print(message2);
      }
     
     if (operation > 1  && conCale==HIGH &&  conCooler==LOW && flag2==0) {
       digitalWrite(RELAYCalefactor, LOW);
       digitalWrite(RELAYCooler, LOW);
       message2="Ca..dor:OFF";
       lcd.setCursor(0,1);
       lcd.print(message2);
       }
      
      
      
     
   
      if( conCooler==LOW && conCale==LOW ){
   
     digitalWrite(RELAYCalefactor, LOW);
       digitalWrite(RELAYCooler, LOW);
        message2="temp Reg.da: OFF";
        lcd.setCursor(0,1);
        lcd.print(message2);
        
      }
    
   }

    

   if(digitalRead(increase)==HIGH && flag==0 && digitalRead(select)==LOW){
      counter++;
      clearLCD();
      
    if(counter==1)
       enableLamp=HIGH,
       message="lamp activada";
       
     
   if(counter==2)
      counter=0,
      enableLamp=LOW,
      message="lamp desact..da";
      
     
   //if(counter==3)
      //messagge(),
      //message="",
      //counter=0;
     
     
     lcd.setCursor(0, 0);
     lcd.print(message);
     delay(3000);
     lcd.clear();
     digitalWrite(RELAYLamp, enableLamp);
     delay(10);
     
   }


   if(digitalRead(decrease)==HIGH && flag==0 && digitalRead(increase)==LOW && digitalRead(select)==LOW){
      lCounter++;
      clearLCD();
   if(lCounter==1)
      displayLcd=HIGH,
      message="Display ON";

   if(lCounter==2)
      displayLcd=LOW,
      lCounter=0,
      message="Display OFF";   

      lcd.setCursor(0, 0);
      lcd.print(message);
      delay(3000);

      digitalWrite(lDisplay, displayLcd);
   }  
   //enableDisableLamp();
   delay(750);
}
