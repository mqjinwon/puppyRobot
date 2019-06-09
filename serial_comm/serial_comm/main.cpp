#include "bluetooh.h"

int main()
{
	bluetoothConnect("COM11");
	while(1)
		bluetoothRecv();
}