/* 
		Write and execute a C program for the cases below;
    - If switch 1 is pressed, RED LED is turn on and BUZZER is turn on.
    - If sensor detects obstacle, GREEN LED is turn on and DC motor moves clockwise.
    - Otherwise, all components are in off state.
*/

#include "stm32f4xx.h"

int main(void) 
{
		RCC->AHB1ENR |= 5;		/* enable GPIOA and GPIOC clock */
				
	
		GPIOA->MODER &= ~0x0000FF0C;		/* clear pin mode PA1,PA4,PA5,PA6,PA7*/
		GPIOA->MODER |=  0x00005504;		/* set pin to output mode PA1,PA4,PA5,PA6,PA7*/
		
		GPIOC->MODER &= ~0x0000000F;		/* clear pin to input mode PC0(SW1) & PC1(SENSOR)*/

		while(1)
		{
			if (GPIOC->IDR & 0x0001)			/* if PC0(switch) is high*/
			{
				GPIOA->ODR = 0x000000A0;		/* turn on RED led PA5 and BUZZER PA7 */
			}
			else {
                GPIOA->ODR = 0x00000000;
			}
			
			if ((GPIOC->IDR & 0x0002) == 0)		/* if PC1(ir sensor) is low */
			{
				GPIOA->ODR = 0x00000042;		/* turn on GREEN led PA6 and MOTOR clockwise PA1*/
			} 

			else {
				GPIOA->ODR = 0x00000000;
			}
			
			
		}
			
}
