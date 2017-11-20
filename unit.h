#ifndef UNIT_H_
#define UNIT_H_

#include "common_types.h"

typedef struct {
    int id;
    int player_id;
    AttackType attack_type; // enum: RANGED, MELEE
    UnitType type; // enum: KING, ARCHER, SWORDSMAN, WHITE_MAGE
    HealthType max_health;
    HealthType health;
    AttackType attack;
    MovePointType max_move_points;
    MovePointType move_points;
    boolean can_attack;
    Point location;
    CashType price;
    HealType heal;
} Unit;

typedef struct UnitListElmt *UnitListElmtAddress;
typedef struct UnitListElmt {
	Unit unit;
	UnitListElmtAddress next;
	UnitListElmtAddress prev;
} UnitListElmt;

typedef struct {
	UnitListElmtAddress first;
    UnitListElmtAddress last;
} UnitList;

/* External global variable */
extern UnitList unit_list;

/* Prototypes */
/* List primitives */
UnitListElmtAddress AllocateUnit(Unit unit);
void DeallocateUnit(UnitListElmtAddress unit_address);
void EmptyUnitList();
void InsertUnit(UnitListElmtAddress unit_address);
void RemoveUnit(UnitListElmtAddress unit_address);
int GetUnitCount();
UnitListElmtAddress GetUnitAddress(int id);
int GetNewUnitId();

/* CRUD operations */
/* Add a new unit to the database, return the new unit's id */
int CreateUnit(Unit unit);

/* Add a new unit to the database (id already specified) */
void AddUnitWithId(Unit unit);

/* Delete a unit with specified id in the database */
void DeleteUnit(int id);

/* Update unit with the same id's data in the database */
void UpdateUnit(Unit unit);

/* Get a unit with specified id from the database */
Unit GetUnit(int id);

#endif
