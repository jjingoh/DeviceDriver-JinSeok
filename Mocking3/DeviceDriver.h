#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    void deviceRead(long address, int result[5]);
    void validateReadData(int result[5]);
    void deviceWrite(long address, int data);
    void checkAddressAlreadyUsed(long address);
    
    const unsigned char EMPTY_DATA = 0xff;

	  FlashMemoryDevice* m_hardware;
};