#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_spi.h"

#ifndef bouncer
#define bouncer

void Konfiguracja_debouncera();
void Konfiguracja_timera_debouncera();
void Konfiguracja_przerwania_debouncera();
void Aktywacja_timera_debouncera();

#endif
