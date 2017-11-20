#ifndef STACK_H
#define STACK_H

#include "common_types.h"

/*Type stack*/
typedef struct {
	int unitid;
	Point point;
} ElmtStack;
typedef struct {
	ElmtStack T[10]; /* tabel penyimpan elemen */
	int top;  /* alamat TOP: elemen puncak */
} Stack;

/*Global variable*/
extern Stack undo_stack;

/*Internal Primitive*/
void CreateEmptyStack(Stack * S);

void Push(Stack * S, int unitid, Point P);

void Pop(Stack * S, int * unitid, Point * P);

/*External Primitive*/
void InitializeStack(Stack * S);

void ResetStack(Stack * S);

void Undo(Stack *S, int * unitid, Point * P);

/*For Push, call when MOVE*/

#endif
