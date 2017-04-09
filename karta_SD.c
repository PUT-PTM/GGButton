#include "karta_SD.h"

void Inicjalizacja_karty_SD(FRESULT *fresult, FATFS *fatfs){

	 disk_initialize(0);
	 *fresult = f_mount(&*fatfs, 1, 1);
}

void Odtwarzaj_utwor(FRESULT *fresult, FIL *plik_wav, UINT licznik, const TCHAR *sciezka, u16 DMA_buffer[]){

	*fresult = f_open(&*plik_wav, sciezka, FA_READ); //FA_CREATE_ALWAYS

	//--- wczytanie pierwszych 44 bajtow naglowka wav + jednej probki 2b

	f_lseek(&*plik_wav,44);
	f_read(&*plik_wav, &DMA_buffer[0], 2048, &licznik);

	//--- pobieranie bufora

    volatile ITStatus it_st; // sprawdzenie flagi DMA

    while(1)
    {
        it_st = RESET;
        while(it_st == RESET)
        {
            it_st = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_HTIF5); // pobieramy flage DMA HTIF ze streamu 5 (w polowie)
        }

        f_read(&*plik_wav, &DMA_buffer[0], 2048, &licznik); // czytaj kolejna probke (2B)
        DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_HTIF5); //
        if(licznik<1024) break; // jezeli koniec utworu to wyjdz

        it_st = RESET;
        while(it_st == RESET)
        {
             it_st = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
        }

        f_read (&*plik_wav,&DMA_buffer[1024],2048,&licznik);
        DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5 );
        if(licznik<1024) break; // jezeli koniec utworu lub wcisnieto przycisk to wyjdz i zmien utwor
    }

	*fresult = f_close(&*plik_wav);
}




