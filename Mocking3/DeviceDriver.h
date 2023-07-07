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

	FlashMemoryDevice* m_hardware;
};