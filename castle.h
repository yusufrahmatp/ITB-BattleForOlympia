#ifndef CASTLE_H_
#define CASTLE_H_

#include "common_types.h"

typedef struct {
	int id;
	int player_id;
	Point position;
	boolean has_unit;
} Castle;

typedef struct CastleListElmt *CastleListElmtAddress;
typedef struct CastleListElmt {
	Castle castle;
	CastleListElmtAddress next;
	CastleListElmtAddress prev;
} CastleListElmt;

typedef struct {
	CastleListElmtAddress first;
    CastleListElmtAddress last;
} CastleList;

/* External global variable */
extern CastleList castle_list;

/* Prototypes */
/* List primitives */
CastleListElmtAddress AllocateCastle(Castle castle);
void DeallocateCastle(CastleListElmtAddress castle_address);
void EmptyCastleList();
void InsertCastle(CastleListElmtAddress castle_address);
void RemoveCastle(CastleListElmtAddress castle_address);
CastleListElmtAddress GetCastleAddress(int id);
int GetNewCastleId();

/* CRUD operations */
/* Add a new castle to the database, return the new castle's id */
int CreateCastle(Castle castle);

/* Delete a castle with specified id in the database */
void DeleteCastle(int id);

/* Update castle with the same id's data in the database */
void UpdateCastle(Castle castle);

/* Get a castle with specified id from the database */
Castle GetCastle(int id);

#endif
