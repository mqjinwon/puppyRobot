#include "bluetooh.h"

using namespace std;
int startflag = 0;

CSerialComm serialComm;

void bluetoothConnect(const char* _portNum)
{
	while (1)
	{
		// STEP 1. SerialPort Connect
		if (!serialComm.connect(_portNum)) {
			printf("connect faliled\n");
		}
		else {
			printf("connect successed\n");
			break;
		}


		Sleep(500);
	}
}

void  bluetoothSend(int data)
{
	//// STEP 2. Send Command
	if (!serialComm.sendCommand('a')) {
		printf("send command failed\n");
	}
	else
		printf("send Command success\n");
}

void bluetoothRecv(void)
{
	BYTE data;
	// STEP 3. Receive Command
	while (1) {

		if (!serialComm.recvCommand(data)) {
			printf("send command failed\n");
		}
		else {

			if (data == 'E') {
				startflag = 0;
				cout << endl;
				break;
			}


			if (startflag == 1 && data == ',') {
				cout << endl;
			}
			else if (startflag == 1) {
				cout << data;
			}


			if (data == 'S') {
				startflag = 1;
			}

		}
	}
}

void bluetoothDisconnect(void)
{
	serialComm.disconnect();
	printf("\nend connect\n");
}
