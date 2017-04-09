#include "ADC.h"

void Konfiguracja_ADC(){

	Konfiguracja_pinu_ADC();
	Konfiguracja_struktury_ADC();
	Konfiguracja_timera_ADC();
	Konfiguracja_przerwania_timera_ADC();
	Aktywacja_timera_ADC();
}

void Konfiguracja_pinu_ADC(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

	GPIO_InitTypeDef  pin_ADC;
	pin_ADC.GPIO_Pin = GPIO_Pin_1;
	pin_ADC.GPIO_Mode = GPIO_Mode_AN;
	pin_ADC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &pin_ADC);
}

void Konfiguracja_struktury_ADC(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

	ADC_CommonInit(&ADC_CommonInitStructure);

	//---

	ADC_InitTypeDef ADC_InitStructure;

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);
}

void Konfiguracja_timera_ADC(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef zegar;

	zegar.TIM_Period = 2099;
	zegar.TIM_Prescaler = 1999;
	zegar.TIM_ClockDivision = TIM_CKD_DIV1;
	zegar.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &zegar);

	TIM_Cmd(TIM2, ENABLE);
}

void Konfiguracja_przerwania_timera_ADC(){

	 NVIC_InitTypeDef przerwanie_timera_ADC;

	 przerwanie_timera_ADC.NVIC_IRQChannel = TIM2_IRQn;
	 przerwanie_timera_ADC.NVIC_IRQChannelPreemptionPriority = 0x00;
	 przerwanie_timera_ADC.NVIC_IRQChannelSubPriority = 0x00;
	 przerwanie_timera_ADC.NVIC_IRQChannelCmd = ENABLE;

	 NVIC_Init(&przerwanie_timera_ADC);
}

void Aktywacja_timera_ADC(){

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

int Odczyt_wartosci_ADC(){

    ADC_SoftwareStartConv(ADC1);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    int dupa = ((ADC_GetConversionValue(ADC1))/16);
    return dupa;
}
