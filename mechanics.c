#include <stdio.h>
#include <string.h>
#include <time.h>

#include "common_types.h"
#include "mechanics.h"
#include "jam.h"

/* Global variables */
int active_player_id;
int active_unit_id;
int map_width;
int map_height;

/* Game data */
void NewGameData() {

    // Initialization
    active_player_id = -1;
    active_unit_id = -1;
    EmptyPlayerList();
    EmptyUnitList();
    InitializeTurnQueue();
    InitializeMoveStack();

    // Set map dimension
    print_logo();
    print_title_plain("Start New Game");
    printf("Enter map row size (min size: 8):\n");
    ask_int_input(&map_height, 8, 100);

    print_logo();
    print_title_plain("Start New Game");
    printf("Enter map column size (min size: 8):\n");
    ask_int_input(&map_width, 8, 100);

    // Create and initialize map
    InitializeMap(map_height, map_width);

    // Create 2 Player
    InitializePlayer();

}

void LoadGameData() {

    char CString[100];

    char file_name[10000];
    print_logo();
    print_title_plain("Load Game");
    printf("Enter load file name:\n");
    ask_input(file_name);

    // INIT
    FILE *f = fopen(file_name, "r");

    // Read save time
    fscanf(f, "%s", CString);
    fscanf(f, "%s", CString);
    fscanf(f, "%s", CString);

    // Read active player id
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &active_player_id);

    // Read active unit id
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &active_unit_id);

    // Read map
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &map.n_brs_eff);

    fscanf(f, " %d", &map.n_kol_eff);

    for (int i = 0; i < map.n_brs_eff; i++) {
        for (int j = 0; j < map.n_kol_eff; j++) {
            fscanf(f, " %c %d %d %d %d %c", &(map.mem[i][j].grid_type), &(map.mem[i][j].unit_type), &(map.mem[i][j].player_id), &(map.mem[i][j].unit_id), &(map.mem[i][j].unit_player_id),
            &(map.mem[i][j].visitable));
        }
    }

    // read move stack
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &(move_stack.top));
    move_stack.top --;

    if(move_stack.top != -1) {
        for (int i = 0; i <= move_stack.top; i++) {
            fscanf(f, "%d %d %d %d %d", &(move_stack.T[i].unit_id), &(move_stack.T[i].move_point),
            &(move_stack.T[i].location.X), &(move_stack.T[i].location.Y), &(move_stack.T[i].map_player_id));
        }
    }

    // read player
    int player_count;
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &player_count);

    for (int i = 0; i < player_count; i++) {
        Player player;

        fscanf(f, "%d %c %d %d %d %d %d",
        &(player.id),
        &(player.alive),
        &(player.cash),
        &(player.income),
        &(player.upkeep),
        &(player.king_id),
        &(player.unit_count)
        );

        for (int j = 0; j < player.unit_count; j++) {
            fscanf(f, "%d", &(player.units[j]));
        }

        AddPlayerWithId(player);
    }

    // unit
    int unit_count;
    fscanf(f, "%s", CString);
    fscanf(f, " %d", &unit_count);

    for (int i = 0; i < unit_count; i++) {
        Unit unit;

        fscanf(f, "%d %d %d %d %d %d %d %d %d %c %d %d %d %d",
        &(unit.id),
        &(unit.player_id),
        &(unit.attack_type),
        &(unit.type),
        &(unit.max_health),
        &(unit.health),
        &(unit.attack),
        &(unit.max_move_points),
        &(unit.move_points),
        &(unit.can_attack),
        &(unit.location.X),
        &(unit.location.Y),
        &(unit.price),
        &(unit.heal)
        );

        AddUnitWithId(unit);
    }

    // Turn Queue
    fscanf(f, "%s", CString);
    fscanf(f, " %d %d %d %d",
    &(turn_queue.T[0]),
    &(turn_queue.T[1]),
    &(turn_queue.head),
    &(turn_queue.tail)
    );

    fclose(f);

}

JAM GetCurrentTime() {
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);

    int year = timeinfo->tm_year+1900;
    int month = timeinfo->tm_mon+1;
    int day = timeinfo->tm_mday;
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;

    JAM now = MakeJAM(year, month, day, hour, minute, second);

    return now;
}

void SaveGameData() {

	char file_name[100];
	printf("Enter save file name:\n");
    ask_input(file_name);

	// INIT
	FILE *f = fopen(file_name, "w+");

    // TIME STAMP
    JAM time_now = GetCurrentTime();
    fprintf(f, "#SAVE_TIME \n");
    fprintf(f, "%d/%d/%d ", time_now.day, time_now.month, time_now.year);
    fprintf(f, "%d:%d:%d \n\n", time_now.hour, time_now.minute, time_now.second);

	// SAVE ACTIVE PLAYER
	fprintf(f, "#ACTIVE_PLAYER_ID \n");
	fprintf(f, "%d \n\n", active_player_id);

	fprintf(f, "#ACTIVE_UNIT_ID \n");
	fprintf(f, "%d \n\n", active_unit_id);

	// SAVE MAP
	fprintf(f, "#MAP \n");
	fprintf(f, "%d %d \n", map.n_brs_eff, map.n_kol_eff);
	for (int i = 0; i < map.n_brs_eff; i++) {
		for (int j = 0; j < map.n_kol_eff; j++) {
			fprintf(f, "%c", map.mem[i][j].grid_type);
			fprintf(f, " %d", map.mem[i][j].unit_type);
			fprintf(f, " %d", map.mem[i][j].player_id);
			fprintf(f, " %d", map.mem[i][j].unit_id);
			fprintf(f, " %d", map.mem[i][j].unit_player_id);
			fprintf(f, " %d \n", map.mem[i][j].visitable);
		}
	}
	fprintf(f, "\n");

	// SAVE MOVE STACK
	fprintf(f, "#MOVE_STACK \n");
	int move_stack_count = move_stack.top + 1;
	fprintf(f, "%d \n", move_stack_count);
	for (int i = 0; i < move_stack_count; i++) {
		fprintf(f, "%d", move_stack.T[i].unit_id);
		fprintf(f, " %d", move_stack.T[i].move_point);
		fprintf(f, " %d", move_stack.T[i].location.X);
		fprintf(f, " %d", move_stack.T[i].location.Y);
		fprintf(f, " %d \n", move_stack.T[i].map_player_id);
	}
	fprintf(f, "\n");

	// SAVE PLAYER
	fprintf(f, "#PLAYER \n");
	int player_count = 2; // masih hardcode
	fprintf(f, "%d \n", player_count);
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
		fprintf(f, " \n");
		cur_player = cur_player->next;
	}
	fprintf(f, "\n");

	// SAVE UNIT
	fprintf(f, "#UNIT \n");
	int unit_count = GetUnitCount();
	fprintf(f, "%d \n", unit_count);
	UnitListElmtAddress cur_unit = unit_list.first;
	for (int i = 0; i < unit_count; i++) {
        Unit U = cur_unit->unit;;
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
		fprintf(f, " %d \n", U.heal);
		cur_unit = cur_unit->next;
	}
	fprintf(f, "\n");


	// SAVE TURN QUEUE
	fprintf(f, "#TURN_QUEUE \n");
	fprintf(f, "%d %d %d %d", turn_queue.T[0], turn_queue.T[1], turn_queue.head, turn_queue.tail);

	fclose(f);
}

/* Game flow */
void InitializeGame() {

    print_intro();

    int input;
    ask_int_input(&input, 1, 3);
    if (input == 1) {
        NewGameData();
    } else if (input == 2) {
        LoadGameData();
    } else {
        clearscr();
        exit(0);
    }

}

void PlayGame() {

    if (active_player_id == -1) {
        active_player_id = NextTurn();
    }
    active_unit_id = GetPlayer(active_player_id).king_id;
    PlayTurn();
    while (!CheckWinner()) {
        active_player_id = NextTurn();
        active_unit_id = GetPlayer(active_player_id).king_id;
        PlayTurn();
    }

}

void PlayTurn() {

    WhiteMageEffect();
    HealByVillage();
    ResetMoveStack();

    Player cur_player = GetPlayer(active_player_id);
    cur_player.cash += cur_player.income - cur_player.upkeep;
    if (cur_player.cash < 0) {
        cur_player.cash = 0;
    }
    UpdatePlayer(cur_player);

    char input[100];

    do {

        UpdateUpkeep();
        UpdateIncome();

        print_default();
        print_home();
        ask_input(input);

        if ((strcmp(input, "MOVE") == 0) || (strcmp(input, "m") == 0)) {
            MoveMap();

        } else if ((strcmp(input, "UNDO") == 0) || (strcmp(input, "u") == 0)) {
            Undo();

        } else if ((strcmp(input, "CHANGE_UNIT") == 0) || (strcmp(input, "cu") == 0)) {
            ChangeActiveUnit();

        } else if ((strcmp(input, "NEXT_UNIT") == 0) || (strcmp(input, "nu") == 0)) {
            NextActiveUnit();

        } else if ((strcmp(input, "RECRUIT") == 0) || (strcmp(input, "r") == 0)) {
            Recruit();

        } else if ((strcmp(input, "ATTACK") == 0) || (strcmp(input, "a") == 0)) {
            Attack();

        } else if ((strcmp(input, "MAP") == 0) || (strcmp(input, "map") == 0)) {
            PrintMap();

        } else if ((strcmp(input, "INFO") == 0) || (strcmp(input, "i") == 0)) {
            InfoMap();

        } else if ((strcmp(input, "SAVE") == 0) || (strcmp(input, "s") == 0)) {
            SaveGame();

        } else if ((strcmp(input, "EXIT") == 0) || (strcmp(input, "e") == 0)) {
            ExitGame();

        } else if ((strcmp(input, "END_TURN") == 0) || (strcmp(input, "et") == 0)) {
            break;
        } else {
            flash("Invalid input, retry!");
        }

    } while (true);

    UpdateUpkeep();
    UpdateIncome();
    ResetActivePlayerUnitsState();

}

void ExitGame() {

    if (!CheckWinner()) {
        print_exit_game();

        int input;
        ask_int_input(&input, 1, 3);
        if (input == 3) {
            return;
        } else if (input == 1) {
            print_heading_vcentered("Exit Game");
            printf("\n");
            print_title("Save Game");
            SaveGameData();
        }
        clearscr();
        exit(0);

    } else {
        print_end_game(CheckWinner());

        int input;
        ask_int_input(&input, 1, 2);
        if (input == 1) {
            InitializeGame();
            PlayGame();
        } else {
            clearscr();
            exit(0);
        }

    }

}

void SaveGame() {

    print_default();
    print_title("Save Game");
    SaveGameData();
    flash("Game saved!");

}

/* Game states */
int CheckWinner() {

    Player player1 = GetPlayer(1);
    Player player2 = GetPlayer(2);

    if ((player1.alive) && (!player2.alive)) {
        return 1;
    } else if ((!player1.alive) && (player2.alive)) {
        return 2;
    } else if ((!player1.alive) && (!player2.alive)){
        return -1;
    } else {
        return 0;
    }

}

void ResetActivePlayerUnitsState() {

    Player current_player = GetPlayer(active_player_id);
    for (int i = 0; i < current_player.unit_count; i ++) {
        Unit current_unit = GetUnit(current_player.units[i]);
        current_unit.move_points = current_unit.max_move_points;
        current_unit.can_attack = true;
        UpdateUnit(current_unit);
    }
    Unit current_king = GetUnit(current_player.king_id);
    current_king.move_points = current_king.max_move_points;
    current_king.can_attack = true;
    UpdateUnit(current_king);

}

/* Game mechanics */
void Attack() {

    // Becomes true if a king dies
    boolean end_game = false;

    // Menampilkan lokasi musuh di kiri, kanan, atas, dan bawah
    Unit active_unit = GetUnit(active_unit_id);
    Point unit_location = active_unit.location;

    // Insisialisai lokasi musuh
    Point enemy_location_up = unit_location;
    Point enemy_location_down = unit_location;
    Point enemy_location_left = unit_location;
    Point enemy_location_right = unit_location;
    enemy_location_up.Y --;
    enemy_location_down.Y ++;
    enemy_location_right.X ++;
    enemy_location_left.X --;

    // Memasukan lokasi id musuh ke array
    int enemy_array[5];
    int enemy_array_length = 0;
    if (enemy_location_up.Y >= 0) {
        if ((map.mem[enemy_location_up.X][enemy_location_up.Y].unit_player_id != active_unit.player_id) && (map.mem[enemy_location_up.X][enemy_location_up.Y].unit_player_id != -1)) {
            enemy_array_length ++;
            enemy_array[enemy_array_length] = map.mem[enemy_location_up.X][enemy_location_up.Y].unit_id;
        }
    }
    if (enemy_location_down.Y <= map.n_brs_eff - 1) {
        if ((map.mem[enemy_location_down.X][enemy_location_down.Y].unit_player_id != active_unit.player_id) && (map.mem[enemy_location_down.X][enemy_location_down.Y].unit_player_id != -1)){
            enemy_array_length ++;
            enemy_array[enemy_array_length] = map.mem[enemy_location_down.X][enemy_location_down.Y].unit_id;
        }
    }
    if (enemy_location_right.X <= map.n_kol_eff - 1) {
        if ((map.mem[enemy_location_right.X][enemy_location_right.Y].unit_player_id != active_unit.player_id) && (map.mem[enemy_location_right.X][enemy_location_right.Y].unit_player_id != -1)) {
            enemy_array_length ++;
            enemy_array[enemy_array_length] = map.mem[enemy_location_right.X][enemy_location_right.Y].unit_id;
        }
    }
    if (enemy_location_left.X >= 0) {
        if ((map.mem[enemy_location_left.X][enemy_location_left.Y].unit_player_id != active_unit.player_id) && (map.mem[enemy_location_left.X][enemy_location_left.Y].unit_player_id != -1)){
            enemy_array_length ++;
            enemy_array[enemy_array_length] = map.mem[enemy_location_left.X][enemy_location_left.Y].unit_id;
        }
    }

    if (enemy_array_length == 0) {
        flash("There are no nearby enemies to attack.");
    }
    else if (!active_unit.can_attack) {
        flash("You are unable to attack.");
    }
    else {

        // Main menu dari attack
        print_default();
        print_title("Select Enemy to Attack");

        Unit enemy_unit;
        int player_probability;
        int enemy_probability;
        int probability;
        char enemy_type[15];
        char player_type[15];

        switch(active_unit.type) {
        case    0 : strcpy(player_type,"King");
                    player_probability = 80;
                    break;
        case    1 : strcpy(player_type,"Archer");
                    player_probability = 50;
                    break;
        case    2 : strcpy(player_type,"Swordsman");
                    player_probability = 90;
                    break;
        case    3 : strcpy(player_type,"White Mage");
                    player_probability = 30;
                    break;
        };

        for (int i = 1; i <= enemy_array_length; i++) {
            enemy_unit = GetUnit(enemy_array[i]);

            switch(enemy_unit.type) {
            case    0 : strcpy(enemy_type,"King");
                        break;
            case    1 : strcpy(enemy_type,"Archer");
                        break;
            case    2 : strcpy(enemy_type,"Swordsman");
                        break;
            case    3 : strcpy(enemy_type,"White Mage");
                        break;
            };

            char health_color[10];
            if (enemy_unit.health <= enemy_unit.max_health / 4) {
                strcpy(health_color, RED);
            } else {
                strcpy(health_color, GREEN);
            }

            char chance_color[10];
            if (player_probability < 40) {
                strcpy(chance_color, RED);
            } if (player_probability < 70) {
                strcpy(chance_color, YELLOW);
            } else {
                strcpy(chance_color, GREEN);
            }

            printf("%d. %s%s (%d,%d)%s | Health: %s%s%d/%d%s | Chance: %s%s%d%%%s\n",i , BOLD, enemy_type, enemy_unit.location.X, enemy_unit.location.Y, NORMAL, BOLD, health_color, enemy_unit.health, enemy_unit.max_health, NORMAL, BOLD, chance_color, player_probability, NORMAL);
        }

        int enemy_option;
        ask_int_input(&enemy_option, 1, enemy_array_length);

        enemy_unit = GetUnit(enemy_array[enemy_option]);

        switch(enemy_unit.type) {
        case    0 : strcpy(enemy_type,"King");
                    enemy_probability = 80;
                    break;
        case    1 : strcpy(enemy_type,"Archer");
                    enemy_probability = 50;
                    break;
        case    2 : strcpy(enemy_type,"Swordsman");
                    enemy_probability = 90;
                    break;
        case    3 : strcpy(enemy_type,"White Mage");
                    enemy_probability = 30;
                    break;
        };

        // Show attack result
        print_default();
        print_title("Attack Result");

        // Player type sama enemy type beda, dan enemy type bukan king
        if ((active_unit.attack_type != enemy_unit.attack_type) && (enemy_unit.type != KING)) {

            probability = RandomNumber(0,100,2);
            if (probability <= player_probability) {
                enemy_unit.health -= active_unit.attack;
                printf("Enemy's %s%s%s is damaged by %s%d%s, ", BOLD, enemy_type, NORMAL, BOLD, active_unit.attack, NORMAL);

                if (enemy_unit.health <= 0) { // Enemy mati
                    printf("it's now %s%sDEAD%s :).\n", BOLD, RED, NORMAL);

                    int row = enemy_unit.location.X;
                    int col = enemy_unit.location.Y;
                    map.mem[row][col].unit_player_id = PLAYER_ID_UNDEF;
                    map.mem[row][col].unit_id = UNIT_ID_UNDEF;

                    DeleteUnit(enemy_unit.id);
                }
                else {
                    if (enemy_unit.health <= enemy_unit.max_health / 4) {
                        printf("it's health is now %s%s%d/%d%s.\n", BOLD, RED, enemy_unit.health, enemy_unit.max_health, NORMAL);
                    } else {
                        printf("it's health is now %s%s%d/%d%s.\n", BOLD, GREEN, enemy_unit.health, enemy_unit.max_health, NORMAL);
                    }
                    UpdateUnit(enemy_unit);
                }
            }
            else {
                printf("Your attack missed.\n");
            }

            active_unit.can_attack = false;
            active_unit.move_points = 0;
            UpdateUnit(active_unit);
            ResetMoveStack();

            wait_return();

        }
        else { // Type beda atau enemy king

            probability = RandomNumber(0,100,5);
            if (probability <= player_probability) {
                enemy_unit.health -= active_unit.attack;
                printf("Enemy's %s%s%s is damaged by %s%d%s, ", BOLD, enemy_type, NORMAL, BOLD, active_unit.attack, NORMAL);
            }
            else {
                printf("Your attack missed.\n");
            }
            if (enemy_unit.health <= 0) { // Kalo enemy mati (ga nyerang balik)

                printf("it's now %s%sDEAD%s :).\n", BOLD, RED, NORMAL);

                if (enemy_unit.type == KING) {
                    Player enemy_player = GetPlayer(enemy_unit.player_id);
                    enemy_player.alive = false;

                    int row = active_unit.location.X;
                    int col = active_unit.location.Y;
                    map.mem[row][col].unit_player_id = PLAYER_ID_UNDEF;
                    map.mem[row][col].unit_id = UNIT_ID_UNDEF;

                    UpdatePlayer(enemy_player);

                    // End game
                    end_game = true;

                } else {
                    int row = enemy_unit.location.X;
                    int col = enemy_unit.location.Y;
                    map.mem[row][col].unit_player_id = PLAYER_ID_UNDEF;
                    map.mem[row][col].unit_id = UNIT_ID_UNDEF;

                    DeleteUnit(enemy_unit.id);
                }

                active_unit.can_attack = false;
                active_unit.move_points = 0;
                UpdateUnit(active_unit);
                ResetMoveStack();
            }
            else {

                if (probability <= player_probability) {

                    if (enemy_unit.health <= enemy_unit.max_health / 4) {
                        printf("it's health is now %s%s%d/%d%s.\n", BOLD, RED, enemy_unit.health, enemy_unit.max_health, NORMAL);
                    } else {
                        printf("it's health is now %s%s%d/%d%s.\n", BOLD, GREEN, enemy_unit.health, enemy_unit.max_health, NORMAL);
                    }

                }
                UpdateUnit(enemy_unit);

                // Enemy nyerang balik
                probability = RandomNumber(0,100,3);
                if (probability <= enemy_probability) {
                    active_unit.health -= enemy_unit.attack;
                    printf("\nEnemy's %s%s%s retaliated. ", BOLD, enemy_type, NORMAL);
                    printf("Your %s%s%s is damaged by %s%d%s, ", BOLD, player_type, NORMAL, BOLD, enemy_unit.attack, NORMAL);
                }
                else {
                    printf("\nEnemy's attack missed.\n");
                }

                if (active_unit.health <= 0) {
                    printf("it's now %s%sDEAD%s :(.\n", BOLD, RED, NORMAL);

                    if (active_unit.type == KING) {
                        Player current_player = GetPlayer(enemy_unit.player_id);
                        current_player.alive = false;

                        int row = active_unit.location.X;
                        int col = active_unit.location.Y;
                        map.mem[row][col].unit_player_id = PLAYER_ID_UNDEF;
                        map.mem[row][col].unit_id = UNIT_ID_UNDEF;

                        UpdatePlayer(current_player);

                        // End game
                        end_game = true;

                    } else {
                        int row = active_unit.location.X;
                        int col = active_unit.location.Y;
                        map.mem[row][col].unit_player_id = PLAYER_ID_UNDEF;
                        map.mem[row][col].unit_id = UNIT_ID_UNDEF;

                        DeleteUnit(active_unit.id);
                    }

                    // Unitnya ketam, harus ganti
                    Player active_player = GetPlayer(active_player_id);
                    active_unit_id = active_player.king_id;
                    Unit next_active_unit = GetUnit(active_unit_id);

                    // Inform unit change
                    char new_flash_message[100];
                    sprintf(new_flash_message, "You are now selecting King (%d,%d).", next_active_unit.location.X, next_active_unit.location.Y);
                    flash(new_flash_message);

                }
                else {

                    if (probability <= enemy_probability) {
                        if (active_unit.health <= active_unit.max_health / 4) {
                            printf("it's health is now %s%s%d/%d%s.\n", BOLD, RED, active_unit.health, active_unit.max_health, NORMAL);
                        } else {
                            printf("it's health is now %s%s%d/%d%s.\n", BOLD, GREEN, active_unit.health, active_unit.max_health, NORMAL);
                        }
                    }

                    active_unit.can_attack = false;
                    active_unit.move_points = 0;
                    UpdateUnit(active_unit);
                    ResetMoveStack();
                }
            }

            wait_return();

            // Exit game
            if (end_game) {
                ExitGame();
            }

        }
    }
}

void Recruit() {

    Player current_player = GetPlayer(active_player_id);
    Unit current_king = GetUnit(current_player.king_id);

    // Check if king is in tower
    if (current_player.id == 1) {
        if (!EQ(current_king.location, tower_p1_loc)) {
            flash("Your king must be in your tower to recruit new units.");
            return;
        }
    } else {
        if (!EQ(current_king.location, tower_p2_loc)) {
            flash("Your king must be in your tower to recruit new units.");
            return;
        }
    }

    // Select castle to spawn unit
    Point avail_castle_loc[4];
    int avail_castle_loc_num = 0;
    int x, y;
    for (int i = 0; i < 4; i ++) {
        if (current_player.id == 1) {
            x = row(castle_p1_loc[i]);
            y = col(castle_p1_loc[i]);
            if (IsGridAvailable(x, y)) {
                avail_castle_loc[avail_castle_loc_num] = castle_p1_loc[i];
                avail_castle_loc_num ++;
            }
        } else {
            x = row(castle_p2_loc[i]);
            y = col(castle_p2_loc[i]);
            if (IsGridAvailable(x, y)) {
                avail_castle_loc[avail_castle_loc_num] = castle_p2_loc[i];
                avail_castle_loc_num ++;
            }
        }
    }

    print_default();
    if (avail_castle_loc_num > 0) {
        print_title("Choose Empty Castle to Recruit Unit");
        for (int i = 0; i < avail_castle_loc_num; i ++) {
            printf("%d. %sCastle (%d,%d)%s\n", i + 1, BOLD, row(avail_castle_loc[i]), col(avail_castle_loc[i]), NORMAL);
        }
    } else {
        flash("No empty castle available to spawn unit.");
        return;
    }

    int input;
    ask_int_input(&input, 1, avail_castle_loc_num);
    Point new_unit_loc = avail_castle_loc[input - 1];

    // Select unit to recruit
    print_default();
    print_title("Choose Unit to Recruit");
	printf("1. Archer    | Health: 20 | ATK: 4 | HEAL: - | Price: 5G\n");
	printf("2. Swordsman | Health: 20 | ATK: 3 | HEAL: - | Price: 4G\n");
	printf("3. WhiteMage | Health: 20 | ATK: 3 | HEAL: 4 | Price: 5G\n");
	ask_int_input(&input, 1, 3);

    // Memilih archer
	if (input == ARCHER) {

        if (current_player.cash >= PRICE_ARCHER) {
			current_player.cash -= PRICE_ARCHER;
			Unit U;
			U.player_id			= active_player_id;
			U.id				= 0; //U.id akan otomatis terganti ketika masuk ke database
			U.attack_type 		= RANGED;
			U.type 				= ARCHER;
			U.max_health		= MAX_HEALTH_ARCHER;
			U.health 			= MAX_HEALTH_ARCHER;
			U.attack 			= ATTACK_ARCHER;
			U.max_move_points	= MAX_MOVE_PTS_ARCHER;
			U.move_points 		= 0;
			U.can_attack 		= 0;
			U.location			= new_unit_loc;
			U.price 			= PRICE_ARCHER;
			U.heal 				= 0;
			int unit_id = CreateUnit(U);
			AddUnitToPlayer(&current_player, unit_id);
			flash("You have recruited an Archer!");
		} else {
            flash("Sorry, your gold is insufficient to recruit an archer.");
        }

    // Memilih swordsman
    } else if (input == SWORDSMAN) {

		if (current_player.cash >= PRICE_SWORDSMAN) {
			current_player.cash -= PRICE_SWORDSMAN;
			Unit U;
			U.player_id			= active_player_id;
			U.id				= 0; //U.id akan otomatis terganti ketika masuk ke database
			U.attack_type 		= MELEE;
			U.type 				= SWORDSMAN;
			U.max_health		= MAX_HEALTH_SWORDSMAN;
			U.health 			= MAX_HEALTH_SWORDSMAN;
			U.attack 			= ATTACK_SWORDSMAN;
			U.max_move_points	= MAX_MOVE_PTS_SWORDSMAN;
			U.move_points 		= 0;
			U.can_attack 		= 0;
			U.location			= new_unit_loc;
			U.price 			= PRICE_SWORDSMAN;
			U.heal 				= 0;
			int unit_id = CreateUnit(U);
			AddUnitToPlayer(&current_player, unit_id);
			flash("You have recruited a Swordsman!");
		} else {
            flash("Sorry, your gold is insufficient to recruit a swordsman.");
        }

        // Memilih whitemage
    } else if (input == WHITE_MAGE) {

		if (current_player.cash >= PRICE_WHITE_MAGE) {
			current_player.cash -= PRICE_WHITE_MAGE;
			Unit U;
			U.player_id			= active_player_id;
			U.id				= 0; //U.id akan otomatis terganti ketika masuk ke database
			U.attack_type 		= RANGED;
			U.type 				= WHITE_MAGE;
			U.max_health		= MAX_HEALTH_WHITE_MAGE;
			U.health 			= MAX_HEALTH_WHITE_MAGE;
			U.attack 			= ATTACK_WHITE_MAGE;
			U.max_move_points	= MAX_MOVE_PTS_WHITE_MAGE;
			U.move_points 		= 0;
			U.can_attack 		= 0;
			U.location			= new_unit_loc;
			U.price 			= PRICE_WHITE_MAGE;
			U.heal 				= HEAL_WHITE_MAGE;
			int unit_id = CreateUnit(U);
			AddUnitToPlayer(&current_player, unit_id);
			flash("You have recruited a White Mage!");
		} else {
            flash("Sorry, your gold is insufficient to recruit a White Mage.");
        }
	}

    UpdatePlayer(current_player);
    UpdateMap();

}

void ChangeActiveUnit() {

    // Initialization
    Player current_player = GetPlayer(active_player_id);
    Unit current_unit;
    int idxunit[350];
    char name[30];
    int input;
    int traverse=0;
    boolean empty = true;

    //Check empty and insert data
    if(current_player.king_id != active_unit_id) {
        idxunit[traverse] = -1;
        traverse++;
        empty = false;
    }

    for (int i = 0; i < current_player.unit_count; i++) {

        Unit current_unit = GetUnit(current_player.units[i]);

        if((current_unit.id != active_unit_id) && (current_unit.move_points != 0)) {
            empty = false;
            idxunit[traverse] = i;
            traverse++;
        }
    }
    if(empty) {
        flash("There are no available units.");
    }
    else {

        // Show the interface
        print_default();
        print_title("Select Unit");

        // Print all the Units
        for(int i=0; i< traverse; i++) {
            if(idxunit[i] == -1) {
                Unit current_unit = GetUnit(current_player.king_id);
                if (current_unit.health <= current_unit.max_health / 4) {
                    printf("%d. %s%s (%d,%d)%s | Health: %s%s%d/%d%s\n", (i + 1), BOLD, "King", current_unit.location.X, current_unit.location.Y, NORMAL, BOLD, RED, current_unit.health, current_unit.max_health, NORMAL);
                } else {
                    printf("%d. %s%s (%d,%d)%s | Health: %s%s%d/%d%s\n", (i + 1), BOLD, "King", current_unit.location.X, current_unit.location.Y, NORMAL, BOLD, GREEN, current_unit.health, current_unit.max_health, NORMAL);
                }
            }
            else {
                Unit current_unit = GetUnit(current_player.units[idxunit[i]]);
                switch(current_unit.type) {
                    case KING : strcpy(name, "King");
                        break;
                    case ARCHER : strcpy(name, "Archer");
                        break;
                    case SWORDSMAN : strcpy(name, "Swordsman");
                        break;
                    case WHITE_MAGE : strcpy(name, "White Mage");
                        break;
                }
                if (current_unit.health <= current_unit.max_health / 4) {
                    printf("%d. %s%s (%d,%d)%s | Health: %s%s%d/%d%s\n", (i + 1), BOLD, name, current_unit.location.X, current_unit.location.Y, NORMAL, BOLD, RED, current_unit.health, current_unit.max_health, NORMAL);
                } else {
                    printf("%d. %s%s (%d,%d)%s | Health: %s%s%d/%d%s\n", (i + 1), BOLD, name, current_unit.location.X, current_unit.location.Y, NORMAL, BOLD, GREEN, current_unit.health, current_unit.max_health, NORMAL);
                }
            }
        }

        ask_int_input(&input, 1, traverse);

        ResetMoveStack();

        if (idxunit[(input-1)] == -1) {
            active_unit_id = current_player.king_id;
            current_unit = GetUnit(current_player.king_id);
            strcpy(name, "King");
        }
        else {
            active_unit_id = current_player.units[idxunit[input-1]];
            current_unit = GetUnit(current_player.units[idxunit[input-1]]);

            switch(current_unit.type) {
                case KING : strcpy(name, "King");
                    break;
                case ARCHER : strcpy(name, "Archer");
                    break;
                case SWORDSMAN : strcpy(name, "Swordsman");
                    break;
                case WHITE_MAGE : strcpy(name, "White Mage");
                    break;
            }
        }
        char new_flash_message[100];
        sprintf(new_flash_message, "You are now selecting %s (%d,%d).", name, current_unit.location.X, current_unit.location.Y);
        flash(new_flash_message);
    }

}

void NextActiveUnit() {

    // Initialization
    Player current_player = GetPlayer(active_player_id);
    Unit current_unit;
    boolean found = false;
    char name[30];

    for(int i = 0; i < current_player.unit_count; i++) {
        current_unit = GetUnit(current_player.units[i]);
        if (active_unit_id == current_unit.id) {
            continue;
        } else if (current_unit.can_attack || (current_unit.move_points != 0)) {
            found = true;
            break;
        }
    }

    if (found) {
        active_unit_id = current_unit.id;

        switch(current_unit.type) {
            case KING : strcpy(name, "King");
                break;
            case ARCHER : strcpy(name, "Archer");
                break;
            case SWORDSMAN : strcpy(name, "Swordsman");
                break;
            case WHITE_MAGE : strcpy(name, "White Mage");
                break;
        }        
        char new_flash_message[100];
        sprintf(new_flash_message, "You are now selecting %s (%d,%d).", name, current_unit.location.X, current_unit.location.Y);
        flash(new_flash_message);
    }
    else {
        flash("There are no available units.");
    }

    // TODO: automatically change active unit to other unit which still has movement points or still able to attack (belom dites)

}

void WhiteMageEffect() {
    UnitListElmtAddress addressElmt = unit_list.first;
    while (addressElmt != NULL) {
        Unit cur = addressElmt->unit;
        Point cur_location = cur.location;
        if (cur.type == WHITE_MAGE) {
            const int x_dir[] = { 0, 0, 1, -1 };
            const int y_dir[] = { 1, -1, 0, 0 };
            const int dir_len = 4;

            for (int i = 0; i < dir_len; i++) {
                int row_now = cur_location.X + x_dir[i];
                int col_now = cur_location.Y + y_dir[i];
                boolean is_point_valid = (row_now >= 0 && row_now < map.n_brs_eff && col_now >= 0 && col_now < map.n_kol_eff);
                boolean can_heal = is_point_valid && (map.mem[row_now][col_now].unit_player_id == cur.player_id);
                if (can_heal) {
                    Unit now_unit = GetUnit(map.mem[row_now][col_now].unit_id);
                    now_unit.health += HEAL_WHITE_MAGE;
                    if (now_unit.health > now_unit.max_health) {
                        now_unit.health = now_unit.max_health;
                    }
                    UpdateUnit(now_unit);
                }
            }
        }
        addressElmt = addressElmt->next;
    }
}

void UpdateUpkeep() {
    Player cur_player = GetPlayer(active_player_id);
    cur_player.upkeep = cur_player.unit_count * C_UPKEEP_CONSTANT;
    UpdatePlayer(cur_player);
}

void UpdateIncome() {
    int income = 0;

    for (int i = 0; i < map.n_brs_eff; i++) {
        for (int j = 0; j < map.n_kol_eff; j++) {
            if (map.mem[i][j].player_id == active_player_id && map.mem[i][j].grid_type == C_VILLAGE_TYPE) {
                income++;
            }
        }
    }

    Player cur_player = GetPlayer(active_player_id);
    cur_player.income = income * C_INCOME_CONSTANT;
    UpdatePlayer(cur_player);
}

/* Game interface */
void InfoMap() {

    int i, j;

    print_default();
    print_title("Cell Info");
    printf("Enter the cell's row:\n");
    ask_int_input(&i, 0, map.n_brs_eff - 1);

    print_default();
    print_title("Cell Info");
    printf("Enter the cell's column:\n");
    ask_int_input(&j, 0, map.n_kol_eff - 1);

    char grid_type[15];
    switch(map.mem[i][j].grid_type) {
        case 'T' : strcpy(grid_type,"Tower");
                    break;
        case 'C' : strcpy(grid_type,"Castle");
                    break;
        case 'V' : strcpy(grid_type,"Village");
                    break;
    }

    print_default();
    char title[20];
    sprintf(title, "Cell Info (%d,%d)", i, j);
    print_title(title);

    char player_color[10];
    if (map.mem[i][j].player_id == 1) {
        strcpy(player_color, BLUE);
    } else {
        strcpy(player_color, RED);
    }

    if (map.mem[i][j].grid_type != C_NORMAL_TYPE) {
        printf("Building Info:\n");
        printf("%s%s%s owned by %s%sPlayer %d%s\n", BOLD, grid_type, NORMAL,  BOLD, player_color, map.mem[i][j].player_id, NORMAL);
    } else {
        printf("There is no buiding owned by any player here.\n");
    }

    printf("\n");

    if (map.mem[i][j].unit_id != UNIT_ID_UNDEF) {
        printf("Unit Info:\n");

        Unit unit_info = GetUnit(map.mem[i][j].unit_id);

        char unit_type[15];
        switch(unit_info.type) {
        case    0 : strcpy(unit_type,"King");
                    break;
        case    1 : strcpy(unit_type,"Archer");
                    break;
        case    2 : strcpy(unit_type,"Swordsman");
                    break;
        case    3 : strcpy(unit_type,"White Mage");
                    break;
        };

        char player_color[10];
        if (map.mem[i][j].player_id == 1) {
            strcpy(player_color, BLUE);
        } else {
            strcpy(player_color, RED);
        }

        printf("%s%s%s ", BOLD, unit_type, NORMAL);
        printf("owned by %s%sPlayer %d%s ", BOLD, player_color, unit_info.player_id, NORMAL);
        if (unit_info.health <= unit_info.max_health / 4) {
            printf("| Health: %s%s%d/%d%s | ATK: %s%d%s\n", BOLD, RED, unit_info.health, unit_info.max_health, NORMAL, BOLD, unit_info.attack, NORMAL);
        } else {
            printf("| Health: %s%s%d/%d%s | ATK: %s%d%s\n", BOLD, GREEN, unit_info.health, unit_info.max_health, NORMAL, BOLD, unit_info.attack, NORMAL);
        }
    }
    else {
        printf("There is no unit on this cell.\n");
    }

    wait_return();
}

void HealByVillage() {
    for (int i = 0; i < map.n_brs_eff; i++) {
        for (int j = 0; j < map.n_kol_eff; j++) {
            if (map.mem[i][j].grid_type == C_VILLAGE_TYPE && map.mem[i][j].unit_id != UNIT_ID_UNDEF) {
                Unit cur = GetUnit(map.mem[i][j].unit_id);
                cur.health += HEAL_VILLAGE;
                if (cur.health > cur.max_health) {
                    cur.health = cur.max_health;
                }
                UpdateUnit(cur);
            }
        }
    }
}
