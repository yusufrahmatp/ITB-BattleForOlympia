/* File: jam.c */
/* Tanggal: 29 Agustus 2017 */
/* IMPLEMENTASI ADT JAM */

/* *** IMPLEMENTASI TYPE JAM <HH:MM:SS> *** */
#include "jam.h"
#include <stdio.h>

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S) {
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
	/* ALGORITMA */
	return (((H>=0)&&(H<24)) && ((M>=0)&&(M<60)) && ((S>=0)&&(S<60)));
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS) {
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
	/* KAMUS */
	JAM time;
	/* ALGORITMA */
	Hour(time) = HH;
	Minute(time) = MM;
	Second(time) = SS;

	return time;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J) {
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
	/* KAMUS */
	int H, M, S;
	/* ALGORITMA */
	do {
		scanf("%d %d %d", &H, &M, &S);
		if (!IsJAMValid(H, M, S)) {
			printf("Jam tidak valid\n");
		}
	} while (!IsJAMValid(H, M, S));

	*J = MakeJAM(H, M, S);
}
   
void TulisJAM (JAM J) {
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
	/*ALGORITMA*/
	printf("%02d:%02d:%02d", Hour(J), Minute(J), Second(J));
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToDetik (JAM J) {
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
	/*ALGORITMA*/
	return(3600*Hour(J)+60*Minute(J)+Second(J));
}

JAM DetikToJAM (long N) {
/* Mengirim  konversi detik ke JAM */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi JAM */
	/*ALGORITMA*/
	N = N % 86400;
	return(MakeJAM((N/3600), ((N%3600)/60), (N%60)));
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2) {
/* Mengirimkan true jika J1=J2, false jika tidak */
	/*ALGORITMA*/
	return(JAMToDetik(J1)==JAMToDetik(J2));
}
boolean JNEQ (JAM J1, JAM J2) {
/* Mengirimkan true jika J1 tidak sama dengan J2 */
	/*ALGORITMA*/
	return(!JEQ(J1, J2));
}
boolean JLT (JAM J1, JAM J2) {
/* Mengirimkan true jika J1<J2, false jika tidak */
	/*ALGORITMA*/
	return(JAMToDetik(J1)<JAMToDetik(J2));
}
boolean JGT (JAM J1, JAM J2) {
/* Mengirimkan true jika J1>J2, false jika tidak */
	/*ALGORITMA*/
	return(JAMToDetik(J1)>JAMToDetik(J2));
}
/* *** Operator aritmatika JAM *** */
JAM NextDetik (JAM J) {
/* Mengirim 1 detik setelah J dalam bentuk JAM */
	/*ALGORITMA*/
	return(DetikToJAM(JAMToDetik(J)+1));
}
JAM NextNDetik (JAM J, int N) {
/* Mengirim N detik setelah J dalam bentuk JAM */
	/*ALGORITMA*/
	return(DetikToJAM(JAMToDetik(J)+N));
}
JAM PrevDetik (JAM J) {
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
	/*KAMUS*/
	long waktu;
	/*ALGORITMA*/
	waktu = JAMToDetik(J) - 1;
	if(waktu == (-1)) {
		waktu = 86399;
	}

	return(DetikToJAM(waktu));
}
JAM PrevNDetik (JAM J, int N) {
/* Mengirim N detik sebelum J dalam bentuk JAM */
/* *** Kelompok Operator Aritmetika *** */
	/*KAMUS*/
	int i;
	long waktu;
	/*ALGORITMA*/
	waktu = JAMToDetik(J);
	waktu = waktu - N;
	while (waktu<0) {
		waktu = 86400 + waktu;
	}
	return DetikToJAM(waktu);
}
long Durasi (JAM JAw, JAM JAkh) {
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
	/*KAMUS*/
	long selisih;
	/*ALGORITMA*/
	selisih = JAMToDetik(JAkh) - JAMToDetik(JAw);
	if(selisih < 0) {
		selisih = 86400 + selisih;
	}
	return selisih;
}
