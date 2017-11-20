#ifndef VILLAGE_H_
#define VILLAGE_H_

#include "common_types.h"

typedef struct {
    int id;
    int player_id;
} Village;

typedef struct VillageListElmt *VillageListElmtAddress;
typedef struct VillageListElmt {
	Village village;
	VillageListElmtAddress next;
	VillageListElmtAddress prev;
} VillageListElmt;

typedef struct {
	VillageListElmtAddress first;
    VillageListElmtAddress last;
} VillageList;

/* External global variable */
extern VillageList village_list;

/* Prototypes */
/* List primitives */
VillageListElmtAddress AllocateVillage(Village village);
void DeallocateVillage(VillageListElmtAddress village_address);
void EmptyVillageList();
void InsertVillage(VillageListElmtAddress village_address);
void RemoveVillage(VillageListElmtAddress village_address);
VillageListElmtAddress GetVillageAddress(int id);
int GetNewVillageId();

/* CRUD operations */
/* Add a new village to the database, return the new village's id */
int CreateVillage(Village village);

/* Delete a village with specified id in the database */
void DeleteVillage(int id);

/* Update village with the same id's data in the database */
void UpdateVillage(Village village);

/* Get a village with specified id from the database */
Village GetVillage(int id);

#endif
