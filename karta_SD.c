#include "karta_SD.h"

void Inicjalizacja_karty_SD(FRESULT *fresult, FATFS *fatfs){

	 disk_initialize(0);
	 *fresult = f_mount(&*fatfs, 1, 1);
}

void Otworz_plik(FRESULT *fresult, FIL *plik_wav, const TCHAR *sciezka){

	*fresult = f_open(&*plik_wav, sciezka, FA_CREATE_ALWAYS);  //FA_READ

	*fresult = f_close(&*plik_wav); // <--- X
}
