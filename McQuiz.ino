#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'&','0','#','/'}
};
bool add, sub, mul, diver;
long opCheck=0, numCheck=0, value=0, points=0, rand_1=0, rand_2=0, rand_3=0, rand_4=0, rand_5=0, rand_6=0, rand_7=0, corrAns=0;
long check[4]; 

byte rowPins[ROWS] = {2,3,4,5}; 
byte colPins[COLS] = {6,7,8,9}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal_I2C lcd(0x3f, 16, 2);
String message, displayText="CHECK101";
char customKey;
void setup() {
  for (int w=0; w<=3; w++){
  check[w]=0;
  }
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("McQuiz");
  lcd.setCursor(10, 1);
  lcd.print("-8th A");
  delay(3000);
  lcd.clear();
  lcd.print("Choose operation:");
  lcd.setCursor(0, 1);
  lcd.print("+ - * /");

} 
void loop(){
  customKey = customKeypad.getKey();
  if ((customKey=='1')||(customKey=='2')||(customKey=='3')||(customKey=='4')||(customKey=='5')||(customKey=='6')||(customKey=='7')||(customKey=='8')||(customKey=='9')||(customKey=='0')){
    number();
  }
  else if(customKey=='#'){
    checker();
  }
  else if(customKey=='&'){
    if ((check[0]==0)&&(check[1]==0)&&(check[2]==0)&&(check[3]==0)){
      return;
    }
    displayText="";
    numCheck=0;
    if (add==true){
      lcd.clear();
      message = String(rand_1) +"+" + String(rand_2) + "= ";
      lcd.print(message);
    }
    else if (sub==true){
      lcd.clear();
      message = String(rand_1) +"-" + String(rand_2) + "= ";
      lcd.print(message);
    }
    else if (mul==true){
      lcd.clear();
      message = String(rand_3) +" "+ "*" +" "+ String(rand_4) + "= ";
      lcd.print(message);
    }
    else if (diver==true){
      lcd.clear();
      message = String(rand_7) +"/" + String(rand_6) + "= ";
      lcd.print(message);
    }
  }
  else if ((customKey=='+') || (customKey=='-') || (customKey=='*') || (customKey=='/')){
    operation();
  }
}
void operation(){
    if (displayText!="CHECK101"){
      return;
    }
    displayText="";
    add=false;
    sub=false;
    mul=false;
    diver=false;
    rand_1=0;
    rand_2=0;
    rand_3=0;
    rand_4=0;
    rand_5=0;
    rand_6=0;
    rand_7=0; 
    if ((customKey=='+')||((check[0]>=1)&&(check[0]<5))){
      lcd.clear();
      welcome();
      randomSeed(millis());
      add=true;
      sub=false;
      mul=false;
      diver=false;
      rand_1=random(50, 1000);
      randomSeed(micros());
      rand_2=random(50, 1000);
      rand_1=rand_1+random(10, 250);
      rand_2=rand_2+random(10, 250);
      numCheck=0;
      opCheck++;
      check[0]++;
      message = String(rand_1) +"+" + String(rand_2) + "= ";
      lcd.print(message);
    }
    else if ((customKey=='-')||((check[1]>=1)&&(check[1]<5))){
      welcome();
      lcd.clear();
      add=false;
      sub=true;
      mul=false;
      diver=false;
      randomSeed(micros());
      randomSeed(millis());
      rand_1=random(50, 1000);
      randomSeed(micros());
      rand_2=random(1, rand_1-1);
      rand_1=rand_1+random(100, 150);
      rand_2=rand_2+random(10, 100);
      numCheck=0;
      opCheck++;
      check[1]++;
      message = String(rand_1) + "-"+ String(rand_2) + "= ";
      lcd.print(message);
    }
    else if ((customKey=='*')||((check[2]>=1)&&(check[2]<5))){
      welcome();
      lcd.clear();
      add=false;
      sub=false;
      mul=true;
      diver=false;
      numCheck=0;
      opCheck++;
      check[2]++;
      randomSeed(millis());
      rand_3=random(30, 100);
      randomSeed(micros());
      rand_4=random(30, 100);\
      rand_3=rand_3+random(10, 50);
      rand_4=rand_4+random(10, 50);
      message = String(rand_3) +" "+ "*" +" "+ String(rand_4) + "= ";
      lcd.print(message);
    }
    else if ((customKey=='/')||((check[3]>=1)&&(check[3]<5))){
      welcome();
      lcd.clear();
      add=false;
      sub=false;
      mul=false;
      diver=true;
      randomSeed(micros());
      rand_5=random(20, 100);
      randomSeed(millis());
      rand_6=random(5, 40);
      numCheck=0;
      opCheck++;
      check[3]++; 
      rand_5=rand_5+ random(1, 40);
      rand_6=rand_6+random(1, 40);
      rand_7= rand_5 * rand_6;
      message = String(rand_7) +"/" +String(rand_6) + "= ";
      lcd.print(message);
    }
}
void number(){
  if (opCheck>=1){
    if (!(numCheck>5)){
      displayText=(displayText+String(customKey));
      lcd.print(customKey);
      numCheck++;
    }
  }
}
void checker(){
  long result = sscanf(displayText.c_str(), "%d", &value);
  if (check[0]>=1){
    if (value==rand_1+rand_2){
      correctAns();
      return;
    }
    else{  
      corrAns=rand_1+rand_2;
      wrongAns();
    }
  }
  else if (check[1]>=1){
     if (value==rand_1-rand_2){
      correctAns();
      return;
    }
    else{  
      corrAns=rand_1-rand_2;
      wrongAns();
    }
  }  
  else if (check[2]>=1){
     if (value==rand_3*rand_4){
      correctAns();
      return;
    }
    else{  
      corrAns=rand_3*rand_4;
      wrongAns();
    }
  }
  else if (check[3]>=1){
     if (value==rand_7/rand_6){
      correctAns();
      return;
    }
    else{  
      corrAns=rand_7/rand_6;
      wrongAns();
    }
  }
  else{
  }
}
void correctAns(){
  for (long a=0; a<=4;a++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
  points++;
  lcd.clear();
  lcd.print("CORRECT ANSWER");
  delay(1000);
  end();
  operation();
}
void wrongAns(){
  for (long a=0; a<=4;a++){
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
  }
  lcd.clear();
  lcd.print("WRONG ANSWER");
  lcd.setCursor(0, 1);
  lcd.print("Correct= ");
  lcd.print(corrAns);
  delay(1800);
  end();
  operation();
  return;
}
void end(){
  numCheck=0;
  displayText="CHECK101";
    if((check[0]==5)||(check[1]==5)||(check[2]==5)||(check[3]==5)){
    lcd.clear();
    lcd.print("The Quiz is over");
    delay(1000);
    lcd.setCursor(1, 1);
    String x= "Score:";
    lcd.print(x + points);
    lcd.print("/5");
    delay(1500);
    lcd.clear();
    lcd.print("Thank you for");
    lcd.setCursor(0,1);
    lcd.print("using McQuiz!!");
    delay(500);
  }
}
void welcome(){
  if ((check[0]==0)&&(check[1]==0)&&(check[2]==0)&&(check[3]==0)){
    lcd.clear();
    lcd.print("Good luck :)");
    delay(1500);
    lcd.setCursor(0,1);
    lcd.print("Quiz has begun-");
    delay(1000);
    lcd.clear();
  }
}