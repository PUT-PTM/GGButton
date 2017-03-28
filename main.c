#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_spi.h"


#include "SPI.h"
#include "ff.h"
#include "diskio.h"

int main(void)
{
	SystemInit();
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);


	Konfiguracja_SPI();







	FRESULT fresult;
	 FIL plik;
	 WORD zapisanych_bajtow;
	 FATFS fatfs;



	 disk_initialize(0);// inicjalizacja karty
	 	fresult = f_mount( &fatfs, 1,1 );// zarejestrowanie dysku logicznego w systemie


	  // Tworzenie pliku
	  fresult = f_open (&plik,"lastone.txt", FA_CREATE_ALWAYS);
	  fresult = f_close (&plik);

	  // Tworzenie katalogu

	  fresult = f_mkdir("folder");





	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  	GPIO_InitTypeDef GPIO_InitStructure;

	  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	  	GPIO_InitTypeDef diody;

	  	diody.GPIO_Pin = GPIO_Pin_12;
	  	diody.GPIO_Mode = GPIO_Mode_OUT;
	  	diody.GPIO_OType = GPIO_OType_PP;
	  	diody.GPIO_Speed = GPIO_Speed_100MHz;
	  	diody.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  	GPIO_Init(GPIOD, &diody);



	  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	  	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	  	TIM_TimeBaseStructure.TIM_Period = 199;
	  	TIM_TimeBaseStructure.TIM_Prescaler = 8399;
	  	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	  	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	  	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  	TIM_Cmd(TIM3, DISABLE);

	  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	  	NVIC_InitTypeDef NVIC_InitStructure;
	  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  	NVIC_Init(&NVIC_InitStructure);

	  	EXTI_InitTypeDef EXTI_InitStructure;
	  	EXTI_InitStructure. EXTI_Line = EXTI_Line0;
	  	EXTI_InitStructure. EXTI_Mode = EXTI_Mode_Interrupt;
	  	EXTI_InitStructure. EXTI_Trigger = EXTI_Trigger_Rising;
	  	EXTI_InitStructure. EXTI_LineCmd = ENABLE;
	  	EXTI_Init(&EXTI_InitStructure);

	  	SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource0);

	  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	  	NVIC_InitTypeDef przerwanie;
	  	przerwanie.NVIC_IRQChannel = TIM3_IRQn;
	  	przerwanie.NVIC_IRQChannelPreemptionPriority = 0x00;
	  	przerwanie.NVIC_IRQChannelSubPriority = 0x00;
	  	przerwanie.NVIC_IRQChannelCmd = ENABLE;
	  	NVIC_Init(&przerwanie);

	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	  	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);




	  while(1)
	      {


	      }
}

void EXTI0_IRQHandler ( void ){
		if (EXTI_GetITStatus(EXTI_Line0) != RESET){
			TIM_Cmd(TIM3, ENABLE);
		}
	}

void TIM3_IRQHandler ( void ){
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){


			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

