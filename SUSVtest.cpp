/*
    SUSV. Simple Example.
*/

#include <stdio.h>
//#include <wiringPi.h>
#include "SUSV.h"

SUSV susv;

int main()
{
	susv.begin();
	
		for (int i = 0; i < 5; i++) {
		//std::cout << "Version: " << susv.get_version() << std::endl;
		printf("Version:         %s\n", susv.get_version().c_str());
		printf("Voltage:         %6.3f\n", susv.get_voltage());
		printf("Battery Voltage: %6.3f\n", susv.get_voltage_bat());
		std::cout << std::endl;
	}
}