#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

#ifndef timer
#define timer

typedef enum Timer {Tim1, Tim2, Tim3, Tim4, Tim5} Timer;

void Ustaw_zegar_ON(Timer tim, unsigned int prescaler, unsigned int period, int zasilanie);
void Aktywacja_przerwania_dla_timera(Timer tim);
void Konfiguracja_zegara_do_DEBOUNCERA_przerwan_zewnetrznych();

#endif
