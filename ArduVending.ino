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

//VARIAVEIS GERAIS//
String inData = ""; //Variável para acumular os dados da serial
String daTa = ""; //Variável com os dados pronto para uso
String cHave = "7WDt3AKJlB"; //Chave de pareamento (10 digitos alfanuméricos)
boolean verif = 0; // Variável que verifica se já foi pareado na execução
long previousMillis = 0; // Variável para comprar o tempo
//---------------//


void setup() {
    Serial.begin(115200); // Habilita a comunicação serial com a velocidade de 115200   
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
      Serial.println("LNFC - OK!");
      daTa = "";
  }
  else
     daTa = "";
     delay (100);
     
}  
           
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

 
} // FECHA LOOP 

