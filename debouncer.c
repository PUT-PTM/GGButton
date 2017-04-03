#include "debouncer.h"

void Konfiguracja_debouncera(){

	Konfiguracja_timera_debouncera();
	Konfiguracja_przerwania_debouncera();
	Aktywacja_timera_debouncera();
}

void Konfiguracja_timera_debouncera(){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef zegar;
	zegar.TIM_Period = 199;
	zegar.TIM_Prescaler = 8399;
	zegar.TIM_ClockDivision = TIM_CKD_DIV1;
	zegar.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &zegar);

	TIM_Cmd(TIM3, DISABLE);
}

void Konfiguracja_przerwania_debouncera(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef przerwanie;
	przerwanie.NVIC_IRQChannel = TIM3_IRQn;
	przerwanie.NVIC_IRQChannelPreemptionPriority = 0x00;
	przerwanie.NVIC_IRQChannelSubPriority = 0x00;
	przerwanie.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&przerwanie);
}

void Aktywacja_timera_debouncera(){

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}
