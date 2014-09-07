//IDE 1.05
//TCC ENGENHENHARIA ELÉTRICA 2014

String inData = ""; //Variável para acumular os dados da serial
String daTa = ""; //Variável com os dados pronto para uso
String cHave = "7WDt3AKJlBX8jdMz7IhlNTiC0PIxAacoPxvy3by2KE7g0cH0d0"; //Chave de pareamento (50 digitos alfanuméricos)
boolean verif = 0; // Variável que verifica se já foi pareado na execução
long previousMillis = 0; // Variável para comprar o tempo

void setup() {
    Serial.begin(9600); // Habilita a comunicação serial com a velocidade de 9600   
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
 
 // BLOCO DA LEITURA DA SERIAL
 
 // BLOCO DAS COMPARAÇÕES
           
} // FECHA LOOP 

