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
