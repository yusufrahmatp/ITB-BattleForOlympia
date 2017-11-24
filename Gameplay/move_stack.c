#include "move_stack.h"

/*Global variable*/
MoveStack move_stack;

void CreateEmptyStack(MoveStack * S) {
    (*S).top = -1;
}

boolean IsEmptyStack(MoveStack S) {
    return (S.top == -1);
}

void Push(MoveStack * S, int unit_id, Point location, MovePointType move_point, int map_player_id) {
    if((*S).top < 10) {
        (*S).top++;
        (*S).T[(*S).top].unit_id = unit_id;
    	(*S).T[(*S).top].location = location;
        (*S).T[(*S).top].move_point = move_point;
        (*S).T[(*S).top].map_player_id = map_player_id;
    }
}

void Pop(MoveStack * S, int * unit_id, Point * location, MovePointType * move_point, int * map_player_id) {
    if((*S).top >= 0) {
        *unit_id = (*S).T[(*S).top].unit_id;
        *location = (*S).T[(*S).top].location;
        *move_point = (*S).T[(*S).top].move_point;
        *map_player_id = (*S).T[(*S).top].map_player_id;
    	(*S).top--;
    }
}

void InitializeMoveStack() {
    CreateEmptyStack(&move_stack);
}

void ResetMoveStack() {
    CreateEmptyStack(&move_stack);
}

void SaveMove(int unit_id, Point location, MovePointType move_point, int map_player_id) {
    Push(&move_stack, unit_id, location, move_point, map_player_id);
}

void UndoMove(int * unit_id, Point * location, MovePointType * move_point, int * map_player_id) {
    if (IsEmptyStack(move_stack)) {
        printf("No more moves to undo.\n");
    } else {
        Pop(&move_stack, unit_id, location, move_point, map_player_id);
    }
}
