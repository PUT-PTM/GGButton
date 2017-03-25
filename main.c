#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "konfiguracja_przelacznika.h"
#include "przerwania_zewnetrzne.h"


int main(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	Przelacznik_konfiguracja();



	// DEBOUNCER

	/*
		 * void EXTI0_IRQHandler ( void ){
			if (EXTI_GetITStatus(EXTI_Line0) != RESET){
				TIM_Cmd(TIM3, ENABLE);
			}
		}

		void TIM3_IRQHandler ( void ){
			if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
				if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){


					GPIO_ToggleBits(GPIOE, GPIO_Pin_7);
					TIM_Cmd(TIM3, DISABLE);
				TIM3->CNT = 0;
			}

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
	}
		 */




    while(1)
    {
    }
}
