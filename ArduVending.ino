//IDE 1.05
//TCC ENGENHENHARIA ELÉTRICA 2014

//INICIALIZAÇÃO NFC//

#include "SPI.h"
#include "PN532_SPI.h"
#include "snep.h"
#include "NdefMessage.h"

PN532_SPI pn532spi(SPI, 10);
SNEP nfc(pn532spi);
uint8_t ndefBuf[128];

//-----------------//

//VARIAVEIS GLOBAIS//
// -- Variaveis de Dados
String inData = ""; //Variável para acumular os dados da serial
String daTa = ""; //Variável com os dados pronto para uso
String cHave = "7WDt3AKJlB"; //Chave de pareamento (10 digitos alfanuméricos)
String preco = "";
long previousMillis = 0; // Variável para comprar o tempo
// -- Variaveis de Verificação -- 
boolean verif = 0; // Variável que verifica se já foi pareado na execução
boolean verifP = 0; // Variavel de preco recebido
boolean verifFNFC = 0; // Variavel para falhas
boolean verifWNFC = 0; // Variavel para verificar quando o smartphone recebeu o valor
//---------------//


void setup() {
    Serial.begin(9600); // Habilita a comunicação serial com a velocidade de 115200   
}

void loop() {
 
 // BLOCO DO PAREAMENTO 
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
  
       if (millis() - previousMillis > 5000) // Se já faz mais de 5 segundos que enviou SP na serial
         {
           previousMillis = millis(); // Guarda o tempo em que SP foi escrito na serial
           Serial.println("SP"); // Escreve SP na serial informando que está pronto para parear
         }
          
       if(daTa == cHave) // Verifica se o dado que está em daTa é a chave de pareamento 
         {
           Serial.println("IP"); // Informa que foi pareado com sucesso
           verif = 1; // Seta o verif para informar que não é mais preciso efetuar o pareamento nesta execução 
         }
       else
           if (daTa != "") // Se tiver dado na variável e ele não for igual a chave de pareamento
            {
              Serial.println("EP"); //Escreve EP na serial informando que não foi pareado
            }
       daTa = ""; // Apaga todos dados da variável
       
 } // FECHA PAREAMENTO
 
 //////////////////////////////////////////////////// BLOCO DA LEITURA DA SERIAL ////////////////////////////////////////////////////////
 
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
 
 ///////////////////////////////////////////////////// FECHA LEITURA SERIAL ////////////////////////////////////////////////////////////
 

 
 /////////////////////////////////////////////////////// BLOCO DAS COMPARAÇÕES//////////////////////////////////////////////////////////
           
 if (daTa.length() > 0)
    {
     
         if(daTa == "AM1")
      {
          Serial.println("AM1 - OK!");
          daTa = "";
      }
      else
       if(daTa == "AM2")
      {
          Serial.println("AM2 - OK!");
          daTa = "";
      }
      else
         if(daTa == "AM3")
      {
          Serial.println("AM3 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TM1")
      {
          Serial.println("TM1 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TM2")
      {
          Serial.println("TM2 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TM3")
      {
          Serial.println("TM3 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TI1")
      {
          Serial.println("TI1 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TI2")
      {
          Serial.println("TI2 - OK!");
          daTa = "";
      }
      else
         if(daTa == "TI3")
      {
          Serial.println("TI3 - OK!");
          daTa = "";
      }
      else
         if(daTa == "AL1")
      {
          Serial.println("AL1 - OK!");
          daTa = "";
      }
      else
         if(daTa == "AL2")
      {
          Serial.println("AL2 - OK!");
            daTa = "";
      }
      else
         if(daTa == "AL3")
      {
          Serial.println("AL3 - OK!");
          daTa = "";
      }
      else
         if(daTa == "LNFC")
      {
          // Serial.println("LNFC - OK!");
          daTa = ""; // Garante que a variavel daTa esteja limpa para ser usada
          verifFNFC = 0; // Confirma que o valor do produto não foi recebido
          NFC(); // Entra na rotina do NFC
      }
      else
         daTa = "";
    delay (100);
     
   }  
           
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

 
} // FECHA LOOP 

//////////////////////////////////////////////////////// BLOCO DAS FUNÇÕES ////////////////////////////////////////////////////////////

void NFC(){

 //ESCRITA DO VALOR ---------------------------------------------------------------------------------
 
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
                        preco = processString; // Após o tratamento do dado recebido copia ele para a variável preco onde ele já está pronto para uso
                        delay (50);
                        inData = ""; // Limpa a variável que acumula os dados da serial
                        verifP = 1; // Confirma recebimento do valor pela serial
                    } 
                 }
    }
    
    
    if (verifFNFC == 0)
        {
            Serial.println("DDDD"); // Confirma recebimento do valor do produto
            verifFNFC = 1;
        }
   
    NdefMessage message = NdefMessage();
    message.addTextRecord(preco);
      
    int messageSize = message.getEncodedSize();
    if (messageSize > sizeof(ndefBuf)) 
        {
             while (1) {
        }
    }

    message.encode(ndefBuf);
    if (0 >= nfc.write(ndefBuf, messageSize)) 
        {
              //Falha
         } 
    else 
        {   
              // Sucesso
              preco = ""; // Limpa a variável preco
              verifP = 0; // Reseta a veriavel de valor recebido pela serial para receber um novo valor
              verifFNFC = 0; // Reseta para solicitar o valor novamente
              verifWNFC = 1; // Confirma que o smartphone recebeu o valor do produto
        }
 }
 
 if (verifWNFC == 1) // Verifica se o smartphone ja recebeu o valor do produto
   {  
            // LEITURA DA CONFIRMAÇÃO -----------------------------------------------------------
 
             int msgSize = nfc.read(ndefBuf, sizeof(ndefBuf));
             if (msgSize > 0) 
    
       {
            NdefMessage msg  = NdefMessage(ndefBuf, msgSize);
       
            
            NdefRecord record = msg.getRecord(0);

            int payloadLength = record.getPayloadLength();
            byte payload[payloadLength];
            record.getPayload(payload); // Lendo os dados do NFC
        
     
            int startChar = 0;        
            if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "T") // Ignora a foramtaçãoda língua
          {
                startChar = payload[0] + 1;
          } 
          
          else if (record.getTnf() == TNF_WELL_KNOWN && record.getType() == "U") // Ignora URL
     
              {
                  startChar = 1;
              }
                          
      
        String payloadAsString = ""; // Inicia a variável payloadAsString vazia
        for (int c = startChar; c < payloadLength; c++) 
              {
                   payloadAsString += (char)payload[c]; // Armazena os dados de Payload lidos na variavel payloadAsString
              }
          
        
        if(payloadAsString == "pagamentoautenticado") // Verifica se pagamento foi autenticado
              {
                  Serial.println("HHHH"); // Se autenticado envia confirmação
              }
        else
              {
                   Serial.println("LLLL"); // Se não envia o saldo insulficiente
              } 
            
    // VOLTAR PARA LOOP -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      }    
     else 
         {
            Serial.println("ENFC"); // Caso erro na leitura, informa tablet
         }

    // ------------------------------------------------------------------------------------
  }
 
    delay(10);

// FIM DO NFC
}

void Teste(){
  
}

void Motor(){
  
}






///////////////////////////////////////////////////// FECHA BLOCO DAS FUNÇÕES /////////////////////////////////////////////////////////

