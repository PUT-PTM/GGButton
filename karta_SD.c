#include "karta_SD.h"

void Inicjalizacja_karty_SD(FRESULT *fresult, FATFS *fatfs){

	 disk_initialize(0);
	 *fresult = f_mount(&*fatfs, 1, 1);
}

void Odtwarzaj_utwor(FRESULT *fresult, FIL *plik_wav, UINT licznik, const TCHAR *sciezka, u16 DMA_buffer[]){

	*fresult = f_open(&*plik_wav, sciezka, FA_CREATE_ALWAYS); //FA_READ

	//--- wczytanie pierwszych 44 bajtow naglowka wav + jednej probki 2b

	f_lseek(&*plik_wav,44);
	f_read(&*plik_wav, &DMA_buffer[0], 2048, &licznik);





	*fresult = f_close(&*plik_wav);


}




