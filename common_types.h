#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include "boolean.h"
#include "pcolor.h"
#include "point.h"

#define NEW_ID_START 1
#define DEFAULT_CASH 20

#define MAX_MOVE_PTS_KING 2
#define MAX_MOVE_PTS_ARCHER 2
#define MAX_MOVE_PTS_SWORDSMAN 3
#define MAX_MOVE_PTS_WHITE_MAGE 1

#define MAX_HEALTH_KING 30
#define MAX_HEALTH_ARCHER 20
#define MAX_HEALTH_SWORDSMAN 20
#define MAX_HEALTH_WHITE_MAGE 20

#define ATTACK_KING 100//5
#define ATTACK_ARCHER 4
#define ATTACK_SWORDSMAN 3
#define ATTACK_WHITE_MAGE 3

#define HEAL_WHITE_MAGE 4
#define HEAL_VILLAGE 4

#define PRICE_ARCHER 5
#define PRICE_SWORDSMAN 4
#define PRICE_WHITE_MAGE 5

#define C_UPKEEP_CONSTANT 1;
#define C_INCOME_CONSTANT 5;

typedef int CashType;
typedef int HealthType;
typedef int MovePointType;
typedef int HealType;
typedef enum AttackType {
    RANGED, MELEE
} AttackType;
typedef enum UnitType {
    KING, ARCHER, SWORDSMAN, WHITE_MAGE
} UnitType;

#include "player.h"
#include "unit.h"
#include "turn_queue.h"
#include "move_stack.h"
#include "map.h"
#include "print_format.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <time.h>
#include <math.h>

#endif
