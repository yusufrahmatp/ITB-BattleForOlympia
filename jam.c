/* File: jam.c */
/* Tanggal: 29 Agustus 2017 */
/* IMPLEMENTASI ADT JAM */

/* *** IMPLEMENTASI TYPE JAM <HH:MM:SS> *** */
#include "jam.h"
#include <stdio.h>

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int year, int month, int day, int hour, int minute, int second) {
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
	/* KAMUS */
	JAM time;
	/* ALGORITMA */
	time.year = year;
	time.month = month;
	time.day = day;
	time.hour = hour;
	time.minute = minute;
	time.second = second;

	return time;
}
