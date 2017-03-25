#include "przerwania_zewnetrzne.h"

void Ustaw_przerwanie_zewnetrzne(unsigned char przerwanie_czego){

	// przerwanie_czego: EXTI[x]_IRQn, TIM[x]_IRQn

	NVIC_InitTypeDef przerwanie_zewnetrzne;

	przerwanie_zewnetrzne.NVIC_IRQChannel = przerwanie_czego;
	przerwanie_zewnetrzne.NVIC_IRQChannelPreemptionPriority = 0x00;
	przerwanie_zewnetrzne.NVIC_IRQChannelSubPriority = 0x00;
	przerwanie_zewnetrzne.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&przerwanie_zewnetrzne);
}

void Ustaw_pin_dla_przerwania_zewnetrznego(int linia_przerwania, unsigned int pin, Port port_GPIO){

	// pin: GPIO_Pin_[x]
	// nr linia_przerwania == nr pin

	EXTI_InitTypeDef konfiguracja_linii;

	switch(linia_przerwania){

		case 0:

			konfiguracja_linii.EXTI_Line = EXTI_Line0;
			break;

		case 1:

			konfiguracja_linii.EXTI_Line = EXTI_Line1;
			break;

		case 2:

			konfiguracja_linii.EXTI_Line = EXTI_Line2;
			break;

		case 3:

			konfiguracja_linii.EXTI_Line = EXTI_Line3;
			break;

		case 4:

			konfiguracja_linii.EXTI_Line = EXTI_Line4;
			break;

		case 5:

			konfiguracja_linii.EXTI_Line = EXTI_Line5;
			break;

		case 6:

			konfiguracja_linii.EXTI_Line = EXTI_Line6;
			break;


		case 7:

			konfiguracja_linii.EXTI_Line = EXTI_Line7;
			break;
	}

	konfiguracja_linii.EXTI_Mode = EXTI_Mode_Interrupt;
	konfiguracja_linii.EXTI_Trigger = EXTI_Trigger_Rising;
	konfiguracja_linii.EXTI_LineCmd = ENABLE;
	EXTI_Init(&konfiguracja_linii);

	GPIO_TypeDef* GPIO;

	switch(port_GPIO){

		case A:
			GPIO = GPIOA;
			break;

		case B:
			GPIO = GPIOB;
			break;

		case C:
			GPIO = GPIOC;
			break;

		case D:
			GPIO = GPIOD;
			break;

		case E:
			GPIO = GPIOE;
			break;
	}

	SYSCFG_EXTILineConfig(GPIO, pin);
}
