#include "konfiguracja_przelacznika.h"

void przelacznik_konfiguracja_wejscia_GPIOE(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef port_E;
	port_E.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

	port_E.GPIO_Mode = GPIO_Mode_IN;
	port_E.GPIO_OType = GPIO_OType_PP;
	port_E.GPIO_Speed = GPIO_Speed_100MHz;
	port_E.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &port_E);
}
