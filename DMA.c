#include "DMA.h"

void Konfiguracja_DMA(u16 DMA_buffer[]){

	DMA_InitTypeDef  DMA_init;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Stream5);

	DMA_init.DMA_Channel = DMA_Channel_0; // kanal
	DMA_init.DMA_PeripheralBaseAddr = (uint32_t)(&(SPI3->DR));// adres docelowy (SPI3 to kodek)
	DMA_init.DMA_Memory0BaseAddr = (uint32_t)&DMA_buffer;// adres zrodlowy
	DMA_init.DMA_DIR = DMA_DIR_MemoryToPeripheral;// memory to peripherial
	DMA_init.DMA_BufferSize = 2048;// liczba danych do przeslania (Probka 2B)
	DMA_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_init.DMA_Mode = DMA_Mode_Circular;
	DMA_init.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;// pol-slowo (flaga htif)
	DMA_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_init.DMA_FIFOMode = DMA_FIFOMode_Disable; //bez kolejki
	DMA_init.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

	DMA_Init(DMA1_Stream5, &DMA_init);
	DMA_Cmd(DMA1_Stream5, ENABLE);

	SPI_I2S_DMACmd(SPI3,SPI_I2S_DMAReq_Tx,ENABLE);
	SPI_Cmd(SPI3,ENABLE);
}
