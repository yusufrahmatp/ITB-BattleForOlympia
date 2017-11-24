#include <stdio.h>
#include <stdlib.h>
#include "common_types.h"
#include "player.h"

/* External global variable */
PlayerList player_list;

/* Player primitives */
/* Units array */
void EmptyPlayerUnits(Player *player) {
    player->unit_count = 0;
}
void AddUnitToPlayer(Player *player, int id) {
    for (int i = 0; i < player->unit_count; i ++) {
        if (player->units[i] == id) return;
    }
    player->units[player->unit_count] = id;
    player->unit_count ++;
}
void DeleteUnitFromPlayer(Player *player, int id) {
    for (int i = 0; i < player->unit_count; i ++) {
        if (player->units[i] == id) {
            for (int j = i; j < player->unit_count - 1; j ++) {
                player->units[j] = player->units[j + 1];
            }
        }
    }
    player->unit_count --;
}
/* Units array */
// void EmptyPlayerVillages(Player *player) {
//     player->village_count = 0;
// }
// void AddVillageToPlayer(Player *player, int id) {
//     for (int i = 0; i < player->village_count; i ++) {
//         if (player->villages[i] == id) return;
//     }
//     player->villages[player->village_count] = id;
//     player->village_count ++;
// }
// void DeleteVillageFromPlayer(Player *player, int id) {
//     for (int i = 0; i < player->village_count; i ++) {
//         if (player->villages[i] == id) {
//             for (int j = i; j < player->village_count - 1; j ++) {
//                 player->villages[j] = player->villages[j + 1];
//             }
//         }
//     }
//     player->village_count --;
// }

/* List primitives */
PlayerListElmtAddress AllocatePlayer(Player player) {
    PlayerListElmtAddress new_player_address = malloc(sizeof(PlayerListElmt));
    if (new_player_address != NULL) {
        new_player_address->player = player;
        new_player_address->next = NULL;
        new_player_address->prev = NULL;
        return new_player_address;
    } else {
        printf("ERROR: Allocation failed.\n");
        return NULL;
    }
}

void DeallocatePlayer(PlayerListElmtAddress player_address) {
    free(player_address);
}

void EmptyPlayerList() {
    player_list.first = NULL;
    player_list.last = NULL;
}

void InsertPlayer (PlayerListElmtAddress player_address) {
    /* Insert new player list elmt to head of list */
    if (player_list.first == NULL) {
        player_list.first = player_address;
        player_list.last = player_address;
    } else {
        PlayerListElmtAddress trav = player_list.first;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = player_address;
        player_address->prev = trav;
        player_address->next = NULL;
        player_list.last = player_address;
    }
}

void RemovePlayer(PlayerListElmtAddress player_address) {
    /* Remove a player with specified address from list */
    if (player_list.first == player_list.last) {
        player_list.first = NULL;
        player_list.last = NULL;
    } else if (player_list.first == player_address) {
        player_list.first = player_list.first->next;
        player_list.first->prev = NULL;
    } else if (player_list.last == player_address) {
        player_list.last = player_list.last->prev;
        player_list.last->next = NULL;
    } else {
        PlayerListElmtAddress trav = player_list.first;
        while (trav != NULL) {
            if (trav == player_address) {
                trav->prev->next = trav->next;
                trav->next->prev = trav->prev;
                break;
            }
            trav = trav->next;
        }
    }
    DeallocatePlayer(player_address);
}

PlayerListElmtAddress GetPlayerAddress(int id) {
    /* Get player address with specified id, if not exist returns NULL */
    PlayerListElmtAddress trav = player_list.first;
    while (trav != NULL) {
        if (trav->player.id == id) {
            return trav;
            break;
        }
        trav = trav->next;
    }
    return NULL;
}

int GetNewPlayerId() {
    int new_id = NEW_ID_START;
    PlayerListElmtAddress trav = player_list.first;
    while (trav != NULL) {
        if (trav->player.id == new_id) {
            new_id ++;
        }
        trav = trav->next;
    }
    return new_id;
}

/* CRUD operations */
int CreatePlayer(Player player) {
    int new_player_id = GetNewPlayerId();
    player.id = new_player_id;
    PlayerListElmtAddress new_player_address = AllocatePlayer(player);
    InsertPlayer(new_player_address);
    return new_player_id;
}

void AddPlayerWithId(Player player) {
    PlayerListElmtAddress new_player_address = AllocatePlayer(player);
    // List empty
    if (player_list.first == NULL) {
        player_list.first = new_player_address;
        player_list.last = new_player_address;
    // not empty
    } else {
        boolean added = false;
        PlayerListElmtAddress trav = player_list.first;
        while (trav != NULL) {
            if (trav->player.id < player.id) {
                // new_player_address->next = trav;
                // new_player_address->prev = trav->prev;
                // trav->prev = new_player_address;
                // if (trav != player_list.first) {
                //     trav->prev->next = new_player_address;
                // } else {
                //     player_list.first = new_player_address;
                // }
                // added = true;
                trav = trav->next;
            }
            else {
                if(trav == player_list.first) {
                    trav->prev = new_player_address;
                    new_player_address->next = trav;
                }
                else {
                    trav->prev->next = new_player_address;
                    new_player_address->prev = trav->prev;
                    trav->prev = new_player_address;
                    new_player_address->next = trav;
                }
                added = true;
                break;
            }
        }
        if (!added) {
            player_list.last->next = new_player_address;
            new_player_address->prev = player_list.last;
            player_list.last = new_player_address;
        }
    }
}

void DeletePlayer(int id) {
    PlayerListElmtAddress player_address = GetPlayerAddress(id);
    RemovePlayer(player_address);
}

void UpdatePlayer(Player player) {
    PlayerListElmtAddress player_address = GetPlayerAddress(player.id);
    if (player_address != NULL) {
        player_address->player = player;
    }
}

Player GetPlayer(int id) {
    PlayerListElmtAddress player_address = GetPlayerAddress(id);
    return player_address->player;
}

/*Return default player stat*/
Player NewDefaultPlayer() {
    Player player;
    player.alive = true;
    player.cash = DEFAULT_CASH;
    player.income = 0;
    player.upkeep = 0;
    player.unit_count = 0;
    // player.village_count = 0;
    return player;
}

void InitializePlayer() {

    int p1_id, p2_id;
    p1_id = CreatePlayer(NewDefaultPlayer());
    p2_id = CreatePlayer(NewDefaultPlayer());

    Player player1 = GetPlayer(1);
    Player player2 = GetPlayer(2);

    Unit king1;
    king1.player_id = 1;
    king1.attack_type = MELEE;
    king1.type = KING;
    king1.max_health = MAX_HEALTH_KING;
    king1.health = MAX_HEALTH_KING;
    king1.attack = ATTACK_KING;
    king1.max_move_points = MAX_MOVE_PTS_KING;
    king1.move_points = MAX_MOVE_PTS_KING;
    king1.can_attack = true;
    Point king1_loc = tower_p1_loc;
    king1.location = king1_loc;
    king1.price = 0;
    king1.heal = 0;

    Unit king2;
    king2.player_id = 2;
    king2.attack_type = MELEE;
    king2.type = KING;
    king2.max_health = MAX_HEALTH_KING;
    king2.health = MAX_HEALTH_KING;
    king2.attack = ATTACK_KING;
    king2.max_move_points = MAX_MOVE_PTS_KING;
    king2.move_points = MAX_MOVE_PTS_KING;
    king2.can_attack = true;
    Point king2_loc = tower_p2_loc;
    king2.location = king2_loc;
    king2.price = 0;
    king2.heal = 0;

    player1.king_id = CreateUnit(king1);
    player2.king_id = CreateUnit(king2);

    AssignGridUnit(king1_loc, player1.king_id);
    AssignGridUnit(king2_loc, player2.king_id);

    UpdatePlayer(player1);
    UpdatePlayer(player2);

}
