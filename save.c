#include <stdio.h>
#include "common_types.h"
#include "mechanics.h"

void SaveGame1() {
	char file_name[100];
	printf("Enter save file name: ");
	scanf("%s", file_name);

	// INIT
	FILE *f = fopen(file_name, "w+");

	// SAVE ACTIVE PLAYER
	fprintf(f, "#ACTIVE_PLAYER_ID\n");
	fprintf(f, "%d\n\n", active_player_id);

	fprintf(f, "#ACTIVE_UNIT_ID\n");
	fprintf(f, "%d\n\n", active_unit_id);

	// SAVE MAP
	fprintf(f, "#MAP\n");
	fprintf(f, "%d %d\n", map.n_brs_eff, map.n_kol_eff);
	for (int i = 0; i < map.n_brs_eff; i++) {
		for (int j = 0; j < map.n_kol_eff; j++) {
			fprintf(f, "%c", map.mem[i][j].grid_type);
			fprintf(f, " %d", map.mem[i][j].unit_type);
			fprintf(f, " %d", map.mem[i][j].player_id);
			fprintf(f, " %d", map.mem[i][j].unit_id);
			fprintf(f, " %d", map.mem[i][j].unit_player_id);
			fprintf(f, " %d\n", map.mem[i][j].visitable);
		}
	}
	fprintf(f, "\n");

	// SAVE MOVE STACK
	fprintf(f, "#MOVE_STACK\n");
	int move_stack_count = move_stack.top + 1;
	fprintf(f, "%d\n", move_stack_count);
	for (int i = 0; i < move_stack_count; i++) {
		fprintf(f, "%d", move_stack.T[i].unit_id);
		fprintf(f, " %d", move_stack.T[i].move_point);
		fprintf(f, " %d", move_stack.T[i].location.X);
		fprintf(f, " %d", move_stack.T[i].location.Y);
		fprintf(f, " %d\n", move_stack.T[i].map_player_id);
	}
	fprintf(f, "\n");

	// SAVE PLAYER
	fprintf(f, "#PLAYER\n");
	int player_count = 2; // masih hardcode
	fprintf(f, "%d\n", player_count);
	PlayerListElmtAddress cur_player = player_list.first;
	for (int i = 0; i < player_count; i++) {
		Player P = cur_player->player;
		fprintf(f, "%d", P.id);
		fprintf(f, " %d", P.alive);
		fprintf(f, " %d", P.cash);
		fprintf(f, " %d", P.income);
		fprintf(f, " %d", P.upkeep);
		fprintf(f, " %d", P.king_id);
		fprintf(f, " %d", P.unit_count);
		for (int j = 0; j < P.unit_count; j++) {
			fprintf(f, " %d", P.units[j]);
		}
		fprintf(f, "\n");
		cur_player = cur_player->next;
	}
	fprintf(f, "\n");

	// SAVE UNIT
	fprintf(f, "#UNIT\n");
	int unit_count = GetUnitCount();
	fprintf(f, "%d\n", unit_count);
	UnitListElmtAddress cur_unit = unit_list.first;
	for (int i = 0; i < unit_count; i++) {
		Unit U = cur_unit->unit;
		fprintf(f, "%d", U.id);
		fprintf(f, " %d", U.player_id);
		fprintf(f, " %d", U.attack_type);
		fprintf(f, " %d", U.type);
		fprintf(f, " %d", U.max_health);
		fprintf(f, " %d", U.health);
		fprintf(f, " %d", U.attack);
		fprintf(f, " %d", U.max_move_points);
		fprintf(f, " %d", U.move_points);
		fprintf(f, " %d", U.can_attack);
		fprintf(f, " %d", U.location.X);
		fprintf(f, " %d", U.location.Y);
		fprintf(f, " %d", U.price);
		fprintf(f, " %d\n", U.heal);
		cur_player = cur_player->next;
	}
	fprintf(f, "\n");


	// SAVE TURN QUEUE
	fprintf(f, "#MAP\n");
	fprintf(f, "%d %d %d %d", turn_queue.T[0], turn_queue.T[1], turn_queue.head, turn_queue.tail);

	fclose(f);
}
