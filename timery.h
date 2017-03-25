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

void Ustaw_zegar(Timer tim, unsigned int prescaler, unsigned int period);
void aktywacja_przerwania_dla_timera(Timer tim);

#endif
