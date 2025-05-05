/*
PLAN LAB EDGE INTERRUPTS
1. Make external button as actuator ( PA5 )
2. Activate clock (RCGCGPIO)
3. Set all registers needed for Edge Interrupt( DIR, DEN, PUR, IS, IBE, ICR, IM and such)
4. Control priority through NVIC
5. Enable interrupts through vector
6. Create ISR ( Turn lights on at PA4)

*/


#include <stdint.h>

//ADDRESS
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define GPIO_PORTA_BASE					(*((volatile uint32_t *)0x40004000)) //Base address for Port A
#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400043FC)) //Offset 0x3fc
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400)) //Offset 0x400
#define GPIO_PORTA_PUR_R        (*((volatile uint32_t *)0x40004510)) //Offset 0x510
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C)) //Offset 0x51c
#define GPIO_PORTA_IS_R 				(*((volatile uint32_t *)0x40004404)) //Offset 0x404
#define GPIO_PORTA_IBE_R 				(*((volatile uint32_t *)0x40004408)) //Offset 0x408
#define GPIO_PORTA_IEV_R 				(*((volatile uint32_t *)0x4000440C)) //Offset 0x40C
#define GPIO_PORTA_ICR_R 				(*((volatile uint32_t *)0x4000441C)) //Offset 0x41C
#define GPIO_PORTA_IM_R 				(*((volatile uint32_t *)0x40004410)) //Offset 0x410

#define NVIC_EN0_R  						(*((volatile uint32_t *)0xE000E100)) //Because interrupt vector for port A is interrupt 0 (OFFSET 0X100)
#define NVIC_PRI0_R  						(*((volatile uint32_t *)0xE000E400)) //PRI0 because interrupt 0 ( Port A ) ( OFFSET 0X400)



void EdgeInterrupt_Init (void)
{
	SYSCTL_RCGCGPIO_R |= 0x01; // Activate Clock for Port A
	GPIO_PORTA_DIR_R &= 0x10; //0001 0000 PA4 Output, PA5 input
	GPIO_PORTA_DEN_R |= 0x30; // 0011 0000 PA4 and PA5 enable digital function
	GPIO_PORTA_PUR_R |= 0x20; // 0010 0000 PA5 input, enable weak pull up
	GPIO_PORTA_IS_R &= ~0x20; // PA5 clear edge sensitive
	GPIO_PORTA_IBE_R &= ~0x20; //Not both Edges ( fully controlled by GPIOIEV)
	GPIO_PORTA_IEV_R &= ~0x20; //falling edge only on PA5
	
	
	
}

void GPIOA_Handler(void)
{
	
}