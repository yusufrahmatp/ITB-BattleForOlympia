#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "print_format.h"

char flash_message[100];

void clearscr() {

    #ifdef _WIN32
        system("cls");
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        system("clear");
    #else
        #error "OS not supported."
    #endif

}

void print_intro() {

    // Intro
    print_logo();
    print_centered("1. New Game             2. Load Game             3. Exit Game");

}

void print_logo() {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_height = w.ws_row;
    int intro_height = 29 + 5;
    int padding_top = (win_height - intro_height) / 2;

    // Clear screen
    clearscr();

    // Top padding
    for (int i = 0; i < padding_top; i ++) {
        printf("\n");
    }

    print_title_battle("▀█████████▄     ▄████████     ███         ███      ▄█          ▄████████");
    print_title_battle("  ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███         ███    ███");
    print_title_battle("  ███    ███   ███    ███    ▀███▀▀██    ▀███▀▀██ ███         ███    █▀ ");
    print_title_battle(" ▄███▄▄▄██▀    ███    ███     ███   ▀     ███   ▀ ███        ▄███▄▄▄    ");
    print_title_battle("▀▀███▀▀▀██▄  ▀███████████     ███         ███     ███       ▀▀███▀▀▀    ");
    print_title_battle("  ███    ██▄   ███    ███     ███         ███     ███         ███    █▄ ");
    print_title_battle("  ███    ███   ███    ███     ███         ███     ███▌    ▄   ███    ███");
    print_title_battle("▄█████████▀    ███    █▀     ▄████▀      ▄████▀   █████▄▄██   ██████████");
    print_title_battle("                                                  ▀                     ");
    printf("\n");
    print_title_for("   ▄████████  ▄██████▄     ▄████████");
    print_title_for("  ███    ███ ███    ███   ███    ███");
    print_title_for("  ███    █▀  ███    ███   ███    ███");
    print_title_for(" ▄███▄▄▄     ███    ███  ▄███▄▄▄▄██▀");
    print_title_for("▀▀███▀▀▀     ███    ███ ▀▀███▀▀▀▀▀  ");
    print_title_for("  ███        ███    ███ ▀███████████");
    print_title_for("  ███        ███    ███   ███    ███");
    print_title_for("  ███         ▀██████▀    ███    ███");
    print_title_for("                          ███    ███");
    printf("\n");
    print_title_olympia(" ▄██████▄   ▄█       ▄██   ▄     ▄▄▄▄███▄▄▄▄      ▄███████▄  ▄█     ▄████████");
    print_title_olympia("███    ███ ███       ███   ██▄ ▄██▀▀▀███▀▀▀██▄   ███    ███ ███    ███    ███");
    print_title_olympia("███    ███ ███       ███▄▄▄███ ███   ███   ███   ███    ███ ███▌   ███    ███");
    print_title_olympia("███    ███ ███       ▀▀▀▀▀▀███ ███   ███   ███   ███    ███ ███▌   ███    ███");
    print_title_olympia("███    ███ ███       ▄██   ███ ███   ███   ███ ▀█████████▀  ███▌ ▀███████████");
    print_title_olympia("███    ███ ███       ███   ███ ███   ███   ███   ███        ███    ███    ███");
    print_title_olympia("███    ███ ███▌    ▄ ███   ███ ███   ███   ███   ███        ███    ███    ███");
    print_title_olympia(" ▀██████▀  █████▄▄██  ▀█████▀   ▀█   ███   █▀   ▄████▀      █▀     ███    █▀ ");
    print_title_olympia("           ▀                                                                 ");

    printf("\n");
    printf("\n");

}

void print_default() {

    Player current_player = GetPlayer(active_player_id);

    // Clear screen
    clearscr();

    // Heading
    char heading[100];
    sprintf(heading, "Player %d's Turn", current_player.id);
    print_heading(heading);
    printf("\n");

    // Map
    PrintMap();

    // Status
    print_turn();

    // Flash message
    if (strlen(flash_message) > 0) {
        printf("\n%s====> %s%s\n", BOLD, flash_message, NORMAL);
        strcpy(flash_message, "");
    }

}

void print_centered(string str) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_width = w.ws_col;
    int str_len = strlen(str);
    int padding_left = (win_width - str_len) / 2;
    for (int i = 0; i < padding_left; i ++) {
        printf(" ");
    }
    printf("%s\n", str);

}

void print_heading(char *heading) {

    Player current_player = GetPlayer(active_player_id);

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int heading_len = strlen(heading);
    int win_width = w.ws_col;
    int padding_left = (win_width - heading_len - 2) / 2;
    int padding_right = padding_left + (win_width - heading_len - 2) % 2;

    // Start bacground and text color
    if (current_player.id == 1) {
        printf(B_GREY);
        printf(BOLD);
        printf(BLUE);
    } else {
        printf(B_GREY);
        printf(BOLD);
        printf(RED);
    }

    for (int i = 0; i < win_width; i ++) {
        printf("=");
    }
    printf("\n");

    for (int i = 0; i < padding_left; i ++) {
        printf("=");
    }

    printf(" %s ", heading);

    for (int i = 0; i < padding_right; i ++) {
        printf("=");
    }

    for (int i = 0; i < win_width; i ++) {
        printf("=");
    }

    // End bacground and text color
    if (current_player.id == 1) {
        printf(NORMAL);
    } else {
        printf(NORMAL);
    }

    printf("\n");

}

void print_heading_vcentered(char* heading) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_height = w.ws_row;
    int padding_top = (win_height - 6) / 2;

    // Clear screen
    clearscr();

    // Top padding
    for (int i = 0; i < padding_top; i ++) {
        printf("\n");
    }

    // Print heading
    print_heading(heading);

}

void print_title(char *title) {

    Player current_player = GetPlayer(active_player_id);

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int title_len = strlen(title);
    int win_width = w.ws_col;
    int padding_left = (win_width - title_len - 2) / 2;
    int padding_right = padding_left + (win_width - title_len - 2) % 2;

    printf("\n");

    // Start bacground and text color
    if (current_player.id == 1) {
        printf(B_GREY);
        printf(BOLD);
        printf(BLUE);
    } else {
        printf(B_GREY);
        printf(BOLD);
        printf(RED);
    }

    for (int i = 0; i < padding_left; i ++) {
        printf("=");
    }

    printf(" %s ", title);

    for (int i = 0; i < padding_right; i ++) {
        printf("=");
    }

    // End bacground and text color
    printf(NORMAL);

    printf("\n");
    printf("\n");

}

void print_title_plain(char *title) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int title_len = strlen(title);
    int win_width = w.ws_col;
    int padding_left = (win_width - title_len - 2) / 2;
    int padding_right = padding_left + (win_width - title_len - 2) % 2;

    printf("\n");

    // Start bacground and text color
    printf(B_GREY);
    printf(BOLD);
    printf(BLACK);

    for (int i = 0; i < padding_left; i ++) {
        printf("=");
    }

    printf(" %s ", title);

    for (int i = 0; i < padding_right; i ++) {
        printf("=");
    }

    // End bacground and text color
    printf(NORMAL);

    printf("\n");
    printf("\n");

}

void print_title_battle(string str) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_width = w.ws_col;
    int str_len = 72;
    int padding_left = (win_width - str_len) / 2;
    for (int i = 0; i < padding_left; i ++) {
        printf(" ");
    }
    printf("%s\n", str);

}

void print_title_for(string str) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_width = w.ws_col;
    int str_len = 36;
    int padding_left = (win_width - str_len) / 2;
    for (int i = 0; i < padding_left; i ++) {
        printf(" ");
    }
    printf("%s\n", str);

}

void print_title_olympia(string str) {

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int win_width = w.ws_col;
    int str_len = 77;
    int padding_left = (win_width - str_len) / 2;
    for (int i = 0; i < padding_left; i ++) {
        printf(" ");
    }
    printf("%s\n", str);

}

void print_turn() {

    Player current_player = GetPlayer(active_player_id);
    Unit current_unit = GetUnit(active_unit_id);

    printf("\n");

    // Body
    char unit_name[100];
    switch(current_unit.type) {
        case KING : strcpy(unit_name, "King");
            break;
        case ARCHER : strcpy(unit_name, "Archer");
            break;
        case SWORDSMAN : strcpy(unit_name, "Swordsman");
            break;
        case WHITE_MAGE : strcpy(unit_name, "White Mage");
            break;
    }

    char health_color[10];
    if (current_unit.health <= current_unit.max_health / 4) {
        strcpy(health_color, RED);
    } else {
        strcpy(health_color, GREEN);
    }

    char move_color[10];
    if (current_unit.move_points == 0) {
        strcpy(move_color, RED);
    } else {
        strcpy(move_color, GREEN);
    }

    char attack_state[30];
    if (current_unit.can_attack) {
        sprintf(attack_state, "%s%sYES%s", BOLD, GREEN, NORMAL);
    } else {
        sprintf(attack_state, "%s%sNO%s", BOLD, RED, NORMAL);
    }

    printf("Cash: %s%s%dG%s | Income: %s%s%dG%s | Upkeep: %s%s%dG%s\n", BOLD, YELLOW, current_player.cash, NORMAL, BOLD, YELLOW, current_player.income, NORMAL, BOLD, YELLOW, current_player.upkeep, NORMAL);

    printf("Unit: %s%s ", BOLD, unit_name); TulisPoint(current_unit.location); printf("%s | Health: %s%s%d/%d%s | Movement point: %s%s%d%s | Can attack: %s\n", NORMAL, BOLD, health_color, current_unit.health, current_unit.max_health, NORMAL, BOLD, move_color, current_unit.move_points, NORMAL, attack_state);

}

void print_home() {

    print_title("Enter Your Command");
    printf("Available commands:\n\n");
    printf(" MOVE (m)   RECRUIT (r)   NEXT_UNIT (nu)     INFO (i)        SAVE (s)\n");
    printf(" UNDO (u)   ATTACK (a)    CHANGE_UNIT (cu)   END_TURN (et)   EXIT (e)\n");

}

void print_exit_game() {

    // Heading
    print_heading_vcentered("Exit Game");
    printf("\n");
    print_title("Do you want to save your game?");

    // Title
    print_centered("1. Save Game            2. Exit Game            3. Back");

}

void print_end_game(int winner_id) {

    // Heading
    if (winner_id == 1) {
        print_heading_vcentered("Player 1 Wins!");
    } else if (winner_id == 2) {
        print_heading_vcentered("Player 2 Wins!");
    } else {
        print_heading_vcentered("It's a tie!");
    }
    printf("\n");
    print_title("Do you want to play again?");

    // Title
    print_centered("1. New Game             2. Exit Game");

}

void flash(char* message) {

    strcpy(flash_message, message);

}

void wait_return() {
    printf("\n%s%s%sPress ENTER to continue... %s", BLINK, ITALIC, BOLD, NORMAL);
    getchar();
    getchar();
}

void ask_input(char *input) {

    printf("\n%s%s>>> %s%s", BLINK, BOLD, NORMAL, BOLD);
    scanf("%s", input);
    printf("%s\n", NORMAL);

}

void ask_int_input(int *input, int min, int max) {

    char str_input[100];
    do {
        printf("\n%s%s>>> %s%s", BLINK, BOLD, NORMAL, BOLD);
        scanf("%s", str_input);
        printf("%s\n", NORMAL);
        *input = atoi(str_input);
        if (*input == 0) {
            if (str_input[0] != '0') {
                *input = max + 1;
            }
        }
        if (*input < min || *input > max) {
            printf("%sInvalid input, retry!%s", BOLD, NORMAL);
        }
    } while (*input < min || *input > max);

}
