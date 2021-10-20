#include <SPI.h>              //Library for using SPI Communicatio#include <mcp2515.h>          //Library for using CAN Communication
#include <mcp2515.h>

struct can_frame canMsg;
//struct can_filter canMsg2;
MCP2515 mcp2515(10);                 // SPI CS Pin 10
int arr[31], id[29], i, k;
int i1;
char hexaDeciNum[20];
int decim = 0;
//int length = i;

void setup() {

  SPI.begin();                       //Begins SPI communication
  Serial.begin(9600);                //Begins Serial Communication at 9600 baudrate

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode

  Serial.print("Frame CAN ID: ");
  Serial.println(canMsg.can_id);
  Serial.print("Frame CAN dlc: ");
  Serial.println(canMsg.can_dlc);
}

void loop()
{

  if (!mcp2515.readMessage(&canMsg)) {
    Serial.print("MCP2515::ERROR_OK: ");
    Serial.println(MCP2515::ERROR_OK);
  }
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    Serial.println(                                               );
    Serial.println("                        _-_-_-_-_-_-_-_CAN BUS INITIALIZED_-_-_-_-_-_-_-_            ");
    Serial.println(                                               );

    dectobinary(canMsg.can_id);
    //    printbinary(arr);

    //    hellofun();
    long resultid = 0;
    int p = 0;
    for (int i = 0; i <= 29; i++) {
      resultid = resultid + arr[i] * pow(2, p);
      p++;
    }
    resultid += 24;

    Serial.print("Frame CAN ID: ");
    
//    decToHexa(resultid);
    Serial.println(resultid.HEX); // Frame structured can id ////2147483647

    int a  = canMsg.data[0];
    int b  = canMsg.data[1];
    int c  = canMsg.data[2];
    int d  = canMsg.data[3];
    int e  = canMsg.data[4];
    int f  = canMsg.data[5];
    int g  = canMsg.data[6];
    int h  = canMsg.data[7];


    Serial.print(" ::: BYTE 0 : "); Serial.println(a);
    Serial.print(" ::: BYTE 1 : "); Serial.println(b);
    Serial.print(" ::: BYTE 2 : "); Serial.println(c);
    Serial.print(" ::: BYTE 3 : "); Serial.println(d);
    Serial.print(" ::: BYTE 4 : "); Serial.println(e);
    Serial.print(" ::: BYTE 5 : "); Serial.println(f);
    Serial.print(" ::: BYTE 6 : "); Serial.println(g);
    Serial.print(" ::: BYTE 7 : "); Serial.println(h);
  }
  delay(1000);

}


void hellofun() {
  for (int j = i - 3; j >= 0; j--)
  {
    //    Serial.print("  ");
    //    Serial.print(j);
    //    Serial.print("__");
    Serial.print(arr[j]);
  }
  Serial.println();
}

void dectobinary(__u32 n)
{
  for (i = 0; n > 0; i++)
  {
    arr[i] = n % 2;
    n = n / 2;
  }
}

void printbinary(int arr[])
{
  for (int j = i - 1; j >= 0; j--)
  {
    Serial.print(arr[j]);
  }
  Serial.println();
}

void decToHexa(long n)
{
    i1 = 0;
    while (n != 0) {
        int temp = 0;
 
        temp = n % 16;
 
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i1++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i1++;
        }
 
        n = n / 16;
    }
 
    for (int j = i1 - 1; j >= 0; j--)
        Serial.print(hexaDeciNum[j]);
}
