#include <SparkFun_VL6180X.h>
#include <SparkFun_TB6612.h>
#include <Wire.h>

#define AIN1 5
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 3
#define PWMB 9
#define STBY 6
const int offsetA = 1;
const int offsetB = 1;
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

#define VL6180X_ADDRESS 0x29
#define NEWVL6180X_ADDRESS_1  0x30  // first VL6180  
#define NEWVL6180X_ADDRESS_2  0x31

int enable1 = 9;  // enable for sensor1
int enable2 = 11;  // enable for sensor 2
int enable3 = 12;  // enable for sensor 3
VL6180xIdentification identification;

VL6180x sensor3(VL6180X_ADDRESS);
VL6180x sensor2(VL6180X_ADDRESS);  // create both sensors
VL6180x sensor1(VL6180X_ADDRESS);
char inputdata = 0;

    void setup()
    {
Serial.begin(9600);                      //Sets the baud rate for bluetooth pins 
Serial.print("CIRCUIT DIGEST\n");

pinMode(enable1, OUTPUT);  // set both pins to output
pinMode(enable2,OUTPUT);
pinMode(enable3,OUTPUT);


Wire.begin(); //Start I2C library
delay(100); // delay .1s
digitalWrite(enable1, HIGH);  // turn on sensor one and shut down sensor 2
digitalWrite(enable2,LOW);
digitalWrite(enable3,LOW);

sensor1.getIdentification(&identification); // Retrieve manufacture info from device memory

    if(sensor1.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
}; 

sensor1.VL6180xDefautSettings(); //Load default settings to get started.

    delay(1000); // delay 1s
sensor1.changeAddress(VL6180X_ADDRESS,NEWVL6180X_ADDRESS_1);  //  change address of sensor 1

    digitalWrite(enable2,HIGH);  // turn on sensor 2

sensor2.getIdentification(&identification); // Retrieve manufacture info from device memory

    if(sensor2.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE 2"); //Initialize device and check for errors
}; 

sensor2.VL6180xDefautSettings(); //Load default settings to get started.

    delay(1000); // delay 1s
sensor2.changeAddress(VL6180X_ADDRESS,NEWVL6180X_ADDRESS_2);  //  change address of sensor 1


    digitalWrite(enable3,HIGH);




sensor3.getIdentification(&identification); // Retrieve manufacture info from device memory

   if(sensor3.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE Sensor 3"); //Initialize device and check for errors
}; 

sensor3.VL6180xDefautSettings(); //Load default settings to get started.

    delay(500); // delay 1s
    }
   
    // código em repetição infinita do projeto;
    void loop()
    {
int left=sensor1.getDistance();
int front=sensor2.getDistance();
int right=sensor3.getDistance();

Serial.print("Distance measured sensor right (mm) = ");
Serial.println(right); 

Serial.print("Distance measured sensor left(mm) = ");
Serial.println(left);

Serial.print("Distance measured sensor front(mm) = ");
Serial.println(front);
 /*    
if (right>50) dir();




     else  if(front > 40) // se caso houver caminho livre a front ele segue esta lógica abaixo:
         {  
           // o uso dos quatro if´s abaixo dentro deste if são para o controle da dirigibilidade do robô,
           // a fim de mantê-lo seguindo a parede right em linha reta;  
           
           if((right > 27 && right < 37)||right>50) // se caso a distância da parede a right estiver entre 9 e 12 cm, o robô se
                                         // mantém em linha reta;
             {              
  motor1.drive( 125);
  motor2.drive( 125); 
  Serial.println("FORWARD 1");                                                        
             }
         
           if(right<50 && right >=30)  // se caso a distância da parede a right estiver maior ou igual a 13 cm, o robô aumenta
                             // sua velocidade do motor esquerdo para se aproximar da parede right;
             {
  motor1.drive( 100);
  motor2.drive( 125); 
  Serial.println("FORWARD 2");                             
             }
             
                 
           if(right <=20)   // se caso a distância da parede a right estiver menor ou igual a 8 cm, o robô aumenta
                             // sua velocidade do motor direito para se distanciar da parede right;
             {
  motor1.drive( 125);
  motor2.drive( 100); 
  Serial.println("FORWARD 3");                
             }
         }
         
             
    //   if(left <=50 && right>50 && front <=45) dir(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for maior que 20 cm e a distância
                                                            //a left for menor ou igual a 20 cm ele chama a função dir();  
           
    //   if(left >50 && right>50 && front <=45) dir(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for maior que 20 cm e a distância
                                                            //a left for maior que 20 cm ele chama a função dir();
       
     else  if(right <=50 && left>50 && front <=40) esq(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for menor ou igual a 20 cm e a distância
                                                            //a left for maior a 20 cm ele chama a função esq();
       
     else  if(right<=50 && left<=50 && front<=40) voltar(); //se caso a distância a front for menor ou igual a 8 cm,
                                                            //a distancia a right for menor ou igual a 20 cm e a distância
                                                            //a left for menor ou igual a 20 cm ele chama a função voltar();                              
 */
    }
       
    void esq() // função para fazer com que o robô gire 90º a left se caso não tiver saída a front e a right;
      {
       
 motor1.drive( 100);
  motor2.drive( -100);
  Serial.println("LEFT");
        delay(1200); 
        motor1.drive( 100);
  motor2.drive( 100);
   delay(2000);     
       
      }
   
    void dir() // função para fazer com que o robô gire 90º a right se caso não tiver saída a front ou a left;
      {
       
motor1.drive( 100);
  motor2.drive( 100);
   delay(1500);   
motor1.drive( -100);
motor2.drive( 100);  
Serial.println("RIGHT");         
        delay(1250);
         
               
      }
   
    void voltar() // função para fazer com que o robô gire 180º se caso não tiver saída a front, a right e a left;
      {
       
motor1.drive( -255);
motor2.drive( 255);  
Serial.println("U_TURN"); 
        delay(830);
        motor1.drive( 100);
  motor2.drive( 100);
   delay(1500); 
         
      } 
