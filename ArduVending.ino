//IDE 1.05
//TCC ENGENHENHARIA ELÉTRICA 2014
//CHAVE 725673

int serIn; //Variável para armazenar a leitura da serial
char KEY = 01234;
int RKEY = 0;


void setup(){
  Serial.begin(9600); //Inicialização da porta serial
  
   Serial.println(KEY);
}

void loop(){
  
  //BLOCO DE PAREAEMENTO (COM ERROS)
  
  while(RKEY != KEY) // Enquanto a chave informada for diferente da chave na memória
  {
  Serial.println("SP"); //Escreve SP na serial informando que está pronto para parear
  delay (100);
   if(Serial.available()) //Se tiver dados na porta serial
    { 
      while (Serial.available()>0) //Enquanto tiver dados na serial 
        {
          RKEY = Serial.read(); //Armazena os dados lidos na variável RKEY
          Serial.write(RKEY);  //Escreve os dados armazenados na serial (Apenas Debug)
        }
      Serial.println(); //Imprime de acordo com ASCII
    }
    
     if (RKEY == KEY){
       Serial.println("IP"); //Escreve IP na serial informando que foi pareado com sucesso
    }
    else{
       Serial.println("EP"); //Escreve EP na serial informando que não foi pareado
       delay (1000);
    }
}
  
  
  
  
  if(Serial.available()) //Se tiver dados na porta serial
    { 
      while (Serial.available()>0) //Enquanto tiver dados na serial 
        {
          serIn = Serial.read(); //Armazena os dados lidos na variável serIn
          Serial.write(serIn);  //Escreve os dados armazenados na serial (Apenas Debug)
        }
      Serial.println(); //Imprime de acordo com ASCII
    }

delay(1000);

// Inicio das comparações

  if (serIn == 01)
    {
       // execução
    }

}


