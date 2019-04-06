// Biblioteca auxiliar
#include <Servo.h>

//RGB
int redPin= 5;
int greenPin = 4;
int bluePin = 3;
//LDR
int ldrPin = 0; //LDR no pino analígico 0
int ldrValorRed = 0; //Valor lido do LDR
int ldrValorGreen = 0; //Valor lido do LDR
int ldrValorBlue = 0; //Valor lido do LDR
int tensaoLdr = 0;


const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
volatile int buttonState = 0;         // variable for reading the pushbutton status
int aux = 0;

// Definições de constantes
#define servoOne        6
#define servoTwo        7
#define servoThree      8
#define servoFour       9
#define servoFive       10

#define redOne         50
#define redTwo        110
#define redThree      170
#define redFour        90

#define greenOne       35
#define greenTwo      120
#define greenThree    160
#define greenFour     140

#define blueOne       13
#define blueTwo      135
#define blueThree    175
#define blueFour     135

// Definiçoes de variaveis
byte positionOne = 90;
byte positionTwo = 90;
byte positionthree = 90;
byte positionfour = 90;
byte positionfive = 90;

// Funções auxiliares
void originPosition();
void backOriginRed();
void backOriginGreen();
void backOriginBlue();
void movePositionRed(byte one, byte two, byte three, byte four);
void movePositionGreen(byte one, byte two, byte three, byte four);
void movePositionBlue(byte one, byte two, byte three, byte four);
void movePositionCube();
void moveServoOne(byte one);
void moveServoTwo(byte two);
void moveServoThree(byte three);
void moveServoFour(byte four);

// Atribuição de objetos (servos do braço)
Servo servo_one, servo_two, servo_three, servo_four, servo_five;

void setup() {

  //configura os pinos dos servos como saída digital
  pinMode(servoOne,   OUTPUT);
  pinMode(servoTwo,   OUTPUT);
  pinMode(servoThree, OUTPUT);
  pinMode(servoFour,  OUTPUT);
  pinMode(servoFive,  OUTPUT);
  
  //atribui os pinos do Arduino ao respectivo servo
  servo_one.attach(servoOne);
  servo_two.attach(servoTwo);
  servo_three.attach(servoThree);
  servo_four.attach(servoFour);
  servo_five.attach(servoFive);
  
  // Manda o braço para posiçao inicial
  //originPosition();
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

  analogWrite(A3, LOW);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(2), pin_ISR, CHANGE);
  //Serial.begin(19200);
  Serial.begin(9600);
  originPosition();
}

void loop() { 
  
  if(digitalRead(2) == HIGH) {
    Serial.println("a");
    movePositionCube();
    originPosition();
    move_arm('R');
  }
  else if(digitalRead(3) == HIGH) {
    Serial.println("b");
    movePositionCube();
    originPosition();
    move_arm('G');
  }
  else if(digitalRead(4) == HIGH) {
    Serial.println("c");
    movePositionCube();
    originPosition();
    move_arm('B');
  }  
}

void pin_ISR() {
  buttonState = digitalRead(buttonPin);
}  

void move_arm(char color){

  analogWrite(A3, LOW);
  
  if(color == 'R'){
    //Serial.print("Vermelho");
    delay(500);
    movePositionRed(redOne, redTwo, redThree, redFour);
    delay(2000);
    
    backOriginRed();
    
  }
  else if(color == 'G'){
    // Serial.println("Verde");
     delay(500);
     movePositionGreen(greenOne, greenTwo, greenThree, greenFour);
     delay(2000);
    
     backOriginGreen();
  }
  else if(color == 'B'){
    //Serial.println("Blue");
    delay(500);
    movePositionBlue(blueOne, blueTwo, blueThree, blueFour);
    delay(2000);
    
    backOriginBlue();
  }
  analogWrite(A3, HIGH);
}

void originPosition(){
  
 moveServoOne(90);
 moveServoFour(120);
 moveServoTwo(170);
 moveServoThree(175);
 
 positionOne = 90;
 positionTwo = 170;
 positionthree = 175;
 positionfour = 120;
 positionfive = 120;
  
}

void movePositionRed(byte one, byte two, byte three, byte four){
   
    moveServoOne(one);
    moveServoThree(three);
    moveServoFour(four);
    moveServoTwo(two);
    
    servo_five.write(90);
   
    positionOne = 50;
    positionTwo = 110;
    positionthree = 170;
    positionfour = 90;
    positionfive = 90;
}

void backOriginRed(){
  moveServoTwo(170);
   moveServoFour(120);
  moveServoThree(175);
  moveServoOne(90);
 
  positionOne = 90;
  positionTwo = 170;
  positionthree = 175;
  positionfour = 120;
  positionfive = 120;
  
  
}

void movePositionGreen(byte one, byte two, byte three, byte four){
  
  moveServoOne(one);
  moveServoThree(three);
  moveServoTwo(two);
  moveServoFour(four);
  
  servo_five.write(90);
   
  positionOne = greenOne;
  positionTwo = greenTwo;
  positionthree = greenThree;
  positionfour = greenFour;
  positionfive = 90;
}

void backOriginGreen(){
  
  
  moveServoFour(120);
  moveServoTwo(170);
  moveServoThree(175);
  moveServoOne(90);
  
 
  positionOne = 90;
  positionTwo = 170;
  positionthree = 175;
  positionfour = 120;
  positionfive = 120;
  
  
  
}

void movePositionBlue(byte one, byte two, byte three, byte four){
    moveServoOne(one);
    moveServoThree(three);
    moveServoFour(four);
    moveServoTwo(two);
    
    servo_five.write(90);
   
    positionOne = blueOne;
    positionTwo = blueTwo;
    positionthree = blueThree;
    positionfour = blueFour;
    positionfive = 90;



}

void movePositionCube(){

   // servo_five.write(90);
 //   moveServoOne(90);
   // positionOne = 90;
    // moveServoTwo(90);
    //positionTwo = 90;
    //moveServoThree(90);
    //positionthree = 90;
    //moveServoFour(90);
    //positionfour = 90;
    servo_five.write(80);
    moveServoFour(150);
    positionfour = 150;
    moveServoTwo(140);
    positionTwo = 140;
    moveServoThree(167);
    positionthree = 167;
    moveServoOne(86);
    positionOne = 86;
    moveServoFour(130);
    positionfour = 130;
    moveServoTwo(105);
    positionTwo = 105;
    moveServoFour(125);
    positionfour = 125;
    moveServoTwo(100);
    positionTwo = 100;
    delay(500);
    servo_five.write(117);
    moveServoTwo(110);
    positionTwo = 110;
    moveServoFour(140);
    positionfour = 140;
    moveServoTwo(120);
    positionTwo = 120;
    positionfive = 110;


}

void backOriginBlue(){
    
  moveServoFour(120);
  moveServoTwo(170);
  moveServoThree(175);
  moveServoOne(90);
  
  positionOne = 90;
  positionTwo = 170;
  positionthree = 175;
  positionfour = 120;
  positionfive = 120;
}

void moveServoOne(byte one){
  if(positionOne > one){
   for(int i = positionOne; i>one; i--){
      servo_one.write(i);
      delay(50);
   }
  }
  else{
    for(int i = positionOne; i<one; i++){
      servo_one.write(i);
      delay(50);
   }
  }
}

void moveServoTwo(byte two){
  if(positionTwo > two){
    for(int i = positionTwo; i>two; i--){
      servo_two.write(i);
      delay(50);
   }
  }
  else{
    for(int i = positionTwo; i<two; i++){
      servo_two.write(i);
      delay(50);
   }
  }
}


void moveServoThree(byte three){
   if(positionthree > three){
    for(int i = positionthree; i>three; i--){
      servo_three.write(i);
      delay(50);
   }
  }
  else{
    for(int i = positionthree; i<three; i++){
      servo_three.write(i);
      delay(50);
   }
  }
}

void moveServoFour(byte four){
 if(positionfour > four){
    for(int i = positionfour; i>four; i--){
      servo_four.write(i);
      delay(50);
  }
  }
  else{
    for(int i = positionfour; i<four; i++){
        servo_four.write(i);
        delay(50);
    }
  }
}
