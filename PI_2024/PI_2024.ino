int BOTAO2 = 0;//Botão pequeno
int BOTAO3 = 0;//Botão pequeno
int BOTAO4 = 0;//Botão pequeno
int mensagem1 = 0;
int mensagem2 = 0;
int botaoA = 0 ;
int botaoB = 0 ;
int botaoC = 0 ;


int checagem[5] = {0,0,0,0,0};
bool check = false;
bool mensagemEnviada = false;

#define LED_1 33  //Led 1 conectado ao pino 2 do Arduino e ao GND com resistor de 220 ohms
#define LED_2 13  //Led 2 conectado ao pino 3 do Arduino e ao GND com resistor de 220 ohms
#define BTN_1 12  //Botão 1 conectado ao pino 4 do Arduino e ao GND
#define BTN_2 25  //Botão 2 conectado ao pino 5 do Arduino e ao GND

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
 
  Serial.begin(115200);
  pinMode(14, INPUT);//Pino com botão será entrada
  pinMode(27, INPUT);
  pinMode(26, INPUT);//

  
}

void loop() {
  mensagemEnviada = false;
  if (digitalRead(BTN_1) == LOW && digitalRead(BTN_2) == HIGH) {  //Botão 1 pressionado
    light(1);
    
  } else if (digitalRead(BTN_1) == HIGH && digitalRead(BTN_2) == LOW) {  //Botão 2 pressionado
    
    light(2);
    
  }

  BOTAO2 = digitalRead(14);
  BOTAO3 = digitalRead(27);
  BOTAO4 = digitalRead(26);

  if (BOTAO2 == 1)
  {
    botaoA = 1;
    botaoB = 0;
    botaoC = 0;
//    Serial.println("A");
//    SerialBT.println("A"); 
    delay(200);
  }
  else if (BOTAO3 == 1)
  {
    botaoA = 0;
    botaoB = 1;
    botaoC = 0;
//    Serial.println("B");
//    SerialBT.println("B"); 
    delay(200);
  }
  else if (BOTAO4 == 1){
    botaoA = 0;
    botaoB = 0;
    botaoC = 1;
//    Serial.println("C");
//    SerialBT.println("C"); 
    delay(200);
  }else{
     botaoA = 0 ;
     botaoB = 0 ;
     botaoC = 0 ;
  }
  //        inicia envio de sinais
        int leitura[5] = {mensagem1,mensagem2,botaoA,botaoB,botaoC};
        for(int i = 0; i < 5; i++){

            Serial.println(leitura[i]);
            Serial.println(checagem[i]);
            if (leitura[i] != checagem[i]){
              check = false;
              break;
            }else{
              check = true;
            }
          }

        if (check == false ){
          Serial.println("LINDÃO----------");
          if (mensagem1 == 1 and mensagem2 == 0){
            Serial.println("botao1");
            
          }

          else if (mensagem1 == 0 and mensagem2 == 1){
            Serial.println("botao2");
            
          }
          else if ((botaoA ==1 and botaoB ==0) and botaoC == 0){
            Serial.println("A");
            
          }
          }else if ((botaoA ==0 and botaoB ==1) and botaoC == 0){
            Serial.println("B");
          
          }else if ((botaoA ==0 and botaoB ==0) and botaoC == 1){
            Serial.println("C");
            
          }




          for(int i = 0; i < 5; i++){


            checagem[i] = leitura[i];
          }

  }


void light(int led) {
  for (int i = 0; i < 30; i++) {
    if (led == 1) {
      digitalWrite(LED_1, !digitalRead(LED_1));
      if (!mensagemEnviada) {
        Serial.println("botao1");
        mensagemEnviada = true;
        
      }
    } else {
      digitalWrite(LED_2, !digitalRead(LED_2));
      if (!mensagemEnviada) {
        Serial.println("botao2");
        mensagemEnviada = true;
      }
    }
    delay(50);
  }
  lightTest();


}

void lightTest() {
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  delay(300);
  digitalWrite(LED_1, HIGH);
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_1, !digitalRead(LED_1));
    digitalWrite(LED_2, !digitalRead(LED_2));
    delay(50);
  }
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  
}
