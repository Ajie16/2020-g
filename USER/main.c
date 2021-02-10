#include "main.h"


int main(void)
{		
	System_Init();
	while(1)
	{
		Task_Schedule();
	}
} 

