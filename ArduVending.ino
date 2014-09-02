//IDE 1.05
//TCC ENGENHENHARIA ELÉTRICA 2014

int serIn; //Variável para armazenar a leitura da serial

void setup(){
  Serial.begin(9600); //Inicialização da porta serial
  
}

void loop(){
  
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


