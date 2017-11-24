/* File: mesintoken.h */
/* Definisi Mesin Token: Model Akuisisi Versi I */

#ifndef __MESINTOKEN_H__
#define __MESINTOKEN_H__

#include "boolean.h"
#include "mesinkar.h"
#include <stdio.h>

#define NMax 100
#define BLANK ' '
#define ENTER '\n'
#define MARK '.'

typedef struct {
  char tkn; /* token yang dibaca */
  int val;  /* nilai bilangan jika tkn = 'b' */
} Token;

/* State Mesin Kata */
extern boolean End;
extern char CString[100];
extern int CInt;

void AdvanceInt(FILE * P);

void AdvanceString(FILE * P);


#endif
