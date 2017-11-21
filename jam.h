#ifndef JAM_H
#define JAM_H

#include "boolean.h"

/* *** Definisi TYPE JAM <HH:MM:SS> *** */
typedef struct {
	int hour; /* integer [0..23] */
	int minute; /* integer [0..59] */
	int second; /* integer [0..59] */
   int year;
   int month;
   int day;
} JAM;

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int year, int month, int day, int hour, int minute, int second);
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */

#endif