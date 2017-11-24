#include "stack.h"

/*Global variable*/
Stack undo_stack;

void CreateEmptyStack(Stack * S)
{
    (*S).top = -1;
}

void Push(Stack * S, int unitid, Point P)
{
    if((*S).top < 10) {
        (*S).top++;
        (*S).T[(*S).top].unitid = unitid;
    	(*S).T[(*S).top].point = P;
    }
}

void Pop(Stack * S, int * unitid, Point * P)
{
    if((*S).top >= 0) {
        *unitid = (*S).T[(*S).top].unitid;
        *P = (*S).T[(*S).top].point;
    	(*S).top--;
    }
}

void InitializeStack(Stack * S)
{
    CreateEmptyStack(S);
}

void ResetStack(Stack * S)
{
    CreateEmptyStack(S);
}

void Undo(Stack * S, int * unitid, Point * P)
{
    Pop(S, unitid, P);
}
