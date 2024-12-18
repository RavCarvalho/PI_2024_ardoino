#include <WiFi.h>

//nome e senha da redes para conecxão inicial
const char *ssid = "OP";
const char *pw = "onepiece";

WiFiServer server(80);

// Botões pretos para alternativas
int BOTAO_A = 26;
int BOTAO_B = 14;
int BOTAO_C = 27;
//Botão para reset
int BOTAO_EN = 4;

//Botões coloridos referente aos jogadores azul e vermalho respectivamente
#define BTN_1 12  //Botão 1 conectado ao pino 4 do Arduino e ao GND
#define BTN_2 25  //Botão 2 conectado ao pino 5 do Arduino e ao GND

bool mensagemEnviada = false;

//???
IPAddress staticIP(192, 168, 43, 186);
IPAddress gateway(192, 168, 43, 151);   // Replace this with your gateway IP Addess
IPAddress subnet(255, 255, 255, 0);  // Replace this with your Subnet Mask
IPAddress dns(192, 168, 43, 151);   // Replace this with your DNS




void setup() {
  //Conecta com rede pré definida
  WiFi.begin(ssid, pw);
  Serial.begin(115200);
  
 //Pino com botão será entrada
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BOTAO_A, INPUT);
  pinMode(BOTAO_B, INPUT);
  pinMode(BOTAO_C, INPUT);
  pinMode(BOTAO_EN, INPUT);

//Verifica e retorna o estado de conexão com WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Conectado ao wifi");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  // Verifica e retorna conexão com o cliente (Godot)
  if (client) {
    client.print("Godot esta conectado a ESP32");
    Serial.println("ESP32 esta conectado ao godot");
    delay(500);
    while (client.connected()) {
      mensagemEnviada = false;
      
      //Condições para envio de msg dos botoes de jogadores 
      if ((digitalRead(BTN_1) == LOW && digitalRead(BTN_2) == HIGH) && mensagemEnviada == false) {  //Botão 1 pressionado
        client.println("B1 ");
        mensagemEnviada = true;
        delay(300);

      } else if ((digitalRead(BTN_1) == HIGH && digitalRead(BTN_2) == LOW) && mensagemEnviada == false) {  //Botão 2 pressionado
        client.println("B2 ");
        mensagemEnviada = true;
        delay(300
        );
      }

      // Condições de envio de msg para botões de alternativas
      // As alternativas, no godot, serrão reconhecidas como 0, 1 e 2, logo ios print serão vistos como L p/ letra e 0,1 ou 2 p representar a letra
      if (digitalRead(BOTAO_A) == 1  && mensagemEnviada == false)//Botão de alternativa A pressionado
      {
        client.println("L 0");
        mensagemEnviada = true;
        delay(300);
      }
 
      else if (digitalRead(BOTAO_B) == 1  && mensagemEnviada == false)//Botão de alternativa B pressionado
      {
        client.println("L 1");
        mensagemEnviada = true;
        delay(300);
      }
      
      else if (digitalRead(BOTAO_C) == 1  && mensagemEnviada == false) //Botão de alternativa C pressionado
      {
        client.println("L 2");
        mensagemEnviada = true;
        delay(300);
      } 
      
      else {
        mensagemEnviada == false;
      }
      


    }
  }//termina comandos para cliente

 //era pra ser a funçao de RESET?
  if (BOTAO_EN == 1 ) {
   // turn LED on:
   Serial.println("RESET");   
   delay(500);
 }
}
