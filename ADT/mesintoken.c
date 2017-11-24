/*
 * Nama    	: Abram Perdanaputra
 * NIM     	: 13516083
 * Tanggal	: Kamis, 28 September 2017
 * Topik	: ADT Mesin Kata
*/

/* File: mesintoken.h */
/* Definisi Mesin Token: Model Akuisisi Versi I */

#include "boolean.h"
#include "mesintoken.h"
#include <stdio.h>

/* State Mesin Kata */
boolean End;
char CString[100];
int CInt;

void AdvanceInt(FILE * P)
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	fscanf(P, "%d", &CInt);
}

void AdvanceString(FILE * P)
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{

    fscanf(P, "%s", CString);
}
