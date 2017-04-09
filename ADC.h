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

#ifndef adc
#define adc

void Konfiguracja_ADC();
void Konfiguracja_pinu_ADC();
void Konfiguracja_struktury_ADC();
void Konfiguracja_timera_ADC();
void Konfiguracja_przerwania_timera_ADC();
void Aktywacja_timera_ADC();
int Odczyt_wartosci_ADC();

#endif
