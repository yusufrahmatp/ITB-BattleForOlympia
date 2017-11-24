/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>
#include <string.h>

/* State Mesin Kata */
boolean EndKata;
Kata CKata;
char CString[NMax+1];
int CInt;

boolean IsAtBlank() {

	return (CC == ' ' || CC == '\n');

}

boolean IsAtEnd() {

	return (CC == EOF);

}

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
	while (IsAtBlank()) {
		ADV();
	}
}

void STARTKATA(char file_name[100])
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
	START(file_name);
	IgnoreBlank();

	if (IsAtEnd()) {
		EndKata = true;
	}

}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	IgnoreBlank();
	if (IsAtEnd()) {
		EndKata = true;
	} else {
		SalinKata();
		IgnoreBlank();
		if (IsAtEnd()) {
			EndKata = true;
		}
	}
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
	CKata.Length = 0;
	while (!IsAtEnd() && !IsAtBlank() && (CKata.Length < NMax)) {
		CKata.Length ++;
		CKata.TabKata[CKata.Length] = CC;
		ADV();
	}
	IgnoreBlank();
}

void InitializeFileReader(char file_name[100]) {
	STARTKATA(file_name);
}

void AdvanceString() {
	ADVKATA();
	for (int i = 1; i <= CKata.Length; i++) {
		CString[i-1] = CKata.TabKata[i];
	}
	CString[CKata.Length] = '\0';
}

void AdvanceInt() {
	CInt = 0;
	boolean is_negative = false;

	if (EndKata) return;

	if (CC == '-') {
		is_negative = true;
		ADV();
		ADVKATA();
	} else {
		CInt = CC - '0';
		ADVKATA();
	}

	for (int i = 1; i <= CKata.Length; i++) {
		CInt = CInt*10 + (CKata.TabKata[i] - '0');
	}

	if (is_negative) {
		CInt *= -1;
	}
}
