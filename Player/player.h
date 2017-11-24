#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Main/common_types.h"
#include "../Gameplay/mechanics.h"

/* Type definitions */
typedef struct {
    int id;
    boolean alive;
    CashType cash;
    CashType income;
    CashType upkeep;
    int king_id;
    int units[100];
    int unit_count;
} Player;

typedef struct PlayerListElmt *PlayerListElmtAddress;
typedef struct PlayerListElmt {
	Player player;
	PlayerListElmtAddress next;
	PlayerListElmtAddress prev;
} PlayerListElmt;

typedef struct {
	PlayerListElmtAddress first;
    PlayerListElmtAddress last;
} PlayerList;

/* External global variable */
extern PlayerList player_list;

/* Prototypes */
/* Player primitives */
void EmptyPlayerUnits(Player *player);
void AddUnitToPlayer(Player *player, int id);
void DeleteUnitFromPlayer(Player *player, int id);
// void EmptyPlayerVillages(Player *player);
// void AddVillageToPlayer(Player *player, int id);
// void DeleteVillageFromPlayer(Player *player, int id);

/* List primitives */
PlayerListElmtAddress AllocatePlayer(Player player);
void DeallocatePlayer(PlayerListElmtAddress player_address);
void EmptyPlayerList();
void InsertPlayer(PlayerListElmtAddress player_address);
void RemovePlayer(PlayerListElmtAddress player_address);
PlayerListElmtAddress GetPlayerAddress(int id);
int GetNewPlayerId();

/* CRUD operations */
/* Add a new player to the database, return the new player's id */
int CreatePlayer(Player player);

/* Add a new player to the database (id already specified) */
void AddPlayerWithId(Player player);

/* Delete a player with specified id in the database */
void DeletePlayer(int id);

/* Update player with the same id's data in the database */
void UpdatePlayer(Player player);

/* Get a player with specified id from the database */
Player GetPlayer(int id);

/* Primitives */
/*Return default player stat*/
Player NewDefaultPlayer();

/*Create 2 default player*/
void InitializePlayer();


#endif
