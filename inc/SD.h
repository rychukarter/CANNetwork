/*
 * SD.h
 *
 *  Created on: 14 cze 2016
 *      Author: Karol
 */

#ifndef SD_H_
#define SD_H_

extern int SD_TotalSize(void);
extern FRESULT scan_files(char* path);
extern void card_check(FATFS* fs);
extern FRESULT open_append(FIL* fp, const char* path);

extern void SD_write();

#endif /* SD_H_ */
