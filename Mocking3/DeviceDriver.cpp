#include "DeviceDriver.h"
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

void DeviceDriver::deviceRead(long address, int result[5])
{
	for (int i = 0; i < 5; ++i)
		result[i] = (int)(m_hardware->read(address));
}

void DeviceDriver::validateReadData(int result[5])
{
	for (int i = 0; i < 4; ++i)
	{
		if (result[i] != result[i + 1])
			throw std::exception("ReadFailException");
	}
}

int DeviceDriver::read(long address)
{
    int result[5];
    deviceRead(address, result);
    validateReadData(result);
    return result[0];
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}