/*
 * SD.c
 *
 *  Created on: 14 cze 2016
 *      Author: Karol
 */
#include "stm32f10x.h"
#include "MPU6050.h"
#include "ff.h"
#include "SPI_MSD_Driver.h"
#include <stdio.h>

int SD_TotalSize(void) {
	FATFS *fs;
	DWORD fre_clust;
	FRESULT res;

	res = f_getfree("0:", &fre_clust, &fs);
	if (res == FR_OK) {

		printf("\r\n%d MB total drive space.\r\n"
				"%d MB available.\r\n",
				((fs->n_fatent - 2) * fs->csize) / 2 / 1024,
				(fre_clust * fs->csize) / 2 / 1024);

		return ENABLE;
	} else
		return DISABLE;
}

FRESULT scan_files(char* path) {
	FILINFO fno;
	DIR dir;
	int i;
	char *fn;
	FRESULT res;
#if _USE_LFN
	static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
	fno.lfname = lfn;
	fno.lfsize = sizeof(lfn);
#endif

	res = f_opendir(&dir, path);
	if (res == FR_OK) {
		i = strlen(path);
		for (;;) {
			res = f_readdir(&dir, &fno);
			if (res != FR_OK || fno.fname[0] == 0)
				break;
			if (fno.fname[0] == '.')
				continue;
#if _USE_LFN
			fn = *fno.lfname ? fno.lfname : fno.fname;
#else
			fn = fno.fname;
#endif
			if (fno.fattrib & AM_DIR) {
				sprintf(&path[i], "/%s", fn);
				res = scan_files(path);
				if (res != FR_OK)
					break;
				path[i] = 0;
			} else {
				printf("%s/%s \r\n", path, fn);
			}
		}
	}

	return res;
}

void card_check(FATFS* fs) {
	if ( _card_insert() == 0) {
		printf("-- SD card detected OK \r\n");

	} else {
		printf("-- Please connect a SD card \r\n");
		while ( _card_insert() != 0)
			;
		printf("-- SD card connection detected \r\n");
	}

	f_mount(0, fs);
}

FRESULT open_append(FIL* fp, const char* path) {
	FRESULT fr;

	/* Opens an existing file. If not exist, creates a new file. */
	fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
	if (fr == FR_OK) {
		/* Seek to end of the file to append data */
		fr = f_lseek(fp, f_size(fp));
		if (fr != FR_OK)
			f_close(fp);
	}
	return fr;
}

void SD_write(){

}
