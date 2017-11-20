#ifndef TURN_QUEUE_H_
#define TURN_QUEUE_H_

#include "common_types.h"

typedef struct {
    int T[2];   /* tabel penyimpan elemen */
    int head;   /* alamat penghapusan */
    int tail;   /* alamat penambahan */
} TurnQueue;

/* Global variables */
extern TurnQueue turn_queue;

/* Prototypes */
/* Queue primitives */
void CreateEmptyQueue(TurnQueue * Q);
boolean IsEmptyQueue(TurnQueue * Q);
void Add(TurnQueue * Q, int X);
void Del(TurnQueue * Q, int * X);

/*External Primitive*/
/* To initialize turn queue when game starts */
void InitializeTurnQueue();
/* Returns the next turn's player id */
int NextTurn();

#endif
