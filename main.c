#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "konfiguracja_przelacznika.h"
#include "przerwania_zewnetrzne.h"
#include "timery.h"

int main(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	Przelacznik_konfiguracja();
	Konfiguracja_zegara_do_DEBOUNCERA_przerwan_zewnetrznych();



	// diody do testow

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =
	GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


    while(1)
    {


    }
}






void EXTI0_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line0) != RESET){

	 	GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line1) != RESET){

		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line2) != RESET){

		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

void EXTI3_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line3) != RESET){

		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI4_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line4) != RESET){

		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

void EXTI9_5_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8) != RESET){

		TIM_Cmd(TIM3, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

void TIM3_IRQHandler(void){



	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){


		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)){

			GPIO_ToggleBits(GPIOD,GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}




