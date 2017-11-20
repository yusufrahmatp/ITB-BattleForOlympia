
#include <stdio.h>
#include <string.h>
#include "common_types.h"
#include "mechanics.h"

void LoadGame() {
    char file_name[10000];
    printf("Enter load file name: ");
    scanf("%s", file_name);

    

    // #ACTIVE_PLAYER_ID
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    active_player_id = CInt;
    printf("%d\n", active_player_id);

    // #ACTIVE_UNIT_ID
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    active_unit_id = CInt;
    printf("%d\n", active_unit_id);

    // #MAP
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    map.n_brs_eff = CInt;
    map_height = map.n_brs_eff;
    printf("%d\n", map.n_brs_eff);
    AdvanceInt();
    map.n_kol_eff = CInt;
    map_width = map.n_kol_eff;
    printf("%d\n", map.n_kol_eff);

    for (int i = 0; i < map.n_brs_eff; i++) {
        for (int j = 0; j < map.n_kol_eff; j++) {
            AdvanceString();
            map.mem[i][j].grid_type = CString[0];

            AdvanceInt();
            map.mem[i][j].unit_type = CInt;

            AdvanceInt();
            map.mem[i][j].player_id = CInt;

            AdvanceInt();
            map.mem[i][j].unit_id = CInt;

            AdvanceInt();
            map.mem[i][j].unit_player_id = CInt;

            AdvanceInt();
            map.mem[i][j].visitable = CInt;
        }
    }

    // #MOVE_STACK
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    move_stack.top = CInt - 1;
    for (int i = 0; i <= move_stack.top; i++) {
        AdvanceInt();
        move_stack.T[i].unit_id = CInt;

        AdvanceInt();
        move_stack.T[i].move_point = CInt;

        AdvanceInt();
        move_stack.T[i].location.X = CInt;

        AdvanceInt();
        move_stack.T[i].location.Y = CInt;

        AdvanceInt();
        move_stack.T[i].map_player_id = CInt;
    }

    // #PLAYER
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    int player_count = CInt;
    for (int i = 0; i < player_count; i++) {
        Player cur_player;

        AdvanceInt();
        cur_player.id = CInt;

        AdvanceInt();
        cur_player.alive = CInt;

        AdvanceInt();
        cur_player.cash = CInt;

        AdvanceInt();
        cur_player.income = CInt;

        AdvanceInt();
        cur_player.upkeep = CInt;

        AdvanceInt();
        cur_player.king_id = CInt;

        AdvanceInt();
        cur_player.unit_count = CInt;

        for (int j = 0; j < cur_player.unit_count; j++) {
            AdvanceInt();
            cur_player.units[j] = CInt;
        }

        AddPlayerWithId(cur_player);

    }

    // #UNIT
    AdvanceString();
    printf("%s\n", CString);
    AdvanceInt();
    int unit_count = CInt;
    for (int i = 0; i < unit_count; i++) {
        Unit unit;

        AdvanceInt();
        unit.id = CInt;

        AdvanceInt();
        unit.player_id = CInt;

        AdvanceInt();
        unit.attack_type = CInt;

        AdvanceInt();
        unit.type = CInt;

        AdvanceInt();
        unit.max_health = CInt;

        AdvanceInt();
        unit.health = CInt;

        AdvanceInt();
        unit.attack = CInt;

        AdvanceInt();
        unit.max_move_points = CInt;

        AdvanceInt();
        unit.move_points = CInt;

        AdvanceInt();
        unit.can_attack = CInt;

        AdvanceInt();
        unit.location.X = CInt;

        AdvanceInt();
        unit.location.Y = CInt;

        AdvanceInt();
        unit.price = CInt;

        AdvanceInt();
        unit.heal = CInt;

        AddUnitWithId(unit);

    }

    // #TURN_QUEUE
    AdvanceString();
    printf("%s\n", CString);

    AdvanceInt();
    turn_queue.T[0] = CInt;

    AdvanceInt();
    turn_queue.T[1] = CInt;

    AdvanceInt();
    turn_queue.head = CInt;

    AdvanceInt();
    turn_queue.tail = CInt;

    ADV();


    // // INIT
    // FILE *f = fopen(file_name, "r");
    //
    // // Read active player id
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &active_player_id);
    // printf("%d\n", active_player_id);
    //
    // // Read active unit id
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &active_unit_id);
    // printf("%d\n", active_unit_id);
    //
    // // // Read active unit id
    // // AdvanceString(f); printf("%s", CString);
    // // AdvanceInt(f); printf("%d", CInt);
    // // active_unit_id = CInt;
    //
    // // Read map
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &map.n_brs_eff);
    // printf("%d\n", map.n_brs_eff);
    //
    // fscanf(f, " %d", &map.n_kol_eff);
    // printf("%d\n", map.n_kol_eff);
    //
    //
    // for (int i = 0; i < map.n_brs_eff; i++) {
    //     for (int j = 0; j < map.n_kol_eff; j++) {
    //         fscanf(f, " %c %d %d %d %d %c", &(map.mem[i][j].grid_type), &(map.mem[i][j].unit_type), &(map.mem[i][j].player_id), &(map.mem[i][j].unit_id), &(map.mem[i][j].unit_player_id),
    //         &(map.mem[i][j].visitable));
    //         printf("%c %d %d %d %d %c\n", (map.mem[i][j].grid_type), (map.mem[i][j].unit_type), (map.mem[i][j].player_id), (map.mem[i][j].unit_id), (map.mem[i][j].unit_player_id),
    //         (map.mem[i][j].visitable));
    //     }
    // }
    //
    // // read move stack
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &(move_stack.top));
    // move_stack.top --;
    // printf("%d\n", move_stack.top);
    //
    // if(move_stack.top != -1) {
    //     for (int i = 0; i <= move_stack.top; i++) {
    //         fscanf(f, "%d %d %d %d %d", &(move_stack.T[i].unit_id), &(move_stack.T[i].move_point),
    //         &(move_stack.T[i].location.X), &(move_stack.T[i].location.Y), &(move_stack.T[i].map_player_id));
    //         printf("%d %d %d %d %d\n", (move_stack.T[i].unit_id), (move_stack.T[i].move_point),
    //         (move_stack.T[i].location.X), (move_stack.T[i].location.Y), (move_stack.T[i].map_player_id));
    //     }
    // }
    //
    // // read player
    // int player_count;
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &player_count);
    // printf("%d\n", player_count);
    //
    // for (int i = 0; i < player_count; i++) {
    //     Player player;
    //
    //     fscanf(f, "%d %c %d %d %d %d %d",
    //     &(player.id),
    //     &(player.alive),
    //     &(player.cash),
    //     &(player.income),
    //     &(player.upkeep),
    //     &(player.king_id),
    //     &(player.unit_count)
    //     );
    //
    //     printf("%d %c %d %d %d %d %d",
    //     (player.id),
    //     (player.alive),
    //     (player.cash),
    //     (player.income),
    //     (player.upkeep),
    //     (player.king_id),
    //     (player.unit_count));
    //
    //     for (int j = 0; j < player.unit_count; j++) {
    //         fscanf(f, "%d", &(player.units[j]));
    //         printf("%d", (player.units[j]));
    //     }
    //
    //     printf("\n");
    //
    //     AddPlayerWithId(player);
    // }
    //
    // // unit
    // int unit_count;
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d", &unit_count);
    // printf("%d\n", unit_count);
    //
    // for (int i = 0; i < unit_count; i++) {
    //     Unit unit;
    //
    //     fscanf(f, "%d %d %d %d %d %d %d %d %d %c %d %d %d %d",
    //     &(unit.id),
    //     &(unit.player_id),
    //     &(unit.attack_type),
    //     &(unit.type),
    //     &(unit.max_health),
    //     &(unit.health),
    //     &(unit.attack),
    //     &(unit.max_move_points),
    //     &(unit.move_points),
    //     &(unit.can_attack),
    //     &(unit.location.X),
    //     &(unit.location.Y),
    //     &(unit.price),
    //     &(unit.heal)
    //     );
    //
    //     printf("%d %d %d %d %d %d %d %d %d %c %d %d %d %d\n",
    //     (unit.id),
    //     (unit.player_id),
    //     (unit.attack_type),
    //     (unit.type),
    //     (unit.max_health),
    //     (unit.health),
    //     (unit.attack),
    //     (unit.max_move_points),
    //     (unit.move_points),
    //     (unit.can_attack),
    //     (unit.location.X),
    //     (unit.location.Y),
    //     (unit.price),
    //     (unit.heal)
    //     );
    //
    //     AddUnitWithId(unit);
    // }
    //
    // // Turn Queue
    // fscanf(f, "%s", CString);
    // printf("%s\n", CString);
    // fscanf(f, " %d %d %d %d",
    // &(turn_queue.T[0]),
    // &(turn_queue.T[1]),
    // &(turn_queue.head),
    // &(turn_queue.tail)
    // );
    //
    // printf("%d %d %d %d\n",
    // (turn_queue.T[0]),
    // (turn_queue.T[1]),
    // (turn_queue.head),
    // (turn_queue.tail)
    // );
    //
    // fclose(f);
}
