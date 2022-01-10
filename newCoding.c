#include "stm32f4xx.h"

void delayMs(int n);
int main(void)
{

	RCC->AHB1ENR |= 5; /* enable GPIOA and GPIOC clock */

	GPIOA->MODER &= ~0x000FFC00; //clear pin mode PA5-PA9
	GPIOA->MODER |= 0x00055400;	 /* set pin to output mode */

	GPIOC->MODER &= ~0x0000003C; /* clear pin mode */ //PC1 and PC2
	
	int state = 0;
	int state1 = 0;
	int state2 = 0;
	
	int var = 0;

	while (1)
	{

		if ((GPIOC->IDR & 0x0002) == 0  && state == 0) 
		{
			 state = 1;
			 var = 1;
			 delayMs(1000);
		}
		
		if ((GPIOC->IDR & 0x0002) == 0  && state == 1) 
		{
			 state = 0;
			 var = 3;
			 delayMs(1000);
		}
		
		
		if ((GPIOC->IDR & 0x0001) == 0 && state1 == 0)
		{
		   state1 = 1;
			 var = 2;
			 delayMs(1000);
		}
		
		if ((GPIOC->IDR & 0x0001) == 0 && state1 == 1)
		{
		   state1 = 0;
			 var = 3;
			 delayMs(1000);
		}
		
		
		
		if ((GPIOC->IDR & 0x0004) == 0 && state2 == 0)
		{
			state2 = 1;
			var = 1;
	  } 
		
		
		switch(var)
		{
		case 1:
			 GPIOA->ODR = 0x03E0;
		   var = 0;
		break;

		case 2:
			 GPIOA->ODR = 0x01E0;
		   var = 0;
		break;
		
		case 3:
			 GPIOA->ODR = 0x0000;
		   var = 0; 
		   state2 = 0;
		break;

		}

  }
  
}

void delayMs(int n)
{
	int i;
	for (; n > 0; n--)
		for (i = 0; i < 3195; i++);
}
