#include "stm32f4xx.h"

int main(void) {
    
    RCC->AHB1ENR |=  5;                /*enable GPIOA clock and GPIOC clock */ 

    GPIOA->MODER &= ~0x0000FC0F;        /* clear pin mode *///PA5,6,7
    GPIOA->MODER |=  0x00005405;        /* set pin to output mode */ // 0,1, 5,6,7
		
	  GPIOC->MODER &= ~0x0C00FC0F;        /* clear pin mode *///PC7,6,5
		
          
       while(1) {
			if (GPIOC->IDR & 0x0020){     /* if Pc5 is high */
				GPIOA->ODR = 0x00000021;   /* motor rotates clockwise and green led on */ // 				
			} else {
				GPIOA->ODR = 0x00000000;
			}
				
            if (GPIOC->IDR & 0x0040) {     /* if Pc6 is high */	
				GPIOA->ODR = 0x000000C2; /*motor rotates anti-clockwise and red led and buzzer on */			
			} else{
				GPIOA->ODR = 0x00000000;
			}
    }
}
