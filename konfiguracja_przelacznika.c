#include "konfiguracja_przelacznika.h"

void Przelacznik_konfiguracja(){

	Przelacznik_konfiguracja_wejscia_GPIOE();
	Przelacznik_konfiguracja_przerwan_zewnetrznych();







}





void Przelacznik_konfiguracja_wejscia_GPIOE(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef port_E;
	port_E.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;

	port_E.GPIO_Mode = GPIO_Mode_IN;
	port_E.GPIO_OType = GPIO_OType_PP;
	port_E.GPIO_Speed = GPIO_Speed_100MHz;
	port_E.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &port_E);
}

void Przelacznik_konfiguracja_przerwan_zewnetrznych(){

	Ustaw_przerwanie_zewnetrzne(EXTI0_IRQn);
	Ustaw_przerwanie_zewnetrzne(EXTI1_IRQn);
	Ustaw_przerwanie_zewnetrzne(EXTI2_IRQn);
	Ustaw_przerwanie_zewnetrzne(EXTI3_IRQn);
	Ustaw_przerwanie_zewnetrzne(EXTI4_IRQn);
	Ustaw_przerwanie_zewnetrzne(EXTI9_5_IRQn);

	Ustaw_pin_dla_przerwania_zewnetrznego(0, GPIO_Pin_0, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(1, GPIO_Pin_1, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(2, GPIO_Pin_2, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(3, GPIO_Pin_3, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(4, GPIO_Pin_4, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(5, GPIO_Pin_5, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(6, GPIO_Pin_6, E);
	Ustaw_pin_dla_przerwania_zewnetrznego(7, GPIO_Pin_7, E);
}
