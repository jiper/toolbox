#include "uart.h"


int main(int argc, char **argv)
{
    uartStruct uartPara;
    uartClass uart_obj;
    uart_obj.initPort(&uartPara);
    uart_obj.readData();
    while(1);
	return 1;
}