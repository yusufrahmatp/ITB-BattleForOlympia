#include <stdio.h>
#include <stdlib.h>
#include "common_types.h"
#include "castle.h"

/* External global variable */
CastleList castle_list;

/* List primitives */
CastleListElmtAddress AllocateCastle(Castle castle) {
    CastleListElmtAddress new_castle_address = malloc(sizeof(CastleListElmt));
    if (new_castle_address != NULL) {
        new_castle_address->castle = castle;
        new_castle_address->next = NULL;
        new_castle_address->prev = NULL;
        return new_castle_address;
    } else {
        printf("ERROR: Allocation failed.\n");
		return NULL;
    }
}

void DeallocateCastle(CastleListElmtAddress castle_address) {
    free(castle_address);
}

void EmptyCastleList() {
    castle_list.first = NULL;
    castle_list.last = NULL;
}

void InsertCastle (CastleListElmtAddress castle_address) {
    /* Insert new castle list elmt to head of list */
    if (castle_list.first == NULL) {
        castle_list.first = castle_address;
        castle_list.last = castle_address;
    } else {
        CastleListElmtAddress trav = castle_list.first;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = castle_address;
        castle_address->prev = trav;
        castle_address->next = NULL;
        castle_list.last = castle_address;
    }
}

void RemoveCastle(CastleListElmtAddress castle_address) {
    /* Remove a castle with specified address from list */
    if (castle_list.first == castle_list.last) {
        castle_list.first = NULL;
        castle_list.last = NULL;
    } else if (castle_list.first == castle_address) {
        castle_list.first = castle_list.first->next;
        castle_list.first->prev = NULL;
    } else if (castle_list.last == castle_address) {
        castle_list.last = castle_list.last->prev;
        castle_list.last->next = NULL;
    } else {
        CastleListElmtAddress trav = castle_list.first;
        while (trav != NULL) {
            if (trav == castle_address) {
                trav->prev->next = trav->next;
                trav->next->prev = trav->prev;
                break;
            }
            trav = trav->next;
        }
    }
    DeallocateCastle(castle_address);
}

CastleListElmtAddress GetCastleAddress(int id) {
    /* Get castle address with specified id, if not exist returns NULL */
    CastleListElmtAddress trav = castle_list.first;
    while (trav != NULL) {
        if (trav->castle.id == id) {
            return trav;
            break;
        }
        trav = trav->next;
    }
    return NULL;
}

int GetNewCastleId() {
    int new_id = NEW_ID_START;
    CastleListElmtAddress trav = castle_list.first;
    while (trav != NULL) {
        if (trav->castle.id == new_id) {
            new_id ++;
        }
        trav = trav->next;
    }
    return new_id;
}

/* CRUD operations */
int CreateCastle(Castle castle) {
    int new_castle_id = GetNewCastleId();
    castle.id = new_castle_id;
    CastleListElmtAddress new_castle_address = AllocateCastle(castle);
    InsertCastle(new_castle_address);
    return new_castle_id;
}

void DeleteCastle(int id) {
    CastleListElmtAddress castle_address = GetCastleAddress(id);
    RemoveCastle(castle_address);
}

void UpdateCastle(Castle castle) {
    CastleListElmtAddress castle_address = GetCastleAddress(castle.id);
    if (castle_address != NULL) {
        castle_address->castle = castle;
    }
}

Castle GetCastle(int id) {
    CastleListElmtAddress castle_address = GetCastleAddress(id);
    return castle_address->castle;
}
