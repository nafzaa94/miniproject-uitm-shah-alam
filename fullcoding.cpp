#include "stm32f4xx.h"
#define RS 0x20                                     /* pb5 mask for regselect*/
#define RW 0x40                                     /* pb6 mask for readwrite*/
#define EN 0x80                                     /* pb7 mask for enable*/
void delayMs (int n) ;                              /* function prototype for delay*/
void LCD_command (unsigned char command);           /* function prototype for unsigned char command */ 
void LCD_data (char data);                          /* function prototype for char data */
void LCD_init (void);                               /* function prototype for LCD */
void PORTS_init (void);

int main(void) {

 	RCC->AHB1ENR |= 7;			/*enable GPIOA clock, GPIOB clock and GPIOC clock*/
	
	GPIOA->MODER &= ~0x0000C303; /* clear pin mode */ //PA0-PA2
	
	GPIOB->MODER &= ~0x000003FF; //clear pin mode PB0-PB4
	GPIOB->MODER |= 0x00000155;	 /* set pin to output mode */
	LCD_init ();
	
	int state = 0;
	int state1 = 0;
	int state2 = 0;
	
	int statelcd = 0;
	
	int var = 0;

	LCD_command(0x01);

	while(1) {
		
		if ((GPIOA->IDR & 0x0010) == 0  && state == 0) 							//if PA4 Panic Button pressed, on 4 LED and buzzer
		{
			state = 1;
			var = 1;
			statelcd = 0;
			delayMs(1000);
		}
		else if ((GPIOA->IDR & 0x0010) == 0  && state == 1) 							//if PA4 Panic Button pressed again, off all component
		{
			state = 0;
			var = 3;
			delayMs(1000);
		}
		else if ((GPIOA->IDR & 0x0080) == 0 && state1 == 0)         //if PA7 Reset Button pressed, on 4 LED
		{
		   	state1 = 1;
			var = 2;
			statelcd = 0;
			delayMs(1000);
		}
		else if ((GPIOA->IDR & 0x0080) == 0 && state1 == 1)         //if PA7 Reset Button pressed, off all component
		{
		   	state1 = 0;
			var = 3;
			delayMs(1000);
		}
		else if ((GPIOA->IDR & 0x0001) == 0 && state2 == 0)        //if PA1 Reset Button pressed, on 4 LED and buzzer
		{
			state2 = 1;
			var = 1;
			delayMs(1000);
	  	} else {
	  		continue;
	  	}

		switch(var)
		{
		case 1:
			GPIOB->ODR = 0x001F;
		  var = 0;
						/* */
		if (statelcd == 0){
			
			LCD_command(1);
			
		  LCD_data('H');                                      /* display H for 1s */
			LCD_data('E');                                      /* display E for 1s */
			LCD_data('L');                                      /* display L for 1s */
			LCD_data('P');                                      /* display P for 1s */
			LCD_data('!');  			                              /* display ! for 1s */
			
			statelcd = 1;
		}
		    
		break;

		case 2:
			GPIOB->ODR = 0x000F;
		    var = 0;
		
		if (statelcd == 0){
		
		  LCD_command(1);
		
			LCD_data('W');                                      /* display W for 1s */
			LCD_data('E');                                      /* display E for 1s */
			LCD_data('L');                                      /* display L for 1s */
			LCD_data('C');                                      /* display C for 1s */
			LCD_data('O');                                      /* display O for 1s */
			LCD_data('M');                                      /* display M for 1s */
			LCD_data('E');                                      /* display E for 1s */
			
			statelcd = 1;
		}
		                                        
		break;
		
		case 3:
			GPIOB->ODR = 0x0000;
		   	var = 0; 
		   	state2 = 0;
		break;
		
		case 4:
			GPIOB->ODR = 0x001F;
		   	delayMs (1000);

		   	GPIOB->ODR = 0x000F;
        delayMs (500);
		
		  
			if (statelcd == 0){
				
				LCD_command(1);
			
				LCD_data('W');                                      /* display W for 1s */
				LCD_data('E');                                      /* display E for 1s */
				LCD_data('L');                                      /* display L for 1s */
				LCD_data('C');                                      /* display C for 1s */
				LCD_data('O');                                      /* display O for 1s */
				LCD_data('M');                                      /* display M for 1s */
				LCD_data('E');                                      /* display E for 1s */
				
				statelcd = 1;
			}
			var = 0;
		 break;		
		
	 }
 }	
}

/*initialize port pin then initialize lcd contoller*/
void LCD_init(void) {
	PORTS_init();

	delayMs(30);   //initialization sequence
	LCD_command(0x30);  //
	delayMs(10);
	LCD_command(0x30);
	delayMs(1);
	LCD_command(0x30); //
	delayMs(10);
	LCD_command (0x38);  //set 8-bit data , 2 line, 5x7 font
	LCD_command (0x06);  //move cursor right after each char
	LCD_command (0x01);  //clear screen, move cursor blinking
	LCD_command (0x0F);  //turn on display , cursor blinking


}
void PORTS_init(void){
	RCC->AHB1ENR |=  0x06;                 /* enable GPIOB and GPIOC clock */

	GPIOB->MODER &= ~0x0000FC00;        /* clear pin mode for MODER 5,6,7 coz connected to PB5,6,7*/
  GPIOB->MODER |=  0x00005400;        /* set pin to output mode */
	GPIOB->BSRR =  0x00C00000;									//turn off EN and RW

	GPIOC->MODER &= ~0x003FFFC0;        // clear pin mode
  GPIOC->MODER |= 0x00155540;        /* set pin to output mode PC3- PC9*/

}

void LCD_command(unsigned char command){

	GPIOB->BSRR= (RS | RW) << 16; //rs=0, rw=0
	GPIOC->ODR=command; //put command on data bus
	GPIOB->BSRR=EN;     // pulse E high
	delayMs(0);
	GPIOB->BSRR = EN << 16;    // clear E
	if (command<4)
		delayMs(2);  // command 1 and 2 needs up to 1.64ms
	else
		delayMs(1);   // all others 40us

}

void LCD_data(char data){

	GPIOB->BSRR=RS;   // RS=1
	GPIOB->BSRR =RW << 16;  //RW =0
	GPIOC->ODR=data;      // put data on data bus
	GPIOB->BSRR=EN;      // pulse E high
	delayMs(0);
	GPIOB->BSRR = EN << 16;  // clear E

	delayMs(1);
}

/*16 MHz SYSCLK*/
void delayMs(int n){
	int i;
	for (; n>0;n--)
		for (i=0; i<3195;i++);
}
