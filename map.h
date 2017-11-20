#ifndef MAP_H_
#define MAP_H_

#include "common_types.h"
#include "point_queue.h"

#define BRS_MIN 1
#define BRS_MAX 100
#define KOL_MIN 1
#define KOL_MAX 100

#define UNIT_ID_UNDEF -1
#define PLAYER_ID_UNDEF -1
#define UNIT_TYPE_UNDEF -1

#define C_TOWER_TYPE 'T'
#define C_CASTLE_TYPE 'C'
#define C_VILLAGE_TYPE 'V'
#define C_NORMAL_TYPE 'N'

typedef int indeks;
typedef int playerIdType;
typedef int unitIdType;

typedef struct tElType {
	char grid_type;
	UnitType unit_type;
	int player_id;
	int unit_id;
	int unit_player_id;
	boolean visitable;
} ElType;

typedef struct {
	ElType mem[BRS_MAX][KOL_MAX];
    int n_brs_eff;
	int n_kol_eff;
} Map;

extern Map map;
extern Point tower_p1_loc;
extern Point tower_p2_loc;
extern Point castle_p1_loc[4];
extern Point castle_p2_loc[4];

void InitializeMap(int row, int col);
void InitializeCastleTower();
void CreateMap(int row, int col);

boolean IsGridAvailable(int i, int j);
boolean IsMapEmpty();

void AssignPlayerId(Point loc, int player_id);
void AssignGridType(Point loc, char grid_type);
void AssignGridPlayer(Point loc, int player_id);
void AssignGridUnit(Point loc, int unit_id);

void PrintStar(int n);
void PrintGridTypeLine(int i);
void PrintGridUnitLine(int i);
void PrintGridThird(int i);
void PrintMap();
void PrintGridType(char grid_type);
void PrintGridPlayer(int player_id);
void PrintGridInfo(int row, int col);

boolean IsInfotypeValid(int n, int m, infotype X);

void ClearMapVisitable();

void UpdateMap();

void UpdateMapMovePath();

void MoveMap();

void Undo();

int RandomNumber(int min_num, int max_num, int multiplier);

boolean IsBuildingEmpty(int i, int j);

void MakeRandomVillage(int multiplier);

#endif
