 #include <Servo.h>

//-------- Variables ------------------------
int mode = 0;
bool stateChangeFlag = 0;
bool countResetFlag = 0;
int reset = 0 ;
int counter_dog = 0;
int counterLimit_dog;
int counter_dog2 = 0;
int counter_cat,counterLimit_cat;
int dutyCycle_dog,dutyCycle_cat;
int resetTime = 2;

float timeInterval_dog,timeInterval_cat;

double CLK_DIVIDER_LIMIT = 50000;
double CLK_DIVIDER_COUNTER = 0;

const int BUFFER_SIZE = 15;
char buf[BUFFER_SIZE];

Servo servo1,servo2;

//--------------------------------------------- 

void dog_motor_movement(int dutyCycle_dog, int counterLimit_dog, int countResetFlag)
{

//TODO: get reset working, issue is that the counter continues the counting where it left and does not reset to zero. *********  
//--------- Clock Divider -------------------------- 
  if(CLK_DIVIDER_COUNTER < CLK_DIVIDER_LIMIT)
       {
          CLK_DIVIDER_COUNTER = CLK_DIVIDER_COUNTER + 1;
          //Serial.println(CLK_DIVIDER_COUNTER);
       }
       else if(CLK_DIVIDER_COUNTER == CLK_DIVIDER_LIMIT)
        {
          CLK_DIVIDER_COUNTER = 0;
            if(counter_dog < counterLimit_dog && countResetFlag == 0)
                {
                  counter_dog = counter_dog + 1;
                  Serial.println(counter_dog);
                }
         } 
//--------- (DOG)Motor Movement --------------------------    
  if(counter_dog == counterLimit_dog && countResetFlag == 0)
          {
            counter_dog = 0;
            Serial.println("Dog food Released.");
            //Serial.println(counterLimit_dog);
            servo1.write(dutyCycle_dog); //release food
            delay(1000);
            servo1.write(0); //stop food flow
          }
}

//--------------------------------------------------------- 

void cat_motor_movement(int dutyCycle_cat, int counterLimit_cat, int countResetFlag)
{
  
//--------- Clock Divider -------------------------- 

  if(CLK_DIVIDER_COUNTER < CLK_DIVIDER_LIMIT)
       {
          CLK_DIVIDER_COUNTER = CLK_DIVIDER_COUNTER + 1;
       }
       else if(CLK_DIVIDER_COUNTER == CLK_DIVIDER_LIMIT)
        {
          CLK_DIVIDER_COUNTER = 0;
            if(counter_cat < counterLimit_cat && countResetFlag == 0)
                {
                  counter_cat = counter_cat + 1;
                }
         }  
           
//--------- (CAT)Motor Movement --------------------------    

  if(counter_cat == counterLimit_cat && countResetFlag == 0)
          {
            counter_cat = 0;
            Serial.println("Cat food Released.");
            //Serial.println(counterLimit_ca);
            servo1.write(dutyCycle_cat); //release food
            delay(1000);
            servo1.write(0); //stop food flow
          }
}
//---------------------------------------------------------

int arrayConcat (String array, int arrayStart, int dataLength) 
{  
    int dummy = 0;
    int dest = 0;
    for (int i = 0; i < dataLength; i++) 
    {
        // first part subtracts 48 to maintain correct character value
        //second part ensures all bits are accounted for (ex. 1000 for 1234)
        dummy = (array[i + arrayStart] - 48) * pow(10, dataLength - i - 1); 
        dest = dest + dummy;
    }
    return dest;
}
//-----------------------------------------------------------

void setup() 
{
  
//--------- Analog Pins - Servo(s) -----------------------------  
    
      servo1.attach(9);
      servo2.attach(8);
      servo1.write(0); //ensure initial position 
      
//--------- Serial Communication ------------------------ 
    
      Serial.begin(9600);
      
}

void loop() 
{

//-------serial communication------------------------------------------------ 
   if (Serial.available() > 0) //characters coming in
   {

      // read the incoming bytes: 010012500250
      int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);

      // prints the received data
      Serial.println("I received: ");
      for(int i = 0; i < rlen; i++)
      Serial.print(buf[i]);
      
      reset = arrayConcat(buf, 0, 1); //1 char
      mode = arrayConcat(buf, 1, 1);  //1 char
      timeInterval_dog = arrayConcat(buf, 2, 3); //3 char
      dutyCycle_dog = arrayConcat(buf, 5, 2); // 2 char 
      timeInterval_cat = arrayConcat(buf, 7, 3);; //3 char
      dutyCycle_cat = arrayConcat(buf, 10, 2);; // 2 char

      counterLimit_dog = timeInterval_dog * 60;
      counterLimit_cat = timeInterval_cat * 60; //minutes to seconds conversion

      Serial.println("");
      Serial.print("Reset = ");
      Serial.println(reset);

      Serial.print("Mode = ");
      Serial.println(mode);

      Serial.print("Dog Time Interval = ");
      Serial.println(counterLimit_dog);

      Serial.print("Dog Duty Cycle = ");
      Serial.println(dutyCycle_dog);

      Serial.print("Cat Time Interval = ");
      Serial.println(counterLimit_cat);

      Serial.print("Cat Duty Cycle = ");
      Serial.println(dutyCycle_cat);

      counter_dog = 0;
      counter_cat = 0;
      stateChangeFlag = 0;
  
  //-----------------------------------------------------------------------------
  
      while (!stateChangeFlag)
      {
      switch(mode)
          {
            case 1: //97(decimal = 01100001(binary) = a(ascii)

                    while(!reset && !Serial.available())
                    {
                      
                    dog_motor_movement(dutyCycle_dog,counterLimit_dog,reset);
                    cat_motor_movement(dutyCycle_cat,counterLimit_cat,reset);
                    
                    }
                    
                    stateChangeFlag = 1; //breaks out of the switch case
        
            break; 
              
            case 2:
                  Serial.println("Manual mode");
                  stateChangeFlag = 1; //breaks out of the switch case
            break;
    
            case 3:
    
                 Serial.println("-----------------------------------------------------------------");
                 Serial.println("Hi, Enter feeding mode: (0 = Automatic, 1 = manual)");
                 stateChangeFlag = 1;
            break;
              
            default:
                 
                  Serial.println("Please try again.");
                  stateChangeFlag = 1; //breaks out of the switch case
                  
            break;
            
          }
       }   
   }
}
