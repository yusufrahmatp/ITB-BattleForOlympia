#include <stdio.h>
#include <stdlib.h>
#include "common_types.h"
#include "unit.h"

/* External global variable */
UnitList unit_list;

/* List primitives */
UnitListElmtAddress AllocateUnit(Unit unit) {
    UnitListElmtAddress new_unit_address = malloc(sizeof(UnitListElmt));
    if (new_unit_address != NULL) {
        new_unit_address->unit = unit;
        new_unit_address->next = NULL;
        new_unit_address->prev = NULL;
        return new_unit_address;
    } else {
        printf("ERROR: Allocation failed.\n");
        return NULL;
    }
}

void DeallocateUnit(UnitListElmtAddress unit_address) {
    free(unit_address);
}

void EmptyUnitList() {
    unit_list.first = NULL;
    unit_list.last = NULL;
}

void InsertUnit (UnitListElmtAddress unit_address) {
    /* Insert new unit list elmt to head of list */
    if (unit_list.first == NULL) {
        unit_list.first = unit_address;
        unit_list.last = unit_address;
    } else {
        UnitListElmtAddress trav = unit_list.first;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = unit_address;
        unit_address->prev = trav;
        unit_address->next = NULL;
        unit_list.last = unit_address;
    }
}

void RemoveUnit(UnitListElmtAddress unit_address) {
    /* Remove a unit with specified address from list */
    if (unit_list.first == unit_list.last) {
        unit_list.first = NULL;
        unit_list.last = NULL;
    } else if (unit_list.first == unit_address) {
        unit_list.first = unit_list.first->next;
        unit_list.first->prev = NULL;
    } else if (unit_list.last == unit_address) {
        unit_list.last = unit_list.last->prev;
        unit_list.last->next = NULL;
    } else {
        UnitListElmtAddress trav = unit_list.first;
        while (trav != NULL) {
            if (trav == unit_address) {
                trav->prev->next = trav->next;
                trav->next->prev = trav->prev;
                break;
            }
            trav = trav->next;
        }
    }
    DeallocateUnit(unit_address);
}

int GetUnitCount() {
    int count = 0;
    UnitListElmtAddress trav = unit_list.first;
    while (trav != NULL) {
        count ++;
        trav = trav->next;
    }
    return count;
}

UnitListElmtAddress GetUnitAddress(int id) {
    /* Get unit address with specified id, if not exist returns NULL */
    UnitListElmtAddress trav = unit_list.first;
    while (trav != NULL) {
        if (trav->unit.id == id) {
            return trav;
            break;
        }
        trav = trav->next;
    }
    return NULL;
}

int GetNewUnitId() {
    int new_id = NEW_ID_START;
    UnitListElmtAddress trav = unit_list.first;
    while (trav != NULL) {
        if (trav->unit.id == new_id) {
            new_id ++;
        }
        trav = trav->next;
    }
    return new_id;
}

/* CRUD operations */
int CreateUnit(Unit unit) {
    int new_unit_id = GetNewUnitId();
    unit.id = new_unit_id;
    UnitListElmtAddress new_unit_address = AllocateUnit(unit);
    InsertUnit(new_unit_address);
    return new_unit_id;
}

void AddUnitWithId(Unit unit) {
    UnitListElmtAddress new_unit_address = AllocateUnit(unit);
    // List empty
    if (unit_list.first == NULL) {
        unit_list.first = new_unit_address;
        unit_list.last = new_unit_address;
    // not empty
    } else {
        boolean added = false;
        UnitListElmtAddress trav = unit_list.first;
        while (trav != NULL) {
            if (trav->unit.id < unit.id) {
                new_unit_address->next = trav;
                new_unit_address->prev = trav->prev;
                trav->prev = new_unit_address;
                if (trav != unit_list.first) {
                    trav->prev->next = new_unit_address;
                }
                added = true;
            }
            trav = trav->next;
        }
        if (!added) {
            unit_list.last->next = new_unit_address;
            new_unit_address->prev = unit_list.last;
            unit_list.last = new_unit_address;
        }
    }
}

void DeleteUnit(int id) {
    UnitListElmtAddress unit_address = GetUnitAddress(id);
    RemoveUnit(unit_address);
}

void UpdateUnit(Unit unit) {
    UnitListElmtAddress unit_address = GetUnitAddress(unit.id);
    if (unit_address != NULL) {
        unit_address->unit = unit;
    }
}

Unit GetUnit(int id) {
    UnitListElmtAddress unit_address = GetUnitAddress(id);
    return unit_address->unit;
}
