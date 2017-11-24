#include <stdio.h>
#include <string.h>
#include "../Gameplay/mechanics.h"
#include "../Main/common_types.h"
#include "map.h"

const char emoji_king[5] = {0xF0, 0x9F, 0x91, 0x91, '\0'};
const char emoji_swordsman[5] = {0xE2, 0x9A, 0x94, ' ', '\0'};
const char emoji_archer[5] = {0xF0, 0x9F, 0x8F, 0xB9, '\0'};
const char emoji_whitemage[5] = {0xF0, 0x9F, 0xA7, 0x99, '\0'};
const char emoji_tower[5] = {0xF0, 0x9F, 0x8f, 0xb0, '\0'};
const char emoji_castle[5] = {0xF0, 0x9F, 0x8f, 0x9b, '\0'};
const char emoji_village[4] = {0xE2, 0x9B, 0xBA, '\0'};

// Initialize global var of map
Map map;
Point tower_p1_loc;
Point tower_p2_loc;
Point castle_p1_loc[4];
Point castle_p2_loc[4];

void InitializeMap(int row, int col) {

	CreateMap(row, col);

	InitializeCastleTower();

	int area = map.n_brs_eff * map.n_kol_eff;
	int village_count = floor(sqrt(area));

	for (int i = 0; i < village_count; i++) {
		MakeRandomVillage(i);
	}
}

void InitializeCastleTower() {
	// set tower p1
	col(tower_p1_loc) = 1;
	row(tower_p1_loc) = map.n_brs_eff - 2;
	AssignGridType(tower_p1_loc, C_TOWER_TYPE);
	AssignPlayerId(tower_p1_loc, 1);

	// Set castle - Player 1
	col(castle_p1_loc[0]) = col(tower_p1_loc) + 1;
	row(castle_p1_loc[0]) = row(tower_p1_loc);
	AssignGridType(castle_p1_loc[0], C_CASTLE_TYPE);
	AssignPlayerId(castle_p1_loc[0], 1);
	col(castle_p1_loc[1]) = col(tower_p1_loc) - 1;
	row(castle_p1_loc[1]) = row(tower_p1_loc);
	AssignGridType(castle_p1_loc[1], C_CASTLE_TYPE);
	AssignPlayerId(castle_p1_loc[1], 1);
	col(castle_p1_loc[2]) = col(tower_p1_loc);
	row(castle_p1_loc[2]) = row(tower_p1_loc) + 1;
	AssignGridType(castle_p1_loc[2], C_CASTLE_TYPE);
	AssignPlayerId(castle_p1_loc[2], 1);
	col(castle_p1_loc[3]) = col(tower_p1_loc);
	row(castle_p1_loc[3]) = row(tower_p1_loc) - 1;
	AssignGridType(castle_p1_loc[3], C_CASTLE_TYPE);
	AssignPlayerId(castle_p1_loc[3], 1);

	// set tower player 2
	col(tower_p2_loc) = map.n_kol_eff - 2;
	row(tower_p2_loc) = 1;
	AssignGridType(tower_p2_loc, C_TOWER_TYPE);
	AssignPlayerId(tower_p2_loc, 2);

	// Set castle - Player 2
	col(castle_p2_loc[0]) = col(tower_p2_loc) + 1;
	row(castle_p2_loc[0]) = row(tower_p2_loc);
	AssignGridType(castle_p2_loc[0], C_CASTLE_TYPE);
	AssignPlayerId(castle_p2_loc[0], 2);
	col(castle_p2_loc[1]) = col(tower_p2_loc) - 1;
	row(castle_p2_loc[1]) = row(tower_p2_loc);
	AssignGridType(castle_p2_loc[1], C_CASTLE_TYPE);
	AssignPlayerId(castle_p2_loc[1], 2);
	col(castle_p2_loc[2]) = col(tower_p2_loc);
	row(castle_p2_loc[2]) = row(tower_p2_loc) + 1;
	AssignGridType(castle_p2_loc[2], C_CASTLE_TYPE);
	AssignPlayerId(castle_p2_loc[2], 2);
	col(castle_p2_loc[3]) = col(tower_p2_loc);
	row(castle_p2_loc[3]) = row(tower_p2_loc) - 1;
	AssignGridType(castle_p2_loc[3], C_CASTLE_TYPE);
	AssignPlayerId(castle_p2_loc[3], 2);
}

void CreateMap(int row, int col) {

	map.n_brs_eff = row;
	map.n_kol_eff = col;

	// empty map
	for (int i = 0; i < map.n_brs_eff; i ++) {
		for (int j = 0; j < map.n_kol_eff; j ++) {
			map.mem[i][j].unit_type = UNIT_TYPE_UNDEF;
			map.mem[i][j].player_id = PLAYER_ID_UNDEF;
			map.mem[i][j].unit_player_id = PLAYER_ID_UNDEF;
			map.mem[i][j].unit_id = UNIT_ID_UNDEF;
			map.mem[i][j].grid_type = C_NORMAL_TYPE;
		}
	}

}

boolean IsGridAvailable(int i, int j) {
	return map.mem[i][j].unit_id == UNIT_ID_UNDEF;
}

boolean IsMapEmpty() {
	return (map.n_brs_eff == 0 && map.n_kol_eff == 0);
}

void AssignPlayerId(Point loc, int player_id) {
	map.mem[row(loc)][col(loc)].player_id = player_id;
}

void AssignGridType(Point loc, char grid_type) {
	map.mem[row(loc)][col(loc)].grid_type = grid_type;
}

void AssignGridPlayer(Point loc, int player_id) {
	map.mem[row(loc)][col(loc)].player_id = player_id;
}

void AssignGridUnit(Point loc, int unit_id) {
	map.mem[row(loc)][col(loc)].unit_id = unit_id;
}

void PrintStar(int n) {
	printf("   ");
	for (int i = 0; i < n; i++) {
		printf("*");
	}
}

void PrintGridTypeLine(int i) {
	printf("   *");
	for(int j = 0; j < map.n_kol_eff; j++) {
		printf(" ");
		// TODO: Filter color based on player id
		if (map.mem[i][j].player_id == 1) {
			if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'C')) {
				print_const_under_red(emoji_castle);
				printf(" ");
			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'T')) {
				print_const_under_red(emoji_tower);

			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'V')) {
				print_const_under_red(emoji_village);
			} else {
				print_const_under_red("  ");
			}
			// print_char_blue(((map.mem[i][j].grid_type && map.mem[i][j].grid_type  != 'N') ? map.mem[i][j].grid_type : ' '));
		} else if (map.mem[i][j].player_id == 2) {
			if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'C')) {
				print_const_under_blue(emoji_castle);
				printf(" ");
			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'T')) {
				print_const_under_blue(emoji_tower);

			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'V')) {
				print_const_under_blue(emoji_village);
			} else {
				print_const_under_blue("  ");
			}
			// print_char_red(((map.mem[i][j].grid_type && map.mem[i][j].grid_type  != 'N') ? map.mem[i][j].grid_type : ' '));
		} else {
			if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'C')) {
				print_const_under(emoji_castle);
				printf(" ");
			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'T')) {
				print_const_under(emoji_tower);

			} else if ((map.mem[i][j].grid_type && map.mem[i][j].grid_type  == 'V')) {
				print_const_under(emoji_village);
			} else {
				print_const_under("  ");
			}
			// printf("%s%c", NORMAL, (map.mem[i][j].grid_type && map.mem[i][j].grid_type  != 'N') ? map.mem[i][j].grid_type : ' ');
		}
		printf("*");
	}
	printf("\n");
}

void PrintGridUnitLine(int i) {
	if (i >= 10) {
		printf("%d *", i);
	} else {
		printf(" %d *", i);
	}
	for(int j = 0; j < map.n_kol_eff; j++) {
		if (map.mem[i][j].unit_id != -1) {
			char unit_type[5];
			switch (map.mem[i][j].unit_type) {
				case KING: strcpy(unit_type, emoji_king); break;
				case ARCHER: strcpy(unit_type, emoji_archer); break;
				case SWORDSMAN: strcpy(unit_type, emoji_swordsman); break;
				case WHITE_MAGE: strcpy(unit_type, emoji_whitemage); break;
			}
			if (map.mem[i][j].unit_player_id == active_player_id && map.mem[i][j].unit_id == active_unit_id) {
				// printf(" ");
				printf("%s%s%s%s%s", BLINK, UNDERLINE, YELLOW, unit_type, NORMAL);
				printf(" *");
			} else if (map.mem[i][j].unit_player_id == 1) {
				// printf(" ");
				print_const_under_cyan(unit_type);
				printf(" *");
			} else if (map.mem[i][j].unit_player_id == 2) {
				// printf(" ");
				print_const_under_magenta(unit_type);
				printf(" *");
			} else {
				printf("   *");
			}
		} else {
			printf("   *");
		}
	}
	printf("\n");
}

void PrintGridThird(int i) {
	printf("   *");
	for(int j = 0; j < map.n_kol_eff; j++) {
		printf(" ");
		if (map.mem[i][j].visitable) {
			if (active_player_id == 1) {
				print_char_blue('#');
			} else {
				print_char_red('#');
			}
		} else {
			printf(" ");
		}
		printf(" *");
	}
	printf("\n");
}

void PrintMapCol() {
	printf("    ");
	for (int i = 0; i < map.n_kol_eff; i++) {
		if (i >= 10) {
			printf(" %d ", i);
		} else {
			printf(" %d  ", i);
		}
	}
	printf("\n");
}

void PrintMap() {
	UpdateMap();
	if (!IsMapEmpty()) {
		PrintMapCol();
		PrintStar(1 + 4*map.n_kol_eff);
		printf("\n");
		for(int i = 0; i < map.n_brs_eff; i++) {
			// printf("\n");
			PrintGridTypeLine(i);
			PrintGridUnitLine(i);
			PrintGridThird(i);
			PrintStar(1 + 4*map.n_kol_eff);
			printf("\n");
		}
	}
}

void PrintGridType(char grid_type) {
	if (grid_type == 'V') {
		printf("Village\n");
	} else {
		printf("Unknown grid type\n");
	}
}

void PrintGridPlayer(int player_id) {
	if (player_id != 0) {
		printf("Owned by Player %d\n", player_id);
	} else {
		printf("Owned by nobody..\n");
	}
}

void PrintGridInfo(int row, int col) {
	printf("==   Cell   Info   ==\n");
	PrintGridType(map.mem[row][col].grid_type);
	PrintGridPlayer(map.mem[row][col].player_id);
	printf("==   Unit   Info   ==\n");
	printf("Swordsman (TODO)\n");
	printf("Owned   by   Player   1 (TODO)\n");
	printf("Health   7/20   |   ATK   3   |   DEF   2 (TODO)\n");
}

boolean IsInfotypeValid(int n, int m, infotype X) {
	return (X.absis >= 0 && X.absis < n && X.ordinat >= 0 && X.ordinat < m);
}

void ClearMapVisitable() {
	for (int i = 0; i < (map).n_brs_eff; i++) {
		for (int j = 0; j < (map).n_kol_eff; j++) {
			(map).mem[i][j].visitable = false;
		}
	}
}

void UpdateMap() {
	// update unit ke map
	UnitListElmtAddress addressElmt = unit_list.first;

	while (addressElmt != NULL) {
		Unit cur = addressElmt->unit;
		Point cur_location = cur.location;
		map.mem[cur_location.X][cur_location.Y].unit_id = cur.id;
		map.mem[cur_location.X][cur_location.Y].unit_player_id = cur.player_id;
		map.mem[cur_location.X][cur_location.Y].unit_type = cur.type;
		// printf("CURRR %d %d\n", cur.id, cur.player_id);
		addressElmt = addressElmt->next;
	}
}

void MoveMap() {
	ClearMapVisitable();

	Unit current_unit = GetUnit(active_unit_id);
	int start_row = current_unit.location.X;
	int start_col = current_unit.location.Y;
	int max_moves = current_unit.move_points;

	if (max_moves == 0) {
		flash("Unit can't move anymore.");
		return;
	}

	const int x_dir[] = { 0, 0, 1, -1 };
	const int y_dir[] = { 1, -1, 0, 0 };
	const int dir_len = 4;
	boolean visited[map.n_brs_eff][map.n_kol_eff];
	int dist[map.n_brs_eff][map.n_kol_eff];

	for(int i = 0; i < map.n_brs_eff; i++) {
		for(int j = 0; j < map.n_kol_eff; j++) {
			visited[i][j] = false;
			dist[i][j] = -1;
		}
	}

	PointQueue Q;
	infotype start_point;
	start_point.absis = start_row;
	start_point.ordinat = start_col;
	dist[start_row][start_col] = 0;

	CreateEmpty(&Q);
	AddPoint(&Q, start_point);

	while (!IsPointQueueEmpty(Q)) {
		infotype latest;
		DelPoint(&Q, &latest);
		visited[latest.absis][latest.ordinat] = true;
		for (int i = 0; i < dir_len; i++) {
			infotype cur;
			cur.absis = latest.absis + x_dir[i];
			cur.ordinat = latest.ordinat + y_dir[i];
			boolean is_infotype_valid = cur.absis >= 0 &&cur.ordinat >= 0 && cur.absis < map.n_brs_eff && cur.ordinat < map.n_kol_eff;
			boolean is_unvisited = is_infotype_valid && !visited[cur.absis][cur.ordinat];
			boolean is_max_moves = is_unvisited && dist[latest.absis][latest.ordinat]+1 <= max_moves;
			boolean can_move = is_max_moves && (map.mem[cur.absis][cur.ordinat].unit_player_id == active_player_id || map.mem[cur.absis][cur.ordinat].unit_player_id == -1);
			if (can_move) {
				dist[cur.absis][cur.ordinat] = dist[latest.absis][latest.ordinat]+1;
				if (map.mem[cur.absis][cur.ordinat].unit_player_id != active_player_id) {
					map.mem[cur.absis][cur.ordinat].visitable = true;
				}
				AddPoint(&Q, cur);
			}
		}
	}

	//PrintMap();

	int row = 0;
	int col = 0;
	print_default();
	print_title("Enter Move Destination");
	printf("Please enter destination cell’s row:\n");
	ask_int_input(&row, 0, map.n_brs_eff);

	print_default();
	print_title("Enter Move Destination");
	printf("Please enter destination cell’s column:\n");
	ask_int_input(&col, 0, map.n_kol_eff);

	if (!(map.mem[row][col].visitable)) {
		flash("Invalid move destination, you can't move there!");
		ClearMapVisitable();
		return;
	}

	SaveMove(current_unit.id, current_unit.location, current_unit.move_points, map.mem[row][col].player_id);

	// Reset old tiles with undefined
	map.mem[start_row][start_col].unit_type = UNIT_TYPE_UNDEF;
	map.mem[start_row][start_col].unit_id = UNIT_ID_UNDEF;
	map.mem[start_row][start_col].unit_player_id = PLAYER_ID_UNDEF;

	// Fill new tiles with unit
	if (map.mem[row][col].grid_type == C_VILLAGE_TYPE) {
		current_unit.move_points = 0;
		map.mem[row][col].player_id = active_player_id;
	} else {
		current_unit.move_points = current_unit.move_points - dist[row][col];
	}
	map.mem[row][col].unit_type = current_unit.type;
	map.mem[row][col].unit_id = current_unit.id;
	map.mem[row][col].unit_player_id = current_unit.player_id;

	current_unit.location = MakePoint(row, col);
	UpdateUnit(current_unit);

	ClearMapVisitable();
}

void UpdateMapMovePath() {
	Unit current_unit = GetUnit(active_unit_id);
	int start_row = current_unit.location.X;
	int start_col = current_unit.location.Y;

	ClearMapVisitable();
	// UpdateMapMovePath();
	PrintMap();

	int row, col;
	printf("Please enter cell’s coordinate x y: ");
	scanf("%d %d", &row, &col);
	while (!(map.mem[row][col].visitable)) {
		printf("You can’t move there\n");
		PrintMap();
		printf("Please enter cell’s coordinate x y: ");
		scanf("%d %d", &row, &col);
	}

	// SaveMove(current_unit.id, current_unit.location, )

	// Reset old tiles with undefined
	map.mem[start_row][start_col].unit_id = UNIT_ID_UNDEF;
	map.mem[start_row][start_col].unit_player_id = PLAYER_ID_UNDEF;

	// Fill new tiles with unit
	map.mem[row][col].unit_id = current_unit.id;
	map.mem[row][col].unit_player_id = current_unit.player_id;

	current_unit.location = MakePoint(col, row);

	ClearMapVisitable();
}

void Undo() {
	if (move_stack.top == -1) {
		flash("No more moves to be undone.");
	}
	else {
		int temp;
		MovePointType move_points;
		Point point;
		int map_player_id;
		Unit current_unit = GetUnit(active_unit_id);

		UndoMove(&temp, &point, &move_points, &map_player_id);

		// Reset old tiles with undefined
		map.mem[current_unit.location.X][current_unit.location.Y].unit_type = UNIT_TYPE_UNDEF;
		map.mem[current_unit.location.X][current_unit.location.Y].unit_id = UNIT_ID_UNDEF;
		map.mem[current_unit.location.X][current_unit.location.Y].unit_player_id = PLAYER_ID_UNDEF;
		map.mem[current_unit.location.X][current_unit.location.Y].player_id = map_player_id;

		char new_flash_message[100];
		sprintf(new_flash_message, "Move from (%d,%d) to (%d,%d) with %d movement pts undone.", point.X, point.Y, current_unit.location.X, current_unit.location.Y, move_points - current_unit.move_points);
		flash(new_flash_message);

		// Fill new tiles with unit
		current_unit.move_points = move_points;
		current_unit.location = point;
		map.mem[point.X][point.Y].unit_type = current_unit.type;
		map.mem[point.X][point.Y].unit_id = current_unit.id;
		map.mem[point.X][point.Y].unit_player_id = current_unit.player_id;

		UpdateUnit(current_unit);

		UpdateIncome();

		UpdateMap();
	}
}

int RandomNumber(int min_num, int max_num, int multiplier)
{
    int result = 0, low_num = 0, hi_num = 0;
    time_t t;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(&t) + 6967872421778739299 * multiplier);
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

boolean IsBuildingEmpty(int i, int j) {
 return ((map.mem[i][j].grid_type != 'V') && (map.mem[i][j].grid_type != 'T') && (map.mem[i][j].grid_type != 'C'));
}

void MakeRandomVillage(int multiplier) {

 int i = RandomNumber(0,map.n_brs_eff - 1, multiplier);
 int j = RandomNumber(0,map.n_kol_eff - 1, 98822 * multiplier);

 while (!IsBuildingEmpty(i,j)) {
  multiplier++;
  i = RandomNumber(0,map.n_brs_eff - 1, multiplier);
  j = RandomNumber(0,map.n_kol_eff - 1, 829262 * multiplier);
 }

 map.mem[i][j].grid_type = 'V';
}
