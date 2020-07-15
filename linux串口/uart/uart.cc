#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include <termios.h> //set baud rate

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <thread>
#include "uart.h"
#include "inner_precision.h"
#include "debug.h"

/*-----------------------------------------------------*/
/*******************************************************/

/*************Linux and Serial Port *********************/
/*************Linux and Serial Port *********************/
bool uartClass::openPort(const char* comport)
{

	fdSerial = open(comport, O_RDWR | O_NOCTTY | O_NDELAY);
	if (-1 == fdSerial)
	{
		perror("Can't Open Serial Port");
		return false;
	}
	else
	{
		printf("open %s .....\n",comport);
	}

	if (fcntl(fdSerial, F_SETFL, 0) < 0)
	{
		printf("fcntl failed!\n");
	}
	else
	{
		printf("fcntl=%d\n", fcntl(fdSerial, F_SETFL, 0));
	}
	if (isatty(STDIN_FILENO) == 0)
	{
		printf("standard input is not a terminal device\n");
	}
	else
	{
		printf("is a tty success!\n");
	}
	printf("fd-open=%d\n", fdSerial);
	return true;
}

bool uartClass::setOpt(int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;
	if (tcgetattr(fdSerial, &oldtio) != 0)
	{
		perror("SetupSerial 1");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch (nBits)
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch (nEvent)
	{
	case 'O': //奇校验
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': //偶校验
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N': //无校验
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch (nSpeed)
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	if (nStop == 1)
	{
		newtio.c_cflag &= ~CSTOPB;
	}
	else if (nStop == 2)
	{
		newtio.c_cflag |= CSTOPB;
	}
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fdSerial, TCIFLUSH);
	if ((tcsetattr(fdSerial, TCSANOW, &newtio)) != 0)
	{
		perror("com set error");
		return -1;
	}
	printf("set done!\n");
	return 0;
}



void uartClass::readDataTty()
{
	int ret, pos;
	char data;

	pos = 0;
	while (1)
	{
		ret = read(fdSerial, &data, 1);
		if (-1 == ret || 0 == ret)
			continue;
		if(pos == 0 && data !='$')
			continue;
		*(rcv_buf + pos)= data;
		pos += 1;
		if (rcv_buf[pos - 1] == '\n')
		{
			rcv_buf[pos - 2] = '\0';
			if(rcv_buf[3] == 'G' && rcv_buf[4]=='G' && rcv_buf[5] == 'A')
			{
				//printf("%s\n", rcv_buf);
				//cout << rcv_buf << endl;
				logFile << rcv_buf << endl;
				CoordinateExtract(rcv_buf);
			}
			pos = 0;
		}
	}
}

int uartClass::sendDataTty(char *send_buf, int Len)
{
	ssize_t ret;
	ret = write(fdSerial, send_buf, Len);
	if (ret == -1)
	{
		printf("write device error\n");
		return -1;
	}
	return 1;
}

bool uartClass::initPort(uartStruct* uartPara)
{
	TimeOut = rcvTimeOut;
	if(false == openPort((uartPara->comPort).c_str()))
		return false;
	if (false == setOpt(uartPara->BPS,uartPara->nBits, uartPara->nEvent, uartPara->nStop))
		return false;
	printf("Serial fdSerial=%d\n", fdSerial);
	tcflush(fdSerial, TCIOFLUSH); //清掉串口缓存
	fcntl(fdSerial, F_SETFL, 0);
	return true;
}

void uartClass::readData()
{
	thread t1(&uartClass::readDataTty,this);
	t1.detach();
}
