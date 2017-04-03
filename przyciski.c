#include "przyciski.h"

void Konfiguracja_przyciskow(){

	Konfiguracja_pinow_wejsciowych();
	Konfiguracja_przerwan_wejsciowych();
}

void Konfiguracja_pinow_wejsciowych(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef piny;

	piny.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	piny.GPIO_Mode = GPIO_Mode_IN;
	piny.GPIO_OType = GPIO_OType_PP;
	piny.GPIO_Speed = GPIO_Speed_100MHz;
	piny.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &piny);
}

void Konfiguracja_przerwan_wejsciowych(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef przerwanie;
	przerwanie.NVIC_IRQChannelPreemptionPriority = 0x00;
	przerwanie.NVIC_IRQChannelSubPriority = 0x00;
	przerwanie.NVIC_IRQChannelCmd = ENABLE;

	EXTI_InitTypeDef linia_przerwania;
	linia_przerwania.EXTI_Mode = EXTI_Mode_Interrupt;
	linia_przerwania.EXTI_Trigger = EXTI_Trigger_Rising;
	linia_przerwania.EXTI_LineCmd = ENABLE;

	//---

	przerwanie.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line1;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

	//---

	przerwanie.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line2;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

	//---

	przerwanie.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line3;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);

	//---

	przerwanie.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line4;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);

	//---

	przerwanie.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9  ;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource6);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);
}
