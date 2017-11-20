/* File: point.h */
/* Tanggal: 28 Agustus 2016 */
/* *** Definisi ABSTRACT DATA TYPE POINT *** */
#include <stdio.h>
#include <math.h>
#ifndef POINT_H
#define POINT_H

#include "boolean.h"

typedef struct {
	int X; /* absis   */
	int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor Point *** */
#define row(P) (P).X
#define col(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (int X, int Y);

void TulisPoint (Point P);

boolean EQ (Point P1, Point P2);

#endif
