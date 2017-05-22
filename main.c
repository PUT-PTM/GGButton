#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rng.h"
#include "misc.h"
#include "delay.h"
#include "codec.h"
//#include "List.h"
#include "ff.h"

#include <stdbool.h>


FATFS fatfs;
FIL file;
FRESULT fresult;
DIR Dir;
FILINFO fileInfo;

u16 sample_buffer[2048];

volatile u16 result_of_conversion=0;

volatile s8 change_song=0;
volatile u8 error_state=0;

const char* utwory[9] = {"0.WAV","1.WAV","2.WAV","3.WAV","4.WAV","5.WAV","6.WAV","7.WAV","8.WAV"};
int obecny_utwor = 0;
int graj = 0;
int posladki = 0;
int lel = 0;


//===

void EXTI9_5_IRQHandler ( void ){

	if (EXTI_GetITStatus(EXTI_Line9) != RESET){

		if(graj == 0){

			graj = 1;
		}


		TIM_Cmd(TIM5, ENABLE);
	}
}

//===

void TIM5_IRQHandler ( void ){

	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_9)){


			graj = 1;


			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

			TIM_Cmd(TIM5, DISABLE);
			TIM5->CNT = 0;
		}

		EXTI_ClearITPendingBit(EXTI_Line9);
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}

//===

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		ADC_conversion();
		Codec_VolumeCtrl(result_of_conversion);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}






/*
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		if (error_state==1)// jesli uruchomiono program bez karty SD w module, zle podpieto kable
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		}
		if (error_state==2)// jesli wyjeto karte SD w trakcie odtwarzania plikow
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		}
		if (error_state==3)// jesli na karcie SD nie ma plikow .wav
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		}

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
*/


/*
void ERROR_TIM_4()
{
	// TIMER DO OBSLUGI DIOD W PRZYPADKU BLEDU
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIMER_4;

	TIMER_4.TIM_Period = 24000-1;
	TIMER_4.TIM_Prescaler = 1000-1;
	TIMER_4.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMER_4.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIMER_4);
	TIM_Cmd(TIM4,DISABLE);

	// KONFIGURACJA PRZERWAN - TIMER/COUNTER
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet glowny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// uruchom dany kanal
	NVIC_Init(&NVIC_InitStructure);// zapisz wypelniona strukture do rejestrow
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);// wyczyszczenie przerwania od timera 4 (wystapilo przy konfiguracji timera)
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);// zezwolenie na przerwania od przepelnienia dla timera 4
}
*/


//===

void Konfiguracja_przyciskow(){

	Konfiguracja_pinow_wejsciowych();
	Konfiguracja_przerwan_wejsciowych();
}

void Konfiguracja_pinow_wejsciowych(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef piny;

	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

	piny.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	piny.GPIO_Mode = GPIO_Mode_IN;
	piny.GPIO_OType = GPIO_OType_PP;
	piny.GPIO_Speed = GPIO_Speed_100MHz;
	piny.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &piny);
}

void Konfiguracja_przerwan_wejsciowych(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef przerwanie;
	przerwanie.NVIC_IRQChannelPreemptionPriority = 0x00;
	przerwanie.NVIC_IRQChannelSubPriority = 0x00;
	przerwanie.NVIC_IRQChannelCmd = ENABLE;

	EXTI_InitTypeDef linia_przerwania;
	linia_przerwania.EXTI_Mode = EXTI_Mode_Interrupt;
	linia_przerwania.EXTI_Trigger = EXTI_Trigger_Rising;
	linia_przerwania.EXTI_LineCmd = ENABLE;

	//---

	przerwanie.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&przerwanie);

	linia_przerwania.EXTI_Line = EXTI_Line9;
	EXTI_Init(&linia_przerwania);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);
}

//===

void Konfiguracja_debouncera(){

	Konfiguracja_timera_debouncera();
	Konfiguracja_przerwania_debouncera();
	Aktywacja_timera_debouncera();
}

void Konfiguracja_timera_debouncera(){

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM_TimeBaseInitTypeDef zegar;
	zegar.TIM_Period = 199;
	zegar.TIM_Prescaler = 8399;
	zegar.TIM_ClockDivision = TIM_CKD_DIV1;
	zegar.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &zegar);

	TIM_Cmd(TIM5, DISABLE);
}

void Konfiguracja_przerwania_debouncera(){

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef przerwanie;
	przerwanie.NVIC_IRQChannel = TIM5_IRQn;
	przerwanie.NVIC_IRQChannelPreemptionPriority = 0x00;
	przerwanie.NVIC_IRQChannelSubPriority = 0x00;
	przerwanie.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&przerwanie);
}

void Aktywacja_timera_debouncera(){

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
}

//===

void Konfiguracja_diod()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef  DIODES;

	DIODES.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	DIODES.GPIO_Mode = GPIO_Mode_OUT;
	DIODES.GPIO_OType = GPIO_OType_PP;
	DIODES.GPIO_Speed = GPIO_Speed_100MHz;
	DIODES.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &DIODES);
}

//===

void MY_DMA_initM2P()
{
	DMA_InitTypeDef  DMA_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;// wybor kanalu DMA
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;// ustalenie rodzaju transferu (memory2memory / peripheral2memory /memory2peripheral)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// tryb pracy - pojedynczy transfer badz powtarzany
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;// ustalenie priorytetu danego kanalu DMA
	DMA_InitStructure.DMA_BufferSize = 2048;// liczba danych do przeslania
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sample_buffer;// adres zrodlowy
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI3->DR));// adres docelowy
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// zezwolenie na inkrementacje adresu po kazdej przeslanej paczce danych
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;// ustalenie rozmiaru przesylanych danych
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;// ustalenie trybu pracy - jednorazwe przeslanie danych
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;// wylaczenie kolejki FIFO
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

	DMA_Init(DMA1_Stream5, &DMA_InitStructure);// zapisanie wypelnionej struktury do rejestrow wybranego polaczenia DMA
	DMA_Cmd(DMA1_Stream5, ENABLE);// uruchomienie odpowiedniego polaczenia DMA

	SPI_I2S_DMACmd(SPI3,SPI_I2S_DMAReq_Tx,ENABLE);
	SPI_Cmd(SPI3,ENABLE);
}
void ADC_conversion()
{
	// Odczyt wartosci przez odpytnie flagi zakonczenia konwersji
	// Wielorazowe sprawdzenie wartosci wyniku konwersji
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	result_of_conversion = ((ADC_GetConversionValue(ADC1))/16);
}
void TIM2_ADC_init()
{
	// Wejscie do przerwania od TIM2 co <0.05 s
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// 2. UTWORZENIE STRUKTURY KONFIGURACYJNEJ
	TIM_TimeBaseInitTypeDef TIMER_2;
	TIMER_2.TIM_Period = 2100-1;// okres zliczania nie przekroczyc 2^16!
	TIMER_2.TIM_Prescaler = 2000-1;// wartosc preskalera, tutaj bardzo mala
	TIMER_2.TIM_ClockDivision = TIM_CKD_DIV1;// dzielnik zegara
	TIMER_2.TIM_CounterMode = TIM_CounterMode_Up;// kierunek zliczania
	TIM_TimeBaseInit(TIM2, &TIMER_2);
	TIM_Cmd(TIM2, ENABLE);// Uruchomienie Timera

	// KONFIGURACJA PRZERWAN - TIMER/COUNTER
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;// numer przerwania
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;// priorytet glowny
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// uruchom dany kanal
	NVIC_Init(&NVIC_InitStructure);// zapisz wypelniona strukture do rejestrow
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);// wyczyszczenie przerwania od timera 2 (wystapilo przy konfiguracji timera)
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);// zezwolenie na przerwania od przepelnienia dla timera 2
}
void ADC_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//---

	GPIO_InitTypeDef  GPIO_InitStructureADC;

	GPIO_InitStructureADC.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructureADC.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructureADC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructureADC);

	//---

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

	//---

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);

	TIM2_ADC_init();
}











bool read_and_send(FRESULT fresult, int position, volatile ITStatus it_status, UINT read_bytes, uint32_t DMA_FLAG)
{


	it_status = RESET;
	while(it_status == RESET)
	{
		it_status = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG);
	}
	fresult = f_read (&file,&sample_buffer[position],1024*2,&read_bytes);
	DMA_ClearFlag(DMA1_Stream5, DMA_FLAG);

	if(fresult != FR_OK)// jesli wyjeto karte w trakcie odtwarzania plikow
	{
		error_state=2;

		return 0;
	}
	if(read_bytes<1024*2||change_song!=0)
	{
		return 0;
	}
	return 1;
}

void play_wav(int piosenka)
{

	UINT read_bytes;// uzyta w f_read
	fresult = f_open( &file, utwory[piosenka], FA_READ );
	if( fresult == FR_OK )
	{
		fresult=f_lseek(&file,44);// pominiecie 44 B naglowka pliku .wav
		volatile ITStatus it_status;// sprawdza flage DMA
		change_song=0;


		while(1)
		{
			if (read_and_send(fresult,0, it_status, read_bytes, DMA_FLAG_HTIF5)==0)
			{
				break;
			}
			if (read_and_send(fresult, 1024, it_status, read_bytes, DMA_FLAG_TCIF5)==0)
			{
				break;
			}
		}

		GPIO_SetBits(GPIOD, GPIO_Pin_13);

		Codec_VolumeCtrl(0);

		fresult = f_close(&file);
	}
}


int main( void )
{
	SystemInit();

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);


	delay_init( 80 );// wyslanie 80 impulsow zegarowych; do inicjalizacji SPI
	SPI_SD_Init();// inicjalizacja SPI pod SD




	// SysTick_CLK... >> taktowany z f = ok. 82MHz/8 = ok. 10MHz
	// Systick_Config >> generuje przerwanie co <10ms
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);// zegar 24-bitowy
	//SysTick_Config(90000);

	// SD CARD





	disk_initialize(0);// inicjalizacja karty
	fresult = f_mount( &fatfs, 1,1 );// zarejestrowanie dysku logicznego w systemie



	codec_init();
	codec_ctrl_init();
	I2S_Cmd(CODEC_I2S, ENABLE);// Integrated Interchip Sound to connect digital devices
	MY_DMA_initM2P();

	ADC_init();

	Konfiguracja_diod();

	Konfiguracja_przyciskow();
	Konfiguracja_debouncera();







//	RNG_Cmd(ENABLE);
//	u32 rand_number=0;
	//u32 i_loop=0;
	//GPIO_SetBits(GPIOD, GPIO_Pin_14);




	for(;;)
	{
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)){

			obecny_utwor = 0;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)){

			obecny_utwor = 1;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)){

			obecny_utwor = 2;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)){

			obecny_utwor = 3;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)){

			obecny_utwor = 4;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)){

			obecny_utwor = 5;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)){

			obecny_utwor = 6;
		}

		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)){

			obecny_utwor = 7;
		}

		if(graj == 1){

			play_wav(obecny_utwor);
			play_wav(8);

			graj = 0;
		}

		posladki++;
	}

	return 0;
}

//===

void SysTick_Handler()
{
	disk_timerproc();
}
