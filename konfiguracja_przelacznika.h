#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "przerwania_zewnetrzne.h"

#ifndef przelocznik
#define przelocznik

void Przelacznik_konfiguracja();
void Przelacznik_konfiguracja_wejscia_GPIOE();
void Przelacznik_konfiguracja_przerwan_zewnetrznych();

#endif
