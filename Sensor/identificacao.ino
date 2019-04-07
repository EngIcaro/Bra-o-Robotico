#include <LiquidCrystal.h>
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define trigger_pin 6
#define echo_pin 7

//Define pinos para led RGB
#define red_pin 12
#define green_pin 11
#define blue_pin 10

//Define pino para o LDR
#define ldr_pin A0

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
Ultrasonic ultrasonic(trigger_pin, echo_pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT); 
  pinMode(13, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(13, LOW);
  lcd.begin(16, 2);
  //Serial.begin(9600);
}

void loop() {
  lcd.clear();
  lcd.print("Aguardando");
  lcd.setCursor(0, 1);
  lcd.print("cubo...");
  
  if (distance() < 7){
    // Eh pq foi colocado um cubo na frente
    char color = identify_color();
    delay(30000);
  //  send_color_to_arm(color);
    //wait_response();
  }
  delay(500);
}

float distance() {
  float distance_cm;
  long microsec = ultrasonic.timing();
  distance_cm = ultrasonic.convert(microsec, Ultrasonic::CM);
  return distance_cm;
}

void setColor(int red_value, int green_value, int blue_value) {
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}

char identify_color() {
  lcd.clear();
  lcd.print("Identificando");
  lcd.setCursor(0, 1);
  lcd.print("cor...");
  delay(2000);
  
  // Red
  setColor(255, 0, 0);
  float aux = 0;
  for(int i = 0; i < 10; i++){
    delay(300);
    aux += analogRead(ldr_pin);
  }
  Serial.println("R:");
  Serial.println(aux);
  float ldr_red_value = aux/10;
  delay(500);
  
  // Green
  setColor(0, 255, 0);
  aux = 0;
  for(int i = 0; i < 10; i++){
    delay(300);
    aux += analogRead(ldr_pin);
  }
  Serial.println("G:");
  Serial.println(aux);
  float ldr_green_value = aux/10;
  delay(500);

  // Blue
  setColor(0, 0, 255);  
  aux = 0;
  for(int i = 0; i < 10; i++){
    delay(300);
    aux += analogRead(ldr_pin);
  }
  Serial.println("B:");
  Serial.println(aux);
  float ldr_blue_value = aux/10;
  delay(500);

  // Off
  setColor(0, 0, 0);

  aux = max(ldr_red_value, ldr_green_value);
  aux = max(aux, ldr_blue_value);

  Serial.print("R: ");
  Serial.print(ldr_red_value);
  Serial.print("G: ");
  Serial.print(ldr_green_value);
  Serial.print("B: ");
  Serial.println(ldr_blue_value);
  Serial.print("Aux: ");
  Serial.println(aux);
  
  lcd.clear();          //limpa o display do LCD.     
  lcd.print("Cor do cubo:");  //imprime a string no display do LCD.
  lcd.setCursor(0, 1);

  if(aux == ldr_red_value){    
    lcd.print("Vermelho");  //imprime a string no display do LCD.
    digitalWrite(0, HIGH);
    delay(200);
    digitalWrite(0, LOW);
    
    delay(500);
    return 'R';
  }
  else if(aux == ldr_green_value){
    lcd.print("Verde");
    digitalWrite(1, HIGH);
    delay(200);
    digitalWrite(1, LOW);
    
    delay(500);
    return 'G';
  }
  else {
    lcd.print("Azul");
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    
    delay(500);
    return 'B';
  }
}

void send_color_to_arm(char color) {
  Serial.print("Enviou a cor: ");
  Serial.println(color);

  Serial.write(color);  //envia cor para braco
}

void wait_response() {
  lcd.clear();
  lcd.print("Aguardando");
  lcd.setCursor(0, 1);
  lcd.print("retirada...");
  Serial.println("Esperando");
  
  //loop esperando braco acabar
  while(!Serial.available()); //enquanto nao receber nada, espera
  char response = Serial.read(); //leitura da resposta no buffer, indicando que braco acabou
  
  Serial.println("passeio do while");
  //delay(5000);
}


