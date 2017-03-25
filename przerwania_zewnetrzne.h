#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

#ifndef przerwanie
#define przerwanie

typedef enum port {A, B, C, D, E} port;

void Ustaw_przerwanie_zewnetrzne(unsigned char przerwanie_czego);
void Ustaw_pin_dla_przerwania_zewnetrznego(int linia_przerwania, unsigned int pin, port port_GPIO);

#endif
