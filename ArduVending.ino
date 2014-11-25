
/*
                                        PROGRAMA DE CONTROLE DE VENDING MACHINE COM PAGAMENTO POR NFC
                    ESTE PROGRAMA FAZ PARTE DE UM TCC E NÃO PODE SER USADO COMERCIALMENTE SEM A AUTORIZAÇÃO DE SEU(S) AUTORE(S)
       
       **** Este trabalho está licenciado com uma Licença Creative Commons - Atribuição-NãoComercial-CompartilhaIgual 4.0 Internacional. ****
                                            http://creativecommons.org/licenses/by-nc-sa/4.0/
                                            
               ESTE PROGRAMA, TODAS AS SUAS VERSÕES E NOTAS ESTÃO DISPONÍVEIS NO ENDEREÇO: https://github.com/lmalmoreno/ArduVending
              
                                                     DESENVOLVIDO COM A IDE 1.0.5-r2
                                                      DESENVOLVIDO PARA ARDUINO UNO
                                                         CONCLUÍDO EM: 20/11/2014
                                                       OBRIGADO PELO SEU INTERESSE!
        

*/

// INÍCIO DO PROGRAMA

#include <Servo.h> // Biblioteca do servo
#include "SPI.h" // Biblioteca da comunicação SPI
#include "PN532_SPI.h" // Biblioteca do módulo NFC
#include "snep.h" // Biblioteca da base SNEP
#include "NdefMessage.h" // Biblioteca do protocolo NDEF

PN532_SPI pn532spi(SPI, 10); // Define os pinos da comunicação SPI
SNEP nfc(pn532spi); // Inicia a configuração SNEP para ler mensagens NDEF
uint8_t ndefBuf[128]; // Tamanho da memória alocada para receber a tabela NDEF (Cuidado ao modificar este valor, o módulo pode parar de responder!)

//-----------------//

//VARIAVEIS GLOBAIS//
// -- Declaração do Servo --
Servo servo1; // Declaração do servo
// -- Declaração de pinos --
int pinmotor = 0; // Pino variável para os motores
int pinsensor = A0; // Pino variável para os sensores
int ledpar = 2;  // Pino de LED de status
int ledNFC = 5;  // Pino de LED de status
int ledsens = 0;  // Pino variável de LED de status
int ledsens1 = A5;  // Pino de LED de status
int ledsens2 = A4;  // Pino de LED de status
int ledsens3 = A3;  // Pino de LED de status
// -- Variaveis de Dados --
String inData = ""; //Variável para acumular os dados da serial
String daTa = ""; //Variável com os dados pronto para uso
String cHave = "7WDt3AKJlB"; //Chave de pareamento (10 digitos alfanuméricos)
String preco = ""; // Variável de proço dos produtos
int leiturasensor = 0; // Váriavel de valor lido dos sensores
long previousMillis = 0; // Variável para comprar o tempo
// -- Variaveis de Verificação -- 
boolean verif = 0; // Variável que verifica se já foi pareado na execução
boolean verifP = 0; // Variavel de preco recebido
boolean verifFNFC = 0; // Variavel para falhas
boolean verifWNFC = 0; // Variavel para verificar quando o smartphone recebeu o valor
boolean verifTM = 0; // Verifica se o motor foi parado por estouro de tempo
//---------------//


void setup() 
    {
        Serial.begin(9600); // Habilita a comunicação serial com a velocidade de 9600
        pinMode(6,OUTPUT); // Pino dos sensores como saída
        pinMode(ledpar, OUTPUT); // Define o pino do LED de status como saída
        pinMode(ledNFC, OUTPUT); // Define o pino do LED de status como saída
        pinMode(ledsens1, OUTPUT); // Define o pino do LED de status como saída
        pinMode(ledsens2, OUTPUT); // Define o pino do LED de status como saída
        pinMode(ledsens3, OUTPUT); // Define o pino do LED de status como saída
        
        digitalWrite(ledpar, HIGH);   //
        digitalWrite(ledNFC, HIGH);   //    LIGA OS LEDS
        digitalWrite(ledsens1, HIGH); //    PARA EFETUAR 
        digitalWrite(ledsens2, HIGH); //       TESTE
        digitalWrite(ledsens3, HIGH); //
        delay(1000); // Aguarda 1 segundo
        digitalWrite(ledpar, LOW);   //    
        digitalWrite(ledNFC, LOW);   //    DESLIGA OS LEDS
        digitalWrite(ledsens1, LOW); //         TESTE
        digitalWrite(ledsens2, LOW); //       COMPLETO
        digitalWrite(ledsens3, LOW); //
        
    }

void loop() {
 
 //////////////////////////////// BLOCO DO PAREAMENTO ///////////////////////////////////
 while (verif == 0) // Enquanto não for feito o pareamento
 {
      while (Serial.available() > 0) //Enquanto tiver dados disponíveis na porta serial
        {
            char recieved = Serial.read(); //Escreve cada caracter por vez na variável "recieved"
            inData += recieved; //Adiciona os caracteres escritos na variável "recieved" na variavel inData
            if (recieved == '\n') //Se a quebra de linha (Enter) tiver sido escrita na variável recieved
            {
                String processString = inData; // Inicia o tratamento do dado recebido na serial copiando o que foi recebido para a variável processString
                processString.replace("\n", ""); // Procura no dado recebido o caractere de quebra de linha (\n) que não pode estar no dado final e apaga ele
                daTa = processString; // Após o tratamento do dado recebido copia ele para a variável daTa onde ele já está pronto para uso
                inData = ""; // Limpa a variável que acumula os dados da serial
            } 
         }
  
    //   if (millis() - previousMillis > 5000) // Se já faz mais de 5 segundos que enviou SP na serial
     //    {
     //      previousMillis = millis(); // Guarda o tempo em que SP foi escrito na serial
     //      Serial.println("SP"); // Escreve SP na serial informando que está pronto para parear
      //   }
          
       if(daTa == cHave) // Verifica se o dado que está em daTa é a chave de pareamento 
         {
           Serial.println("IP"); // Informa que foi pareado com sucesso
           verif = 1; // Seta o verif para informar que não é mais preciso efetuar o pareamento nesta execução
           digitalWrite(ledpar, HIGH); // Liga o LED indicando que o pareamento foi feito com sucesso
         }
       else
           if (daTa != "") // Se tiver dado na variável e ele não for igual a chave de pareamento
            {
              Serial.println("EP"); //Escreve EP na serial informando que não foi pareado
            }
       daTa = ""; // Apaga todos dados da variável
       
 } // FECHA PAREAMENTO
 
 /////////////////////////// BLOCO DA LEITURA DA SERIAL /////////////////////////////////
 
 while (Serial.available() > 0) //Enquanto tiver dados disponíveis na porta serial
        {
            char recieved = Serial.read(); //Escreve cada caracter por vez na variável "recieved"
            inData += recieved; //Adiciona os caracteres escritos na variável "recieved" na variavel inData
            if (recieved == '\n') //Se a quebra de linha (Enter) tiver sido escrita na variável recieved
            {
                String processString = inData; // Inicia o tratamento do dado recebido na serial copiando o que foi recebido para a variável processString
                processString.replace("\n", ""); // Procura no dado recebido o caractere de quebra de linha (\n) que não pode estar no dado final e apaga ele
                daTa = processString; // Após o tratamento do dado recebido copia ele para a variável daTa onde ele já está pronto para uso
                inData = ""; // Limpa a variável que acumula os dados da serial
            } 
         }
 
 /////////////////////////// FECHA LEITURA SERIAL ///////////////////////////////////
 

 
 ////////////////////////// BLOCO DAS COMPARAÇÕES////////////////////////////////////
           
 if (daTa.length() > 0) // Se existir algum dado pronto para uso
    {
     
         if(daTa == "AM1") // Aciona Motor 1
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          verifTM = 0; // Declara que ainda não houve estouro de tempo
          analogWrite(3,250); // Ativa emissor dos sensores com PWM
          pinmotor = 4; // Declara o pino do motor 1 
          pinsensor = 2; // Declara o pino do sensor 1
          ledsens = A5; // Declara a porta do LED do sensor 1
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Motor(); // Chama void motores  
      }
      else
       if(daTa == "AM2") // Aciona Motor 2
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          verifTM = 0; // Declara que ainda não houve estouro de tempo
          analogWrite(3,250); // Ativa emissor dos sensores com PWM
          pinmotor = 7; // Declara o pino do motor 2 
          pinsensor = 1; // Declara o pino do sensor 2
          ledsens = A4; // Declara a porta do LED do sensor 2
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Motor(); // Chama void motores 
      }
      else
         if(daTa == "AM3") // Aciona Motor 3
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          verifTM = 0; // Declara que ainda não houve estouro de tempo
          analogWrite(3,250); // Ativa emissor dos sensores com PWM
          pinmotor = 8; // Declara o pino do motor 3
          pinsensor = 0; // Declara o pino do sensor 3
          ledsens = A3; // Declara a porta do LED do sensor 3
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Motor(); // Chama void motores 
      }
      else
         if(daTa == "TM1") // Teste Motor 1
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          pinmotor = 4; // Declara o pino do motor 1
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Teste(); // Chama void testes
          
      }
      else
         if(daTa == "TM2") // Teste Motor 2
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          pinmotor = 7; // Declara o pino do motor 2
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Teste(); // Chama void testes
      }
      else
         if(daTa == "TM3") // Teste Motor 3
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          pinmotor = 8; // Declara o pino do motor 3
          previousMillis = millis(); // Armazena o valor atual de tempo para posterior comparação
          Teste(); // Chama void testes
      }
       else
         if(daTa == "AAAA")
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          verifFNFC = 0; // Confirma que o valor do produto não foi recebido
          NFC(); // Entra na rotina do NFC
      }
       else
         if(daTa == "7WDt3AKJlB")   //// MODIFICADO
      {
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada      //// MODIFICADO
          Serial.println("IP");
      }
      else
         daTa = ""; // Apaga os dados para ser usada novamente
         
    delay (50); // Delay para terminar tarefas pendentes
     
   }  
           

  // FECHA LOOP

} 

////////////////////////////// BLOCO DAS FUNÇÕES ///////////////////////////////////

void NFC()
{
  
// INICIO DO NFC

// Envio do valor para o smartphone
  digitalWrite(ledNFC, HIGH); // Acende o LED indicando que ativou o NFC
  if (verifWNFC == 0) // Verifica se o smartphone ja recebeu o valor do produto
 {   
    if (verifFNFC == 0) // Verifia se houve falha na leitura para não solicitar o valor novamente
        {
            Serial.println("BBBB"); //Solicita o valor do produto
        }   
    while (verifP == 0) // Verifica se o valor ja foi recebido pela serial
    {
          while (Serial.available() > 0) //Enquanto tiver dados disponíveis na porta serial
                {
                    char recieved = Serial.read(); //Escreve cada caracter por vez na variável "recieved"
                    inData += recieved; //Adiciona os caracteres escritos na variável "recieved" na variavel inData
                    if (recieved == '\n') //Se a quebra de linha (Enter) tiver sido escrita na variável recieved
                    {
                        String processString = inData; // Inicia o tratamento do dado recebido na serial copiando o que foi recebido para a variável processString
                        processString.replace("\n", ""); // Procura no dado recebido o caractere de quebra de linha (\n) que não pode estar no dado final e apaga ele
                        delay (50); // Delay para terminar tarefas pendentes
                        preco = processString; // Após o tratamento do dado recebido copia ele para a variável preco onde ele já está pronto para uso
                        delay (50); // Delay para terminar tarefas pendentes
                        inData = ""; // Limpa a variável que acumula os dados da serial
                        verifP = 1; // Confirma recebimento do valor pela serial
                    } 
                 }
    }
    
    
    if (verifFNFC == 0) // Se o valor foi recebido pelo arduino
        {
            Serial.println("DDDD"); // Confirma recebimento do valor do produto
            verifFNFC = 1; // Seta variavél para não solicitar o valor novamente
            delay(50); // Delay para terminar tarefas pendentes
        }
        
   // Envio do valor
    NdefMessage message = NdefMessage(); // Prepara variáveis internas para receber valor a ser enviado
    delay(10); // Delay para terminar tarefas pendentes
    message.addTextRecord(preco); // Grava valor a ser enviado na variável
    delay(10); // Delay para terminar tarefas pendentes
    int messageSize = message.getEncodedSize(); // Determina o tamanho da mensagem
    delay(10); // Delay para terminar tarefas pendentes
    message.encode(ndefBuf); // Monta tabela NDEF que está pronta para envio
    delay(10); // Delay para terminar tarefas pendentes
      
                if (0 >= nfc.write(ndefBuf, messageSize)) // Se tabela enviada estiver vazia
                    { 
                          // Falha
                          // Este é decorrente de uma falha de sincronia entre o Arduino e o Módulo, para corrigir esse erro é necessário remontar a tabela
                          NFC(); // Volta na rotina do NFC corrigindo o erro
                    } 
                else 
                    {   
                          // Sucesso
                          preco = ""; // Limpa a variável preco
                          verifP = 0; // Reseta a veriavel de valor recebido pela serial para receber um novo valor
                          verifFNFC = 0; // Reseta para solicitar o valor novamente
                          verifWNFC = 1; // Confirma que o smartphone recebeu o valor do produto
                          delay(1050); // Delay para terminar tarefas pendentes
                    }
            
 }
 
 
  // Leitura da autenticação de pagamento
 if (verifWNFC == 1) // Verifica se o smartphone ja recebeu o valor do produto
   {  
           
             int msgSize = nfc.read(ndefBuf, sizeof(ndefBuf)); // Prepara e recebe a tabela NDEF na variável
             if (msgSize > 0) // Se a tabela NDEF foi recebida   
                 {
                      NdefMessage msg  = NdefMessage(ndefBuf, msgSize); // Inicia o tratamento da mensagem NDEF
                      NdefRecord record = msg.getRecord(0); // Copia a tabela NDEF para uma variável
                      int payloadLength = record.getPayloadLength(); // Copia somente o Payload para uma variável apenas para medir seu tamanho
                      byte payload[payloadLength]; // Mede o tamanho do Payload
                      record.getPayload(payload); // Copia novamente o Payload agora para uma variável manipulável
                      int startChar = 0; // Inicia uma váriavel para tratar o Payload
                      if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "T") // Ignora a foramtação da língua
                        {
                            startChar = payload[0] + 1; // Padrões de formatação de lingua do NDEF para mais informações ver especificações do NDEF
                        } 
          
                      else if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "U") // Ignora qualquer URL
     
                        {
                            startChar = 1; // Padrões de URL do NDEF para mais informações ver especificações do NDEF
                        }
                          
      
                      String payloadAsString = ""; // Inicia a variável payloadAsString vazia
                      for (int c = startChar; c < payloadLength; c++) // Grava Payload na variável
                              {
                                   payloadAsString += (char)payload[c]; // Armazena os dados de Payload lidos na variavel payloadAsString
                              }
          
        
                      if(payloadAsString == "pagamentoautenticado") // Compara os dados da Payload e verifica se pagamento foi autenticado
                              {
                                  Serial.println("HHHH"); // Se autenticado envia confirmação
                                  verifWNFC = 0; // Reseta variável para um novo ciclo
                              }
                      else
                              {
                                  Serial.println("LLLL"); // Se não envia o saldo insulficiente
                               } 
            
                delay(100); // Delay para terminar tarefas pendentes
                }
                
                
            else 
                {
                   Serial.println("ENFC"); // Caso erro na leitura, informa tablet
                   NFC(); // Volta na rotina do NFC corrigindo o erro
                }
  }
    digitalWrite(ledNFC, LOW); // Apagao LED indicando que desativou o NFC
    delay(50); // Delay para terminar tarefas pendentes

    
// FIM DO NFC

}

void Teste()
{
  // INICIO TESTES
  
  servo1.attach(pinmotor); // Define o pino do servo
  servo1.write(180); // Liga o servo motor

  if (millis()- previousMillis > 10000) // Se passar 10 segundos
      {
         servo1.detach(); // Desliga o servo
         Serial.println("IT"); // Informa que o teste está concluido
      }
      else
      {  
         servo1.write(180); // Liga o servo motor
         Teste(); // Retorna para a rotina de testes
      }
      
   // FIM TESTES
}

void Motor()
{
  
 // INICIO DO MOTOR 
  
  servo1.attach(pinmotor); // Define o pino do servo
  servo1.write(180); // Liga o servo motor
  leiturasensor = analogRead(pinsensor); // Armazena o valor do sensor na variável
  delay(10);
  if (leiturasensor >= 200) // Se o valor for maior ou igual 200 
      {
        digitalWrite(ledsens, HIGH); // Ativa o LED indicando que o sensor foi ativado
        servo1.detach(); // Desliga o servo motor
        digitalWrite(6,LOW); // Desliga emissor dos sensores
        Serial.println("JJJJ"); // Informa que o produto foi dispensado com sucesso
        delay(500);
        digitalWrite(ledsens, LOW); // Desativa o LED 
        loop();
      }
  else // Se não
      {
        
        if (millis()- previousMillis > 5000) // Se passar 5 segundos com o valor do sensor menor que 200
          {
             servo1.detach(); // Desliga o servo
             digitalWrite(6,LOW); // Desliga emissor dos sensores
             Serial.println("PPPP"); // Informa que houve erro na dispensa do produto
             verifTM = 1; // Seta a verificação de estouro de tempo
          }
          else
          {
            if (verifTM == 0) // Se não parou por estouro de tempo
                {  
                    Motor(); // Retorna para o void ligar
                }
          }
    
    }
  
 // FIM DO MOTOR 
 
}

///////////////////////////// FECHA BLOCO DAS FUNÇÕES /////////////////////////////

