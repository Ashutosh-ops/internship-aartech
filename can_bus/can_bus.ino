
#include <SPI.h>              //Library for using SPI Communicatio#include <mcp2515.h>          //Library for using CAN Communication
#include <mcp2515.h> 

struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10 
 
void setup() {
  
  
  SPI.begin();                       //Begins SPI communication
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate 
  
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
}

void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
     int a  = canMsg.data[0];         
     int b  = canMsg.data[1];       
     int c  = canMsg.data[2];
     int d  = canMsg.data[3];         
     int e  = canMsg.data[4];       
     int f  = canMsg.data[5];
     int g  = canMsg.data[6];         
     int h  = canMsg.data[7];       
     
       float i =( (b * 256 ) + c ) * 0.005 ;
       Serial.print("Voltage = ");
       Serial.println(i);

       float j =( (d * 256 ) + e ) * 0.0001 ;
       Serial.print("Highest voltage = ");
       Serial.println(j);

       float k =( (f * 256 ) + g ) * 0.0001 ;
       Serial.print("Average voltage = ");
       Serial.println(k);

       
      Serial.println(                                               );
      Serial.println("                        _-_-_-_-_-_-_-_CAN BUS INITIALIZED_-_-_-_-_-_-_-_            ");
      Serial.println(                                               ); 
      Serial.print("BYTE 0 : "); Serial.print(a);
      Serial.print(" ::: BYTE 1 : "); Serial.print(b);
      Serial.print(" ::: BYTE 2 : "); Serial.print(c);
      Serial.print(" ::: BYTE 3 : "); Serial.print(d);
      Serial.print(" ::: BYTE 4 : "); Serial.print(e);
      Serial.print(" ::: BYTE 5 : "); Serial.print(f);
      Serial.print(" ::: BYTE 6 : "); Serial.print(g);
      Serial.print(" ::: BYTE 7 : "); Serial.println(h);

      delay(1000);
        
     
   
//    Serial.println(                                               );
//    Serial.println(a);
//    Serial.println("data msg a");
//    Serial.println(a , HEX);
//    Serial.println(a , DEC);
//    Serial.println(a , BIN);
//    Serial.println(                                               );
    
    
//    Serial.print("######################################");
//
//    
//    Serial.println(                                               );
//    Serial.println("data msg b");
//    Serial.println(b);
//    Serial.println(b , HEX);
//    Serial.println(b , DEC);
//    Serial.println(b , BIN);

   

  }
    
}            
