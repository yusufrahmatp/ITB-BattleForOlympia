#include <stdio.h>
#include "point.h"
#include "math.h"

Point MakePoint (int X, int Y){
/* Membentuk sebuah Point dari komponen-komponennya */
	Point P;
	row(P) 	= X;
	col(P) 	= Y;

	return P;
}

void TulisPoint (Point P){
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
	printf("(%d,%d)", row(P), col(P));
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	return ((row(P1) == row(P2)) && (col(P1) == col(P2)));
}
