#include <stdio.h>
#include <stdlib.h>
#include "../Main/common_types.h"
#include "tower.h"

/* External global variable */
TowerList tower_list;

/* List primitives */
TowerListElmtAddress AllocateTower(Tower tower) {
    TowerListElmtAddress new_tower_address = malloc(sizeof(TowerListElmt));
    if (new_tower_address != NULL) {
        new_tower_address->tower = tower;
        new_tower_address->next = NULL;
        new_tower_address->prev = NULL;
        return new_tower_address;
    } else {
        printf("ERROR: Allocation failed.\n");
		return NULL;
    }
}

void DeallocateTower(TowerListElmtAddress tower_address) {
    free(tower_address);
}

void EmptyTowerList() {
    tower_list.first = NULL;
    tower_list.last = NULL;
}

void InsertTower (TowerListElmtAddress tower_address) {
    /* Insert new tower list elmt to head of list */
    if (tower_list.first == NULL) {
        tower_list.first = tower_address;
        tower_list.last = tower_address;
    } else {
        TowerListElmtAddress trav = tower_list.first;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = tower_address;
        tower_address->prev = trav;
        tower_address->next = NULL;
        tower_list.last = tower_address;
    }
}

void RemoveTower(TowerListElmtAddress tower_address) {
    /* Remove a tower with specified address from list */
    if (tower_list.first == tower_list.last) {
        tower_list.first = NULL;
        tower_list.last = NULL;
    } else if (tower_list.first == tower_address) {
        tower_list.first = tower_list.first->next;
        tower_list.first->prev = NULL;
    } else if (tower_list.last == tower_address) {
        tower_list.last = tower_list.last->prev;
        tower_list.last->next = NULL;
    } else {
        TowerListElmtAddress trav = tower_list.first;
        while (trav != NULL) {
            if (trav == tower_address) {
                trav->prev->next = trav->next;
                trav->next->prev = trav->prev;
                break;
            }
            trav = trav->next;
        }
    }
    DeallocateTower(tower_address);
}

TowerListElmtAddress GetTowerAddress(int id) {
    /* Get tower address with specified id, if not exist returns NULL */
    TowerListElmtAddress trav = tower_list.first;
    while (trav != NULL) {
        if (trav->tower.id == id) {
            return trav;
            break;
        }
        trav = trav->next;
    }
    return NULL;
}

int GetNewTowerId() {
    int new_id = NEW_ID_START;
    TowerListElmtAddress trav = tower_list.first;
    while (trav != NULL) {
        if (trav->tower.id == new_id) {
            new_id ++;
        }
        trav = trav->next;
    }
    return new_id;
}

/* CRUD operations */
int CreateTower(Tower tower) {
    int new_tower_id = GetNewTowerId();
    tower.id = new_tower_id;
    TowerListElmtAddress new_tower_address = AllocateTower(tower);
    InsertTower(new_tower_address);
    return new_tower_id;
}

void DeleteTower(int id) {
    TowerListElmtAddress tower_address = GetTowerAddress(id);
    RemoveTower(tower_address);
}

void UpdateTower(Tower tower) {
    TowerListElmtAddress tower_address = GetTowerAddress(tower.id);
    if (tower_address != NULL) {
        tower_address->tower = tower;
    }
}

Tower GetTower(int id) {
    TowerListElmtAddress tower_address = GetTowerAddress(id);
    return tower_address->tower;
}
