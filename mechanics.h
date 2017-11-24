#ifndef MECHANICS_H
#define MECHANICS_H

#include <stdio.h>
#include <string.h>
#include "common_types.h"

/* Global variables */
extern int active_player_id;
extern int active_unit_id;
extern int map_width;
extern int map_height;

/* Game data */
/* Men-generate data untuk game baru */
void NewGameData();
/* Me-load data game dari file eksternal */
void LoadGameData();
/* Men-save data game ke file eksternal */
int SaveGameData();

/* Game flow */
/* Menginisialisasi game: menjalankan NewGameData atau LoadGameData */
void InitializeGame();
/* Loop utama game. Menjakankan PlayTurn untuk setiap player sampe ada yang menang. */
void PlayGame();
/* Menjalankan turn suatu player. Minta input, jalanin, ulang ampe end turn. */
void PlayTurn();
/* Menampilkan pilihan untuk men-save game atau langsung keluar dari game. */
void ExitGame();
/* Menampilkan UI untuk save game. */
void SaveGame();

/* Game states */
/* Mengembalikan id player yang menang. Kalo belom ada yang menang, return 0 */
int CheckWinner();
void ResetActivePlayerUnitsState();

/* Game mechanics */
void Attack();
void Recruit();
/* Mengganti unit yang aktif dari seorang player */
void ChangeActiveUnit();
/* Mengganti unit yang aktif dari seorang player secara otomatis ke unit lainnya yang masih punya movement point atau kesempatan menyerang (bonus) */
void NextActiveUnit();
void WhiteMageEffect();
void UpdateUpkeep();
void UpdateIncome();

/* Game interface */
/* Menampilkan info sebuah lokasi di map */
void InfoMap();

void HealByVillage();

#endif
