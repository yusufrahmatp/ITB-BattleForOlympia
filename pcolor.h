/**
Filename: pcolor.h
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 30/10/2017
**/

/**
Details

print_xxx(c) will print c with xxx color. Import this header to use the declared functions.
We only provide 8 colors. Feel free to modify/add colors if you want to.
**/

#ifndef PCOLOR_H_
#define PCOLOR_H_

#define NORMAL      "\x1B[0m"
#define BOLD        "\x1B[1m"
#define THIN        "\x1B[2m"
#define ITALIC      "\x1B[3m"
#define UNDERLINE   "\x1B[4m"
#define BLINK       "\x1B[5m"
#define underGROUND "\x1B[7m"
#define BLACK       "\x1B[30m"
#define RED         "\x1B[31m"
#define GREEN       "\x1B[32m"
#define YELLOW      "\x1B[33m"
#define BLUE        "\x1B[34m"
#define MAGENTA     "\x1B[35m"
#define CYAN        "\x1B[36m"
#define WHITE       "\x1B[37m"
#define B_BLACK     "\x1B[40m"
#define B_RED       "\x1B[41m"
#define B_GREEN     "\x1B[42m"
#define B_YELLOW    "\x1B[43m"
#define B_BLUE      "\x1B[44m"
#define B_MAGENTA   "\x1B[45m"
#define B_CYAN      "\x1B[46m"
#define B_GREY      "\x1B[47m"

void print_char_red(char c);
void print_char_green(char c);
void print_char_yellow(char c);
void print_char_blue(char c);
void print_char_magenta(char c);
void print_char_cyan(char c);

void print_red(char * s);
void print_green(char * s);
void print_yellow(char * s);
void print_blue(char * s);
void print_magenta(char * s);
void print_cyan(char * s);

void print_const_under(const char c[5]);
void print_const_under_red(const char c[5]);
void print_const_under_green(const char c[5]);
void print_const_under_yellow(const char c[5]);
void print_const_under_blue(const char c[5]);
void print_const_under_magenta(const char c[5]);
void print_const_under_cyan(const char c[5]);

#endif
