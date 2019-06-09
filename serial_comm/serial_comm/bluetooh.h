#pragma once
#include <stdio.h>
#include "serialcomm.h"
#include <iostream>


void bluetoothConnect(const char* _portNum);
void  bluetoothSend(int data);
void bluetoothRecv(void);
void bluetoothDisconnect(void);