#ifndef MOVE_STACK_H_
#define MOVE_STACK_H_

#include "common_types.h"

/*Type stack*/
typedef struct {
	int unit_id;
	MovePointType move_point;
	Point location;
	int map_player_id;
} ElmtMoveStack;
typedef struct {
	ElmtMoveStack T[20];
	int top;
} MoveStack;

/*Global variable*/
extern MoveStack move_stack;

/*Internal Primitive*/
void CreateEmptyStack(MoveStack * S);
boolean IsEmptyStack(MoveStack S);
void Push(MoveStack * S, int unit_id, Point location, MovePointType move_point, int map_player_id);
void Pop(MoveStack * S, int * unit_id, Point * location, MovePointType * move_point, int * map_player_id);

/*External Primitive*/
void InitializeMoveStack();
void ResetMoveStack();
/* Save a movement of a unit, call when MOVE */
void SaveMove(int unit_id, Point location, MovePointType move_point, int map_player_id);
void UndoMove(int * unitid, Point * location, MovePointType * move_point, int * map_player_id);

#endif
