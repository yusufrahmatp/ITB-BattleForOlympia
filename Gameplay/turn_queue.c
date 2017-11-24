#include "turn_queue.h"

/* Global Variable */
TurnQueue turn_queue;

/*Internal Primitive*/
void CreateEmptyQueue(TurnQueue * Q) {
	Q->head = -1;
	Q->tail = -1;
}

boolean IsEmptyQueue(TurnQueue * Q) {
	return (Q->head == -1 && Q->tail == -1);
}

void Add(TurnQueue * Q, int X) {
	if (IsEmptyQueue(Q)) {
		Q->head = 0;
		Q->tail = 0;
		Q->T[0] = X;
	} else {
		Q->tail = (Q->tail + 1) % 2;
		Q->T[Q->tail] = X;
	}
}

void Del(TurnQueue * Q, int * X) {
	*X = Q->T[Q->head];
	if (Q->head == Q->tail) {
		Q->head = -1;
		Q->tail = -1;
	} else {
		Q->head = (Q->head + 1) % 2;
	}
}

/* External primitive */
void InitializeTurnQueue() {
	CreateEmptyQueue(&turn_queue);
	Add(&turn_queue,1);
	Add(&turn_queue,2);
}

int NextTurn() {
	int next_player;
	Del(&turn_queue, &next_player);
	Add(&turn_queue, next_player);
	return next_player;
}
