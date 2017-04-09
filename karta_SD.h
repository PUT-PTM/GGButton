#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_spi.h"

#include "ff.h"
#include "diskio.h"

#ifndef SD
#define SD

void Inicjalizacja_karty_SD(FRESULT *fresult, FATFS *fatfs);
void Odtwarzaj_utwor(FRESULT *fresult, FIL *plik_wav, UINT licznik, const TCHAR *sciezka, u16 DMA_buffer[]);

#endif
