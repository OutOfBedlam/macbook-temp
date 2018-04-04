//
//  main.c
//  mbinfo
//
//  Created by Eirny on 8/27/14.
//  Copyright (c) 2014 EirnyKwon. All rights reserved.
//

#include <stdio.h>
#include "SmcMain.h"

int main(int argc, const char * argv[])
{
	kern_return_t result;

	result = SMCOpen();

	if (result != kIOReturnSuccess)
	{
		printf("SMCOpen Failure\n");
		return -1;
	}

	printf("CPU Temp: %0.2f °C\n", SMCGetTemperature(SMC_KEY_CPU_TEMP));

	int fanNum = SMCGetFanNumber(SMC_KEY_FAN_NUM);
	for (int i = 0; i < fanNum; i++)
		printf("Fan#%d Speed: %0.0f rpm\n", i, SMCGetFanSpeed(i));

	int designCycleCount = getDesignCycleCount();

	if (designCycleCount)
		printf ("Design Cycle: %i\n", designCycleCount);

	char batteryHealth[256];
	strncpy(batteryHealth, getBatteryHealth(), 255);

	//if (batteryHealth)
    printf ("Battery Status: %s\n", batteryHealth);

	SMCClose();

	return 0;
}
