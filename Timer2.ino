#include <LiquidCrystal.h>
int valMin, valSec;
boolean keySec, keyMin, start, prevState;
String stringTime; 
String stringPunto  = ":"; 
String stringZero = "0";
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int debounceDelay = 20;
 
boolean debounce(int pin){
 boolean state;
 boolean previousState;
 previousState = digitalRead(pin);
 for(int counter=0; counter < debounceDelay; counter++) {
  delay(1);
  state = digitalRead(pin);
  if( state != previousState) {
    counter = 0;
    previousState = state; }
  }
  return state;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("Timer:"); 
}

void loop() {
  lcd.setCursor(0, 1);
  keySec = digitalRead(10);
  keyMin = digitalRead(9);
  if (keySec == HIGH){
    valSec = valSec + 10;
    delay(250);
    if (valSec >= 60){
      valSec = 0;
      valMin++;
    }
  }
  if (keyMin == HIGH){
    valMin++;
    delay(250);
  } 
  stringTime = valMin +stringPunto + valSec ;
  lcd.print(stringTime);
  start = debounce(8);
  if((start == HIGH) && (prevState == LOW)){
    while(valMin != -1){
      lcd.clear();
      lcd.print("Tempo residuo:");
      lcd.setCursor(0,1);
      //controllo se il valore dei secondi è inferiore a 10 per aggiungere  
      //uno 0 davanti ai secondi 
      if((valSec < 11) && (valSec >= 1)){
        valSec--;
        stringTime = valMin +stringPunto + stringZero + valSec ;
        lcd.print(stringTime);
        delay(1000); 
      }
      // controllo se il valore dei secondi è maggiore di 10
      if(valSec >= 10) {
        valSec--;
        stringTime = valMin +stringPunto + valSec ;
        lcd.print(stringTime);
        delay(1000); 
      }
      //controlo se valSec è a 0 per diminuire i minuti e riportare a 60
      //i secondi e scrivo 00 sul display
      if(valSec == 0){
        valMin--;
        valSec = 60;
        stringTime = valMin +stringPunto + "00";
        lcd.print(stringTime);
      } 
    } 
  }
  else{
    prevState = LOW;
  }
  //se i minuti sono -1 allora il conteggio è finito
  if(valMin == -1){
    valMin = 0;
    valSec = 0;
    lcd.clear();
    lcd.print("TEMPO FINITO");
  } 
}
