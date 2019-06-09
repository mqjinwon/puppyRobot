#include <stdio.h>
#include "serialcomm.h"
#include <iostream>

using namespace std;

int main()
{
	CSerialComm serialComm;
	//char inputData;
	BYTE data;

	while (1) {
		// STEP 1. SerialPort Connect
		if (!serialComm.connect("COM6"))
		{
			printf("connect faliled");
			return -1;
		}
		else
			//printf("connect successed\n");


		//// STEP 2. Send Command
		/*if (!serialComm.sendCommand('b'))
		{
			printf("send command failed\n");
		}
		else
			printf("send Command success\n");*/


		// STEP 2. Receive Command
		if (!serialComm.recvCommand(data))
		{
			printf("send command failed\n");
		}
		else {
			//printf("성공적으로 받았습니다.");
			cout << data << endl;
			//printf(data);
		}
			


	// STEP 3. SerialPort disConnect
		serialComm.disconnect();

		//printf("\nend connect\n");

		
	}
	
	return 0;

}