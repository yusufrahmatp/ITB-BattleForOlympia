#include <stdio.h>
#include <stdlib.h>
#include "common_types.h"

int main() {

    int players[100];
    int player_count = 0;

    EmptyPlayerList();

    Player p1;
    p1.cash = 1000;
    players[player_count] = CreatePlayer(p1);
    player_count ++;

    Player p2;
    p2.cash = 2000;
    players[player_count] = CreatePlayer(p2);
    player_count ++;

    for (int i = 0; i < player_count; i ++) {
        Player p = GetPlayer(players[i]);
        printf("%d\n", p.cash);
    }

    return 0;
}
