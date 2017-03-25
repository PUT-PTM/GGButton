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




    while(1)
    {
    }
}






void EXTI0_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line0) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI1_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line1) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI2_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line2) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI3_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line3) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI4_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line4) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI9_5_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line5 | EXTI_Line6 | EXTI_Line7) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void TIM3_IRQHandler(void){

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)){

			//cos
			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		EXTI_ClearITPendingBit(EXTI_Line0);
		EXTI_ClearITPendingBit(EXTI_Line1);
		EXTI_ClearITPendingBit(EXTI_Line2);
		EXTI_ClearITPendingBit(EXTI_Line3);
		EXTI_ClearITPendingBit(EXTI_Line4);
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}




