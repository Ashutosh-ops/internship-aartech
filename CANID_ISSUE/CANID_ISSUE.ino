#include <Streaming.h>
#include <SPI.h>              //Library for using SPI Communicatio#include <mcp2515.h>          //Library for using CAN Communication
#include <mcp2515.h>
//#include <modbusDevice.h>
//#include <modbusRegBank.h>
//#include <modbusSlave.h>

//modbusDevice regBank;
//modbusSlave slave;

struct can_frame canMsg;
//struct can_filter canMsg2;
MCP2515 mcp2515(10);                 // SPI CS Pin 10
int arr[31], i, k;        // arr array is used for storing id of can module.
int decim = 0;
//int length = i;
int ff[8];
int s = 0, j, rem;

void setup() {
  //  regBank.setId(8); ///Set Slave ID
  //Add Analog Output registers 40001-40020 to the register bank
  //  regBank.add(40001);
  //  regBank.add(40002);
  //  regBank.add(40003);
  //  regBank.add(40004);
  //  regBank.add(40005);
  //  regBank.add(40006);
  //  regBank.add(40007);
  //  regBank.add(40008);
  //  regBank.add(40009);
  //  regBank.add(40010);
  //  regBank.add(40011);
  //  regBank.add(40012);
  //  regBank.add(40013);
  //  regBank.add(40014);
  //  regBank.add(40015);
  //  regBank.add(40016);
  //  regBank.add(40017);
  //  regBank.add(40018);
  //  regBank.add(40019);
  //  regBank.add(40020);

  /*
    Assign the modbus device object to the protocol handler
    This is where the protocol handler will look to read and write
    register data.  Currently, a modbus slave protocol handler may
    only have one device assigned to it.
  */
  //  slave._device = &regBank;

  // Initialize the serial port for coms at 9600 baud
  //  slave.setBaud(19200);

  SPI.begin();                       //Begins SPI communication
  Serial.begin(19200);                //Begins Serial Communication at 9600 baudrate

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode

}

void loop()
{
  //  regBank.set(40001, 0);
  //  regBank.set(40002, 0);
  //  regBank.set(40003, 0);
  //  regBank.set(40004, 0);
  //  regBank.set(40005, 0);
  //  regBank.set(40006, 0);
  //  regBank.set(40007, 0);
  //  regBank.set(40008, 0);
  //  regBank.set(40009, 0);
  //  regBank.set(40010, 0);
  //  regBank.set(40011, 0);
  //  regBank.set(40012, 0);
  //  regBank.set(40013, 0);
  //  regBank.set(40014, 0);
  //  regBank.set(40015, 0);
  //  regBank.set(40016, 0);
  //  regBank.set(40017, 0);
  //  regBank.set(40018, 0);
  //  regBank.set(40019, 0);
  //  regBank.set(40020, 0);

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // To receive data (Poll Read)
  {
    Serial << "================*______CAN BUS INITIALIZED_____*===============" << endl;
    //    Serial << ((canMsg.can_id)-2147483648)<<endl;
    //    Serial << (((canMsg.can_id)-2147483648), HEX)<<endl;

    //    dectobinary(canMsg.can_id);

    //    long resultid = 0;
    //    int p = 0;
    //    for (int i = 0; i <= 29; i++) {
    //      resultid = resultid + arr[i] * pow(2, p);
    //      p++;
    //    }
    //    resultid += 24;
    //        resultid = canMsg.can_id % 10000000;
    //    resultid += 4472656;
    //        if (2487754768 == canMsg.can_id) { //m
    //          resultid = 14482010;
    //        }
    //        else if(2219319424){ //8
    //          resultid = 04482080;
    //        }
    //    else if (2219319416) { //7
    //
    //    }
    //    else if (2219319408) { //6
    //
    //    }
    //    else if (2219319400) { //5
    //
    //    }
    //    else if (2219319392) { //4
    //
    //    }
    //    else if (2219319384) { //3
    //
    //    }
    //    else if (2219319376) { //2
    //
    //    }
    //    else if (2219319268) { //1
    //
    //    }

    String operat = String(canMsg.can_id, HEX);
    Serial << canMsg.can_id << endl; // Frame structured can id ////eg. 2147483647
    String ids = operat.substring(1);
    if (operat.charAt(0) == '8') {
      ids = '0' + ids;
    }
    else if (operat.charAt(0) == '9') {
      ids = '1' + ids;
    }
    Serial << "CANID: " << ids << endl;
    String senter = ids.substring(4);
    senter = ids.charAt(0) + senter;
    int idint = senter.toInt();

    if(12010 == idint){
      
    }
    
    int a  = canMsg.data[0]; // Byte0 : Fault Flag
    int b  = canMsg.data[1]; // Byte1 : Warning Flga
    int c  = canMsg.data[2]; // Byte2 : Module or System Volatge
    int d  = canMsg.data[3]; // Byte3 : Module or System Volatge, Volatge can be find by: ((Byte 2 * 256)+ Byte 3)* precision = System Volatge
    int e  = canMsg.data[4]; // Byte4 : Hight Temperature, 1'C precison offset at -45'C i.e -45'C = 0 (Byte4 + offset Value) = Hight Temp
    int f  = canMsg.data[5]; // Byte5 : Hight Cell Voltage, 0.01V precision offset at 0.5V i.e 0.5 V = 0 (Byte5 + offset Value) = High Cell Voltage
    int g  = canMsg.data[6]; // Byte6 : Average Cell Volatge 0.01V precision offset st 0.5V i.e 0.5V = 0 (Byte6 + offset Value) = Avg. Cell Volatge
    //*  int h  = canMsg.data[7];

    Serial << ":   " << a << "  " << b << "  " << c << "  " << d << "  " << e << "  " << f << "  " << g << endl << endl;

    for (int u = 0; u < 8; u++) {
      u[ff] = 0;
    }

    Serial << "/*_________Byte0__Fault Flag___________*/" << endl;
    j = a; s = 0;
    while (j > 0) {
      rem = j % 2;
      ff[s++] = rem;
      j /= 2;
    }

    if (1[ff]) {
      //      regBank.set(40001, 1[ff]);
      Serial << "Balancing active: Undefined" << endl; // LSB from 0th index
    }
    if (2[ff]) {
      //      regBank.set(40002, 2[ff]);
      Serial << "Low Module Voltage: < 18 V" << endl;
    }
    if (3[ff]) {
      //      regBank.set(40003, 3[ff]);
      Serial << "Reserved" << endl;
    }
    if (4[ff]) {
      //      regBank.set(40004, 4[ff]);
      Serial << "Cell Imbalance: > 0.20 V (difference between max-min cell)" << endl;
    }
    if (5[ff]) {
      //      regBank.set(40005, 5[ff]);
      Serial << "Low Temperature: < -40°C" << endl;
    }
    if (6[ff]) {

      Serial << "High Temperature: > 60°C" << endl;
    }
    if (77[ff]) {
      Serial << "Cell Voltage: > 2.9 V" << endl;
    }

    for (int u = 0; u < 8; u++) {
      u[ff] = 0;
    }

    Serial << endl;
    Serial << "/*_________Byte1__Warning Flag_________*/" << endl;
    j = b; s = 0;
    while (j > 0) {
      rem = j % 2;
      ff[s++] = rem;
      j /= 2;
    }
    if (1[ff]) {
      Serial << "Balancing active: Boolean, Active High" << endl; // LSB from 0th index
    }
    if (2[ff]) {
      Serial << "Low Module Voltage: < 36 V" << endl;
    }
    if (3[ff]) {
      Serial << "Reserved" << endl;
    }
    if (4[ff]) {
      Serial << "Cell Imbalance: > 0.15 V (difference between max-min cell)" << endl;
    }
    if (5[ff]) {
      Serial << "Low Temperature: < -30°C" << endl;
    }
    if (6[ff]) {
      Serial << "High Temperature: > 50°C" << endl;
    }
    if (7[ff]) {
      Serial << "Cell Voltage: > 2.85 V" << endl;
    }

    int ad1 = ((f / 100.0f) + 0.5) ;
    int ad2 = ((g / 100.0f) + 0.5) ;
    //    Serial << endl;
    //    ((c * 256 + d) * 0.1f)
    Serial << "Byte2+Byte3__System Voltage: " << (c * 256 + d) * 0.1f << "V" << endl << endl;
    //        regBank.set(40002, (word)(c * 256 + d) * 10.0f );
    Serial << "Byte4__Highest Temperature: " << e - 45 << "°C" << endl << endl;
    //        regBank.set(40003, (word)random(0,1500) );
    Serial << "Byte5__Highest cell voltage: " << f  << endl << endl;
    //        regBank.set(40003, (word)ad1*100);
    Serial << "Byte6__Average cell voltage: " << g  << endl << endl;
    //        regBank.set(40004, (word)ad2*100);
  }
  else {
    Serial << "MCP2515 Data Frame not received." << endl;
  }

  //  slave.run(); // Status applied__OK
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
