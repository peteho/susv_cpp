/*
SUSV.h - Header file for S.USV

*/

#ifndef SUSV_h
#define SUSV_h

#include <stdint.h>
#include <iostream>
#include <string>
using namespace std;

#define SUSV_ADDR (0x0F)
#define SUSV_VOLTAGE (0xD0)
#define SUSV_POWER_EXT (0xD1)
#define SUSV_POWER_BAT 0(xD2)
#define SUSV_VOLTAGE_BAT (0xD3)
#define SUSV_STATE_BAT (0xD4)
#define SUSV_CHARGE (0x35)
#define SUSV_VERSION (0x22)
#define SUSV_POWER_STATE (0x45)

class SUSV
{
	public:

		bool begin(uint8_t address = SUSV_ADDR);
		std::string get_version(void);
		float get_voltage(void);
		float get_voltage_bat(void);

	private:

		int8_t susvAddress;
};

#endif
