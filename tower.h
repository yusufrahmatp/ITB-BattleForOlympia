#ifndef TOWER_H_
#define TOWER_H_

#include "common_types.h"

typedef struct {
    int id;
    int player_id;
} Tower;

typedef struct TowerListElmt *TowerListElmtAddress;
typedef struct TowerListElmt {
	Tower tower;
	TowerListElmtAddress next;
	TowerListElmtAddress prev;
} TowerListElmt;

typedef struct {
	TowerListElmtAddress first;
    TowerListElmtAddress last;
} TowerList;

/* External global variable */
extern TowerList tower_list;

/* Prototypes */
/* List primitives */
TowerListElmtAddress AllocateTower(Tower tower);
void DeallocateTower(TowerListElmtAddress tower_address);
void EmptyTowerList();
void InsertTower(TowerListElmtAddress tower_address);
void RemoveTower(TowerListElmtAddress tower_address);
TowerListElmtAddress GetTowerAddress(int id);
int GetNewTowerId();

/* CRUD operations */
/* Add a new tower to the database, return the new tower's id */
int CreateTower(Tower tower);

/* Delete a tower with specified id in the database */
void DeleteTower(int id);

/* Update tower with the same id's data in the database */
void UpdateTower(Tower tower);

/* Get a tower with specified id from the database */
Tower GetTower(int id);

#endif
