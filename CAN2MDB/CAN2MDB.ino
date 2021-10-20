//#include <Streaming.h>
#include <SPI.h>              //Library for using SPI Communicatio#include <mcp2515.h>          //Library for using CAN Communication
#include <mcp2515.h>  //can library
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

//#include <SoftwareSerial.h>
//
//SoftwareSerial mySerial(2, 3); // RX, TX

// Objects and References Declarations
modbusDevice regBank;
modbusSlave slave;
struct can_frame canMsg;

MCP2515 mcp2515(10);                 // SPI CS Pin 10

int arr[31], i, k;        // arr array is used for storing id of can module.
int decim = 0;
int ff[8];
int s = 0, j, rem;

void setup() {
  regBank.setId(8); ///Set Slave ID
  //Add Analog Output registers 40001-40020 to the register bank
  for (int i = 0; i <= 20; i++) {
    regBank.add(40000 + i);// 40000 to 49999
  }

  /*
    Assign the modbus device object to the protocol handler
    This is where the protocol handler will look to read and write
    register data.  Currently, a modbus slave protocol handler may
    only have one device assigned to it.
  */
  slave._device = &regBank;

  // Initialize the serial port for coms at 19200 baud
  slave.setBaud(19200);

  SPI.begin();                       //Begins SPI communication

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode

  regBank.set(40001, 0);

  regBank.set(40010, 0);
  regBank.set(40011, 0);
  regBank.set(40012, 0);
  regBank.set(40013, 0);
  regBank.set(40014, 0);
  regBank.set(40015, 0);
  regBank.set(40016, 0);
  regBank.set(40017, 0);
  regBank.set(40018, 0);
  regBank.set(40019, 0);
  regBank.set(40020, 0);
}
int kq = 32545;
void loop()
{
  if (!(regBank.get(40007) != 0)) {
    for (int i = 2; i <= 9; i++) {
      regBank.set(40000 + i, 0);
    }
  }

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    //    Serial << "================___CAN BUS INITIALIZED__===============" << endl;
    //    dectobinary(canMsg.can_id);

    //    long resultid = 0;
    //    int p = 0;
    //    for (int i = 0; i <= 29; i++) {
    //      resultid = resultid + arr[i] * (1 << p);
    //      p++;
    //    }
    //    resultid += 24;

    //    Serial << String(resultid, HEX);  // Frame structured can id ////2147483647
    //    String myString = String(resultid, HEX);

    String operat = String(canMsg.can_id, HEX);
    //    Serial << canMsg.can_id << endl; // Frame structured can id ////eg. 2147483647
    String ids = operat.substring(1);
    if (operat.charAt(0) == '8') {
      ids = '0' + ids;
    }
    else if (operat.charAt(0) == '9') {
      ids = '1' + ids;
    }
    //    Serial << "CANID: " << ids << endl;
    String senter = ids.substring(4);
    senter = ids.charAt(0) + senter;
    int idint = senter.toInt();

    if (12010 == idint) {
      regBank.set(40002, (word)idint );
      regBank.set(40003, (word)canMsg.data[0]);
      regBank.set(40004, (word)canMsg.data[1]);
      regBank.set(40005, (word)canMsg.data[2]);
      regBank.set(40006, (word)canMsg.data[3]);
      regBank.set(40007, (word)canMsg.data[4]);
      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
      //      int ad1 = ((f / 100.0f) + 0.5) ;
      //      int ad2 = ((g / 100.0f) + 0.5) ;
      regBank.set(40008, (word)f);
      regBank.set(40009, (word)g);
    }

    
//    else if (02010 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02020 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02030 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02040 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02050 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02060 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02070 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }
//    else if (02080 == idint) {
//      regBank.set(40002, (word)idint );
//      regBank.set(40003, (word)canMsg.data[0]);
//      regBank.set(40004, (word)canMsg.data[1]);
//      regBank.set(40005, (word)canMsg.data[2]);
//      regBank.set(40006, (word)canMsg.data[3]);
//      regBank.set(40007, (word)canMsg.data[4]);
//      int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
//      int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V
//      //      int ad1 = ((f / 100.0f) + 0.5) ;
//      //      int ad2 = ((g / 100.0f) + 0.5) ;
//      regBank.set(40008, (word)f);
//      regBank.set(40009, (word)g);
//    }


    //    int a  = canMsg.data[0]; // Byte0 : Fault Flag
    //    regBank.set(40003, (word)a );
    //    int b  = canMsg.data[1]; // Byte1 : Warning Flga
    //    regBank.set(40004, (word)b );
    //    int c  = canMsg.data[2]; // Byte2 : Module or System Volatge
    //    regBank.set(40005, (word)c);
    //    int d  = canMsg.data[3]; // Byte3 : Module or System Volatge, Volatge can be find by: ((Byte 2 * 256)+ Byte 3)* precision = System Volatge
    //    //    regBank.set(40004, (word)d );
    //    int e  = canMsg.data[4]; // Byte4 : Hight Temperature, 1'C precison offset at -45'C i.e -45'C = 0 (Byte4 + offset Value) = Hight Temp
    //    //    regBank.set(40005, (word)e );
    //    int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
    //    //    regBank.set(40006, (word)f );
    //    int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V = 0 (Byte6 + offset Value) = Avg. Cell Volatge
    //    //    regBank.set(40007, (word)g );
    //    //*  int h  = canMsg.data[7];
    //
    //    //    Serial << ":   " << a << "  " << b << "  " << c << "  " << d << "  " << e << "  " << f << "  " << g << endl << endl;
    //
    //    for (int u = 0; u < 8; u++) {
    //      u[ff] = 0;
    //    }
    //
    //    //    Serial << "/____Byte0Fault Flag____/" << endl;
    //    j = a; s = 0;
    //    while (j > 0) {
    //      rem = j % 2;
    //      ff[s++] = rem;
    //      j /= 2;
    //    }
    //    //    for (int i = 1; i < 8; i++) {
    //    //      regBank.set(40000 + i, i[ff]);  // Byte0's 7 bit info  (MSB-->LSB) and (LSB-->MSB)
    //    //    }
    //
    //    for (int u = 0; u < 8; u++) {
    //      u[ff] = 0;           // Reset the flag array.
    //    }
    //
    //    //    Serial << "/____Byte1Warning Flag____/" << endl;
    //    j = b; s = 0;
    //    while (j > 0) {
    //      rem = j % 2;
    //      ff[s++] = rem;
    //      j /= 2;
    //    }
    //
    //    //    for (int i = 1; i < 8; i++) {
    //    //      regBank.set(40010 + i, i[ff]);   // Byte1's 7 bit info (MSB-->LSB) and (LSB-->MSB)
    //    //    }
    //
    //
    //    int ad1 = ((f / 100.0f) + 0.5) * 100;
    //    int ad2 = ((g / 100.0f) + 0.5) * 100;
    //
    //    //    Serial << "Byte2+Byte3__System Voltage: " << (c * 256 + d) * 0.1f << "V" << endl << endl;
    //    regBank.set(40006, (word)d);
    //    //    Serial << "Byte4__Highest Temperature: " << e - 45 << "°C" << endl << endl;
    //    regBank.set(40007, (word)(e - 45));
    //    //    Serial << "Byte5__Highest cell voltage: " << ad1  << endl << endl;
    //    regBank.set(40008, (word)ad1);
    //    //    Serial << "Byte6__Average cell voltage: " << ad2  << endl << endl;
    //    regBank.set(40009, (word)ad2);
    //    regBank.set(40010, 0);
  }

  slave.run(); // Status applied__OK
  delay(100);

}

void dectobinary(__u32 n)
{
  for (i = 0; n > 0; i++)
  {
    arr[i] = n % 2;
    n = n / 2;
  }
}
