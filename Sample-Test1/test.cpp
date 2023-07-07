#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Mocking3/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class FlashMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverTest, TestDeviceWriteSuccess) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	EXPECT_CALL(mock, read(0x1234))
		.WillRepeatedly(Return(0xff));
	EXPECT_CALL(mock, write(0x1234, 0x12))
		.Times(1);
	driver.write(0x1234, 0x12);
}

TEST(DeviceDriverTest, TestWriteCallDeviceRead) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	EXPECT_CALL(mock, read(0x1234))
		.Times(1)
		.WillRepeatedly(Return(0xff));
	driver.write(0x1234, 0x12);
}

TEST(DeviceDriverTest, TestWriteCallDeviceAlreadyHasData) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	EXPECT_CALL(mock, read(0x1234))
		.Times(1)
		.WillRepeatedly(Return(0xab));
	EXPECT_THROW(driver.write(0x1234, 0x12), std::exception);
}

TEST(DeviceDriverTest, TestDeviceReadSuccess) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	EXPECT_CALL(mock, read(0x1234))
		.WillRepeatedly(Return(5));

	EXPECT_THAT(driver.read(0x1234), Eq(5));

}

TEST(DeviceDriverTest, TestDeviceReadCall5Times) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	EXPECT_CALL(mock, read(0x1234))
		.Times(5)
		.WillRepeatedly(Return(5));

	EXPECT_THAT(driver.read(0x1234), Eq(5));
}

TEST(DeviceDriverTest, TestDeviceReadHasDifferentResult) {
	FlashMock mock;
	DeviceDriver driver(&mock);

	vector<vector<int>> fake_result = {
		{5,5,5,5,4},
		{5,5,5,4,5},
		{5,5,4,5,5},
		{5,4,5,5,5},
		{4,5,5,5,5}
	};

	for (auto& item : fake_result) {
		EXPECT_CALL(mock, read(0x1234))
			.WillOnce(Return(item[0]))
			.WillOnce(Return(item[1]))
			.WillOnce(Return(item[2]))
			.WillOnce(Return(item[3]))
			.WillOnce(Return(item[4]));
		EXPECT_THROW(driver.read(0x1234), std::exception);
	}
}
