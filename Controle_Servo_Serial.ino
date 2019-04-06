/*
Aluno: Ícaro Gabriel Paiva Bastos
Disciplina: Microcontrolador
Código: Achar a ângulo correta do braço para a captura do objeto.

INSTRUÇÕES

  A - (0 - 180 GRAUS) : MOVIMENTA O MOTOR UM
  B - (0 - 180 GRAUS) : MOVIMENTA O MOTOR DOIS
  C - (0 - 180 GRAUS) : MOVIMENTA O MOTOR TRÊS
  D - (0 - 180 GRAUS) : MOVIMENTA O MOTOR QUATRO
  E - (0 - 180 GRAUS) : MOVIMENTA O MOTOR CINCO
  F - (0 - 180 GRAUS) : MOVIMENTA O MOTOR SEIS
  
PONTOS INICIAIS
  A -
  B -
  C -
  D -
  E -
  F -

PONTOS FINAIS
  A -
  B -
  C -
  D -
  E -
  F -

*/

// Biblioteca auxiliar
#include <Servo.h>


// Definições de constantes
#define servoOne       10
#define servoTwo        9
#define servoThree      8
#define servoFour       7
#define servoFive       6
#define servoSix       12


// Funções auxiliares
void splitString(char* data);
void setPosition(char* data);


// Atribuição de objetos (servos do braço)
Servo servo_one, servo_two, servo_three, servo_four, servo_five, servo_six;


// Variáveis
char buffer[18]; // vetor para armazenar string de texto
                 // maior que o máximo permitido (16) para
                 // evitar estouros de buffer

void setup()
{
 Serial.begin(9600);  // Inicia comunicação serial a 9600bps
 Serial.flush();      // Libera caracteres que estejam na linha
                      // Serial, deixando-a pronta para in/outs
  
  //configura os pinos dos servos como saída digital
  pinMode(servoOne,   OUTPUT);
  pinMode(servoTwo,   OUTPUT);
  pinMode(servoThree, OUTPUT);
  pinMode(servoFour,  OUTPUT);
  pinMode(servoFive,  OUTPUT);
  pinMode(servoSix,   OUTPUT);
  
  
  //atribui os pinos do Arduino ao respectivo servo
  servo_one.attach(servoOne);
  servo_two.attach(servoTwo);
  servo_three.attach(servoThree);
  servo_four.attach(servoFour);
  servo_five.attach(servoFive);
  servo_six.attach(servoSix);
}

void loop()
{
 if(Serial.available() > 0)            //verifica se foi enviado um caractere para serial
 {                                  
  byte index = 0;                      //armazena a posição de um ponteiro para os
                                       //caracteres do vetor
                                       
  delay(100);                          //deixa o buffer encher
  byte numChar = Serial.available();   //atribui o numero de 
                                       //caracteres digitados
    
  if(numChar > 15) numChar = 15;       //evita o estouro do buffer
 
  while(numChar--) //executa até que numChar seja zero
  {
   buffer[index++] = Serial.read();   //le a serial e armazena no vetor
  } 
  splitString(buffer);                //chama a função splitString com buffer como parametro
 }
}

void splitString(char* data)
{
 Serial.println(" ");
 Serial.print("                  Data entered: ");
 Serial.println(data);
 Serial.println("....................................");
 Serial.print(">> ");
 char* parameter = data;                     //variavel para acessar os elementos do vetor data

 setPosition(parameter);                      // chama a funço parameter

for(int x=0; x<16; x++)
{
 buffer[x]='\0'; 
}

  Serial.flush();                     //libera caracteres que estejam na linha
                                      //serial, deixando-a pronta para in/outs
}

void setPosition(char* data)
{
 if((data[0] == 'a') || (data[0] == 'A'))  //verifica letra inicial (qual servo)
 {
  int Ans = strtol(data+1, NULL, 10);     //define Ans como numero na proxima parte do texto
  
  Ans = constrain(Ans,0,180);             //garante que Ans esteja entre 0 e 180
  servo_one.write(Ans);                   //atribui o grau da posição do eixo do servo
  Serial.print("Claw is set to: ");
  Serial.println(Ans);
 } 
 
 if((data[0] == 'b') || (data[0] == 'B'))
 {
  int Ans = strtol(data+1, NULL, 10);
  
  Ans = constrain(Ans,0,180);
  servo_two.write(Ans);
  Serial.print("Fist Rotate is set to: ");
  Serial.println(Ans);
 } 
 
 if((data[0] == 'c') || (data[0] == 'C'))
 {
  int Ans = strtol(data+1, NULL, 10);
  
  Ans = constrain(Ans,0,180);
  servo_three.write(Ans);
  Serial.print("Fist is set to: ");
  Serial.println(Ans);
 } 
 
 if((data[0] == 'd') || (data[0] == 'D'))
 {
  int Ans = strtol(data+1, NULL, 10);
  
  Ans = constrain(Ans,0,180);
  servo_four.write(Ans);
  Serial.print("Elbow is set to: ");
  Serial.println(Ans);
 } 
 
 if((data[0] == 'e') || (data[0] == 'E'))
 {
  int Ans = strtol(data+1, NULL, 10);
  
  Ans = constrain(Ans,0,180);
  servo_five.write(Ans);
  Serial.print("Shoulder is set to: ");
  Serial.println(Ans);
 } 
 
 if((data[0] == 'f') || (data[0] == 'F'))
 {
  int Ans = strtol(data+1, NULL, 10);
  
  Ans = constrain(Ans,0,180);
  servo_six.write(Ans);
  Serial.print("Base is set to: ");
  Serial.println(Ans);
 }
} // end setPosition
