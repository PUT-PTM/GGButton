#include "timery.h"

void Ustaw_zegar(Timer tim, unsigned int prescaler, unsigned int period, int zasilanie){

	// zasilanie: 1 - ON | 0 - OFF

	TIM_TypeDef* TIM;
	unsigned int RCC_TIM;

	switch(tim){

		case Tim2:

			TIM = TIM2;
			RCC_TIM = RCC_APB1Periph_TIM2;
			break;

		case Tim3:

			TIM = TIM3;
			RCC_TIM = RCC_APB1Periph_TIM3;
			break;

		case Tim4:

			TIM = TIM4;
			RCC_TIM = RCC_APB1Periph_TIM4;
			break;

		case Tim5:

			TIM = TIM5;
			RCC_TIM = RCC_APB1Periph_TIM5;
			break;
	}

	RCC_APB1PeriphClockCmd(RCC_TIM, ENABLE);

	TIM_TimeBaseInitTypeDef zegar;
	zegar.TIM_Period = period;
	zegar.TIM_Prescaler = prescaler;
	zegar.TIM_ClockDivision = TIM_CKD_DIV1;
	zegar.TIM_CounterMode =  TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM, &zegar);

	if(zasilanie == 1){

		TIM_Cmd(TIM, ENABLE);
	}
}

void Aktywacja_przerwania_dla_timera(Timer tim){

	switch(tim){

		case Tim2:

			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
			break;

		case Tim3:

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
			break;

		case Tim4:

			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
			break;

		case Tim5:

			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
			TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
			break;
	}
}

void Konfiguracja_zegara_do_DEBOUNCERA_przerwan_zewnetrznych(){

	int prescaler = 8399;
	int period = 199;

	Ustaw_zegar(Tim3, prescaler, period, 0);
}
