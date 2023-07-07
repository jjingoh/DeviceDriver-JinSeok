#include "DeviceDriver.h"
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	// TODO: implement this method properly
	return (int)(m_hardware->read(address));
}


void DeviceDriver::write(long address, int data)
{
	checkAddressAlreadyUsed(address);
	deviceWrite(address, data);

}

void DeviceDriver::checkAddressAlreadyUsed(long address)
{
	auto result = m_hardware->read(address);
	if (result == EMPTY_DATA) return;
	throw std::exception("WriteFailException");
}

void DeviceDriver::deviceWrite(long address, int data)
{
	m_hardware->write(address, (unsigned char)data);
}
