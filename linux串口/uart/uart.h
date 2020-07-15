#ifndef __UART_H
#define __UART_H

#include <iostream>

#define buffLen 1024
#define rcvTimeOut 2

using namespace std;
struct uartStruct
    {
        string comPort;
        int BPS;
        int nBits; 
        char nEvent; 
        int nStop;
        uartStruct(string l_comPort = "/dev/ttyUSB0",\
                   int l_BPS = 115200,\
                   int l_nBits = 8,\
                   char l_nEvent = 'N',\
                   int l_nStop = 1)
        {
            comPort = l_comPort;
            BPS = l_BPS;
            nBits = l_nBits;
            nEvent = l_nEvent;
            nStop = l_nStop; 
        }
    };
class uartClass
{
  //  friend class NtripClient;
public:
    char rcv_buf[buffLen];
    bool initPort(uartStruct *uartPara);
    void readData();
    int sendDataTty(char *send_buf, int Len);
    void readDataTty();
private:
	int fdSerial = 0;
    int TimeOut;
    bool openPort(const char* comport);
    bool setOpt(int nSpeed, int nBits, char nEvent, int nStop);
   // void readDataTty();
};
#endif