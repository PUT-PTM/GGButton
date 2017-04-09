#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"

#include "ff.h"
#include "diskio.h"
#include "codec.h"

#include "SPI.h"
#include "przyciski.h"
#include "debouncer.h"
#include "karta_SD.h"
#include "DMA.h"

FRESULT fresult;
FIL plik_wav;
UINT licznik;
FATFS fatfs;


WORD zapisanych_bajtow; // <-----X

u16 DMA_buffer[2048];

int wartosc_ADC;

const TCHAR *obecny_utwor = "1.wav";

int main(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);




	Konfiguracja_SPI();
	Konfiguracja_przyciskow();
	Konfiguracja_debouncera();
	Inicjalizacja_karty_SD(&fresult, &fatfs);
	codec_init();
	codec_ctrl_init();
	I2S_Cmd(CODEC_I2S, ENABLE);
	Konfiguracja_DMA(DMA_buffer);










	  // Tworzenie pliku
	  //fresult = f_open (&plik_wav,"abc", FA_CREATE_ALWAYS);  //FA_READ
	  //fresult = f_close (&plik_wav);

	  // Tworzenie katalogu

	  //fresult = f_mkdir("qaz");







	  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	  	GPIO_InitTypeDef diody;

	  	diody.GPIO_Pin = GPIO_Pin_12;
	  	diody.GPIO_Mode = GPIO_Mode_OUT;
	  	diody.GPIO_OType = GPIO_OType_PP;
	  	diody.GPIO_Speed = GPIO_Speed_100MHz;
	  	diody.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  	GPIO_Init(GPIOD, &diody);












	  while(1)
	      {


	      }
}

void EXTI1_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line1) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI2_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line2) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI3_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line3) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI9_5_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line5) ||
		EXTI_GetITStatus(EXTI_Line6) ||
		EXTI_GetITStatus(EXTI_Line7) ||
		EXTI_GetITStatus(EXTI_Line8) ||
		EXTI_GetITStatus(EXTI_Line9) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void EXTI10_15_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line10) != RESET){

		TIM_Cmd(TIM3, ENABLE);
	}
}

void TIM3_IRQHandler ( void ){

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)){

			obecny_utwor = "test.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}
/*
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)){

			obecny_utwor = "2.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}
*//*
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)){

			obecny_utwor = "3.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)){

			obecny_utwor = "4.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)){

			obecny_utwor = "5.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)){

			obecny_utwor = "6.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}
*//*
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)){

			obecny_utwor = "7.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}
		*//*
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)){

			obecny_utwor = "8.wav";

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}
*/
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)){

			Odtwarzaj_utwor(&fresult, &plik_wav, licznik, obecny_utwor, DMA_buffer);

			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

			TIM_Cmd(TIM3, DISABLE);
			TIM3->CNT = 0;
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		EXTI_ClearITPendingBit(EXTI_Line1);
		EXTI_ClearITPendingBit(EXTI_Line2);
		EXTI_ClearITPendingBit(EXTI_Line3);
		EXTI_ClearITPendingBit(EXTI_Line4);
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line6);
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_ClearITPendingBit(EXTI_Line8);
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
    	wartosc_ADC = Odczyt_wartosci_ADC();
        Codec_VolumeCtrl(wartosc_ADC);
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

