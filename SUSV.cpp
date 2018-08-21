/*
SUSV.cpp - Class file for the S.USV Lib

*/

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <string>
using namespace std;

#include "SUSV.h"

bool SUSV::begin(uint8_t address)
{
	//----- OPEN THE I2C BUS -----
	char *filename = (char*)"/dev/i2c-1";
	if ((susvAddress = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return false;
	}
	
	if (ioctl(susvAddress, I2C_SLAVE, address) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return false;
	}
	return true;
}

std::string SUSV::get_version(void)
{
	char buf[4];
	
	// write "get version"
	buf[0] = SUSV_VERSION;
	write(susvAddress, buf, 1);
	usleep(200000);
	
	// read: cmd, v1, v2, model
	read(susvAddress, buf, 4);
	return std::to_string(buf[1]) + "." + std::to_string(buf[2]);
}

float SUSV::get_voltage(void)
{
	char buf[3];

	// write "get voltage"
	buf[0] = SUSV_VOLTAGE;
	write(susvAddress, buf, 1);
	usleep(200000);
	
	// read: cmd, v_high, v_low
	read(susvAddress, buf, 3);
	//printf("SUSV_VOLTAGE: %02x %02x %02x\n", buf[0], buf[1], buf[2]);
	return (buf[1] + buf[2] * 256) / 1000.0;
}

float SUSV::get_voltage_bat(void)
{
	char buf[3];

	// write "get battey voltage"
	buf[0] = SUSV_VOLTAGE_BAT;
	write(susvAddress, buf, 1);
	usleep(200000);
	
	// read: cmd, v_high, v_low
	read(susvAddress, buf, 3);
	//printf("SUSV_VOLTAGE_BAT: %02x %02x %02x\n", buf[0], buf[1], buf[2]);
	return (buf[1] + buf[2] * 256) / 1000.0;
}
