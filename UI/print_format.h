#ifndef PRINT_FORMAT_H_
#define PRINT_FORMAT_H_

#include "../Main/common_types.h"
#include "pcolor.h"

typedef char* string;

extern char flash_message[100];

void clearscr();

void print_intro();
void print_logo();
void print_default();

void print_centered(string str);
void print_heading(char *heading);
void print_heading_vcentered(char* heading);
void print_title(char *title);
void print_title_plain(char *title);

void print_title_battle(string str);
void print_title_for(string str);
void print_title_olympia(string str);

void print_turn();
void print_home();
void print_exit_game();
void print_end_game(int winner_id);

void flash(char* message);

void wait_return();
void ask_input(char *input);
void ask_int_input(int *input, int min, int max);

#endif
