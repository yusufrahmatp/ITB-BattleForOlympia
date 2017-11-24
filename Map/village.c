#include <stdio.h>
#include <stdlib.h>
#include "../Main/common_types.h"
#include "village.h"

/* External global variable */
VillageList village_list;

/* List primitives */
VillageListElmtAddress AllocateVillage(Village village) {
    VillageListElmtAddress new_village_address = malloc(sizeof(VillageListElmt));
    if (new_village_address != NULL) {
        new_village_address->village = village;
        new_village_address->next = NULL;
        new_village_address->prev = NULL;
        return new_village_address;
    } else {
        printf("ERROR: Allocation failed.\n");
		return NULL;
    }
}

void DeallocateVillage(VillageListElmtAddress village_address) {
    free(village_address);
}

void EmptyVillageList() {
    village_list.first = NULL;
    village_list.last = NULL;
}

void InsertVillage (VillageListElmtAddress village_address) {
    /* Insert new village list elmt to head of list */
    if (village_list.first == NULL) {
        village_list.first = village_address;
        village_list.last = village_address;
    } else {
        VillageListElmtAddress trav = village_list.first;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = village_address;
        village_address->prev = trav;
        village_address->next = NULL;
        village_list.last = village_address;
    }
}

void RemoveVillage(VillageListElmtAddress village_address) {
    /* Remove a village with specified address from list */
    if (village_list.first == village_list.last) {
        village_list.first = NULL;
        village_list.last = NULL;
    } else if (village_list.first == village_address) {
        village_list.first = village_list.first->next;
        village_list.first->prev = NULL;
    } else if (village_list.last == village_address) {
        village_list.last = village_list.last->prev;
        village_list.last->next = NULL;
    } else {
        VillageListElmtAddress trav = village_list.first;
        while (trav != NULL) {
            if (trav == village_address) {
                trav->prev->next = trav->next;
                trav->next->prev = trav->prev;
                break;
            }
            trav = trav->next;
        }
    }
    DeallocateVillage(village_address);
}

VillageListElmtAddress GetVillageAddress(int id) {
    /* Get village address with specified id, if not exist returns NULL */
    VillageListElmtAddress trav = village_list.first;
    while (trav != NULL) {
        if (trav->village.id == id) {
            return trav;
            break;
        }
        trav = trav->next;
    }
    return NULL;
}

int GetNewVillageId() {
    int new_id = NEW_ID_START;
    VillageListElmtAddress trav = village_list.first;
    while (trav != NULL) {
        if (trav->village.id == new_id) {
            new_id ++;
        }
        trav = trav->next;
    }
    return new_id;
}

/* CRUD operations */
int CreateVillage(Village village) {
    int new_village_id = GetNewVillageId();
    village.id = new_village_id;
    VillageListElmtAddress new_village_address = AllocateVillage(village);
    InsertVillage(new_village_address);
    return new_village_id;
}

void DeleteVillage(int id) {
    VillageListElmtAddress village_address = GetVillageAddress(id);
    RemoveVillage(village_address);
}

void UpdateVillage(Village village) {
    VillageListElmtAddress village_address = GetVillageAddress(village.id);
    if (village_address != NULL) {
        village_address->village = village;
    }
}

Village GetVillage(int id) {
    VillageListElmtAddress village_address = GetVillageAddress(id);
    return village_address->village;
}
