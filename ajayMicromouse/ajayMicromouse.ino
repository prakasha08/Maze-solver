/* Algoritmo Daileon – Resolvedor de Labirintos
    Criado por: Jaspion Lopes de Freitas
    Curso: Ciência da Computação
    Instituição: Faculdade Pitágoras Votorantim-Sorocaba
    */

    // definições e declarações de variáveis do código do robô resolvedor de labirintos;
   
    #define left_enable 11  // controla velocidade do motor esquerdo;
    #define right_enable 10  // controla velocidade do motor direito;        
    #define e1 6  // controla sentido de rotação do motor esquerdo;
    #define e2 7  // controla sentido de rotação do motor esquerdo;
    #define d1 9  //controla sentido de rotação do motor direito;
    #define d2 8  // controla sentido de rotação do motor direito;
 
int trigger_front = A3; // controls the impulse sent from the front sensor
int echo_front = A2; // check the pulse received from the front sensor
int trigger_left = A1;// controls the impulse sent from the front sensor
int echo_left = A0;// check the pulse received from the front sensor
int trigger_right = A5;// controls the impulse sent from the front sensor
int echo_right = A4;// check the pulse received from the front sensor

   
    // configuração dos tipos de entrada das variáveis declaradas;    
    void setup()
    {
        Serial.begin(115200);
        pinMode(trigger_front, OUTPUT); // saída de sinal do arduino do trigger_front
        pinMode(echo_front, INPUT);// entrada de sinal do arduino do echo_front
       
        pinMode(trigger_left, OUTPUT);// saída de sinal do arduino do trigger_front
        pinMode(echo_left, INPUT);// entrada de sinal do arduino do echo_front        
       
        pinMode(trigger_right, OUTPUT);// saída de sinal do arduino do trigger_front
        pinMode(echo_right, INPUT);// entrada de sinal do arduino do echo_front
       
        pinMode(left_enable, OUTPUT);// saída de sinal do arduino da velocidade do motor esquerdo
        pinMode(right_enable, OUTPUT);// saída de sinal do arduino da velocidade do motor direito
     
        pinMode(e1, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor esquerdo
        pinMode(e2, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor esquerdo
        pinMode(d1, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor direito
        pinMode(d2, OUTPUT);// saída de sinal do arduino do controle do sentido de rotação do motor direito      
        delay(3000);
    }
   
    // código em repetição infinita do projeto;
    void loop()
    {
     // declaração de variáveis utilizadas para controle do projeto;
     long duration_front, duration_left, duration_right, right, left, front;
     
     
     digitalWrite(trigger_front, LOW);  // é declarada as respectivas entradas e saídas de sinal do
     delayMicroseconds(2);               // sensor ultrassônico e armazenada pela variável do sensor
     digitalWrite(trigger_front, HIGH); // que converte a velocidade do som que é de 340 m/s ou  
     delayMicroseconds(5);               // 29 microsegundos por centímetro, como o sinal vai e volta
     digitalWrite(trigger_front, LOW);  // esse tempo é a metade sendo sensor= tempo/29/2 ;
     duration_front = pulseIn(echo_front, HIGH); // assim segue também nos outros dois sensores .
     front = duration_front/29/2;
     Serial.print("front ");
    Serial.println(front);
   
     digitalWrite(trigger_left, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_left, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_left, LOW);
     duration_left = pulseIn(echo_left, HIGH);
     left = duration_left/29/2;
     Serial.print("left ");
    Serial.println(left);
   
     digitalWrite(trigger_right, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_right, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_right, LOW);
     duration_right = pulseIn(echo_right, HIGH);
     right = duration_right/29/2;
     Serial.print("right ");
    Serial.println(right);
     
     analogWrite(left_enable, 0);  //bloco para inicializar as entradas com pulso 0 ou desligado;
     analogWrite(right_enable, 0); //
     analogWrite(e1, 0);            //
     analogWrite(e2, 0);            //  
     analogWrite(d1, 0);            //
     analogWrite(d2, 0);            //
     
       if(front > 6) // se caso houver caminho livre a front ele segue esta lógica abaixo:
         {  
           // o uso dos quatro if´s abaixo dentro deste if são para o controle da dirigibilidade do robô,
           // a fim de mantê-lo seguindo a parede right em linha reta;  
           
           if(right > 7 && right < 13) // se caso a distância da parede a right estiver entre 9 e 12 cm, o robô se
                                         // mantém em linha reta;
             {              
               analogWrite(left_enable, 120);
               analogWrite(right_enable, 120);
           
               digitalWrite(e1, HIGH);
               digitalWrite(e2, LOW);
               digitalWrite(d1, LOW);
               digitalWrite(d2, HIGH);                                                        
             }
         
           if(right >=13)  // se caso a distância da parede a right estiver maior ou igual a 13 cm, o robô aumenta
                             // sua velocidade do motor esquerdo para se aproximar da parede right;
             {
               analogWrite(left_enable, 130);
               analogWrite(right_enable, 120);
           
               digitalWrite(e1, HIGH);
               digitalWrite(e2, LOW);
               digitalWrite(d1, LOW);
               digitalWrite(d2, HIGH);                              
             }
             
                 
           if(right <=7)   // se caso a distância da parede a right estiver menor ou igual a 8 cm, o robô aumenta
                             // sua velocidade do motor direito para se distanciar da parede right;
             {
               analogWrite(left_enable, 120);
               analogWrite(right_enable, 130);
           
               digitalWrite(e1, HIGH);
               digitalWrite(e2, LOW);
               digitalWrite(d1, LOW);
               digitalWrite(d2, HIGH);                  
             }
         }
         
             
       if(left <=20 && right>20 && front <=5) dir(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for maior que 20 cm e a distância
                                                            //a left for menor ou igual a 20 cm ele chama a função dir();  
           
       if(left >20 && right>20 && front <=5) dir(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for maior que 20 cm e a distância
                                                            //a left for maior que 20 cm ele chama a função dir();
       
       if(right <=20 && left>20 && front <=4) esq(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for menor ou igual a 20 cm e a distância
                                                            //a left for maior a 20 cm ele chama a função esq();
       
       if(right<=20 && left<=20 && front<=5) voltar(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for menor ou igual a 20 cm e a distância
                                                            //a left for menor ou igual a 20 cm ele chama a função voltar();                              
 
    }
       
    void esq() // função para fazer com que o robô gire 90º a left se caso não tiver saída a front e a right;
      {
       
        analogWrite(left_enable, 120);
        analogWrite(right_enable, 120);
           
        digitalWrite(e1, LOW);
        digitalWrite(e2, HIGH);
        digitalWrite(d1, LOW);
        digitalWrite(d2, HIGH);
        delay(500);      
       
      }
   
    void dir() // função para fazer com que o robô gire 90º a right se caso não tiver saída a front ou a left;
      {
       
     
        analogWrite(left_enable, 120);
        analogWrite(right_enable, 120);
       
        digitalWrite(e1, HIGH);
        digitalWrite(e2, LOW);
        digitalWrite(d1, HIGH);
        digitalWrite(d2, LOW);            
        delay(400);
               
      }
   
    void voltar() // função para fazer com que o robô gire 180º se caso não tiver saída a front, a right e a left;
      {
       
        analogWrite(left_enable, 120);
        analogWrite(right_enable, 120);
           
        digitalWrite(e1, HIGH);
        digitalWrite(e2, LOW);
        digitalWrite(d1, HIGH);
        digitalWrite(d2, LOW);
        delay(500);
         
      } 
